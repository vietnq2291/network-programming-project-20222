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
    _conn_db = mysql_init(NULL);
    if (!mysql_real_connect(_conn_db, database_host.c_str(), database_user.c_str(), database_password.c_str(), database_name.c_str(), 0, NULL, 0)) {
        std::cerr << "Error: " << mysql_error(_conn_db) << std::endl;
        exit(1);
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
    mysql_close(_conn_db);
    close(_listen_fd);
    exit(0);
}

void Server::receive_message(int conn_fd) {
    int bytes_received;
    MessagePacket packet;

    if ((bytes_received = recv(conn_fd, &packet, sizeof(packet), 0)) <= 0) {
        if (bytes_received == 0) {
            std::cout << "Socket " << conn_fd << " hung up" << std::endl;
        } else {
            std::cerr << "Can not receive message from socket " << conn_fd << std::endl;
        }
        close(conn_fd);
        FD_CLR(conn_fd, &_master);
    } else {
        if (packet.type == MessageType::DATA) {
            packet.chat_header.sender = conn_fd;
            process_data_message(packet);
        } else if (packet.type == MessageType::REQUEST) {
            packet.request_header.sender = conn_fd;
        }
    }
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

    // sent to all clients (for testing purpose)
    std::cout << "Socket " << (*message_ptr).get_sender() << " sent message" << std::endl;
    MessagePacket cur_packet;
    for (int i = 0; i <= _fdmax; i++) {
        if (FD_ISSET(i, &_master)) {
            if (i != _listen_fd && i != (*message_ptr).get_sender()) {
                while ((*message_ptr).get_next_packet(cur_packet)) {
                    if (send(i, &cur_packet, sizeof(cur_packet), 0) < 0) {
                        std::cerr << "Can not send message" << std::endl;
                        stop();
                    }
                }
            }
        }
    }
}

// void Server::process_request_message(Message& message) {   
// }
