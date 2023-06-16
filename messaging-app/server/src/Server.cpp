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
            remove_client(conn_fd);
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
            if ((*it).is_match_header(packet) == true) {
                (*it).add_packet(packet);


                if ((*it).is_complete() == false)
                    return;

                found = true;
                message_ptr = &(*it);
                _message_list.erase(it);
                break;
            }
        }
        if (found == false) {
            message_ptr = new Message(packet);
            if (message_ptr->is_complete() == false) {
                _message_list.push_back(*message_ptr);
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

void Server::remove_client(int conn_fd) {
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
    FD_CLR(conn_fd, &_master);
    _num_clients--;
    close(conn_fd);
}

void Server::process_chat_message(Message& message, int conn_fd) {
    MessagePacket response_packet(MessageType::RESPONSE);  
    Message response_message;  

    // Insert to database
    bool is_saved = message.save(_sql_query, response_packet);
    response_message.set_template_packet(response_packet);
    send_message(response_message, conn_fd);
    if (is_saved == false) {
        log(LogType::ERROR, "Can not save message to database", conn_fd);
        return;
    }

    // TODO: Forward message to receiver

    // send response to sender
    // if (send(packet.chat_header.sender, &response_packet, sizeof(response_packet), 0) < 0) {
    //     std::cerr << "Can not send response to sender" << std::endl;
    //     stop();
    // }

    // sent to all clients (for testing purpose)
    // std::cout << "Socket " << (*message_ptr).get_sender() << " sent message" << std::endl;
    // MessagePacket cur_packet;
    // for (int i = 0; i <= _fdmax; i++) {
    //     if (FD_ISSET(i, &_master)) {
    //         if (i != _listen_fd && i != (*message_ptr).get_sender()) {
    //             while ((*message_ptr).get_next_packet(cur_packet)) {
    //                 if (send(i, &cur_packet, sizeof(cur_packet), 0) < 0) {
    //                     std::cerr << "Can not send message" << std::endl;
    //                     stop();
    //                 }
    //             }
    //         }
    //     }
    // }
}

// set default value for message argument
void Server::send_message(Message& message, int conn_fd) {
    MessagePacket packet;
    if (FD_ISSET(conn_fd, &_master)) {
        while (message.get_next_packet(packet)) {
            if (send(conn_fd, &packet, sizeof(packet), 0) < 0) {
                std::cerr << "Can not send message" << std::endl;
                stop();
            }
        }
    }
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
                    log(LogType::ERROR, "Can not create private chat", conn_fd);
                } else {
                    _sql_query.next_result(); // skip the first result to get last insert id
                    if (_sql_query.is_select_successful() == false) {
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
                            log(LogType::ERROR, "Can not create private chat", conn_fd);
                        } else {
                            response_packet.response_header.response_type = ResponseType::SUCCESS;
                            sprintf(response_packet.data, "%d", chat_id);
                            response_packet.data_length = strlen(response_packet.data);

                            log(LogType::INFO, response_packet.data, conn_fd);
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
            response_packet.response_header.response_type = ResponseType::FAILURE;
            strcpy(response_packet.data, "Failed to query database");
            response_packet.data_length = strlen(response_packet.data);
            
            log(LogType::ERROR, response_packet.data, conn_fd);
        }

        _sql_query.free_result();
    }

    response_message.set_template_packet(response_packet);
    send_message(response_message, conn_fd);   
}


