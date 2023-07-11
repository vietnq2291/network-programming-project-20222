#include <iostream>
#include <cstring>
#include <string>
#include <sstream>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/select.h>

#include "../include/Client.h"
#include "../include/Message.h"
#include "../include/Utils.h"
#include "../../shared/common.h"

Client::Client(int port, std::string ip, std::string folder_path) {
    _server_port = port;
    _server_ip = ip;
    _folder_path = folder_path;
    _user_id = -1;
    _display_name = "";
    _friend_list = std::vector<Friend>();
    _buff = "";

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
                    // buff = C <chat_type> <data_type> <chat_id> <message>
                    // where <chat_type> = G (group chat) or P (private chat) or A (anonymous chat)
                    
                    ChatType chat_type;
                    DataType data_type;
                    if (buff[2] == 'G') {
                        chat_type = ChatType::GROUP_CHAT;
                    } else if (buff[2] == 'P') {
                        chat_type = ChatType::PRIVATE_CHAT;
                    } else if (buff[2] == 'A') {
                        chat_type = ChatType::ANONYMOUS_CHAT;
                    } else {
                        std::cout << "Invalid chat type" << std::endl;
                        continue;
                    }
                    if (buff[4] == 'F') {
                        data_type = DataType::FILE;
                    } else if (buff[4] == 'T') {
                        data_type = DataType::TEXT;
                    } else {
                        std::cout << "Invalid data type" << std::endl;
                        continue;
                    }
                    int chat_id = std::stoi(buff.substr(6, buff.find(' ', 6) - 6));
                    buff = buff.substr(buff.find(' ', 6) + 1);
                    send_chat_message(buff, chat_id, chat_type, data_type);
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
    std::string data;

    if (data_type == DataType::TEXT) {
        // data to send is buff
        data = buff;
    } else if (data_type == DataType::FILE) {
        // buff is file path, data to send is of the form <file_name_length>:<file_name><file_content_length>:<file_content>
        FILE *fptr;
        std::string filename;

        if ((fptr = fopen(buff.c_str(), "rb")) == NULL) {
            std::cerr << "Error: Can not open file" << std::endl;
            return;
        }

        // get file name
        int i = buff.length() - 1;
        while ((buff[i] != '/') &&  (i >= 0)) {
            filename = buff[i] + filename;
            i--;
        }

        // get file content size
        fseek(fptr, 0, SEEK_END);
        int content_length = ftell(fptr);
        rewind(fptr);
        std::string header = std::to_string(filename.length()) + ":" + filename + std::to_string(content_length) + ":";

        // read file content and add to data
        data.resize(header.length() + content_length);
        memcpy(&data[0], header.c_str(), header.length());
        fread(&data[header.length()], sizeof(char), content_length, fptr);
        fclose(fptr);        
    } else {
        std::cerr << "Error: Invalid data type" << std::endl;
        return;
    }

    // create message
    Message message(MessageType::CHAT, chat_type, data_type, _user_id, chat_id, time(NULL), data);

    // send message
    MessagePacket packet;
    while (message.get_next_packet(packet)) {
        if (send(_conn_fd, &packet, sizeof(packet), 0) < 0) {
            std::cerr << "Error: Can not send message" << std::endl;
            break;
        }

        //print all data of packet
        std::string type, chat_type, data_type;
        if (packet.type == MessageType::REQUEST) {
            type = "REQUEST";
        } else if (packet.type == MessageType::RESPONSE) {
            type = "RESPONSE";
        } else if (packet.type == MessageType::CHAT) {
            type = "CHAT";
        } else {
            type = "UNKNOWN";
        }
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
        std::cout << "Sent message: (type, chat_type, data_type, sender, chat_id, timestamp, data) = " << "(" << type <<
                                                                                                        ", " << chat_type << 
                                                                                                        ", " << data_type << 
                                                                                                        ", " << packet.chat_header.sender << 
                                                                                                        ", " << packet.chat_header.chat_id << 
                                                                                                        ", " << packet.chat_header.timestamp << 
                                                                                                        ", " << packet.data << ")" <<
                                                                                                        " - " << packet.data_length <<
                                                                                                        " - " << packet.fin <<
                                                                                                        " - " << packet.seq << std::endl;
    }
}

