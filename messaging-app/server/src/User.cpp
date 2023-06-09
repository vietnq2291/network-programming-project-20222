#include <iostream>

#include "../include/User.h"

User::User(std::string username) {
    _username = username;
}

bool User::authenticate(std::string password, MYSQL *conn_db) {
    std::string query = "SELECT * FROM users WHERE username = '" + _username + "' AND password = '" + password + "'";
    if (mysql_query(conn_db, query.c_str())) {
        std::cerr << "Error: " << mysql_error(conn_db) << std::endl;
        exit(1);
    }

    MYSQL_RES *result = mysql_store_result(conn_db);
    if (result == NULL) {
        std::cerr << "Error: " << mysql_error(conn_db) << std::endl;
        exit(1);
    }

    int num_fields = mysql_num_fields(result);
    MYSQL_ROW row;
    if ((row = mysql_fetch_row(result))) {
        mysql_free_result(result);
        return true;
    } else {
        mysql_free_result(result);
        return false;
    }
}