#ifndef CLIENT_UTILS_H
#define CLIENT_UTILS_H

#include <string>
#include <tuple>
#include <vector>

std::string encode_auth_data(const std::string username, const std::string password);
std::string encode_signup_data(const std::string username, const std::string password, const std::string display_name);
std::string encode_update_account_data(const std::string data);
std::string encode_create_group_chat(const std::string group_name, const std::vector<std::string> members);

std::tuple<int, std::string> parse_user_info_data(const std::string info_data);

#endif // CLIENT_UTILS_H