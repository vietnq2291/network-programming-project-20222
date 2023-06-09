// main.cpp
#include "../include/Server.h"

int main(int argc, char *argv[]) {

    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <port>" << std::endl;
        return 1;
    }
    int port = atoi(argv[1]);
    
    Server my_server(port, 10);
    my_server.connectdb();
    my_server.start();

    return 0;
}