void Client::receive_message() {
    MessagePacket packet;
    std::string buff; 

    int bytes_received = recv(_conn_fd, &packet, sizeof(packet), 0);
    
    if (bytes_received < 0) {
        std::cerr << "Error: receive failed!" << std::endl;
        return;
    }
    if (bytes_received == 0) {
        std::cerr << "Error: server closed connection!" << std::endl;
        stop();
        return;
    } 

    std::string data = packet.data;
    
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
        } else if (packet.response_header.response_type == ResponseType::CREATE_PRIVATE_CHAT_SUCCESS) {
            response_type = "CREATE_PRIVATE_CHAT_SUCCESS";
        } else if (packet.response_header.response_type == ResponseType::CREATE_GROUP_CHAT_SUCCESS) {
            response_type = "CREATE_GROUP_CHAT_SUCCESS";
        } else if (packet.response_header.response_type == ResponseType::GET_FRIEND_LIST_SUCCESS) {
            response_type = "GET_FRIEND_LIST_SUCCESS";
            write_buff(data);
            if (packet.fin == 1) {
                _friend_list.clear();
                process_friend_list(_buff);
                clean_buff();
            }
        } else if (packet.response_header.response_type == ResponseType::WAIT_FOR_ANONYMOUS_CHAT) {
            response_type = "WAIT_FOR_ANONYMOUS_CHAT";
        } else if (packet.response_header.response_type == ResponseType::JOIN_ANONYMOUS_CHAT_SUCCESS) {
            response_type = "JOIN_ANONYMOUS_CHAT_SUCCESS";
        } else if (packet.response_header.response_type == ResponseType::GET_CHAT_LIST_SUCCESS) {
            response_type = "GET_CHAT_LIST_SUCCESS";
            write_buff(data);
            if (packet.fin == 1) {
                _chat_list.clear();
                process_chat_list(_buff);
                clean_buff();
            }
        } else if (packet.response_header.response_type == ResponseType::ADD_TO_GROUP_CHAT_SUCCESS) {
            response_type = "ADD_TO_GROUP_CHAT_SUCCESS";
        } else if (packet.response_header.response_type == ResponseType::ADD_TO_GROUP_CHAT_FAILURE) {
            response_type = "ADD_TO_GROUP_CHAT_FAILURE";
        } else if (packet.response_header.response_type == ResponseType::LEAVE_GROUP_CHAT_SUCCESS) {
            response_type = "LEAVE_GROUP_CHAT_SUCCESS";
        } else if (packet.response_header.response_type == ResponseType::GET_GROUP_CHAT_MEMBERS_SUCCESS) {
            response_type = "GET_GROUP_CHAT_MEMBERS_SUCCESS";
        } else if (packet.response_header.response_type == ResponseType::GET_CHAT_MESSAGES_SUCCESS) {
            response_type = "GET_CHAT_MESSAGES_SUCCESS";
        } else {
            response_type = "UNKOWN";
        }
        std::cout << "Received message: (type, respose_type, fin, seq, data_len, data) = " << 
                "(" << "RESPONSE" <<
                ", " << response_type << 
                ", " << packet.fin << 
                ", " << packet.seq << 
                ", " << packet.data_length << 
                ", " << packet.data << ")" << std::endl;

        if (packet.response_header.response_type == ResponseType::LOGIN_SUCCESS) {
            std::tie(_user_id, _display_name) = parse_user_info_data(packet.data);
        }
    } 
    
    else if (packet.type == MessageType::CHAT) {
        int chat_id = process_chat_packet(packet);
        // Print if this is last packet
        if (packet.fin == 1) {
            ChatMessage latest_msg = chat_map[chat_id].back();
            std::cout << "\n\033[32m(" << chat_id << 
                        ", " << latest_msg.sender << 
                        ", " << format_time(latest_msg.timestamp) <<
                        "): \033[0m";
                        
            if (packet.chat_header.data_type == DataType::FILE) {
                std::string file_path = latest_msg.data;
                std::cout <<  "New file at \"" << file_path << "\"" << std::endl;
            } else {
                std::cout << latest_msg.data << std::endl;
            } 
        }

        // //print all data of packet for debug
        // std::string chat_type, data_type;
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
        // std::cout << "Received message: (type, chat_type, data_type, sender, chat_id, timestamp, data) = " 
        //         << "(" << "CHAT" <<
        //         ", " << chat_type << 
        //         ", " << data_type << 
        //         ", " << packet.chat_header.sender << 
        //         ", " << packet.chat_header.chat_id << 
        //         ", " << packet.chat_header.timestamp << 
        //         ", " << packet.fin <<
        //         ", " << packet.seq <<
        //         ", " << packet.data_length <<
        //         ", " << packet.data << ")" << std::endl;
    } 

    else if (packet.type == MessageType::PUSH) {
        // print all data of packet for debug
        std::string push_type;
        if (packet.push_header.push_type == PushType::FRIEND_REQUEST) {
            push_type = "FRIEND_REQUEST";
        } else if (packet.push_header.push_type == PushType::FRIEND_ACCEPT) {
            push_type = "FRIEND_ACCEPT";
        } else if (packet.push_header.push_type == PushType::FRIEND_REJECT) {
            push_type = "FRIEND_REJECT";
        } else if (packet.push_header.push_type == PushType::GROUP_CHAT_JOINED) {
            push_type = "GROUP_CHAT_JOINED";
        } else if (packet.push_header.push_type == PushType::GROUP_CHAT_LEFT) {
            push_type = "GROUP_CHAT_LEFT";
        } else if (packet.push_header.push_type == PushType::GROUP_CHAT_NEW_MEMBER) {
            push_type = "GROUP_CHAT_NEW_MEMBER";
        } else {
            push_type = "UNKNOWN";
        }
        std::cout << "Received message: (type, push_type, sender, fin, seq, data_len, data) = " << "(" << "PUSH" <<
                                                                                                ", " << push_type << 
                                                                                                ", " << packet.push_header.sender <<
                                                                                                ", " << packet.fin << 
                                                                                                ", " << packet.seq << 
                                                                                                ", " << packet.data_length << 
                                                                                                ", " << packet.data << ")" << std::endl;
    } 
    
    else {
        std::cout << "Invalid message type" << std::endl;
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
            if (no_members < 2) {
                std::cerr << "Error: Number of people in a group chat must be at least three!" << std::endl;
                return;
            }
            std::vector<std::string> members;
            for (int i = 0; i < no_members; ++i) {
                sep_idx = data.find(' ', sep_idx + 1);
                members.push_back(data.substr(sep_idx + 1, data.find(' ', sep_idx + 1) - sep_idx - 1));
            }
            
            std::string create_group_chat_data = encode_create_group_chat(group_name, members);
            message_ptr = new Message(MessageType::REQUEST, RequestType::CREATE_GROUP_CHAT, _user_id, create_group_chat_data);
        } 
        // from here, chat_type is just a 3rd argument of R C, not ChatType class
        else if (chat_type == "L") {
            // list all chats: R C L
            message_ptr = new Message(MessageType::REQUEST, RequestType::GET_CHAT_LIST, _user_id);
        } else if (chat_type == "A") {
            // send invitation to join group chat to other users: R C A <group_id> <number of other users> <user_id_1> <user_id_2> ... <user_id_n>
            std::string buff = data.substr(2); 
            std::string invite_group_chat_data = encode_invite_group_chat(buff);
            message_ptr = new Message(MessageType::REQUEST, RequestType::ADD_TO_GROUP_CHAT, _user_id, invite_group_chat_data);
        } else if (chat_type == "Q") {
            // quit group chat: R C Q <group_id>
            std::string group_id = data.substr(2);
            message_ptr = new Message(MessageType::REQUEST, RequestType::LEAVE_GROUP_CHAT, _user_id, group_id);
        } else if (chat_type == "M") {
            // get group chat members: R C M <group_id>
            std::string group_id = data.substr(2);
            message_ptr = new Message(MessageType::REQUEST, RequestType::GET_GROUP_CHAT_MEMBERS, _user_id, group_id);
        } else {
            std::cerr << "Error: invalid chat type!" << std::endl;
            return;
        }
    } else if (buff[2] == 'F') {
        if (buff[4] == 'R') {
            // request add friend: R F R <other_username>
            std::string other_username = buff.substr(6);
            message_ptr = new Message(MessageType::REQUEST, RequestType::ADD_FRIEND, _user_id, other_username);
        } else if (buff[4] == 'U') {
            // unfriend: R F U <other_user_id>
            std::string other_user_id = buff.substr(6);
            message_ptr = new Message(MessageType::REQUEST, RequestType::REMOVE_FRIEND, _user_id, other_user_id);
        } else if (buff[4] == 'A') {
            // accept friend request: R F A <other_user_id>
            std::string other_user_id = buff.substr(6);
            message_ptr = new Message(MessageType::REQUEST, RequestType::ACCEPT_FRIEND, _user_id, other_user_id);
        } else if (buff[4] == 'J') {
            // Reject friend request: R F J <other_user_id>
            std::string other_user_id = buff.substr(6);
            message_ptr = new Message(MessageType::REQUEST, RequestType::REJECT_FRIEND, _user_id, other_user_id);
        } else if (buff[4] == 'L') {
            // List all friends: R F L
            message_ptr = new Message(MessageType::REQUEST, RequestType::GET_FRIEND_LIST, _user_id);
        } else {
            std::cerr << "Error: invalid request type!" << std::endl;
            return;
        }
    } else if (buff[2] == 'A') {
        if (buff[4] == 'C') {
            // request to create anonymous chat: R A C
            message_ptr = new Message(MessageType::REQUEST, RequestType::CREATE_ANONYMOUS_CHAT, _user_id);
        } else if (buff[4] == 'E') {
            // request to end anonymous chat: R A E <chat_id>
            std::string chat_id = buff.substr(6);
            message_ptr = new Message(MessageType::REQUEST, RequestType::END_ANONYMOUS_CHAT, _user_id, chat_id);
        }
    } else if (buff[2] == 'M') {
        // request to get some latest messages of chat: R M <chat_id> <number of messages> <offset>
        // where offset is the number of messages that have been sent to client
        buff = buff.substr(4);
        std::string get_latest_messages_data = encode_get_latest_messages(buff);
        message_ptr = new Message(MessageType::REQUEST, RequestType::GET_CHAT_MESSAGES, _user_id, get_latest_messages_data);
    } else if (buff[2] == 'E') {
        // request to end connection: R E
        message_ptr = new Message(MessageType::REQUEST, RequestType::EXIT, _user_id);
    }

    while ((*message_ptr).get_next_packet(packet)) {
        if (send(_conn_fd, &packet, sizeof(packet), 0) < 0) {
            std::cerr << "Can not send message" << std::endl;
            break;
        }

    //     //print all data of packet
    //     std::string type, request_type;
    //     if (packet.type == MessageType::REQUEST) {
    //         type = "REQUEST";
    //     } else if (packet.type == MessageType::RESPONSE) {
    //         type = "RESPONSE";
    //     } else if (packet.type == MessageType::CHAT) {
    //         type = "CHAT";
    //     } else {
    //         type = "UNKNOWN";
    //     }
    //     if (packet.request_header.request_type == RequestType::LOGIN) {
    //         request_type = "LOGIN";
    //     } else if (packet.request_header.request_type == RequestType::SIGNUP) {
    //         request_type = "SIGNUP";
    //     } else if (packet.request_header.request_type == RequestType::LOGOUT) {
    //         request_type = "LOGOUT";
    //     } else if (packet.request_header.request_type == RequestType::UPDATE_ACCOUNT) {
    //         request_type = "UPDATE_ACCOUNT";
    //     } else {
    //         request_type = "UNKNOWN";
    //     }

    //     std::cout << "Sent message: (type, request_type, sender, fin, seq, data_len, data) = " << "(" << type <<
    //                                                                                                 ", " << request_type << 
    //                                                                                                 ", " << packet.request_header.sender << 
    //                                                                                                 ", " << packet.fin << 
    //                                                                                                 ", " << packet.seq << 
    //                                                                                                 ", " << packet.data_length << 
    //                                                                                                 ", " << packet.data << ")" << std::endl;
    }
}

