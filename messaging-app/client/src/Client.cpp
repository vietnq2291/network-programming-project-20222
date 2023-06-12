#include <iostream>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/select.h>

#include "../include/Client.h"
#include "../include/Message.h"
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
            perror("select"); // error occurred in select()
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
                    send_data_message(buff, 0, ChatType::PRIVATE_CHAT, DataType::TEXT);
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

void Client::send_data_message(std::string buff, int receiver, ChatType chat_type, DataType data_type) {
    Message message(buff, 0, receiver, chat_type, data_type, time(NULL)); // set sender = 0 because this attribute is not used for message sent from client to server
    MessagePacket packet;

    while (message.get_next_packet(packet)) {
        if (send(_conn_fd, &packet, sizeof(packet), 0) < 0) {
            std::cerr << "Can not send message" << std::endl;
            stop();
        }
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
        std::cout << "Received message: (fin, seq, data) = " << "(" << packet.chat_header.fin << ", " << packet.chat_header.seq << ", " << packet.data << ")" << std::endl;
    }
}

void Client::send_request_message(std::string buff) {
    Message *message_ptr;
    MessagePacket packet;

    if (buff[2] == 'L') {
        // buff = R L <username> <password>
        std::string auth_data = buff.substr(4, buff.length() - 4);
        message_ptr = new Message(auth_data, RequestType::LOGIN);
    } else if (buff[2] == 'R') {
        // buff = R R <username> <password> <display_name>
        std::string signup_data = buff.substr(4, buff.length() - 4);
        message_ptr = new Message(signup_data, RequestType::SIGNUP);
    } else if (buff[2] == 'X') {
        message_ptr = new Message(RequestType::LOGOUT);        
    }

    while ((*message_ptr).get_next_packet(packet)) {
        if (send(_conn_fd, &packet, sizeof(packet), 0) < 0) {
            std::cerr << "Can not send message" << std::endl;
            stop();
        }
    }
}