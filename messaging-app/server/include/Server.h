#ifndef SERVER_H
#define SERVER_H

#include <iostream>
#include <arpa/inet.h>
#include <queue>
#include <map>
#include <variant>
#include <string>

#include "Message.h"
#include "User.h"
#include "SQLQuery.h"

class Server {
public:
    Server(int port, int backlog);
    
    void start();
    void connectdb();
    void listen();
    void accept();
    void receive_message(int conn_fd);
    void process_data_message(MessagePacket& packet);
    void process_request_message(MessagePacket& packet);
    void handle_login(MessagePacket& packet);
    void handle_signup(MessagePacket& packet);
    void handle_logout(MessagePacket& packet);
    // void handle_create_group();
    // void handle_leave_group();
    // void handle_private_chat();
    void handle_group_chat();
    void stop();

private:
    int _listen_fd;
    struct sockaddr_in _addr;
    int _port;
    int _backlog;

    SQLQuery _sql_query;

    fd_set _master;
    fd_set _read_fds;
    int _fdmax;

    std::vector<Message> _message_list;
    std::map<std::variant<int, std::string>, User> _online_user_list;
    std::map<int, int> _socket_to_user_id;
};

#endif // SERVER_H
