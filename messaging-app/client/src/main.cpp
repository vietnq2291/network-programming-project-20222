#include <iostream>
#include <cstring>
#include <pthread.h>

#include "../include/Client.h"
#include "../../shared/common.h"

void* receive_thread_message(void* arg) {
    Client* client = static_cast<Client*>(arg);
    client->receive_message(NULL);
    return NULL;
}

void* send_thread_message(void* arg) {
    Client* client = static_cast<Client*>(arg);
    client->send_message(NULL);
    return NULL;
}

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
    
    Client* client = new Client(port, ip, folder_path);
    client->connect();

    // Create threads
    const int num_threads = 2;
    pthread_t threads[num_threads];
    int rc = pthread_create(&threads[0], NULL, receive_thread_message, client);
    if (rc) {
        std::cerr << "Error: unable to create receive thread, " << rc << std::endl;
        exit(-1);
    }
    rc = pthread_create(&threads[1], NULL, send_thread_message, client);
    if (rc) {
        std::cerr << "Error: unable to create send thread, " << rc << std::endl;
        exit(-1);
    }

    // Wait for threads to finish
    for (int i = 0; i < num_threads; ++i) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}