#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>
#include <arpa/inet.h>

#include "../../shared/common.h"

class Client {
public:
    Client(int port, std::string ip);

    void connect();
    void start();
    void send_data_message(std::string buff, int receiver, ChatType chat_type, DataType data_type);
    void send_request_message(std::string buff);
    void receive_message();
    void stop();

private:
    int _conn_fd;
    int _server_port;
    std::string _server_ip;
    struct sockaddr_in _server_addr;

    fd_set _read_fds;
};

#endif // CLIENT_H
