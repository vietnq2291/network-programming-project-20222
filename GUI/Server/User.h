#ifndef USER_H
#define USER_H

#include <string>
#include <vector>
#include <mysql/mysql.h>

#include "common.h"
#include "SQLQuery.h"

class User {
public:
    User(std::string username);

    static User *signup(std::string username, std::string password, std::string display_name, SQLQuery sql_query, MessagePacket& response_packet);

    bool authenticate(std::string password, SQLQuery sql_query, MessagePacket& response_packet);
    bool update_account(std::string field, std::string value, SQLQuery sql_query, MessagePacket& response_packet);
    bool check_friend(std::string friend_username, SQLQuery sql_query, MessagePacket& response_packet, std::string& data, int& receiver_id);
    bool add_friend(std::string friend_username, SQLQuery sql_query, MessagePacket& response_packet);
    bool remove_friend(std::string friend_id, SQLQuery sql_query, MessagePacket& response_packet);
    std::pair<bool, std::vector<std::pair<int, std::string>>> get_friend_list(SQLQuery sql_query, MessagePacket& response_packet);
    std::pair<bool, std::string> get_chat_list(SQLQuery sql_query, MessagePacket& response_packet);

    int get_id() { return _id; }
    std::string get_username() { return _username; }
    std::string get_display_name() { return _display_name; }

private:
    int _id;
    std::string _username;
    std::string _display_name;

    std::vector<std::string> _friend_list;
};

#endif // USER_H
