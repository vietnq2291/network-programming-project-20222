#include "../include/Utils.h"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

std::tuple<std::string, std::string> parse_auth_data(const std::string& auth_data) {    
    // parse username and password
    // input is of the form: <username_len>:<username><password_len>:<password>
    size_t username_delim = auth_data.find(':');
    size_t password_delim = auth_data.find(':', username_delim + 1);

    int username_len = std::stoi(auth_data.substr(0, username_delim));
    int password_len = std::stoi(auth_data.substr(username_len + username_delim + 1, password_delim - (username_len + username_delim + 1)));

    std::string username = auth_data.substr(username_delim + 1, username_len);
    std::string password = auth_data.substr(password_delim + 1, password_len);

    return std::make_tuple(username, password);
}


std::tuple<std::string, std::string, std::string> parse_signup_data(const std::string& signup_data) {
    // parse username and password
    // input is of the form: <username_len>:<username><password_len>:<password><display_name_len>:<display_name>
    size_t username_delim = signup_data.find(':');
    size_t password_delim = signup_data.find(':', username_delim + 1);
    size_t display_name_delim = signup_data.find(':', password_delim + 1);

    int username_len = std::stoi(signup_data.substr(0, username_delim));
    int password_len = std::stoi(signup_data.substr(username_len + username_delim + 1, password_delim - (username_len + username_delim + 1)));
    int display_name_len = std::stoi(signup_data.substr(password_delim + 1 + password_len, display_name_delim - (password_delim + 1 + password_len)));

    std::string username = signup_data.substr(username_delim + 1, username_len);
    std::string password = signup_data.substr(password_delim + 1, password_len);
    std::string display_name = signup_data.substr(display_name_delim + 1, display_name_len);

    return std::make_tuple(username, password, display_name);
}