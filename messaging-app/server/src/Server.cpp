#include <iostream>
#include <map>
#include <vector>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>
#include <mysql/mysql.h>
#include <fstream>

#include "../include/Server.h"
#include "../include/Message.h"
#include "../include/Utils.h"
#include "../include/SQLQuery.h"
#include "../../shared/common.h"

Server::Server(int port, int backlog) {
    _port = port;
    _backlog = backlog;
    _num_clients = 0;

    /* ----- setup server socket ----- */
    // create listen socket
    if ((_listen_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        std::cerr << "Can not create socket" << std::endl;
        exit(1);
    }

    // set server address
    bzero((char *)&_addr, sizeof(_addr));
    _addr.sin_family = AF_INET;
    _addr.sin_port = htons(_port);
    _addr.sin_addr.s_addr = htonl(INADDR_ANY);

    // set socket option to reuse port (prevent 'Address already in use' error)
    int opt = 1;
    setsockopt(_listen_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    // bind socket to server address
    if (bind(_listen_fd, (struct sockaddr *)&_addr, sizeof(_addr)) == -1) {
        std::cerr << "Can not bind socket to address" << std::endl;
        exit(1);
    }

    /* ----- setup file descriptor sets ----- */
    // create file descriptor sets
    FD_ZERO(&_master);
    FD_ZERO(&_read_fds);

    // add listen socket to master set
    FD_SET(_listen_fd, &_master);

    // keep track of the biggest file descriptor
    _fdmax = _listen_fd;

    log(LogType::INFO, "Server is running at " + std::string(inet_ntoa(_addr.sin_addr)) + ":" + std::to_string(_port));
}

void Server::start() {
    listen();
    
    while (true) {
        _read_fds = _master;
        if (select(_fdmax + 1, &_read_fds, NULL, NULL, NULL) == -1) {
            log(LogType::ERROR, "Cannot listen for incoming connection, select() failed");
            stop();
        }

        for (int i = 0; i <= _fdmax; i++) {
            if (FD_ISSET(i, &_read_fds)) {
                if (i == _listen_fd) {
                    accept();
                } else {
                    receive_message(i);
                }
            }
        }
    }
}

void Server::connectdb() {
    // Read database configuration from config file
    std::ifstream config_file("../config/config.txt");
    std::string line;
    std::map<std::string, std::string> config_map;
    while (std::getline(config_file, line)) {
        size_t pos = line.find('=');
        if (pos != std::string::npos) {
            std::string key = line.substr(0, pos);
            std::string value = line.substr(pos + 1);
            config_map[key] = value;
        }
    }

    std::string database_host = config_map["database_host"];
    std::string database_name = config_map["database_name"];
    std::string database_user = config_map["database_user"];
    std::string database_password = config_map["database_password"];
    std::string config_multi_statements = config_map["multi_statements"];

    // Connect to the MySQL database
    if (_sql_query.connect(database_host, database_user, database_password, database_name, config_multi_statements) == false) {
        log(LogType::ERROR, "Can not connect to database");
        stop();
    }
}

void Server::listen() {
    // listen for incoming connection
    if (::listen(_listen_fd, _backlog) == -1) {
        log(LogType::ERROR, "Can not listen for incoming connection");
        stop();
    }
}

void Server::accept() {
    socklen_t sin_size;
    struct sockaddr_in client_addr;
    int conn_fd;

    // accept new connection
    sin_size = sizeof(client_addr);
    if ((conn_fd = ::accept(_listen_fd, (struct sockaddr *)&client_addr, &sin_size)) == -1) {
        log(LogType::ERROR, "Can not accept new connection");
    } else {
        // check if the number of clients exceeds the maximum
        if (_num_clients >= _backlog) {
            log(LogType::WARNING, "Can not accept new connection, maximum number of clients reached");
            close(conn_fd);
        } else {
            // add new connection to master set
            _num_clients++;
            FD_SET(conn_fd, &_master);
            if (conn_fd > _fdmax) {
                _fdmax = conn_fd;
            }
            log(LogType::INFO, "New connection from " + std::string(inet_ntoa(client_addr.sin_addr)) + " on socket " + std::to_string(conn_fd));
        }
    }
}

void Server::stop() {
    std::cout << "\nStopping server...\n" << std::endl;
    _sql_query.disconnect();
    close(_listen_fd);
    exit(0);
}

void Server::receive_message(int conn_fd) {
    int bytes_received;
    MessagePacket packet;

    if ((bytes_received = recv(conn_fd, &packet, sizeof(packet), 0)) <= 0) {
        if (bytes_received == 0) {
            log(LogType::INFO, "Socket " + std::to_string(conn_fd) + " disconnected");
            remove_client(conn_fd, true);
        } else {
            log(LogType::ERROR, "Can not receive message from socket " + std::to_string(conn_fd));
            log(LogType::INFO, "Force disconnect socket " + std::to_string(conn_fd));
        }
        close(conn_fd);
        FD_CLR(conn_fd, &_master);
    } else {
        Message *message_ptr = nullptr;
        bool found = false;

        // check if packet is a part of a previous message
        for (auto it = _message_list.begin(); it != _message_list.end(); it++) {
            if ((**it).is_match_header(packet) == true) {
                (**it).add_packet(packet);

                if ((**it).is_complete() == false)
                    return;

                found = true;
                message_ptr = *it;
                _message_list.erase(it);
                break;
            }
        }
        if (found == false) {
            message_ptr = new Message(packet);
            if (message_ptr->is_complete() == false) {
                _message_list.push_back(message_ptr);
                return;
            }
        }   

        if (packet.type == MessageType::CHAT) {
            process_chat_message(*message_ptr, conn_fd);
        } else if (packet.type == MessageType::REQUEST) {
            process_request_message(*message_ptr, conn_fd);
        }
    }

     // debug
    std::cout << "Online users:\n";
    for (auto it = _online_user_list.begin(); it != _online_user_list.end(); it++) {
        std::cout << it->second->get_id() << " " << it->second->get_username() << std::endl;
    }
    std::cout << "user_id - socket:\n";
    for (auto it = _user_id_to_socket.begin(); it != _user_id_to_socket.end(); it++) {
        std::cout << it->first << " " << it->second << std::endl;
    }
}

void Server::remove_client(int conn_fd, bool is_force) {
    // remove any running anonymous chat room
    int chat_id = _anonymous_chat_room.get_chat_id(conn_fd);
    if (chat_id != -1) {
        Message message;
        handle_end_anonymous_chat(message, conn_fd, chat_id);
    }

    // remove user if it is logged in
    for (auto it = _user_id_to_socket.begin(); it != _user_id_to_socket.end(); it++) {
        if (it->second == conn_fd) {
            int user_id = it->first;
            std::string username = _online_user_list[user_id]->get_username();

            _online_user_list.erase(user_id);
            _online_user_list.erase(username);
            _user_id_to_socket.erase(it);
            break;
        }
    }

    if (is_force == true) {
        FD_CLR(conn_fd, &_master);
        _num_clients--;
        close(conn_fd);
    }
}

void Server::process_chat_message(Message& message, int conn_fd) {
    MessagePacket response_packet(MessageType::RESPONSE);  
    Message response_message;  

    if (message.get_chat_type() == ChatType::ANONYMOUS_CHAT){
        int receiver_fd = _anonymous_chat_room.get_other_client_fd(message.get_chat_id(), conn_fd);

        if (receiver_fd == -1) {
            response_packet.response_header.response_type = ResponseType::FAILURE;
            strcpy(response_packet.data, "Chat does not exist");
            response_packet.data_length = strlen(response_packet.data);

            log(LogType::WARNING, response_packet.data, conn_fd);
        } else {
            if(send_message(message, receiver_fd) == false) {
                response_packet.response_header.response_type = ResponseType::FAILURE;
                strcpy(response_packet.data, "Can not send message to receiver");
                response_packet.data_length = strlen(response_packet.data);

                log(LogType::WARNING, response_packet.data, conn_fd);
            } else {
                response_packet.response_header.response_type = ResponseType::SUCCESS;
                strcpy(response_packet.data, "Message sent");
                response_packet.data_length = strlen(response_packet.data);

                log(LogType::INFO, response_packet.data, conn_fd);
            }
        }
    } else {
        // Insert to database
        bool is_saved = message.save(_sql_query, response_packet);
        response_message.set_template_packet(response_packet);
        send_message(response_message, conn_fd);
        if (is_saved == false) {
            log(LogType::ERROR, "Can not save message to database", conn_fd);
            return;
        }

        // Forward message to receiver
        int sender = message.get_chat_sender();
        int chat_id = message.get_chat_id();
        std::string query = "SELECT `m`.`user_id` FROM `Chat` `c` JOIN `Membership` `m` ON `c`.`id` = `m`.`chat_id` WHERE `m`.`chat_id` = " + std::to_string(chat_id) + " AND `m`.`user_id` != " + std::to_string(sender) + ";";
        
        _sql_query.query(query, response_packet);
        if (_sql_query.is_select_successful() == true) {
            if (_sql_query.is_result_empty() == true) {
                response_packet.response_header.response_type = ResponseType::FAILURE;
                strcpy(response_packet.data, "Can not find receiver of chat");
                response_packet.data_length = strlen(response_packet.data);

                log(LogType::WARNING, response_packet.data, conn_fd);
            } else {
                MYSQL_RES *result = _sql_query.get_result();
                MYSQL_ROW row;
                bool is_sent = true;

                while ((row = mysql_fetch_row(result)) != NULL) {
                    int receiver = std::stoi(row[0]);
                    int receiver_socket = _user_id_to_socket[receiver];

                    if(send_message(message, receiver_socket) == false) {
                        is_sent = false;
                    }
                }

                if (is_sent == false) {
                    response_packet.response_header.response_type = ResponseType::FAILURE;
                    strcpy(response_packet.data, "Can not send message to receiver");
                    response_packet.data_length = strlen(response_packet.data);

                    log(LogType::WARNING, response_packet.data, conn_fd);
                } else {
                    response_packet.response_header.response_type = ResponseType::SUCCESS;
                    strcpy(response_packet.data, "Message sent");
                    response_packet.data_length = strlen(response_packet.data);

                    log(LogType::INFO, response_packet.data, conn_fd);
                }
            }
        } else {
            response_packet.response_header.response_type = ResponseType::ERROR;
            strcpy(response_packet.data, "Failed to query database");
            response_packet.data_length = strlen(response_packet.data);

            log(LogType::ERROR, response_packet.data, conn_fd);
        }
        _sql_query.free_result();
    }

    response_message.set_template_packet(response_packet);
    send_message(response_message, conn_fd);
}

bool Server::send_message(Message& message, int conn_fd) {
    MessagePacket packet;
    if (FD_ISSET(conn_fd, &_master) && conn_fd != 0) {
        while (message.get_next_packet(packet)) {
            if (send(conn_fd, &packet, sizeof(packet), 0) < 0) {
                log(LogType::ERROR, "Can not send message", conn_fd);
                return false;
            }
        }
    } else {
        log(LogType::ERROR, "Socket is not set", conn_fd);
        return false;
    }

    return true;
}

void Server::process_request_message(Message& message, int conn_fd) {
    switch (message.get_request_type()) {
        case RequestType::LOGIN:
            handle_login(message, conn_fd);
            break;
        case RequestType::SIGNUP:
            handle_signup(message, conn_fd);
            break;
        case RequestType::LOGOUT:
            handle_logout(message, conn_fd);
            break;
        case RequestType::UPDATE_ACCOUNT:
            handle_update_account(message, conn_fd);
            break;
        case RequestType::CREATE_PRIVATE_CHAT:
            handle_create_private_chat(message, conn_fd);
            break;
        case RequestType::CREATE_GROUP_CHAT:
            handle_create_group_chat(message, conn_fd);
            break;
        case RequestType::ADD_TO_GROUP_CHAT:
            handle_add_to_group_chat(message, conn_fd);
            break;
        case RequestType::LEAVE_GROUP_CHAT:
            handle_leave_group_chat(message, conn_fd);
            break;
        case RequestType::GET_GROUP_CHAT_MEMBERS:
            handle_get_group_chat_members(message, conn_fd);
            break;
        case RequestType::CREATE_ANONYMOUS_CHAT:
            handle_create_anonymous_chat(message, conn_fd);
            break;
        case RequestType::END_ANONYMOUS_CHAT:
            handle_end_anonymous_chat(message, conn_fd);
            break;
        case RequestType::GET_CHAT_LIST:
            handle_get_chat_list(message, conn_fd);
            break;
        case RequestType::GET_CHAT_MESSAGES:
            handle_get_chat_messages(message, conn_fd);
            break;
        case RequestType::ADD_FRIEND: 
        case RequestType::ACCEPT_FRIEND: 
        case RequestType::REJECT_FRIEND:
            handle_add_friend(message, conn_fd);
            break;
        case RequestType::REMOVE_FRIEND:
            handle_remove_friend(message, conn_fd);
            break;
        case RequestType::GET_FRIEND_LIST:
            handle_get_friend_list(message, conn_fd);
            break;
        case RequestType::EXIT:
            handle_close_client_connection(conn_fd);
            break;
        default:
            break;
    }
}

void Server::handle_login(Message& message, int conn_fd) {
    MessagePacket response_packet(MessageType::RESPONSE);
    Message response_message;  

    log(LogType::INFO, "Send login request to server", conn_fd);

    // parse username and password/
    std::string username, password, auth_data = message.get_data();
    std::tie(username, password) = parse_auth_data(auth_data);

    // check if username and password are valid
    if (_online_user_list.find(username) != _online_user_list.end()) {
        // user is already logged in
        response_packet.response_header.response_type = ResponseType::FAILURE;
        strcpy(response_packet.data, "Account is already logged in on another device");
        response_packet.data_length = strlen(response_packet.data);

        log(LogType::WARNING, response_packet.data, conn_fd);
    } else {
        User *user = new User(username);
        if (user->authenticate(password, _sql_query, response_packet) == false) {
            log(LogType::ERROR, "Can not authenticate user", conn_fd);
        } else if (response_packet.response_header.response_type == ResponseType::LOGIN_SUCCESS) {
            // add user to online user list
            _online_user_list.insert(std::pair<std::string, User*>(username, user));
            _online_user_list.insert(std::pair<int, User*>(user->get_id(), user));

            // map socket to user
            _user_id_to_socket[user->get_id()] = conn_fd;

            log(LogType::INFO, "Login success", conn_fd);
        } else {
            log(LogType::WARNING, response_packet.data, conn_fd);
        }
    }

    response_message.set_template_packet(response_packet);
    send_message(response_message, conn_fd);
}

void Server::handle_signup(Message& message, int conn_fd) {
    MessagePacket response_packet(MessageType::RESPONSE);
    Message response_message;  

    log(LogType::INFO, "Send signup request to server", conn_fd);

    // parse username and password and display_name
    std::string username, password, display_name, signup_data = message.get_data();
    std::tie(username, password, display_name) = parse_signup_data(signup_data);

    User *user = User::signup(username, password, display_name, _sql_query, response_packet);

    if (response_packet.response_header.response_type == ResponseType::ERROR) {
        log(LogType::ERROR, "Internal error. Can not create new user", conn_fd);
    } else if(response_packet.response_header.response_type == ResponseType::FAILURE){
        log(LogType::WARNING, response_packet.data, conn_fd);
    } else {
        log(LogType::INFO, response_packet.data, conn_fd);
    }

    response_message.set_template_packet(response_packet);
    send_message(response_message, conn_fd);
}

void Server::handle_logout(Message& message, int conn_fd) {
    MessagePacket response_packet(MessageType::RESPONSE);
    Message response_message;  

    log(LogType::INFO, "Send logout request to server", conn_fd);

    int user_id = message.get_request_sender();
    auto it = _online_user_list.find(user_id);
    if (it == _online_user_list.end()) {
        response_packet.response_header.response_type = ResponseType::FAILURE;
        strcpy(response_packet.data, "Can not find user");
        response_packet.data_length = strlen(response_packet.data);

        log(LogType::WARNING, response_packet.data, conn_fd);
    } else {
        int user_id = it->second->get_id();
        std::string username = it->second->get_username();

        // remove user from online user list
        _online_user_list.erase(username);
        _online_user_list.erase(user_id);

        // remove socket to user mapping
        _user_id_to_socket.erase(user_id);

        response_packet.response_header.response_type = ResponseType::SUCCESS;
        strcpy(response_packet.data, "Logout successfully");
        response_packet.data_length = strlen(response_packet.data); 

        log(LogType::INFO, response_packet.data, conn_fd);
    }

    response_message.set_template_packet(response_packet);
    send_message(response_message, conn_fd);
}

void Server::handle_update_account(Message& message, int conn_fd) {
    MessagePacket response_packet(MessageType::RESPONSE);
    Message response_message;  

    log(LogType::INFO, "Send update account request to server", conn_fd);

    int user_id = message.get_request_sender();
    auto it = _online_user_list.find(user_id);
    if (it == _online_user_list.end()) {
        response_packet.response_header.response_type = ResponseType::FAILURE;
        strcpy(response_packet.data, "You are not logged in");
        response_packet.data_length = strlen(response_packet.data);

        log(LogType::WARNING, response_packet.data, conn_fd);
    } else {
        std::string field, data, update_account_data = message.get_data();
        std::tie(field, data) = parse_update_account_data(update_account_data);
        if (it->second->update_account(field, data, _sql_query, response_packet) == false) {
            log(LogType::ERROR, "Can not update account", conn_fd);
        } else {
            log(LogType::INFO, response_packet.data, conn_fd);
        }
    }

    response_message.set_template_packet(response_packet);
    send_message(response_message, conn_fd);
}

void Server::handle_create_private_chat(Message& message, int conn_fd) {
    MessagePacket response_packet(MessageType::RESPONSE);
    Message response_message;  
    std::vector<int> user_id_list;

    log(LogType::INFO, "Send create private chat request to server", conn_fd);

    int user_id = message.get_request_sender();
    auto it = _online_user_list.find(user_id);
    if (it == _online_user_list.end()) {
        response_packet.response_header.response_type = ResponseType::FAILURE;
        strcpy(response_packet.data, "You are not logged in");
        response_packet.data_length = strlen(response_packet.data);

        log(LogType::WARNING, response_packet.data, conn_fd);
    } else {
        std::string user_id_str = std::to_string(user_id);
        std::string other_user_id_str = message.get_data();
        user_id_list.push_back(user_id);

        if (std::stoi(other_user_id_str) == user_id) {
            response_packet.response_header.response_type = ResponseType::FAILURE;
            strcpy(response_packet.data, "You can not create private chat with yourself");
            response_packet.data_length = strlen(response_packet.data);

            log(LogType::WARNING, response_packet.data, conn_fd);
        } else {
            user_id_list.push_back(std::stoi(other_user_id_str));

            std::string query = "SELECT `c`.`id` FROM `Membership` `m1` JOIN `Membership` `m2` ON `m1`.`chat_id` = `m2`.`chat_id` JOIN `Chat` `c` ON `m1`.`chat_id` = `c`.`id` WHERE `m1`.`user_id` = " + user_id_str + " AND `m2`.`user_id`= " + other_user_id_str + " AND `c`.`type` = 'PRIVATE';";
            MYSQL_RES *result;

            _sql_query.query(query, response_packet);
            if (_sql_query.is_select_successful() == true) {
                if (_sql_query.is_result_empty() == true) {
                    // add new chat
                    query = "INSERT INTO `Chat` (`type`, `time_created`) VALUES ('PRIVATE', NOW());";
                    query += "SELECT LAST_INSERT_ID();";

                    _sql_query.query(query, response_packet);
                    if (_sql_query.is_insert_successful() == false) {
                        response_packet.response_header.response_type = ResponseType::ERROR;
                        strcpy(response_packet.data, "Can not create private chat");
                        response_packet.data_length = strlen(response_packet.data);

                        log(LogType::ERROR, "Can not create private chat", conn_fd);
                    } else {
                        _sql_query.next_result(); // skip the first result to get last insert id
                        if (_sql_query.is_select_successful() == false) {
                            response_packet.response_header.response_type = ResponseType::ERROR;
                            strcpy(response_packet.data, "Can not create private chat");
                            response_packet.data_length = strlen(response_packet.data);

                            log(LogType::ERROR, "Can not create private chat", conn_fd);
                        } else {
                            result = _sql_query.get_result();
                            MYSQL_ROW row = mysql_fetch_row(result);
                            int chat_id = std::stoi(row[0]);

                            // add membership
                            query = "INSERT INTO `Membership` (`user_id`, `chat_id`) VALUES (" + user_id_str + ", " + std::to_string(chat_id) + ");";
                            query += "INSERT INTO `Membership` (`user_id`, `chat_id`) VALUES (" + other_user_id_str + ", " + std::to_string(chat_id) + ");";

                            _sql_query.query(query, response_packet);
                            if (_sql_query.is_insert_successful() == false) {
                                response_packet.response_header.response_type = ResponseType::ERROR;
                                strcpy(response_packet.data, "Can not create private chat");
                                response_packet.data_length = strlen(response_packet.data);

                                log(LogType::ERROR, "Can not create private chat", conn_fd);
                            } else {
                                response_packet.response_header.response_type = ResponseType::SUCCESS;
                                sprintf(response_packet.data, "%d", chat_id);
                                response_packet.data_length = strlen(response_packet.data);

                                log(LogType::INFO, "Create private chat successfully", conn_fd);
                            }
                        }
                    }                
                } else {
                    response_packet.response_header.response_type = ResponseType::FAILURE;
                    strcpy(response_packet.data, "Chat already exists");
                    response_packet.data_length = strlen(response_packet.data);

                    log(LogType::WARNING, response_packet.data, conn_fd);
                }
            } else {
                response_packet.response_header.response_type = ResponseType::ERROR;
                strcpy(response_packet.data, "Failed to query database");
                response_packet.data_length = strlen(response_packet.data);
                
                log(LogType::ERROR, response_packet.data, conn_fd);
            }

            _sql_query.free_result();
        }
    }

    // send response to all online users if success
    if (response_packet.response_header.response_type == ResponseType::SUCCESS) {
        response_packet.response_header.response_type = ResponseType::CREATE_PRIVATE_CHAT_SUCCESS;
        response_message.set_template_packet(response_packet);
        for (int user_id : user_id_list) {
            send_message(response_message, _user_id_to_socket[user_id]);
        }
    } else {
        response_message.set_template_packet(response_packet);
        send_message(response_message, conn_fd);
    }
}

void Server::handle_create_group_chat(Message& message, int conn_fd) {
    MessagePacket response_packet(MessageType::RESPONSE);
    Message response_message;  
    std::vector<int> user_id_list;

    log(LogType::INFO, "Send create group chat request to server", conn_fd);

    int user_id = message.get_request_sender();
    auto it = _online_user_list.find(user_id);
    if (it == _online_user_list.end()) {
        response_packet.response_header.response_type = ResponseType::FAILURE;
        strcpy(response_packet.data, "You are not logged in");
        response_packet.data_length = strlen(response_packet.data);

        log(LogType::WARNING, response_packet.data, conn_fd);
    } else {
        std::string user_id_str = std::to_string(user_id);
        std::string group_name;
        std::vector<std::string> members;
        std::tie(group_name, members) = parse_create_group_data(message.get_data());
        user_id_list.push_back(user_id);

        // add new chat
        std::string query = "INSERT INTO `Chat` (`type`, `time_created`, `name`) VALUES ('GROUP', NOW(), '" + group_name + "');";
        query += "SELECT LAST_INSERT_ID();";
        MYSQL_RES *result;

        _sql_query.query(query, response_packet);
        if (_sql_query.is_insert_successful() == true) {
            _sql_query.next_result(); // skip the first result to get last insert id
            if (_sql_query.is_select_successful() == false) {
                response_packet.response_header.response_type = ResponseType::ERROR;
                strcpy(response_packet.data, "Can not create group chat");
                response_packet.data_length = strlen(response_packet.data);

                log(LogType::ERROR, "Can not create group chat", conn_fd);
            } else {
                result = _sql_query.get_result();
                MYSQL_ROW row = mysql_fetch_row(result);
                int chat_id = std::stoi(row[0]);

                // add membership
                query = "INSERT INTO `Membership` (`user_id`, `chat_id`) VALUES ";
                for (auto& member : members) {
                    user_id_list.push_back(std::stoi(member));
                    query += "(" + member + ", " + std::to_string(chat_id) + "), ";
                }
                query += "(" + user_id_str + ", " + std::to_string(chat_id) + ");";

                _sql_query.query(query, response_packet);
                if (_sql_query.is_insert_successful() == false) {
                    response_packet.response_header.response_type = ResponseType::ERROR;
                    strcpy(response_packet.data, "Can not add members to group chat");
                    response_packet.data_length = strlen(response_packet.data);

                    log(LogType::ERROR, "Can not add members to group chat", conn_fd);
                } else {
                    response_packet.response_header.response_type = ResponseType::SUCCESS;
                    sprintf(response_packet.data, "%d", chat_id);
                    response_packet.data_length = strlen(response_packet.data);

                    log(LogType::INFO, response_packet.data, conn_fd);
                }
            }
        } else {
            response_packet.response_header.response_type = ResponseType::FAILURE;
            strcpy(response_packet.data, "Failed to query database");
            response_packet.data_length = strlen(response_packet.data);
            
            log(LogType::ERROR, response_packet.data, conn_fd);
        }

        _sql_query.free_result();
    }

        // send response to all online users if success
    if (response_packet.response_header.response_type == ResponseType::SUCCESS) {
        response_packet.response_header.response_type = ResponseType::CREATE_GROUP_CHAT_SUCCESS;
        response_message.set_template_packet(response_packet);
        for (int user_id : user_id_list) {
            send_message(response_message, _user_id_to_socket[user_id]);
        }
    } else {
        response_message.set_template_packet(response_packet);
        send_message(response_message, conn_fd);
    }
}

void Server::handle_add_friend(Message& message, int conn_fd) {
    MessagePacket response_packet(MessageType::RESPONSE), push_packet(MessageType::PUSH);
    Message response_message, push_message;

    log(LogType::INFO, "Send add friend request to server", conn_fd);

    int user_id = message.get_request_sender();
    auto it = _online_user_list.find(user_id);
    if (it == _online_user_list.end()) {
        response_packet.response_header.response_type = ResponseType::FAILURE;
        strcpy(response_packet.data, "Can not find user");
        response_packet.data_length = strlen(response_packet.data);

        log(LogType::WARNING, response_packet.data, conn_fd);
    } else {
        User *user = it->second;
        std::string data;
        int other_user_id;

        push_packet.push_header.sender = user_id;
        if (message.get_request_type() == RequestType::ADD_FRIEND) {
            if (user->check_friend(message.get_data(), _sql_query, response_packet, data, other_user_id) == false) {
                log(LogType::ERROR, response_packet.data, conn_fd);
            } else {
                if (response_packet.response_header.response_type == ResponseType::SUCCESS) {
                    log(LogType::INFO, response_packet.data, conn_fd);

                    // send push to receiver
                    push_packet.push_header.push_type = PushType::FRIEND_REQUEST;
                    strcpy(push_packet.data, data.c_str());
                    push_packet.data_length = data.length();
                    push_message.set_template_packet(push_packet);

                    send_message(push_message, _user_id_to_socket[other_user_id]);
                } else {
                    log(LogType::WARNING, response_packet.data, conn_fd);
                }
            }
        } else if (message.get_request_type() == RequestType::REJECT_FRIEND) {
            other_user_id = std::stoi(message.get_data());

            response_packet.response_header.response_type = ResponseType::SUCCESS;
            strcpy(response_packet.data, "Reject add friend request successfully");
            response_packet.data_length = strlen(response_packet.data);

            log(LogType::INFO, response_packet.data, conn_fd);

            // send push to receiver
            push_packet.push_header.push_type = PushType::FRIEND_REJECT;
            push_message.set_template_packet(push_packet);
            send_message(push_message, _user_id_to_socket[other_user_id]);
        } else if (message.get_request_type() == RequestType::ACCEPT_FRIEND) {
            other_user_id = std::stoi(message.get_data());

            if(user->add_friend(message.get_data(), _sql_query, response_packet) == false) {
                log(LogType::ERROR, response_packet.data, conn_fd);
            } else {
                if (response_packet.response_header.response_type == ResponseType::SUCCESS) {
                    log(LogType::INFO, response_packet.data, conn_fd);

                    // send push to receiver
                    push_packet.push_header.push_type = PushType::FRIEND_ACCEPT;
                    data = std::to_string(std::to_string(user_id).length()) + ":" + std::to_string(user_id) + std::to_string(user->get_display_name().length()) + ":" + user->get_display_name();
                    strcpy(push_packet.data, data.c_str());
                    push_packet.data_length = data.length();
                    
                    push_message.set_template_packet(push_packet);
                    send_message(push_message, _user_id_to_socket[other_user_id]);
                } else {
                    log(LogType::WARNING, response_packet.data, conn_fd);
                }
            }
        }
        push_packet.push_header.sender = user_id;
    }

    response_message.set_template_packet(response_packet);
    send_message(response_message, conn_fd);
}

void Server::handle_remove_friend(Message& message, int conn_fd) {
    MessagePacket response_packet(MessageType::RESPONSE);
    Message response_message;

    log(LogType::INFO, "Send remove friend request to server", conn_fd);

    int user_id = message.get_request_sender();
    auto it = _online_user_list.find(user_id);
    if (it == _online_user_list.end()) {
        response_packet.response_header.response_type = ResponseType::FAILURE;
        strcpy(response_packet.data, "Can not find user");
        response_packet.data_length = strlen(response_packet.data);

        log(LogType::WARNING, response_packet.data, conn_fd);
    } else {
        User *user = it->second;

        if(user->remove_friend(message.get_data(), _sql_query, response_packet) == false) {
            log(LogType::ERROR, response_packet.data, conn_fd);
        } else {
            if (response_packet.response_header.response_type == ResponseType::SUCCESS) {
                log(LogType::INFO, response_packet.data, conn_fd);
            } else if (response_packet.response_header.response_type == ResponseType::FAILURE) {
                log(LogType::WARNING, response_packet.data, conn_fd);
            } else {
                log(LogType::ERROR, response_packet.data, conn_fd);
            }
        }
    }

    response_message.set_template_packet(response_packet);
    send_message(response_message, conn_fd);
}

void Server::handle_get_friend_list(Message& message, int conn_fd) {
    MessagePacket response_packet(MessageType::RESPONSE);
    Message response_message;

    log(LogType::INFO, "Send get friend list request to server", conn_fd);

    int user_id = message.get_request_sender();
    auto it = _online_user_list.find(user_id);
    if (it == _online_user_list.end()) {
        response_packet.response_header.response_type = ResponseType::FAILURE;
        strcpy(response_packet.data, "Can not find user");
        response_packet.data_length = strlen(response_packet.data);

        log(LogType::WARNING, response_packet.data, conn_fd);
    } else {
        User *user = it->second;
        std::pair<bool, std::vector<std::pair<int, std::string>>> result = user->get_friend_list(_sql_query, response_packet);

        if(result.first == false) {
            log(LogType::ERROR, response_packet.data, conn_fd);
        } else {
            if (response_packet.response_header.response_type == ResponseType::SUCCESS) {
                response_packet.response_header.response_type = ResponseType::GET_FRIEND_LIST_SUCCESS;            
                log(LogType::INFO, "Get friend list successfully", conn_fd);

                int num_friend = result.second.size();
                std::string data = std::to_string(std::to_string(num_friend).length()) + ":" + std::to_string(num_friend);
                for (int i = 0; i < num_friend; i++) {
                    data += result.second[i].second;

                    // check if user is online
                    int uid = result.second[i].first;
                    auto uit = _online_user_list.find(uid);
                    data += std::to_string((uit != _online_user_list.end()) ? 1 : 0);
                }
                
                response_message.set_data(data, response_packet);
                send_message(response_message, conn_fd);
                return;
            } else if (response_packet.response_header.response_type == ResponseType::FAILURE) {
                log(LogType::WARNING, response_packet.data, conn_fd);
            } else {
                log(LogType::ERROR, response_packet.data, conn_fd);
            }
        }
    }

    response_message.set_template_packet(response_packet);
    send_message(response_message, conn_fd);
}

void Server::handle_create_anonymous_chat(Message& message, int conn_fd) {
    MessagePacket response_packet(MessageType::RESPONSE);
    Message response_message;
    int other_client_fd=-1;

    log(LogType::INFO, "Send create anonymous chat request to server", conn_fd);

    int user_id = message.get_request_sender();
    auto it = _online_user_list.find(user_id);
    if (it == _online_user_list.end()) {
        response_packet.response_header.response_type = ResponseType::FAILURE;
        strcpy(response_packet.data, "Can not find user");
        response_packet.data_length = strlen(response_packet.data);

        log(LogType::WARNING, response_packet.data, conn_fd);
    } else {
        User *user = it->second;
        int chat_id = _anonymous_chat_room.add_client(conn_fd, user);

        if (chat_id == -1) {
            response_packet.response_header.response_type = ResponseType::WAIT_FOR_ANONYMOUS_CHAT;
            strcpy(response_packet.data, "Wait for another user to join");
            response_packet.data_length = strlen(response_packet.data);

            log(LogType::INFO, response_packet.data, conn_fd);
        } else if (chat_id == -2) {
            response_packet.response_header.response_type = ResponseType::FAILURE;
            strcpy(response_packet.data, "You already requested to create anonymous chat");
            response_packet.data_length = strlen(response_packet.data);

            log(LogType::WARNING, response_packet.data, conn_fd);
        } else {
            other_client_fd = _anonymous_chat_room.get_other_client_fd(chat_id, conn_fd);

            response_packet.response_header.response_type = ResponseType::JOIN_ANONYMOUS_CHAT_SUCCESS;
            strcpy(response_packet.data, std::to_string(chat_id).c_str());
            response_packet.data_length = strlen(response_packet.data);

            log(LogType::INFO, "Create anonymous chat successfully", conn_fd);
        }
    }

    response_message.set_template_packet(response_packet);
    send_message(response_message, conn_fd);
    if (other_client_fd != -1) {
        send_message(response_message, other_client_fd);
    }
}

void Server::handle_end_anonymous_chat(Message& message, int conn_fd, int chat_id) {
    /*
    chat_id >= 0: end anonymous chat with specific chat_id, used when client closed connection but not end anonymous chat
    chat_id = -1: end anonymous chat when client still in connection
    */
    MessagePacket response_packet(MessageType::RESPONSE);
    Message response_message;
    int other_client_fd=-1;

    log(LogType::INFO, "Send end anonymous chat request to server", conn_fd);

    int user_id = message.get_request_sender();
    auto it = _online_user_list.find(user_id);
    if (it == _online_user_list.end() && chat_id < 0) {
        response_packet.response_header.response_type = ResponseType::FAILURE;
        strcpy(response_packet.data, "Can not find user");
        response_packet.data_length = strlen(response_packet.data);

        log(LogType::WARNING, response_packet.data, conn_fd);
    } else {
        if (chat_id == -1) {
            chat_id = std::stoi(message.get_data());
        }

        other_client_fd = _anonymous_chat_room.get_other_client_fd(chat_id, conn_fd);
        bool ret = _anonymous_chat_room.end_chat(chat_id);

        if (ret == false || other_client_fd == -1) {
            response_packet.response_header.response_type = ResponseType::FAILURE;
            strcpy(response_packet.data, "Chat room does not exist");
            response_packet.data_length = strlen(response_packet.data);

            log(LogType::WARNING, response_packet.data, conn_fd);
        } else {
            if (it != _online_user_list.end()) {
                // only send response if user is still connected
                response_packet.response_header.response_type = ResponseType::SUCCESS;
                strcpy(response_packet.data, "End anonymous chat successfully");
                response_packet.data_length = strlen(response_packet.data);
            }

            // forward message to inform other client
            Message push_message;
            MessagePacket push_packet(MessageType::PUSH);
            push_packet.push_header.push_type = PushType::ANONYMOUS_CHAT_ENDED;
            strcpy(push_packet.data, "Anonymous chat ended");
            push_packet.data_length = strlen(push_packet.data);

            push_message.set_template_packet(push_packet);
            send_message(push_message, other_client_fd);

            log(LogType::INFO, "End anonymous chat successfully", conn_fd);
        }
    }

    response_message.set_template_packet(response_packet);
    send_message(response_message, conn_fd);
}

void Server::handle_close_client_connection(int conn_fd) {
    log(LogType::INFO, "Close connection", conn_fd);
    remove_client(conn_fd, false);

    // Send response to client
    Message response_message;
    MessagePacket response_packet(MessageType::RESPONSE);
    response_packet.response_header.response_type = ResponseType::SUCCESS;
    strcpy(response_packet.data, "Close connection successfully");
    response_packet.data_length = strlen(response_packet.data);

    response_message.set_template_packet(response_packet);
    send_message(response_message, conn_fd);

    // Close connection
    FD_CLR(conn_fd, &_master);
    _num_clients--;
    close(conn_fd);
}

void Server::handle_get_chat_list(Message& message, int conn_fd) {
    MessagePacket response_packet(MessageType::RESPONSE);
    Message response_message;

    log(LogType::INFO, "Send get chat list request to server", conn_fd);

    int user_id = message.get_request_sender();
    auto it = _online_user_list.find(user_id);
    if (it == _online_user_list.end()) {
        response_packet.response_header.response_type = ResponseType::FAILURE;
        strcpy(response_packet.data, "Can not find user");
        response_packet.data_length = strlen(response_packet.data);

        log(LogType::WARNING, response_packet.data, conn_fd);
    } else {
        User *user = it->second;
        std::pair<bool, std::string> ret = user->get_chat_list(_sql_query, response_packet);

        if (ret.first == false) {
            log(LogType::WARNING, response_packet.data, conn_fd);
        } else {
            if (response_packet.response_header.response_type == ResponseType::SUCCESS) {
                response_packet.response_header.response_type = ResponseType::GET_CHAT_LIST_SUCCESS;
                log(LogType::INFO, "Get chat list successfully", conn_fd);

                response_message.set_data(ret.second, response_packet);
                send_message(response_message, conn_fd);
                return;
            } else if (response_packet.response_header.response_type == ResponseType::FAILURE) {
                log(LogType::WARNING, response_packet.data, conn_fd);
            } else {
                log(LogType::ERROR, response_packet.data, conn_fd);
            }
        }
    }

    response_message.set_template_packet(response_packet);
    send_message(response_message, conn_fd);
}

void Server::handle_add_to_group_chat(Message& message, int conn_fd) {
    MessagePacket response_packet(MessageType::RESPONSE);
    Message response_message;

    log(LogType::INFO, "Send invite to group chat request to server", conn_fd);

    int user_id = message.get_request_sender();
    auto it = _online_user_list.find(user_id);
    if (it == _online_user_list.end()) {
        response_packet.response_header.response_type = ResponseType::FAILURE;
        strcpy(response_packet.data, "Can not find user");
        response_packet.data_length = strlen(response_packet.data);

        log(LogType::WARNING, response_packet.data, conn_fd);
    } else {
        // received data = <group_id_len>:<group_id><num_users>:<user_id_1>:<user_id_2>:...:<user_id_n>
        auto [group_id, user_ids] = parse_add_to_group_data(message.get_data());

        for (int receiver_user_id : user_ids) {
            std::string other_user_id = std::to_string(receiver_user_id);
            std::string query = "SELECT * FROM `Membership` WHERE `user_id` = " + other_user_id + " AND `chat_id` = " + group_id;
            MYSQL_RES *res;

            _sql_query.query(query, response_packet);
            if (_sql_query.is_select_successful() == false) {
                response_packet.response_header.response_type = ResponseType::ERROR;
                strcpy(response_packet.data, "Internal server error");
                response_packet.data_length = strlen(response_packet.data);
            } else {
                // if other user is already in group chat then the query return multiple rows
                res = _sql_query.get_result();
                if (mysql_num_rows(res) > 0) {
                    response_packet.response_header.response_type = ResponseType::ADD_TO_GROUP_CHAT_FAILURE;
                    strcpy(response_packet.data, other_user_id.c_str());
                    response_packet.data_length = strlen(response_packet.data);

                    log(LogType::WARNING, response_packet.data, conn_fd);
                } else {
                    // add user to group chat
                    query = "INSERT INTO `Membership` (`user_id`, `chat_id`) VALUES (" + other_user_id + ", " + group_id + ")";
                    _sql_query.query(query, response_packet);

                    if (_sql_query.is_insert_successful() == false) {
                        response_packet.response_header.response_type = ResponseType::ERROR;
                        strcpy(response_packet.data, "Internal server error");
                        response_packet.data_length = strlen(response_packet.data);
                    } else {
                        // get all user in group chat
                        query = "SELECT `m`.`user_id`, `a`.`display_name`, `c`.`name` FROM `Membership` `m` JOIN `Account` `a` ON `m`.`user_id` = `a`.`id` JOIN `Chat` `c` ON `m`.`chat_id` = `c`.`id` WHERE `chat_id` = " + group_id;
                        _sql_query.query(query, response_packet);

                        if (_sql_query.is_select_successful() == false) {
                            response_packet.response_header.response_type = ResponseType::ERROR;
                            strcpy(response_packet.data, "Internal server error");
                            response_packet.data_length = strlen(response_packet.data);
                        } else {
                            res = _sql_query.get_result();
                            int num_rows = mysql_num_rows(res);
                            int *group_mem_ids = new int[num_rows];
                            int i = 0;
                            std::string added_user_display_name, group_name;
                            MYSQL_ROW row;
                            while ((row = mysql_fetch_row(res))) {
                                group_mem_ids[i] = std::stoi(row[0]);
                                i++;
                                if (std::stoi(row[0]) == receiver_user_id) {
                                    added_user_display_name = row[1];
                                    group_name = row[2];
                                }
                            }

                            // forward information to all users in group chat, including new user
                            MessagePacket push_packet(MessageType::PUSH), push_packet_chat_members(MessageType::PUSH);
                            Message push_message, push_message_chat_members;

                            push_packet.push_header.push_type = PushType::GROUP_CHAT_JOINED;
                            push_packet.push_header.sender = user_id;
                            // data = <group_id_length>:<group_id><group_name_length>:<group_name>
                            std::string push_data = std::to_string(group_id.length()) + ":" + group_id + std::to_string(group_name.length()) + ":" + group_name;
                            strcpy(push_packet.data, push_data.c_str());
                            push_packet.data_length = strlen(push_packet.data);
                            push_message.set_template_packet(push_packet);

                            push_packet_chat_members.push_header.push_type = PushType::GROUP_CHAT_NEW_MEMBER;
                            push_packet_chat_members.push_header.sender = user_id;
                            // data = <added_user_display_name>
                            strcpy(push_packet_chat_members.data, added_user_display_name.c_str());
                            push_packet_chat_members.data_length = strlen(push_packet_chat_members.data);
                            push_message_chat_members.set_template_packet(push_packet_chat_members);

                            for (int i = 0; i < num_rows; i++) {
                                if (group_mem_ids[i] == user_id) {
                                    continue;
                                }                               

                                auto it_forward = _online_user_list.find(group_mem_ids[i]);
                                if (it_forward != _online_user_list.end()) {
                                    int push_fd = _user_id_to_socket[group_mem_ids[i]];
                                    if (group_mem_ids[i] == receiver_user_id) {
                                        send_message(push_message, push_fd);
                                    } else {
                                        send_message(push_message_chat_members, push_fd);
                                    }
                                }
                                
                            }

                            // send response to sender
                            response_packet.response_header.response_type = ResponseType::ADD_TO_GROUP_CHAT_SUCCESS;
                            strcpy(response_packet.data, other_user_id.c_str());
                            response_packet.data_length = strlen(response_packet.data);

                            log(LogType::INFO, "Add user to group chat successfully", conn_fd);
                        }
                        _sql_query.free_result();
                    }
                }
                response_message.set_template_packet(response_packet);
                send_message(response_message, conn_fd);
            }
        }        
        return;
    }

    response_message.set_template_packet(response_packet);
    send_message(response_message, conn_fd);
}

void Server::handle_leave_group_chat(Message& message, int conn_fd) {
    MessagePacket response_packet(MessageType::RESPONSE);
    Message response_message;

    log(LogType::INFO, "Send leave group chat request to server", conn_fd);

    int user_id = message.get_request_sender();
    auto it = _online_user_list.find(user_id);
    if (it == _online_user_list.end()) {
        response_packet.response_header.response_type = ResponseType::FAILURE;
        strcpy(response_packet.data, "Can not find user");
        response_packet.data_length = strlen(response_packet.data);

        log(LogType::WARNING, response_packet.data, conn_fd);        
    } else {
        std::string group_id_str = message.get_data();
        std::string query = "DELETE FROM `Membership` WHERE `user_id` = " + std::to_string(user_id) + " AND `chat_id` = " + group_id_str;
        _sql_query.query(query, response_packet);

        if (_sql_query.is_delete_successful() == false) {
            response_packet.response_header.response_type = ResponseType::ERROR;
            strcpy(response_packet.data, "Internal server error");
            response_packet.data_length = strlen(response_packet.data);
        } else {
            response_packet.response_header.response_type = ResponseType::LEAVE_GROUP_CHAT_SUCCESS;
            log(LogType::INFO, "Leave group chat successfully", conn_fd);

            // forward information to other users in group chat
            MessagePacket push_packet(MessageType::PUSH);
            Message push_message;
            push_packet.push_header.push_type = PushType::GROUP_CHAT_LEFT;
            push_packet.push_header.sender = user_id;
            std::string user_id_str = it->second->get_display_name();
            strcpy(push_packet.data, user_id_str.c_str());
            push_packet.data_length = strlen(push_packet.data);
            push_message.set_template_packet(push_packet);

            query = "SELECT `user_id` FROM `Membership` WHERE `chat_id` = " + group_id_str;
            _sql_query.query(query, response_packet);

            if (_sql_query.is_select_successful() == false) {
                response_packet.response_header.response_type = ResponseType::ERROR;
                strcpy(response_packet.data, "Internal server error");
                response_packet.data_length = strlen(response_packet.data);
            } else {
                MYSQL_RES *res = _sql_query.get_result();
                MYSQL_ROW row;
                while ((row = mysql_fetch_row(res)) != NULL) {
                    int receiver_user_id = std::stoi(row[0]);
                    if (receiver_user_id != user_id) {
                        // only forward to online users
                        if (_online_user_list.find(receiver_user_id) == _online_user_list.end()) {
                            continue;
                        }
                        int receive_fd = _user_id_to_socket[receiver_user_id];
                        send_message(push_message, receive_fd);
                    }
                }
            }
        }
    }

    response_message.set_template_packet(response_packet);
    send_message(response_message, conn_fd);
}

void Server::handle_get_group_chat_members(Message& message, int conn_fd) {
    MessagePacket response_packet(MessageType::RESPONSE);
    Message response_message;

    log(LogType::INFO, "Send get group chat member list request to server", conn_fd);

    int user_id = message.get_request_sender();
    auto it = _online_user_list.find(user_id);
    if (it == _online_user_list.end()) {
        response_packet.response_header.response_type = ResponseType::FAILURE;
        strcpy(response_packet.data, "Can not find user");
        response_packet.data_length = strlen(response_packet.data);

        log(LogType::WARNING, response_packet.data, conn_fd);        
    } else {
        std::string group_id_str = message.get_data();
        std::string query = "SELECT `a`.`id`, `a`.`display_name` FROM `Membership` `m` JOIN `Account` `a` ON `m`.`user_id` = `a`.`id` WHERE `chat_id` = " + group_id_str;
        _sql_query.query(query, response_packet);

        if (_sql_query.is_select_successful() == false) {
            response_packet.response_header.response_type = ResponseType::ERROR;
            strcpy(response_packet.data, "Internal server error");
            response_packet.data_length = strlen(response_packet.data);

            log(LogType::ERROR, response_packet.data, conn_fd);
        } else {
            MYSQL_RES *res = _sql_query.get_result();
            MYSQL_ROW row;
            int num_rows = mysql_num_rows(res);
            response_packet.response_header.response_type = ResponseType::GET_GROUP_CHAT_MEMBERS_SUCCESS;

            // send data of the form: <num_members_length>:<num_members><user_1><user_2>...
            // where <user_i> = <user_id_length>:<user_id><display_name_length>:<display_name>
            std::string data = std::to_string(std::to_string(num_rows).length()) + ":" + std::to_string(num_rows);
            while ((row = mysql_fetch_row(res)) != NULL) {
                std::string user_id_str = row[0];
                std::string display_name = row[1];
                data += std::to_string(user_id_str.length()) + ":" + user_id_str;
                data += std::to_string(display_name.length()) + ":" + display_name;
            }

            log(LogType::INFO, "Get group chat member list successfully", conn_fd);

            response_message.set_data(data, response_packet);
            send_message(response_message, conn_fd);
            return;
        }
    }

    response_message.set_template_packet(response_packet);
    send_message(response_message, conn_fd);
}

void Server::handle_get_chat_messages(Message& message, int conn_fd) {
    MessagePacket response_packet(MessageType::RESPONSE);
    Message response_message;

    log(LogType::INFO, "Send get chat messages request to server", conn_fd);

    int user_id = message.get_request_sender();
    auto it = _online_user_list.find(user_id);
    if (it == _online_user_list.end()) {
        response_packet.response_header.response_type = ResponseType::FAILURE;
        strcpy(response_packet.data, "Can not find user");
        response_packet.data_length = strlen(response_packet.data);

        log(LogType::WARNING, response_packet.data, conn_fd);        
    } else {
        auto [chat_id_str, num_messages] = parse_get_chat_messages_request(message.get_data());
        std::string query = "SELECT * FROM (SELECT `id`, `chat_id`, `type`, `content`, `time_created`, `sender_id` FROM `Message` WHERE `chat_id` = " + chat_id_str 
                            + " ORDER BY `id` DESC LIMIT " + std::to_string(num_messages) + ") AS subquery "
                            + "ORDER BY `id` ASC;";
        _sql_query.query(query, response_packet);

        if (_sql_query.is_select_successful() == false) {
            response_packet.response_header.response_type = ResponseType::ERROR;
            strcpy(response_packet.data, "Internal server error");
            response_packet.data_length = strlen(response_packet.data);

            log(LogType::ERROR, response_packet.data, conn_fd);
        } else {
            MYSQL_RES *res = _sql_query.get_result();
            MYSQL_ROW row;
            int num_rows = mysql_num_rows(res);

            // send data of the form: <num_messages_length>:<num_messages><message_1><message_2>...
            // where <message_i> = <msg_id_length>:<msg_id><chat_id_length>:<chat_id><data_type><content_length>:<content><time_created_length>:<time_created><sender_id_length>:<sender_id>
            // where <data_type> = 'T' or 'F'
            std::string data = std::to_string(std::to_string(num_rows).length()) + ":" + std::to_string(num_rows);
            while ((row = mysql_fetch_row(res)) != NULL) {
                std::string msg_id_str = row[0];
                std::string chat_id_str = row[1];
                std::string data_type = row[2];
                std::string content = row[3];
                std::string time_created = row[4];
                std::string sender_id_str = row[5];

                data += std::to_string(msg_id_str.length()) + ":" + msg_id_str;
                data += std::to_string(chat_id_str.length()) + ":" + chat_id_str;
                data += (strcmp(data_type.c_str(), "TEXT") == 0) ? "T" : "F";
                data += std::to_string(content.length()) + ":" + content;
                data += std::to_string(time_created.length()) + ":" + time_created;
                data += std::to_string(sender_id_str.length()) + ":" + sender_id_str;
            }

            log(LogType::INFO, "Get chat messages successfully", conn_fd);

            response_packet.response_header.response_type = ResponseType::GET_CHAT_MESSAGES_SUCCESS;
            response_message.set_data(data, response_packet);
            send_message(response_message, conn_fd);
            _sql_query.free_result();
            return;
        }
        _sql_query.free_result();
    }

    response_message.set_template_packet(response_packet);
    send_message(response_message, conn_fd);
}

