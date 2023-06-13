#ifndef AUTHUTILS_H
#define AUTHUTILS_H

#include <string>
#include <tuple>

std::tuple<std::string, std::string> parse_auth_data(const std::string& auth_data);
std::tuple<std::string, std::string, std::string> parse_signup_data(const std::string& auth_data);

#endif // AUTHUTILS_H