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
    void stop();
    void remove_client(int conn_fd);

    void receive_message(int conn_fd);
    void process_chat_message(Message& message, int conn_fd);
    void process_request_message(Message& message, int conn_fd);
    
    void handle_login(Message& message, int conn_fd);
    void handle_signup(Message& message, int conn_fd);
    void handle_logout(Message& message, int conn_fd);
    void handle_update_account(Message& message, int conn_fd);
    bool send_message(Message& message, int conn_fd);
    void handle_create_private_chat(Message& message, int conn_fd);
    void handle_create_group_chat(Message& message, int conn_fd);

private:
    int _listen_fd;
    struct sockaddr_in _addr;
    int _port;
    int _backlog;
    int _num_clients;

    SQLQuery _sql_query;

    fd_set _master;
    fd_set _read_fds;
    int _fdmax;

    std::vector<Message> _message_list;
    std::map<std::variant<int, std::string>, User*> _online_user_list;
    std::map<int, int> _user_id_to_socket;
};

#endif // SERVER_H
