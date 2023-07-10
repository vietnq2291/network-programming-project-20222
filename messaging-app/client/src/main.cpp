#include <iostream>
#include <cstring>

#include "../include/Client.h"
#include "../../shared/common.h"

int main(int argc, char *argv[]) {
    std::string ip;
    int port;
    std::string folder_path;

    // read command line arguments
    if (argc == 4) {
        ip = argv[1];
        port = atoi(argv[2]);
        folder_path = argv[3];
    } else if ((argc == 2) && (strcmp(argv[1], "--help") == 0)) {
        std::cout << "Usage:    " << argv[0] << " [ip] [port] [path/to/store/files]" << std::endl;
        // std::cout << "\nIf no ip and port are provided, the default ip and port will be used." << std::endl;
        // std::cout << "    Default ip: " << DEFAULT_IP << std::endl;
        // std::cout << "    Default port: " << DEFAULT_PORT << std::endl;
        return 0;
    // } else if (argc == 1) {
    //     ip = DEFAULT_IP;
    //     port = DEFAULT_PORT;
    } else {
        std::cerr << "Wrong arguments.\nSee " << argv[0] << " --help" << std::endl;
        return 1;
    }
    
    // init client
    Client client(port, ip, folder_path);
    client.connect();
    client.start();

    return 0;
}
