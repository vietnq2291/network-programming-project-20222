#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <iostream>
#include <arpa/inet.h>

#include "common.h"

class client: public QObject
{
    Q_OBJECT
public:
    client(int port, std::string ip);

    void connect();
    void start();
    void send_chat_message(std::string buff, int chat_id, ChatType chat_type, DataType data_type);
    void send_request_message(std::string buff);
    void receive_message();
    void stop();

signals:
    void messageReceived();

private:
    int _conn_fd;
    int _server_port;
    std::string _server_ip;
    struct sockaddr_in _server_addr;

    fd_set _read_fds;

    int _user_id; // user id of the current user or -1 if the user has not logged in
    std::string _display_name; // username of the current user or "" if the user has not logged in
};

#endif // CLIENT_H
