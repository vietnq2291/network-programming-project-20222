#include <mysql/mysql.h>
#include <cstring>
#include <iostream>

#include "../include/SQLQuery.h"
#include "../include/Utils.h"

SQLQuery::SQLQuery() {
    _conn = mysql_init(NULL);
}

bool SQLQuery::connect(std::string host, std::string user, std::string password, std::string database, std::string is_multi_statements) {
    if (!mysql_real_connect(_conn, host.c_str(), user.c_str(), password.c_str(), database.c_str(), 0, NULL, 0)) {
        log(LogType::ERROR, std::string(mysql_error(_conn)));
        return false;
    }

    if (is_multi_statements == "true") {
        mysql_set_server_option(_conn, MYSQL_OPTION_MULTI_STATEMENTS_ON);
    } else {
        mysql_set_server_option(_conn, MYSQL_OPTION_MULTI_STATEMENTS_OFF);
    }
    return true;
}

void SQLQuery::disconnect() {
    mysql_close(_conn);
}

void SQLQuery::query(std::string query, MessagePacket& response_packet) {
    if (mysql_query(_conn, query.c_str())) {
        log(LogType::ERROR, std::string(mysql_error(_conn)));
        response_packet.response_header.response_type = ResponseType::ERROR;
        strcpy(response_packet.data, "Internal server error");
        response_packet.data_length = strlen(response_packet.data);
        _result = NULL;
        return;
    }
    
    _result = mysql_store_result(_conn);
}

MYSQL_RES *SQLQuery::get_result() {
    return _result;
}

bool SQLQuery::is_result_empty() {
    return mysql_num_rows(_result) == 0;
}

bool SQLQuery::next_result() {
    if (mysql_next_result(_conn) != 0) {
        return false;
    }
    _result = mysql_store_result(_conn);
    return true;
}

bool SQLQuery::is_select_successful() {
    return _result != NULL;
}

bool SQLQuery::is_insert_successful() {
    return mysql_affected_rows(_conn) >= 1;
}

bool SQLQuery::is_update_successful() {
    return mysql_affected_rows(_conn) >= 1;
}

void SQLQuery::free_result() {
    while (mysql_next_result(_conn) == 0) {}
    if (_result != NULL) {        
        mysql_free_result(_result);
    }
}