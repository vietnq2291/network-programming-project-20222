#include "../include/Utils.h"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

std::string encode_auth_data(const std::string& username, const std::string& password) {
    std::stringstream ss;
    // output is of the form: <username_len>:<username><password_len>:<password>
    ss << username.length() << ":" << username << password.length() << ":" << password;
    return ss.str();
}

std::string encode_signup_data(const std::string& username, const std::string& password, const std::string& display_name) {
    std::stringstream ss;
    // output is of the form: <username_len>:<username><password_len>:<password><display_name_len>:<display_name>
    ss << username.length() << ":" << username << password.length() << ":" << password << display_name.length() << ":" << display_name;
    return ss.str();
}

std::string encode_update_account_data(const std::string& data) {
    std::stringstream ss;
    // input: data = <type> <data>
    // output is of the form: <type><data_len>:<data>, where type is either 'P' (password) or 'N' (display name)
    ss << data[0] << data.length() - 2 << ":" << data.substr(2);
    return ss.str();
}
