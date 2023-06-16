#include <iostream>
#include <cstring>

#include "../include/Server.h"
#include "../include/Utils.h"

int main(int argc, char *argv[]) {
    int port, backlog;
    int ret;
    
    ret = read_command_line_arguments(argc, argv, port, backlog);
    if (ret == 1) {
        std::cerr << "Wrong arguments.\nSee " << argv[0] << " --help" << std::endl;
        return 1;
    } else if (ret == 2) {
        return 0;
    }

    Server my_server(port, backlog);
    my_server.connectdb();
    my_server.start();

    return 0;
}
