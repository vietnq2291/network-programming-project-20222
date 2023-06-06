#include <iostream>
#include <arpa/inet.h>

#ifndef CLIENT_H
#define CLIENT_H

class Client {
public:
    Client(int port, std::string ip);

    void connect();
    void start();
    void send_message(char *buff);
    void receive_message(char *buff);
    void stop();

private:
    int _conn_fd;
    int _server_port;
    std::string _server_ip;
    struct sockaddr_in _server_addr;

    fd_set _read_fds;
};

#endif
