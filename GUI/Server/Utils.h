#ifndef UTILS_H
#define UTILS_H


#include <string>
#include <tuple>
#include <vector>

enum class LogType {
    INFO,
    WARNING,
    ERROR
};

std::tuple<std::string, std::string> parse_auth_data(const std::string& auth_data);
std::tuple<std::string, std::string, std::string> parse_signup_data(const std::string& auth_data);
std::tuple<std::string, std::string> parse_update_account_data(const std::string& data);
std::tuple<std::string, std::vector<std::string>> parse_create_group_data(const std::string& data);
std::tuple<std::string, std::vector<int>> parse_add_to_group_data(const std::string& data);
std::tuple<int, int, int> parse_get_chat_messages_request(const std::string& data);

int read_command_line_arguments(int argc, char *argv[], int &port, int &backlog);
void log(LogType log_type, std::string message, int client_fd = -1);

#endif // UTILS_H
