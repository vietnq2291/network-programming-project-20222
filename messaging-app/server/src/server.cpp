#include <iostream>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>

#include "../include/server.h"
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
                    process_message(i);
                }
            }
        }
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
    close(_listen_fd);
    exit(0);
}

void Server::process_message(int conn_fd) {
    int bytes_received;
    char data[BUFF_SIZE];

    if ((bytes_received = recv(conn_fd, data, sizeof(data), 0)) <= 0) {
        if (bytes_received == 0) {
            std::cout << "Socket " << conn_fd << " hung up" << std::endl;
        } else {
            std::cerr << "Can not receive message from socket " << conn_fd << std::endl;
        }
        close(conn_fd);
        FD_CLR(conn_fd, &_master);
    } else {
        data[bytes_received] = '\0';
        std::cout << "Received message from socket " << conn_fd << ": " << data << std::endl;
        // send to all clients
        for (int i = 0; i <= _fdmax; i++) {
            if (FD_ISSET(i, &_master)) {
                if (i != _listen_fd && i != conn_fd) {
                    if (send(i, data, bytes_received, 0) == -1) {
                        std::cerr << "Can not send message to socket " << i << std::endl;
                    }
                }
            }
        }
    }
}
