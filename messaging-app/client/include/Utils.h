#ifndef AUTHUTILS_H
#define AUTHUTILS_H

#include <string>
#include <tuple>

std::string encode_auth_data(const std::string& username, const std::string& password);
std::string encode_signup_data(const std::string& username, const std::string& password, const std::string& display_name);
std::string encode_update_account_data(const std::string& data);
std::tuple<int, std::string> parse_user_info_data(const std::string& info_data);

#endif // AUTHUTILS_H