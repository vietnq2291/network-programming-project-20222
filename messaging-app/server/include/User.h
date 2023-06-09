#ifndef USER_H
#define USER_H

#include <string>
#include <vector>
#include <mysql/mysql.h>

class User {
public:
    User(std::string username);

    bool authenticate(std::string password, MYSQL *conn_db);

private:
    int id;
    std::string _username;

    std::vector<std::string> _friend_list;
};

#endif // USER_H