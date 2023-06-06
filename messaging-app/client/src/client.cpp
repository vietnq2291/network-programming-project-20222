#include <iostream>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/select.h>

#include "../include/client.h"
#include "../../shared/common.h"

Client::Client(int port, std::string ip) {
    _server_port = port;
    _server_ip = ip;

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
        std::cerr << "Can not connect to server" << std::endl;
        exit(1);
    }

    std::cout << "Connected to server at " << _server_ip << ":" << _server_port << std::endl;
}

void Client::start() {
    char buff[BUFF_SIZE];
    
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

        if (rv == -1)
        {
            perror("select"); // error occurred in select()
        }
        else
        {
            // one or both of the descriptors have data
            if (FD_ISSET(STDIN_FILENO, &_read_fds))
            {
                std::cin.getline(buff, BUFF_SIZE);
                send_message(buff);
            }

            if (FD_ISSET(_conn_fd, &_read_fds))
            {
                receive_message(buff);
            }
        }
    }
}

void Client::stop() {
    std::cout << "Client stopped" << std::endl;
    close(_conn_fd);
    exit(0);
}

void Client::send_message(char *buff) {
    if (send(_conn_fd, buff, strlen(buff), 0) < 0) {
        std::cerr << "Can not send message" << std::endl;
        stop();
    }
}

void Client::receive_message(char *buff) {

    int bytes_received = recv(_conn_fd, buff, BUFF_SIZE - 1, 0);
    if (bytes_received < 0) {
        std::cerr << "Error: receive failed!" << std::endl;
    } else if (bytes_received == 0) {
        std::cerr << "Error: server closed connection!" << std::endl;
    } else {
        buff[bytes_received] = '\0';
        std::cout << "Reply: " << buff << std::endl;
    }
}
