#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>
#include <arpa/inet.h>
#include <map>
#include <vector>

#include "../../shared/common.h"

class Client {
public:
    Client(int port, std::string ip, std::string folder_path);

    void connect();
    void start();
    void send_chat_message(std::string buff, int chat_id, ChatType chat_type, DataType data_type);
    void send_request_message(std::string buff);
    void receive_message();
    void stop();
    int process_chat_packet(MessagePacket& packet);
    void process_friend_list(std::string& data);
    void write_buff(std::string& data);
    void clean_buff();

private:
    int _conn_fd;
    int _server_port;
    std::string _server_ip;
    struct sockaddr_in _server_addr;
    std::string _buff;

    fd_set _read_fds;

    int _user_id; // user id of the current user or -1 if the user has not logged in
    std::string _display_name; // username of the current user or "" if the user has not logged in
    std::map<int, std::vector<ChatMessage>> chat_map;
    std::string _folder_path;
    std::vector<Friend> _friend_list;
};

#endif // CLIENT_H
