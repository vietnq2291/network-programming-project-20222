#include "../include/Utils.h"

#include "../../shared/common.h"

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
    // output is of the form: <type>:<data_len>:<data>, where type is either 'P' (password) or 'N' (display name)

    std::stringstream ss;
    ss << data[0] << ":" << data.length() - 2 << ":" << data.substr(2);
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
    // output is of the form: <group_name_len>:<group_name><num_members>:<member1_len>:<member1>...<memberN_len>:<memberN>

    std::stringstream ss;
    ss << group_name.length() << ":" << group_name << members.size() << ":";
    for (auto member : members) {
        ss << member.length() << ":" << member;
    }
    return ss.str();
}

std::string encode_invite_group_chat(const std::string buff) {
    // buff = <group_id> <number of other users> <user_id_1> <user_id_2> ... <user_id_n>
    std::istringstream iss(buff);
    std::string group_id;
    int num_users;
    iss >> group_id >> num_users;
    std::vector<std::string> user_ids(num_users);
    for (int i = 0; i < num_users; ++i) {
        iss >> user_ids[i];
    }

    // output data = <group_id_len>:<group_id><num_users>:<user_id_1>:<user_id_2>:...:<user_id_n>
    std::ostringstream oss;
    oss << group_id.size() << ':' << group_id
        << num_users;
    for (const auto& user_id : user_ids) {
        oss << ':' << user_id;
    }
    std::string data = oss.str();

    return data;
}

std::string encode_get_latest_messages(const std::string buff) {
    // buff = <chat_id> <number of messages>
    std::istringstream iss(buff);
    std::string chat_id;
    int num_messages;
    iss >> chat_id >> num_messages;

    // output data = <chat_id_len>:<chat_id><num_messages>
    std::ostringstream oss;
    oss << chat_id.size() << ':' << chat_id
        << num_messages;
    std::string data = oss.str();

    return data;
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

std::string format_time(std::time_t timestamp)
{
    std::tm* time_info = std::localtime(&timestamp);

    char buffer[80];
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", time_info);

    return std::string(buffer);
}

std::tuple<std::string, std::string> process_file_header(const std::string& data, const std::string& folder_path)
{
    size_t fn_delim = data.find(':');
    size_t fd_delim = data.find(':', fn_delim + 1);

    long long fn_len = std::stoll(data.substr(0, fn_delim));
    long long fd_len = std::stoll(data.substr(fn_delim + fn_len + 1, fd_delim - (fn_delim + fn_len + 1)));

    std::string file_name = data.substr(fn_delim + 1, fn_len);
    std::string file_data = data.substr(fd_delim + 1, fd_len);

    std::string file_path = folder_path + "/" + file_name;

    return std::make_tuple(file_path, file_data);
}

void write_file(const std::string& data, const std::string& file_path) {
    std::ofstream file(file_path);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file for appending." << std::endl;
        return;
    }

    file << data;
    if (file.fail() || file.bad()) {
        std::cerr << "Error: Failed to append to file." << std::endl;
        file.close();
        return;
    }

    file.close();
}  

void append_file(const std::string& data, const std::string& file_path) {
    std::ofstream file(file_path, std::ios_base::app);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file for appending." << std::endl;
        return;
    }

    file << data;
    if (file.fail() || file.bad()) {
        std::cerr << "Error: Failed to append to file." << std::endl;
        file.close();
        return;
    }

    file.close();
}  

ChatMessage create_chat_message(MessagePacket p, std::string& folder_path) {
    std::string data;
    
    if (p.chat_header.data_type == DataType::FILE) {
        auto [file_path, fdata] = process_file_header(p.data, folder_path);
        write_file(fdata, file_path);
        data = file_path;
    } else {
        data = p.data;
    }

    ChatMessage m {
        p.chat_header.sender,
        p.chat_header.timestamp,
        p.chat_header.data_type,
        data
    };
    return m;
}
