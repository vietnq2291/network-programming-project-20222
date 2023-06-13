#ifndef SQLQUERY_H
#define SQLQUERY_H

#include <mysql/mysql.h>
#include <string>

#include "../../shared/common.h"

class SQLQuery {
public:
    SQLQuery();
    bool connect(std::string host, std::string user, std::string password, std::string database);
    void query(std::string query, MessagePacket& response_packet);
    MYSQL_RES *get_result();
    bool is_insert_successful();
    bool is_update_successful();
    void free_result();
    void disconnect();


private:
    MYSQL *_conn;
    MYSQL_RES *_result;
};

#endif // SQLQUERY_H