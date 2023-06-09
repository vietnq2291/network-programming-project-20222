#include <iostream>
#include <cstring>
#include <mysql/mysql.h>
#include <arpa/inet.h>

#include "../include/User.h"
#include "../../shared/common.h"

User::User(std::string username) {
    _username = username;
}

bool User::authenticate(std::string password, SQLQuery sql_query, MessagePacket& response_packet) {
    std::string query = "SELECT * FROM Account WHERE username = '" + _username + "'";
    MYSQL_RES *result;

    sql_query.query(query, response_packet);
    if ((result = sql_query.get_result()) == NULL) {
        return false;
    }

    MYSQL_ROW row;
    if ((row = mysql_fetch_row(result))) {
        if (row[2] == password) {
            // password is correct
            _id = atoi(row[0]);

            response_packet.response_header.response_type = ResponseType::SUCCESS;
            strcpy(response_packet.data, "Login success");
            response_packet.data_length = strlen(response_packet.data);
        } else {
            // password is incorrect
            response_packet.response_header.response_type = ResponseType::FAILURE;
            strcpy(response_packet.data, "Password is incorrect");
            response_packet.data_length = strlen(response_packet.data);
        }
    } else {
        // user does not exist
        response_packet.response_header.response_type = ResponseType::FAILURE;
        strcpy(response_packet.data, "Account does not exist");
        response_packet.data_length = strlen(response_packet.data);
    }
    
    mysql_free_result(result);
    return true;
}

User *User::signup(std::string username, std::string password, std::string display_name, SQLQuery sql_query, MessagePacket& response_packet) {
    // check if username is not taken
    std::string query = "SELECT * FROM Account WHERE username = '" + username + "'";
    MYSQL_RES *result;

    sql_query.query(query, response_packet);
    if ((result = sql_query.get_result()) == NULL) {
        return NULL;
    }

    User *user = NULL;
    MYSQL_ROW row;
    if ((row = mysql_fetch_row(result))) {
        // username is taken
        response_packet.response_header.response_type = ResponseType::FAILURE;
        strcpy(response_packet.data, "Username is taken");
        response_packet.data_length = strlen(response_packet.data);
    } else {
        // username is not taken
        query = "INSERT INTO Account (username, password, display_name, status, time_created) VALUES ('" 
                + username + "', '" + password + "', '" + display_name + "', '" + "ACTIVE" 
                + "', FROM_UNIXTIME(" + std::to_string(time(0)) + "))";

        sql_query.query(query, response_packet);
        if (sql_query.is_insert_successful()) {
            // insert successful
            user = new User(username);
            response_packet.response_header.response_type = ResponseType::SUCCESS;
            strcpy(response_packet.data, "Signup success");
            response_packet.data_length = strlen(response_packet.data);
        } else {
            // insert failed
            response_packet.response_header.response_type = ResponseType::ERROR;
            strcpy(response_packet.data, "Internal server error");
            response_packet.data_length = strlen(response_packet.data);
        }
    }

    mysql_free_result(result);
    return user;
}
