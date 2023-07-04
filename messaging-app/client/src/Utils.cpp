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

    int userid_len = std::stoi(info_data.substr(0, userid_delim));
    int display_name_len = std::stoi(info_data.substr(userid_len + userid_delim + 1, name_delim - (userid_len + userid_delim + 1)));

    std::string user_id = info_data.substr(userid_delim + 1, userid_len);
    std::string display_name = info_data.substr(name_delim + 1, display_name_len);

    return std::make_tuple(std::stoi(user_id), display_name);
}

std::string encode_create_group_chat(const std::string group_name, const std::vector<std::string> members) {
    // output is of the form: <group_name_len>:<group_name><num_members>:<member1_len>:<member1>...<memberN_len>:<memberN>:

    std::stringstream ss;
    ss << group_name.length() << ":" << group_name << members.size() << ":";
    for (auto member : members) {
        ss << member.length() << ":" << member;
    }
    return ss.str();
}

std::tuple<std::string, std::string> parse_file_data(const std::string file_data) {
    // input is of the form: <file_name_length>:<file_name><file_content_length>:<file_content>

    size_t name_delim = file_data.find(':');
    size_t content_delim = file_data.find(':', name_delim + 1);

    int file_name_len = std::stoi(file_data.substr(0, name_delim));
    int file_content_len = std::stoi(file_data.substr(name_delim + 1, content_delim - (name_delim + 1)));

    std::string file_name = file_data.substr(name_delim + 1, file_name_len);
    std::string file_content = file_data.substr(content_delim + 1, file_content_len);

    return std::make_tuple(file_name, file_content);
}