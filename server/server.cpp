#include <iostream>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>

using namespace std;

// define BACKLOG (max number of pending connection requests)
const int BACKLOG = 10;

// define buffer size
const int BUFF_SIZE = 1024;

enum class Status
{
    SUCCESS,
    FAIL
};

Status setup_server(int argc, char *argv[], int &listen_sock, struct sockaddr_in &server_addr, fd_set &master, fd_set &read_fds, int &fdmax)
{
    /* ----- read command line arguments ----- */
    if (argc != 2)
    {
        cerr << "Usage: server <port>" << endl;
        return Status::FAIL;
    }
    int port = atoi(argv[1]);

    /* ----- setup server socket ----- */
    // create listen socket
    if ((listen_sock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        cerr << "Can not create socket" << endl;
        return Status::FAIL;
    }

    // set server address
    bzero((char *)&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port); // network byte order
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    // set socket option to reuse port (prevent 'Address already in use' error)
    int opt = 1;
    setsockopt(listen_sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    // bind socket to server address
    if (bind(listen_sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
    {
        cerr << "Can not bind socket to address" << endl;
        return Status::FAIL;
    }

    // listen for incoming connection
    if (listen(listen_sock, BACKLOG) == -1)
    {
        cerr << "Can not listen on socket" << endl;
        return Status::FAIL;
    }

    /* ----- setup file descriptor sets ----- */
    // create file descriptor sets
    FD_ZERO(&master);
    FD_ZERO(&read_fds);

    // add listen socket to master set
    FD_SET(listen_sock, &master);

    // keep track of the biggest file descriptor
    fdmax = listen_sock;

    return Status::SUCCESS;
}

Status accept_request(int listen_sock_fd, int &conn_sock_fd, fd_set &master, fd_set &read_fds, int &fdmax)
{
    socklen_t sin_size;
    struct sockaddr_in client_addr;

    // accept new connection
    sin_size = sizeof(client_addr);
    if ((conn_sock_fd = accept(listen_sock_fd, (struct sockaddr *)&client_addr, &sin_size)) == -1)
    {
        cerr << "Can not accept connection" << endl;
        return Status::FAIL;
    }
    else
    {
        // add new connection to master set
        FD_SET(conn_sock_fd, &master);
        // update max file descriptor
        if (conn_sock_fd > fdmax)
            fdmax = conn_sock_fd;

        cout << "New connection from " << inet_ntoa(client_addr.sin_addr) << " on socket " << conn_sock_fd << endl;
    }

    return Status::SUCCESS;
}

int main(int argc, char *argv[])
{
    fd_set master, read_fds;
    int listen_sock_fd, conn_sock_fd;
    int fdmax;
    struct sockaddr_in server_addr;

    if(setup_server(argc, argv, listen_sock_fd, server_addr, master, read_fds, fdmax) == Status::FAIL) {
        return 1;
    }

    // communication loop
    while (1)
    {
        // list all the file descriptors in the master set ------------------ debug ------------------
        cout << "List of file descriptors in master set:" << endl;
        for (int i = 0; i <= fdmax; i++)
        {
            if (FD_ISSET(i, &master))
            {
                cout << "fd: " << i << endl;
            }
        }

        // select() will modify read_fds set, so we need to copy it to a temporary set
        read_fds = master;
        // wait for an activity on one of the sockets, timeout = NULL (wait indefinitely)
        if (select(fdmax + 1, &read_fds, NULL, NULL, NULL) == -1)
        {
            cerr << "Can not select socket" << endl;
            return 1;
        }

        // run through the existing connections looking for data to read
        for (int i = 0; i <= fdmax; i++)
        {
            if (FD_ISSET(i, &read_fds))
            {
                if (i == listen_sock_fd)
                {
                    if (accept_request(listen_sock_fd, conn_sock_fd, master, read_fds, fdmax) == Status::FAIL)
                    {
                        return 2;
                    }
                }
                else
                {
                    // handle data from a client
                    int bytes_received;
                    char data[BUFF_SIZE];
                    if ((bytes_received = recv(i, data, BUFF_SIZE, 0)) <= 0)
                    {
                        // got error or connection closed by client
                        if (bytes_received == 0)
                        {
                            // connection closed
                            cout << "Socket " << i << " hung up" << endl;
                        }
                        else
                        {
                            cerr << "Can not receive data from socket " << i << endl;
                        }
                        // close connection
                        close(i);
                        // remove from master set
                        FD_CLR(i, &master);
                    }
                    else
                    {
                        // we got some data from a client
                        data[bytes_received] = '\0';
                        cout << "Socket " << i << " sent: " << data << endl;

                        // send to all clients except the sender
                        for (int j = 0; j <= fdmax; j++)
                        {
                            // send to everyone except the listen socket and ourselves
                            if (FD_ISSET(j, &master) && j != listen_sock_fd && j != i)
                            {
                                if (send(j, data, bytes_received, 0) == -1)
                                {
                                    cerr << "Can not send data to socket " << j << endl;
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    return 0;
}
