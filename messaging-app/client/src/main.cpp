#include "../include/client.h"
#include "../../shared/common.h"

int main(int argc, char *argv[]) {
    // read command line arguments
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <ip> <port>" << std::endl;
        return 1;
    }
    std::string ip = argv[1];
    int port = atoi(argv[2]);
    
    // init client
    Client client(port, ip);
    client.connect();
    client.start();

    return 0;
}