int Client::process_chat_packet(MessagePacket& p) {
    int cid = p.chat_header.chat_id;
    DataType dtype = p.chat_header.data_type;

    if (chat_map.find(cid) == chat_map.end()) {
        chat_map[cid] = std::vector<ChatMessage>();
    }
    if (chat_map[cid].empty()) {
        ChatMessage m = create_chat_message(p, _folder_path);
        chat_map[cid].push_back(m);
    } 
    else {
        if (p.chat_header.sender == chat_map[cid].back().sender 
            && p.chat_header.timestamp == chat_map[cid].back().timestamp) {
                if (dtype == DataType::TEXT) { 
                    chat_map[cid].back().data += p.data; 
                } else {
                    std::cout << "\033[34mWriting to: \033[0m" << chat_map[cid].back().data << std::endl;
                    append_file(p.data, chat_map[cid].back().data);
                }
                    
        } else {
            ChatMessage m = create_chat_message(p, _folder_path);
            chat_map[cid].push_back(m);
        }
    }
    return cid;
}

void Client::process_friend_list(std::string& data) {
    // parse the number of friends
    size_t num_delim = data.find(':');
    int num_friends_len = std::stoi(data.substr(0, num_delim));
    int num_friends = std::stoi(data.substr(num_delim + 1, num_friends_len));
    std::cout << "\033[38;5;208mNumber of friends: \033[0m" << num_friends << std::endl;

    // parse each friend
    size_t pos = num_delim + num_friends_len + 1;
    for (int i = 0; i < num_friends; i++) {
        // parse the friend ID
        size_t id_delim = data.find(':', pos);
        int id_len = std::stoi(data.substr(pos, id_delim - pos));
        int id = std::stoi(data.substr(id_delim + 1, id_len));
        pos = id_delim + id_len + 1;

        // parse the friend display name
        size_t name_delim = data.find(':', pos);
        int name_len = std::stoi(data.substr(pos, name_delim - pos));
        std::string name = data.substr(name_delim + 1, name_len);
        pos = name_delim + name_len + 1;

        // parse the friend status
        int status = std::stoi(data.substr(pos, 1));
        pos += 1;

        // add the friend to friend list
        Friend friend_obj = {id, name, status};
        _friend_list.push_back(friend_obj);
        std::cout << "  ID: " << id << ", dname: " << name << ", online: " << status << std::endl;
    }
}

