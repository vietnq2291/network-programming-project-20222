#include <iostream>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/select.h>

#include "../include/Client.h"
#include "../include/Message.h"
#include "../include/Utils.h"
#include "../../shared/common.h"

Client::Client(int port, std::string ip) {
    _server_port = port;
    _server_ip = ip;
    _user_id = -1;
    _display_name = "";

    /* ----- setup client socket ----- */
    // create socket
    if ((_conn_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        std::cerr << "Can not create socket" << std::endl;
        exit(1);
    }

    // set server address
    bzero((char *)&_server_addr, sizeof(_server_addr));
    _server_addr.sin_family = AF_INET;
    _server_addr.sin_port = htons(_server_port);
    _server_addr.sin_addr.s_addr = inet_addr(_server_ip.c_str());

    std::cout << "Client started" << std::endl;
}

void Client::connect() {

    if (::connect(_conn_fd, (struct sockaddr *)&_server_addr, sizeof(struct sockaddr)) < 0) {
        std::cerr << "Can not connect to server at " << _server_ip << ":" << _server_port << std::endl;
        exit(1);
    }

    std::cout << "Connected to server at " << _server_ip << ":" << _server_port << std::endl;
}

void Client::start() {
    std::string buff;
    
    while (true) {
        // clear the set ahead of time
        FD_ZERO(&_read_fds);

        // add our descriptors to the set
        FD_SET(_conn_fd, &_read_fds);
        FD_SET(STDIN_FILENO, &_read_fds);

        // find the largest descriptor
        int maxfd = std::max(_conn_fd, STDIN_FILENO);

        // wait until either socket has data ready to be recv()
        int rv = select(maxfd + 1, &_read_fds, NULL, NULL, NULL);

        if (rv == -1) {
            std::cerr << "Error: select()" << std::endl; 
        } else {
            // one or both of the descriptors have data
            if (FD_ISSET(STDIN_FILENO, &_read_fds))
            {
                std::getline(std::cin, buff);
                // buff is like <type> <data>
                // if type = R, then call send_request_message()
                // if type = C, then call send_chat_message()

                // check first character of buff to determine message type
                if (buff[0] == 'R') {
                    send_request_message(buff);
                } else if (buff[0] == 'C') {
                    // buff = C <chat_type> <chat_id> <message>
                    // where <chat_type> = G (group chat) or P (private chat)
                    
                    ChatType chat_type;
                    if (buff[2] == 'G') {
                        chat_type = ChatType::GROUP_CHAT;
                    } else if (buff[2] == 'P') {
                        chat_type = ChatType::PRIVATE_CHAT;
                    } else {
                        std::cout << "Invalid chat type" << std::endl;
                    }
                    int chat_id = std::stoi(buff.substr(4, buff.find(' ', 4) - 4));
                    buff = buff.substr(buff.find(' ', 4) + 1);
                    send_chat_message(buff, chat_id, chat_type, DataType::TEXT);
                } else {
                    std::cout << "Invalid message type" << std::endl;
                }
            }

            if (FD_ISSET(_conn_fd, &_read_fds))
            {
                receive_message();
            }
        }
    }
}

void Client::stop() {
    std::cout << "Client stopped" << std::endl;
    close(_conn_fd);
    exit(0);
}

void Client::send_chat_message(std::string buff, int chat_id, ChatType chat_type, DataType data_type) {
    Message message(MessageType::CHAT, chat_type, data_type, _user_id, chat_id, time(NULL), buff);
    MessagePacket packet;

    while (message.get_next_packet(packet)) {
        if (send(_conn_fd, &packet, sizeof(packet), 0) < 0) {
            std::cerr << "Error: Can not send message" << std::endl;
            break;
        }

        // //print all data of packet
        // std::string type, chat_type, data_type;
        // if (packet.type == MessageType::REQUEST) {
        //     type = "REQUEST";
        // } else if (packet.type == MessageType::RESPONSE) {
        //     type = "RESPONSE";
        // } else if (packet.type == MessageType::CHAT) {
        //     type = "CHAT";
        // } else {
        //     type = "UNKNOWN";
        // }
        // if (packet.chat_header.chat_type == ChatType::GROUP_CHAT) {
        //     chat_type = "GROUP_CHAT";
        // } else if (packet.chat_header.chat_type == ChatType::PRIVATE_CHAT) {
        //     chat_type = "PRIVATE_CHAT";
        // } else {
        //     chat_type = "UNKNOWN";
        // }
        // if (packet.chat_header.data_type == DataType::TEXT) {
        //     data_type = "TEXT";
        // } else if (packet.chat_header.data_type == DataType::FILE) {
        //     data_type = "FILE";
        // } else {
        //     data_type = "UNKNOWN";
        // }
        // std::cout << "Sent message: (type, chat_type, data_type, sender, chat_id, timestamp, data) = " << "(" << type <<
        //                                                                                                 ", " << chat_type << 
        //                                                                                                 ", " << data_type << 
        //                                                                                                 ", " << packet.chat_header.sender << 
        //                                                                                                 ", " << packet.chat_header.chat_id << 
        //                                                                                                 ", " << packet.chat_header.timestamp << 
        //                                                                                                 ", " << packet.data << ")" <<
        //                                                                                                 " - " << packet.data_length <<
        //                                                                                                 " - " << packet.fin <<
        //                                                                                                 " - " << packet.seq << std::endl;
    }
}

void Client::receive_message() {
    MessagePacket packet;
    int bytes_received = recv(_conn_fd, &packet, sizeof(packet), 0);
    
    if (bytes_received < 0) {
        std::cerr << "Error: receive failed!" << std::endl;
    } else if (bytes_received == 0) {
        std::cerr << "Error: server closed connection!" << std::endl;
        stop();
    } else {        
        if (packet.type == MessageType::RESPONSE) {
            //print all data of packet for debug
            std::string response_type;
            if (packet.response_header.response_type == ResponseType::SUCCESS) {
                response_type = "SUCCESS";
            } else if (packet.response_header.response_type == ResponseType::FAILURE) {
                response_type = "FAILURE";
            } else if (packet.response_header.response_type == ResponseType::LOGIN_SUCCESS) {
                response_type = "LOGIN_SUCCESS";
            } else if (packet.response_header.response_type == ResponseType::ERROR) {
                response_type = "ERROR";
            } else {
                response_type = "UNKNOWN";
            }
            std::cout << "Received message: (type, respose_type, fin, seq, data_len, data) = " << "(" << "RESPONSE" <<
                                                                                                    ", " << response_type << 
                                                                                                    ", " << packet.fin << 
                                                                                                    ", " << packet.seq << 
                                                                                                    ", " << packet.data_length << 
                                                                                                    ", " << packet.data << ")" << std::endl;

            if (packet.response_header.response_type == ResponseType::LOGIN_SUCCESS) {
                std::tie(_user_id, _display_name) = parse_user_info_data(packet.data);
            }
        } else if (packet.type == MessageType::CHAT) {
            //print all data of packet for debug
            std::string chat_type, data_type;
            if (packet.chat_header.chat_type == ChatType::GROUP_CHAT) {
                chat_type = "GROUP_CHAT";
            } else if (packet.chat_header.chat_type == ChatType::PRIVATE_CHAT) {
                chat_type = "PRIVATE_CHAT";
            } else {
                chat_type = "UNKNOWN";
            }
            if (packet.chat_header.data_type == DataType::TEXT) {
                data_type = "TEXT";
            } else if (packet.chat_header.data_type == DataType::FILE) {
                data_type = "FILE";
            } else {
                data_type = "UNKNOWN";
            }
            std::cout << "Received message: (type, chat_type, data_type, sender, chat_id, timestamp, data) = " << "(" << "CHAT" <<
                                                                                                    ", " << chat_type << 
                                                                                                    ", " << data_type << 
                                                                                                    ", " << packet.chat_header.sender << 
                                                                                                    ", " << packet.chat_header.chat_id << 
                                                                                                    ", " << packet.chat_header.timestamp << 
                                                                                                    ", " << packet.fin <<
                                                                                                    ", " << packet.seq <<
                                                                                                    ", " << packet.data_length <<
                                                                                                    ", " << packet.data << ")" << std::endl;
        } else {
            std::cout << "Invalid message type" << std::endl;
        }
    }
}

void Client::send_request_message(std::string buff) {
    Message *message_ptr;
    MessagePacket packet;

    if (buff[2] == 'L') {
        // buff = R L <username> <password>
        std::string data = buff.substr(4);
        std::string username = data.substr(0, data.find(' '));
        std::string password = data.substr(data.find(' ') + 1);
        std::string auth_data = encode_auth_data(username, password);
        message_ptr = new Message(MessageType::REQUEST, RequestType::LOGIN, _user_id, auth_data);
    } else if (buff[2] == 'R') {
        // buff = R R <username> <password> <display_name>
        std::string data = buff.substr(4, buff.length() - 4);
        std::string username = data.substr(0, data.find(' '));
        std::string password = data.substr(data.find(' ') + 1, data.length() - data.find(' ') - 1);
        std::string display_name = password.substr(password.find(' ') + 1, password.length() - password.find(' ') - 1);
        password = password.substr(0, password.find(' '));
        std::string signup_data = encode_signup_data(username, password, display_name);
        message_ptr = new Message(MessageType::REQUEST, RequestType::SIGNUP, _user_id, signup_data);
    } else if (buff[2] == 'X') {
        message_ptr = new Message(MessageType::REQUEST, RequestType::LOGOUT, _user_id);    
    } else if (buff[2] == 'U') {
        std::string data = buff.substr(4, buff.length() - 4);
        std::string update_data = encode_update_account_data(data);
        message_ptr = new Message(MessageType::REQUEST, RequestType::UPDATE_ACCOUNT, _user_id, update_data);
    } else if (buff[2] == 'C') {
        // create new chat:
        // + Private chat: R C P <other_user_id>
        // + Group chat:   R C G <group_name> <number of other users> <user_id_1> <user_id_2> ... <user_id_n>
        std::string data = buff.substr(4, buff.length() - 4);
        std::string chat_type = data.substr(0, data.find(' '));
        if (chat_type == "P") {
            std::string other_user_id = data.substr(data.find(' ') + 1);
            message_ptr = new Message(MessageType::REQUEST, RequestType::CREATE_PRIVATE_CHAT, _user_id, other_user_id);
        } else if (chat_type == "G") {
            int sep_idx = data.find(' ');
            std::string group_name = data.substr(sep_idx + 1, data.find(' ', sep_idx + 1) - sep_idx - 1);
            sep_idx = data.find(' ', sep_idx + 1);
            int no_members = std::stoi(data.substr(sep_idx + 1, data.find(' ', sep_idx + 1) - sep_idx - 1));
            std::vector<std::string> members;
            for (int i = 0; i < no_members; ++i) {
                sep_idx = data.find(' ', sep_idx + 1);
                members.push_back(data.substr(sep_idx + 1, data.find(' ', sep_idx + 1) - sep_idx - 1));
            }
            
            std::string create_group_chat_data = encode_create_group_chat(group_name, members);
            message_ptr = new Message(MessageType::REQUEST, RequestType::CREATE_GROUP_CHAT, _user_id, create_group_chat_data);
        } else {
            std::cerr << "Error: invalid chat type!" << std::endl;
            return;
        }
    }

    while ((*message_ptr).get_next_packet(packet)) {
        if (send(_conn_fd, &packet, sizeof(packet), 0) < 0) {
            std::cerr << "Can not send message" << std::endl;
            break;
        }

        // //print all data of packet
        // std::string type, request_type;
        // if (packet.type == MessageType::REQUEST) {
        //     type = "REQUEST";
        // } else if (packet.type == MessageType::RESPONSE) {
        //     type = "RESPONSE";
        // } else if (packet.type == MessageType::CHAT) {
        //     type = "CHAT";
        // } else {
        //     type = "UNKNOWN";
        // }
        // if (packet.request_header.request_type == RequestType::LOGIN) {
        //     request_type = "LOGIN";
        // } else if (packet.request_header.request_type == RequestType::SIGNUP) {
        //     request_type = "SIGNUP";
        // } else if (packet.request_header.request_type == RequestType::LOGOUT) {
        //     request_type = "LOGOUT";
        // } else if (packet.request_header.request_type == RequestType::UPDATE_ACCOUNT) {
        //     request_type = "UPDATE_ACCOUNT";
        // } else {
        //     request_type = "UNKNOWN";
        // }

        // std::cout << "Sent message: (type, request_type, sender, fin, seq, data_len, data) = " << "(" << type <<
        //                                                                                             ", " << request_type << 
        //                                                                                             ", " << packet.request_header.sender << 
        //                                                                                             ", " << packet.fin << 
        //                                                                                             ", " << packet.seq << 
        //                                                                                             ", " << packet.data_length << 
        //                                                                                             ", " << packet.data << ")" << std::endl;
    }
}
