#include <iostream>
#include <cstring>
#include <mysql/mysql.h>

#include "../include/User.h"
#include "../../shared/common.h"

User::User(std::string username) {
    _username = username;
}

bool User::authenticate(std::string password, SQLQuery sql_query, MessagePacket& response_packet) {
    std::string query = "SELECT * FROM Account WHERE username = '" + _username + "'";
    MYSQL_RES *result;

    sql_query.query(query, response_packet);
    if (sql_query.is_select_successful() == false) {
        return false;
    } else {
        result = sql_query.get_result();
    }

    MYSQL_ROW row;
    if ((row = mysql_fetch_row(result))) {
        if (row[2] == password) {
            // password is correct
            _id = atoi(row[0]);
            _display_name = row[3];

            response_packet.response_header.response_type = ResponseType::LOGIN_SUCCESS;
            sprintf(response_packet.data, "%ld:%s%ld:%s", strlen(row[0]), row[0], strlen(row[3]), row[3]);
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
    
    sql_query.free_result();
    return true;
}

bool User::update_account(std::string field, std::string value, SQLQuery sql_query, MessagePacket& response_packet) {
    std::string query = "UPDATE Account SET " + field + " = '" + value + "' WHERE username = '" + _username + "'";
    sql_query.query(query, response_packet);
    
    if (sql_query.is_update_successful()) {
        // update successful
        if (field == "display_name")
            _display_name = value;
        
        response_packet.response_header.response_type = ResponseType::SUCCESS;
        strcpy(response_packet.data, "Update successful");
        response_packet.data_length = strlen(response_packet.data);

        sql_query.free_result();
        return true;
    } else {
        // update failed
        response_packet.response_header.response_type = ResponseType::FAILURE;
        strcpy(response_packet.data, "Update failed");
        response_packet.data_length = strlen(response_packet.data);

        sql_query.free_result();
        return false;
    }
}

User *User::signup(std::string username, std::string password, std::string display_name, SQLQuery sql_query, MessagePacket& response_packet) {
    // check if username is not taken
    std::string query = "SELECT * FROM Account WHERE username = '" + username + "'";
    MYSQL_RES *result;

    sql_query.query(query, response_packet);
    if (sql_query.is_select_successful() == false) {
        return NULL;
    } else {
        result = sql_query.get_result();
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
        query = "INSERT INTO `Account` (`username`, `password`, `display_name`, `time_created`) VALUES ('" 
                + username + "', '" + password + "', '" + display_name
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

    sql_query.free_result();
    return user;
}

bool User::check_friend(std::string friend_username, SQLQuery sql_query, MessagePacket& response_packet, std::string& data, int& receiver_id) {
    // check if friend exists
    std::string query = "SELECT * FROM `Account` WHERE `username` = '" + friend_username + "' and `id` != '" + std::to_string(_id) + "'";
    MYSQL_RES *result;

    sql_query.query(query, response_packet);
    if (sql_query.is_select_successful() == false) {
        response_packet.response_header.response_type = ResponseType::ERROR;
        strcpy(response_packet.data, "Internal server error");
        response_packet.data_length = strlen(response_packet.data);

        return false;
    } else {
        result = sql_query.get_result();
    }

    MYSQL_ROW row;
    if ((row = mysql_fetch_row(result))) {
        std::string friend_id_str = row[0];
        std::string friend_display_name = row[3];

        query = "SELECT * FROM `Friendship` WHERE (`user1_id` = '" + std::to_string(_id) 
                                          + "' and `user2_id` = '" + friend_id_str 
                                          + "') or (`user1_id` = '" + friend_id_str 
                                          + "' and `user2_id` = '" + std::to_string(_id) + "')";
        
        sql_query.query(query, response_packet);
        if (sql_query.is_select_successful() == false) {
            response_packet.response_header.response_type = ResponseType::ERROR;
            strcpy(response_packet.data, "Internal server error");
            response_packet.data_length = strlen(response_packet.data);

            return false;
        } else {
            result = sql_query.get_result();
        }

        if ((row = mysql_fetch_row(result))) {
            // friend exists
            response_packet.response_header.response_type = ResponseType::FAILURE;
            strcpy(response_packet.data, "Friend is already added");
            response_packet.data_length = strlen(response_packet.data);
        } else {
            // friend does not exist, possible to add
            response_packet.response_header.response_type = ResponseType::SUCCESS;
            strcpy(response_packet.data, "Add friend request sent");
            response_packet.data_length = strlen(response_packet.data);

            // write data = <user_id_length>:<user_id><user_name_length>:<user_name><user_display_name_length>:<user_display_name>
            data = std::to_string(std::to_string(_id).length()) + ":" + std::to_string(_id) + ":" + std::to_string(_username.length()) + ":" + _username + ":" + std::to_string(_display_name.length()) + ":" + _display_name;
            receiver_id = std::stoi(friend_id_str);
        }
    } else {
        // username does not exist or is the same as the user
        response_packet.response_header.response_type = ResponseType::FAILURE;
        strcpy(response_packet.data, "Invalid friend username");
        response_packet.data_length = strlen(response_packet.data);
    }

    sql_query.free_result();
    return true;
}

bool User::add_friend(std::string friend_id_str, SQLQuery sql_query, MessagePacket& response_packet) {
    // check if friend exists
    std::string query = "SELECT * FROM `Account` WHERE `id` = '" + friend_id_str + "' and `id` != '" + std::to_string(_id) + "'";
    MYSQL_RES *result;

    sql_query.query(query, response_packet);
    if (sql_query.is_select_successful() == false) {
        response_packet.response_header.response_type = ResponseType::ERROR;
        strcpy(response_packet.data, "Internal server error");
        response_packet.data_length = strlen(response_packet.data);

        return false;
    } else {
        result = sql_query.get_result();
    }

    MYSQL_ROW row;
    if ((row = mysql_fetch_row(result))) {
        query = "SELECT * FROM `Friendship` WHERE (`user1_id` = '" + std::to_string(_id) 
                                          + "' and `user2_id` = '" + friend_id_str
                                          + "') or (`user1_id` = '" + friend_id_str
                                          + "' and `user2_id` = '" + std::to_string(_id) + "')";
        sql_query.query(query, response_packet);

        if (sql_query.is_select_successful() == false) {
            response_packet.response_header.response_type = ResponseType::ERROR;
            strcpy(response_packet.data, "Internal server error");
            response_packet.data_length = strlen(response_packet.data);

            return false;
        } else {
            result = sql_query.get_result();
        }

        if ((row = mysql_fetch_row(result))) {
            // friendship already exists
            response_packet.response_header.response_type = ResponseType::FAILURE;
            strcpy(response_packet.data, "Friend already added");
            response_packet.data_length = strlen(response_packet.data);
        } else {
            // friendship does not exist, add friend
            query = "INSERT INTO `Friendship` (`user1_id`, `user2_id`) VALUES ('" 
                    + std::to_string(_id) + "', '" + friend_id_str + "')";

            sql_query.query(query, response_packet);
            if (sql_query.is_insert_successful()) {
                // insert successful
                response_packet.response_header.response_type = ResponseType::SUCCESS;
                strcpy(response_packet.data, "Friend added");
                response_packet.data_length = strlen(response_packet.data);
            } else {
                // insert failed
                response_packet.response_header.response_type = ResponseType::ERROR;
                strcpy(response_packet.data, "Internal server error");
                response_packet.data_length = strlen(response_packet.data);

                sql_query.free_result();
                return false;
            }
        }
    } else {
        // friend does not exist 
        response_packet.response_header.response_type = ResponseType::FAILURE;
        strcpy(response_packet.data, "Username does not valid");
        response_packet.data_length = strlen(response_packet.data);
    }

    sql_query.free_result();
    return true;
}

bool User::remove_friend(std::string friend_id, SQLQuery sql_query, MessagePacket& response_packet) {
    // check if friend exists
    std::string query = "SELECT * FROM `Account` WHERE `id` = '" + friend_id + "'";
    MYSQL_RES *result;

    sql_query.query(query, response_packet);
    if (sql_query.is_select_successful() == false) {
        response_packet.response_header.response_type = ResponseType::ERROR;
        strcpy(response_packet.data, "Internal server error");
        response_packet.data_length = strlen(response_packet.data);

        return false;
    } else {
        result = sql_query.get_result();
    }

    MYSQL_ROW row;
    if ((row = mysql_fetch_row(result))) {
        query = "SELECT * FROM `Friendship` WHERE (`user1_id` = '" + std::to_string(_id) 
                                          + "' and `user2_id` = '" + friend_id 
                                          + "') or (`user1_id` = '" + friend_id 
                                          + "' and `user2_id` = '" + std::to_string(_id) + "')";
        sql_query.query(query, response_packet);

        if (sql_query.is_select_successful() == false) {
            response_packet.response_header.response_type = ResponseType::ERROR;
            strcpy(response_packet.data, "Internal server error");
            response_packet.data_length = strlen(response_packet.data);

            return false;
        } else {
            result = sql_query.get_result();
        }

        if ((row = mysql_fetch_row(result))) {
            // friendship exists, remove friend
            query = "DELETE FROM `Friendship` WHERE (`user1_id` = '" + std::to_string(_id) 
                                          + "' and `user2_id` = '" + friend_id 
                                          + "') or (`user1_id` = '" + friend_id 
                                          + "' and `user2_id` = '" + std::to_string(_id) + "')";

            sql_query.query(query, response_packet);
            if (sql_query.is_delete_successful()) {
                // delete successful
                response_packet.response_header.response_type = ResponseType::SUCCESS;
                strcpy(response_packet.data, "Friend removed");
                response_packet.data_length = strlen(response_packet.data);
            } else {
                // delete failed
                response_packet.response_header.response_type = ResponseType::ERROR;
                strcpy(response_packet.data, "Internal server error");
                response_packet.data_length = strlen(response_packet.data);

                return false;
            }
        } else {
            // friendship does not exist
            response_packet.response_header.response_type = ResponseType::FAILURE;
            strcpy(response_packet.data, "Friend does not exist");
            response_packet.data_length = strlen(response_packet.data);
        }
    } else {
        // friend does not exist 
        response_packet.response_header.response_type = ResponseType::FAILURE;
        strcpy(response_packet.data, "Username does not valid");
        response_packet.data_length = strlen(response_packet.data);
    }

    sql_query.free_result();
    return true;
}
