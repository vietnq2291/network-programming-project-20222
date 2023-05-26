#include <iostream>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/select.h>

using namespace std;

const int BUFF_SIZE = 1024;

enum class Status
{
    SUCCESS,
    FAIL
};

Status establish_connection(int argc, char *argv[], int &client_sock_fd, struct sockaddr_in &server_addr)
{
    /* ----- read command line arguments ----- */
    if (argc != 3)
    {
        printf("Usage: %s <server IP> <server port>\n", argv[0]);
        return Status::FAIL;
    }
    int server_port = atoi(argv[2]);
    char *server_IP = argv[1];

    /* ----- setup client socket ----- */
    // create socket
    if ((client_sock_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        cerr << "Can not create socket" << endl;
        return Status::FAIL;
    }

    // set server address
    bzero((char *)&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(server_port); // network byte order
    server_addr.sin_addr.s_addr = inet_addr(server_IP);

    // request to connect server
    if (connect(client_sock_fd, (struct sockaddr *)&server_addr, sizeof(struct sockaddr)) < 0)
    {
        printf("\nError!Can not connect to sever! Client exit imediately! ");
        return Status::FAIL;
    }

    return Status::SUCCESS;
}

Status send_message(int client_sock_fd, char *buff)
{
    int bytes_sent;

    bytes_sent = send(client_sock_fd, buff, strlen(buff), 0);
    if (bytes_sent < 0)
    {
        cerr << "Error: send failed!" << endl;
        return Status::FAIL;
    }

    return Status::SUCCESS;
}

Status recv_message(int client_sock_fd, char *buff)
{
    int bytes_received;

    bytes_received = recv(client_sock_fd, buff, BUFF_SIZE - 1, 0);
    if (bytes_received < 0)
    {
        cerr << "Error: receive failed!" << endl;
        return Status::FAIL;
    }
    else if (bytes_received == 0)
    {
        cerr << "Error: server closed connection!" << endl;
        return Status::FAIL;
    }
    else
    {
        buff[bytes_received] = '\0';
        cout << "Reply: " << buff << endl;
    }

    return Status::SUCCESS;
}

void input(char *buff)
{
    memset(buff, 0, BUFF_SIZE);
    fgets(buff, BUFF_SIZE, stdin);
}

int main(int argc, char *argv[])
{
    int client_sock_fd;
    struct sockaddr_in server_addr;

    if (establish_connection(argc, argv, client_sock_fd, server_addr) == Status::FAIL)
    {
        return 1;
    }

    char buff[BUFF_SIZE];
    fd_set readfds;

    while (1)
    {
        // clear the set ahead of time
        FD_ZERO(&readfds);

        // add our descriptors to the set
        FD_SET(client_sock_fd, &readfds);
        FD_SET(STDIN_FILENO, &readfds);

        // find the largest descriptor
        int maxfd = max(client_sock_fd, STDIN_FILENO);

        // wait until either socket has data ready to be recv()
        int rv = select(maxfd + 1, &readfds, NULL, NULL, NULL);

        if (rv == -1)
        {
            perror("select"); // error occurred in select()
        }
        else
        {
            // one or both of the descriptors have data
            if (FD_ISSET(STDIN_FILENO, &readfds))
            {
                input(buff);
                if (send_message(client_sock_fd, buff) == Status::FAIL)
                {
                    return 1;
                }
            }

            if (FD_ISSET(client_sock_fd, &readfds))
            {
                if (recv_message(client_sock_fd, buff) == Status::FAIL)
                {
                    return 1;
                }
            }
        }
    }

    close(client_sock_fd);
    return 0;
}
