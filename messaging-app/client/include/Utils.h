#ifndef AUTHUTILS_H
#define AUTHUTILS_H

#include <string>
#include <tuple>

std::string encode_auth_data(const std::string& username, const std::string& password);
std::string encode_signup_data(const std::string& username, const std::string& password, const std::string& display_name);

#endif // AUTHUTILS_H