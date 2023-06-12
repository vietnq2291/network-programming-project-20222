#ifndef USER_H
#define USER_H

#include <string>
#include <vector>
#include <mysql/mysql.h>

#include "../../shared/common.h"
#include "SQLQuery.h"

class User {
public:
    User(std::string username);

    static User *signup(std::string username, std::string password, std::string display_name, SQLQuery sql_query, MessagePacket& response_packet);

    bool authenticate(std::string password, SQLQuery sql_query, MessagePacket& response_packet);

    int get_id() { return _id; }
    std::string get_username() { return _username; }

private:
    int _id;
    std::string _username;

    std::vector<std::string> _friend_list;
};

#endif // USER_H