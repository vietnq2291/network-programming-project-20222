#include <mysql/mysql.h>
#include <cstring>
#include <iostream>

#include "../include/SQLQuery.h"

SQLQuery::SQLQuery() {
    _conn = mysql_init(NULL);
}

bool SQLQuery::connect(std::string host, std::string user, std::string password, std::string database) {
    if (!mysql_real_connect(_conn, host.c_str(), user.c_str(), password.c_str(), database.c_str(), 0, NULL, 0)) {
        std::cerr << "Error: " << mysql_error(_conn) << std::endl;
        return false;
    }
    return true;
}

void SQLQuery::disconnect() {
    mysql_close(_conn);
}

void SQLQuery::query(std::string query, MessagePacket& response_packet) {
    if (mysql_query(_conn, query.c_str())) {
        std::cerr << "Error: " << mysql_error(_conn) << std::endl;
        response_packet.response_header.response_type = ResponseType::ERROR;
        strcpy(response_packet.data, "Internal server error");
        response_packet.data_length = strlen(response_packet.data);
        _result = NULL;
        return;
    }
    
    _result = mysql_store_result(_conn);
    if (_result == NULL && mysql_field_count(_conn) != 0) {
        std::cerr << "Error: " << mysql_error(_conn) << std::endl;
        response_packet.response_header.response_type = ResponseType::ERROR;
        strcpy(response_packet.data, "Internal server error");
        response_packet.data_length = strlen(response_packet.data);
    }
}

MYSQL_RES *SQLQuery::get_result() {
    return _result;
}

bool SQLQuery::is_insert_successful() {
    return mysql_affected_rows(_conn) == 1;
}

bool SQLQuery::is_update_successful() {
    return mysql_affected_rows(_conn) >= 1;
}