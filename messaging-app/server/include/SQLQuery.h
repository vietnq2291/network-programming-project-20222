#ifndef SQLQUERY_H
#define SQLQUERY_H

#include <mysql/mysql.h>
#include <string>

#include "../../shared/common.h"

class SQLQuery {
public:
    SQLQuery();
    bool connect(std::string host, std::string user, std::string password, std::string database, std::string is_multi_statements);
    void query(std::string query, MessagePacket& response_packet);
    MYSQL_RES *get_result();
    bool next_result();
    bool is_result_empty();
    bool is_select_successful();
    bool is_insert_successful();
    bool is_update_successful();
    bool is_delete_successful();
    void disconnect();
    void free_result();
    MYSQL *get_connection() const { return _conn; }


private:
    MYSQL *_conn;
    MYSQL_RES *_result;
};

#endif // SQLQUERY_H