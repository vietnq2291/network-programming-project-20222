#include <iostream>
#include <string>
#include <cstring>
#include <sstream>
#include <vector>

#include "../include/Utils.h"
#include "../../shared/common.h"

std::tuple<std::string, std::string> parse_auth_data(const std::string& auth_data) {    
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

std::tuple<std::string, std::string> parse_update_account_data(const std::string& data) {
    // data is of the form: <type>:<data_len>:<data>, where type is either 'P' (password) or 'N' (display name)
    size_t type_delim = data.find(':');
    size_t data_delim = data.find(':', type_delim + 1);
    int data_len = std::stoi(data.substr(type_delim + 1, data_delim - (type_delim + 1)));
    std::string data_value = data.substr(data_delim + 1, data_len);

    std::string field;
    if (data[0] == 'P')
        field = "password";
    else if (data[0] == 'N')
        field = "display_name";

    return std::make_tuple(field, data_value);
}

std::tuple<std::string, std::vector<std::string>> parse_create_group_data(const std::string& data) {
    // data is of the form: <group_name_len>:<group_name><num_members>:<member1_len>:<member1>...<memberN_len>:<memberN>
    size_t group_name_delim = data.find(':');
    size_t num_members_delim = data.find(':', group_name_delim + 1);

    int group_name_len = std::stoi(data.substr(0, group_name_delim));
    int num_members = std::stoi(data.substr(group_name_len + group_name_delim + 1, num_members_delim - (group_name_len + group_name_delim + 1)));
    std::string group_name = data.substr(group_name_delim + 1, group_name_len);

    std::vector<std::string> members;
    size_t prev_member_last = num_members_delim;
    size_t member_delim;
    for (int i = 0; i < num_members; i++) {
        member_delim = data.find(':', prev_member_last + 1);
        int member_len = std::stoi(data.substr(prev_member_last + 1, member_delim - (prev_member_last + 1)));
        std::string member = data.substr(member_delim + 1, member_len);
        members.push_back(member);
        prev_member_last = member_delim + member_len;

    }

    return std::make_tuple(group_name, members);
}

std::tuple<std::string, std::vector<int>> parse_add_to_group_data(const std::string& data) {
    // input data <group_id_len>:<group_id><num_users>:<user_id_1>:<user_id_2>:...:<user_id_n>
    std::istringstream iss(data);
    std::string group_id;
    int group_id_len, group_name_len, num_users;
    char colon;

    iss >> group_id_len >> colon;
    group_id.resize(group_id_len);
    iss.read(&group_id[0], group_id_len);

    iss >> num_users;
    std::vector<int> user_ids(num_users);
    for (int i = 0; i < num_users; ++i) {
        iss >> colon >> user_ids[i];
    }
    
    return {group_id, user_ids};
}



int read_command_line_arguments(int argc, char *argv[], int &port, int &backlog) {
    /* return 0 if the arguments are valid
     * return 1 if the arguments are invalid
     * return 2 if the user asked for help
     */

    int ret;

    switch (argc) {
        case 1:
            port = DEFAULT_PORT;
            backlog = DEFAULT_BACKLOG;
            ret = 0;
            break;
        case 2:
            if (strcmp(argv[1], "--help") == 0) {
                std::cout << "Usage:    " << argv[0] << " -p [port] -b [backlog]" << std::endl;
                std::cout << "          " << argv[0] << " --help" << std::endl;
                std::cout << "\nIf no port or backlog is provided, the default value will be used." << std::endl;
                std::cout << "    Default port: " << DEFAULT_PORT << std::endl;
                std::cout << "    Default backlog (maximum number of connections): " << DEFAULT_BACKLOG << std::endl;
                ret = 2;
            } else {
                ret = 1;
            }
            break;
        case 3:
            if (strcmp(argv[1], "-p") == 0) {
                port = atoi(argv[2]);
                backlog = DEFAULT_BACKLOG;
                ret = 0;
            } else if (strcmp(argv[1], "-b") == 0) {
                port = DEFAULT_PORT;
                backlog = atoi(argv[2]);
                ret = 0;
            } else {
                ret = 1;
            }
            break;
        case 5:
            if (strcmp(argv[1], "-p") == 0) {
                port = atoi(argv[2]);
                if (strcmp(argv[3], "-b") == 0) {
                    backlog = atoi(argv[4]);
                    ret = 0;
                } else {
                    ret = 1;
                }
            } else if (strcmp(argv[1], "-b") == 0) {
                backlog = atoi(argv[2]);
                if (strcmp(argv[3], "-p") == 0) {
                    port = atoi(argv[4]);
                    ret = 0;
                } else {
                    ret = 1;
                }
            } else {
                ret = 1;
            }
            break;
        default:
            ret = 1;
            break;
    }

    return ret;
}

void log(LogType log_type, std::string message, int client_fd) {
    std::string log_type_str, client_fd_str;
    switch (log_type) {
        case LogType::INFO:
            log_type_str = "\033[32m INFO    \033[0m";
            break;
        case LogType::WARNING:
            log_type_str = "\033[33m WARNING \033[0m"; 
            break;
        case LogType::ERROR:
            log_type_str = "\033[31m ERROR   \033[0m";
            break;
    }
    
    if (client_fd != -1)
        client_fd_str = "(client " + std::to_string(client_fd) + ")";
    else
        client_fd_str = "";

    if (log_type == LogType::ERROR) {
        std::cout << "[" << log_type_str << "] " << client_fd_str << " " << message << std::endl;        
    } else {
        std::cerr << "[" << log_type_str << "] " << client_fd_str << " " << message << std::endl;
    }
}
