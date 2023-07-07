#ifndef CLIENT_UTILS_H
#define CLIENT_UTILS_H

#include <string>
#include <tuple>
#include <vector>

std::string encode_auth_data(const std::string username, const std::string password);
std::string encode_signup_data(const std::string username, const std::string password, const std::string display_name);
std::string encode_update_account_data(const std::string data);
std::string encode_create_group_chat(const std::string group_name, const std::vector<std::string> members);
std::string encode_invite_group_chat(const std::string buff);
std::string encode_get_latest_messages(const std::string buff);

std::tuple<int, std::string> parse_user_info_data(const std::string info_data);
std::tuple<std::string, std::string> parse_file_data(const std::string file_data);

#endif // CLIENT_UTILS_H