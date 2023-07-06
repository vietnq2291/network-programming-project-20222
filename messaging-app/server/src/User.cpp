#include <iostream>
#include <cstring>
#include <vector>
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
        response_packet.response_header.response_type = ResponseType::ERROR;
        strcpy(response_packet.data, "Error occurred while authenticating");
        response_packet.data_length = strlen(response_packet.data);

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
        response_packet.response_header.response_type = ResponseType::ERROR;
        strcpy(response_packet.data, "Internal server error");
        response_packet.data_length = strlen(response_packet.data);

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

            // write data = <user_id_length>:<user_id><user_display_name_length>:<user_display_name>
            data = std::to_string(std::to_string(_id).length()) + ":" + std::to_string(_id) + std::to_string(_display_name.length()) + ":" + _display_name;
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
                strcpy(response_packet.data, "Friend added successfully");
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
                strcpy(response_packet.data, "Unfriend successfully");
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
            strcpy(response_packet.data, "Friendship does not exist");
            response_packet.data_length = strlen(response_packet.data);
        }
    } else {
        // friend does not exist 
        response_packet.response_header.response_type = ResponseType::FAILURE;
        strcpy(response_packet.data, "Friend account does not exist");
        response_packet.data_length = strlen(response_packet.data);
    }

    sql_query.free_result();
    return true;
}

std::pair<bool, std::vector<std::pair<int, std::string>>> User::get_friend_list(SQLQuery sql_query, MessagePacket& response_packet) {
    std::string query = "SELECT `id`, `display_name` FROM `Account` WHERE `id` IN (SELECT `user2_id` FROM `Friendship` WHERE `user1_id` = " + std::to_string(_id) +
                        " UNION SELECT `user1_id` FROM `Friendship` WHERE `user2_id` = " + std::to_string(_id) + ")";
    MYSQL_RES *result;
    std::vector<std::pair<int, std::string>> friend_list;

    sql_query.query(query, response_packet);
    if (sql_query.is_select_successful() == false) {
        response_packet.response_header.response_type = ResponseType::ERROR;
        strcpy(response_packet.data, "Internal server error");
        response_packet.data_length = strlen(response_packet.data);

        return std::make_pair(false, friend_list);
    } else {
        result = sql_query.get_result();
    }

    MYSQL_ROW row;
    while ((row = mysql_fetch_row(result))) {
        std::string friend_id = row[0];
        std::string friend_name = row[1];
        friend_list.push_back(std::make_pair(std::stoi(friend_id), std::to_string(friend_id.length()) + ":" + friend_id + std::to_string(friend_name.length()) + ":" + friend_name));
    }

    response_packet.response_header.response_type = ResponseType::SUCCESS;
    sql_query.free_result();    
    return std::make_pair(true, friend_list);
}

std::pair<bool, std::string> User::get_chat_list(SQLQuery sql_query, MessagePacket& response_packet) {
    std::string query = "SELECT c.id, c.type, CASE WHEN c.type = 'private' THEN (SELECT a.display_name FROM Account a JOIN Membership m ON a.id = m.user_id WHERE m.chat_id = c.id AND m.user_id != " + std::to_string(_id) + ") ELSE c.name END AS name FROM Chat c JOIN Membership m ON c.id = m.chat_id WHERE m.user_id = " + std::to_string(_id) + " ORDER BY c.id";
    MYSQL_RES *result;

    sql_query.query(query, response_packet);
    if (sql_query.is_select_successful() == false) {
        response_packet.response_header.response_type = ResponseType::ERROR;
        strcpy(response_packet.data, "Internal server error");
        response_packet.data_length = strlen(response_packet.data);

        return std::make_pair(false, "");
    } else {
        result = sql_query.get_result();
    }

    // chat_list = <number_of_chats><chat_1><chat_2>...<chat_n>
    MYSQL_ROW row;
    std::string chat_list = std::to_string(mysql_num_rows(result));
    while ((row = mysql_fetch_row(result))) {
        // each chat is of the form: <chat_type><chat_id_length>:<chat_id><chat_name_length>:<chat_name>
        // where chat_type is either 'P' or 'G'
        std::string chat_id = row[0];
        std::string chat_type = (strcmp(row[1], "PRIVATE") == 0 ? "P" : "G");
        std::string chat_name = row[2];

        chat_list += chat_type + std::to_string(chat_id.length()) + ":" + chat_id + std::to_string(chat_name.length()) + ":" + chat_name;
    }

    response_packet.response_header.response_type = ResponseType::SUCCESS;
    sql_query.free_result();
    return std::make_pair(true, chat_list);
}
