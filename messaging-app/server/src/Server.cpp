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
}

void Server::start() {
    listen();
    
    while (true) {
        _read_fds = _master;
        if (select(_fdmax + 1, &_read_fds, NULL, NULL, NULL) == -1) {
            std::cerr << "Can not select" << std::endl;
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

    // Connect to the MySQL database
    if (_sql_query.connect(database_host, database_user, database_password, database_name) == false) {
        stop();
    }
}

void Server::listen() {
    // listen for incoming connection
    if (::listen(_listen_fd, _backlog) == -1) {
        std::cerr << "Can not listen on socket" << std::endl;
        exit(1);
    }
}

void Server::accept() {
    socklen_t sin_size;
    struct sockaddr_in client_addr;
    int conn_fd;

    // accept new connection
    sin_size = sizeof(client_addr);
    if ((conn_fd = ::accept(_listen_fd, (struct sockaddr *)&client_addr, &sin_size)) == -1) {
        std::cerr << "Can not accept new connection" << std::endl;
    } else {
        FD_SET(conn_fd, &_master);
        if (conn_fd > _fdmax) {
            _fdmax = conn_fd;
        }
        std::cout << "New connection from " << inet_ntoa(client_addr.sin_addr) << " on socket " << conn_fd << std::endl;
    }
}

void Server::stop() {
    std::cout << "Stopping server..." << std::endl;
    _sql_query.disconnect();
    close(_listen_fd);
    exit(0);
}

void Server::receive_message(int conn_fd) {
    int bytes_received;
    MessagePacket packet;

    if ((bytes_received = recv(conn_fd, &packet, sizeof(packet), 0)) <= 0) {
        if (bytes_received == 0) {
            std::cout << "Socket " << conn_fd << " hung up" << std::endl;
            remove_client(conn_fd);
        } else {
            std::cerr << "Can not receive message from socket " << conn_fd << std::endl;
        }
        close(conn_fd);
        FD_CLR(conn_fd, &_master);
    } else {
        if (packet.type == MessageType::CHAT) {
            process_data_message(packet);
        } else if (packet.type == MessageType::REQUEST) {
            process_request_message(packet, conn_fd);
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
    close(conn_fd);
}

void Server::process_data_message(MessagePacket& packet) {
    Message *message_ptr = nullptr;
    bool found = false;

    // check if packet is a part of a previous message
    for (auto it = _message_list.begin(); it != _message_list.end(); it++) {
        if ((*it).find(packet) == true) {
            (*it).add_packet(packet);

            if ((*it).get_fin() == 0) 
                return;

            found = true;
            message_ptr = &(*it);
            _message_list.erase(it);
            break;
        }
    }
    if (found == false) {
        Message new_message(packet);
        _message_list.push_back(new_message);
        if (packet.chat_header.fin == 0) 
            return;
        message_ptr = &new_message;
    }

    // TODO: insert into database...

    // forward message to receiver
    switch (packet.chat_header.chat_type) {
        case ChatType::PRIVATE_CHAT:
            std::cout << "send from (user id, socket): (" << (*message_ptr).get_sender() << ", " << _user_id_to_socket[packet.chat_header.receiver] << ") to user id: " << packet.chat_header.receiver << std::endl;
            send_chat_message(*message_ptr, _user_id_to_socket[packet.chat_header.receiver]);
            break;
    }

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

void Server::send_chat_message(Message& message, int conn_fd) {
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

void Server::process_request_message(MessagePacket& request_packet, int conn_fd) {
    switch (request_packet.request_header.request_type) {
        case RequestType::LOGIN:
            handle_login(request_packet, conn_fd);
            break;
        case RequestType::SIGNUP:
            handle_signup(request_packet, conn_fd);
            break;
        case RequestType::LOGOUT:
            handle_logout(request_packet, conn_fd);
            break;
        case RequestType::UPDATE_ACCOUNT:
            handle_update_account(request_packet, conn_fd);
            break;
        default:
            break;
    }
}

void Server::handle_login(MessagePacket& request_packet, int conn_fd) {
    MessagePacket response_packet(MessageType::RESPONSE);

    // parse username and password
    std::string auth_data(request_packet.data, request_packet.data + request_packet.data_length);
    std::string username, password;
    std::tie(username, password) = parse_auth_data(auth_data);

    // check if username and password are valid
    if (_online_user_list.find(username) != _online_user_list.end()) {
        // user is already logged in
        response_packet.response_header.response_type = ResponseType::FAILURE;
        strcpy(response_packet.data, "Account is already logged in on another device");
        response_packet.data_length = strlen(response_packet.data);
    } else {
        User *user = new User(username);
        if (user->authenticate(password, _sql_query, response_packet) == false) {
            stop();
        }
        
        if (response_packet.response_header.response_type == ResponseType::LOGIN_SUCCESS) {
            // add user to online user list
            _online_user_list.insert(std::pair<std::string, User*>(username, user));
            _online_user_list.insert(std::pair<int, User*>(user->get_id(), user));

            // map socket to user
            _user_id_to_socket[user->get_id()] = conn_fd;
        }
    }

    if (send(conn_fd, &response_packet, sizeof(response_packet), 0) < 0) {
        std::cerr << "Can not send message" << std::endl;
        stop();
    }
}

void Server::handle_signup(MessagePacket& request_packet, int conn_fd) {
    // parse username and password and display_name
    std::string auth_data(request_packet.data, request_packet.data + request_packet.data_length);
    std::string username, password, display_name;
    std::tie(username, password, display_name) = parse_signup_data(auth_data);

    MessagePacket response_packet(MessageType::RESPONSE);

    User *user = User::signup(username, password, display_name, _sql_query, response_packet);

    if (send(conn_fd, &response_packet, sizeof(response_packet), 0) < 0) {
        std::cerr << "Can not send message" << std::endl;
        stop();
    }
}

void Server::handle_logout(MessagePacket& request_packet, int conn_fd) {
    MessagePacket response_packet(MessageType::RESPONSE);

    int user_id = request_packet.request_header.sender;
    auto it = _online_user_list.find(user_id);
    if (it == _online_user_list.end()) {
        response_packet.response_header.response_type = ResponseType::FAILURE;
        strcpy(response_packet.data, "Can not find user");
        response_packet.data_length = strlen(response_packet.data);
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
    }

    if (send(conn_fd, &response_packet, sizeof(response_packet), 0) < 0) {
        std::cerr << "Can not send message" << std::endl;
        stop();
    }
}

void Server::handle_update_account(MessagePacket& request_packet, int conn_fd) {
    MessagePacket response_packet(MessageType::RESPONSE);

    // get user id
    int user_id = request_packet.request_header.sender;
    auto it = _online_user_list.find(user_id);
    if (it == _online_user_list.end()) {
        response_packet.response_header.response_type = ResponseType::FAILURE;
        strcpy(response_packet.data, "You are not logged in");
        response_packet.data_length = strlen(response_packet.data);
    } else {
        // data is of the form: <type><data_len>:<data>, where type is either 'P' (password) or 'N' (display name)
        std::string field, data;
        std::tie(field, data) = parse_update_account_data(std::string(request_packet.data, request_packet.data + request_packet.data_length));
        it->second->update_account(field, data, _sql_query, response_packet);
    }

    if (send(conn_fd, &response_packet, sizeof(response_packet), 0) < 0) {
        std::cerr << "Can not send message" << std::endl;
        stop();
    }
}

