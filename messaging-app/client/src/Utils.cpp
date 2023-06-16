#include "../include/Utils.h"
#include <string>
#include <sstream>
#include <vector>

std::string encode_auth_data(const std::string username, const std::string password) {
    // output is of the form: <username_len>:<username><password_len>:<password>

    std::stringstream ss;
    ss << username.length() << ":" << username << password.length() << ":" << password;
    return ss.str();
}

std::string encode_signup_data(const std::string username, const std::string password, const std::string display_name) {
    // output is of the form: <username_len>:<username><password_len>:<password><display_name_len>:<display_name>

    std::stringstream ss;
    ss << username.length() << ":" << username << password.length() << ":" << password << display_name.length() << ":" << display_name;
    return ss.str();
}

std::string encode_update_account_data(const std::string data) {
    // input: data = <type> <data>
    // output is of the form: <type><data_len>:<data>, where type is either 'P' (password) or 'N' (display name)

    std::stringstream ss;
    ss << data[0] << data.length() - 2 << ":" << data.substr(2);
    return ss.str();
}

std::tuple<int, std::string> parse_user_info_data(const std::string info_data) {
    // input is of the form: <user_id_len>:<user_id><display_name_len>:<display_name>

    size_t userid_delim = info_data.find(':');
    size_t name_delim = info_data.find(':', userid_delim + 1);

    int username_len = std::stoi(info_data.substr(0, userid_delim));
    int password_len = std::stoi(info_data.substr(username_len + userid_delim + 1, name_delim - (username_len + userid_delim + 1)));

    std::string user_id = info_data.substr(userid_delim + 1, username_len);
    std::string display_name = info_data.substr(name_delim + 1, password_len);

    return std::make_tuple(std::stoi(user_id), display_name);
}

std::string encode_create_group_chat(const std::string group_name, const std::vector<std::string> members) {
    // output is of the form: <group_name_len>:<group_name><num_members>:<member1_len>:<member1>...<memberN_len>:<memberN>

    std::stringstream ss;
    ss << group_name.length() << ":" << group_name << members.size() << ":";
    for (auto member : members) {
        ss << member.length() << ":" << member;
    }
    return ss.str();
}