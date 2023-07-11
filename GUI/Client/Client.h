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
    int process_chat_packet(MessagePacket& packet);
    void process_friend_list(std::string& data);
    void write_buff(std::string& data);
    void clean_buff();

signals:
    void messageReceived(ChatMessage Message);
    void authSuccess(std::vector<Friend> friend_list);

private slots:
    void setChat(QString chat_name);
    void sendMessage(QString packet);

private:
    int _conn_fd;
    int _server_port;
    std::string _server_ip;
    struct sockaddr_in _server_addr;
    std::string _buff;

    fd_set _read_fds;

    int _user_id; // user id of the current user or -1 if the user has not logged in
    int _chat_id; // chat id of the current chat
    std::string _display_name; // username of the current user or "" if the user has not logged in
    std::map<int, std::vector<ChatMessage>> chat_map;
    std::string _folder_path;
    std::vector<Friend> _friend_list;
};

#endif // CLIENT_H