void Client::process_chat_list(std::string& data) {
    size_t num_delim = data.find(':');
    int num_chats = std::stoi(data.substr(0, num_delim));
    std::cout << "\033[38;5;208mNumber of chats: \033[0m" << num_chats << std::endl;
    
    size_t pos = num_delim + 1;
    for (int i = 0; i < num_chats; i++) {
        std::string chat_type = data.substr(pos, 1);
        pos += 1;

        size_t id_delim = data.find(':', pos);
        int id_len = std::stoi(data.substr(pos, id_delim - pos));
        int id = std::stoi(data.substr(id_delim + 1, id_len));
        pos = id_delim + id_len + 1;

        size_t name_delim = data.find(':', pos);
        int name_len = std::stoi(data.substr(pos, name_delim - pos));
        std::string name = data.substr(name_delim + 1, name_len);
        pos = name_delim + name_len + 1;

        ChatType ctype = (chat_type == "P") ? ChatType::PRIVATE_CHAT : ChatType::GROUP_CHAT;
        Chat chat_obj = {ctype, id, name};
        _chat_list.push_back(chat_obj);
        std::cout << "  ID: " << id << ", name: " << name << ", type: " << ((ctype == ChatType::PRIVATE_CHAT) ? "Private" : "Group") << std::endl;
    }
}

void Client::write_buff(std::string& data) {
    _buff += data;
}

void Client::clean_buff() {
    _buff = "";
}