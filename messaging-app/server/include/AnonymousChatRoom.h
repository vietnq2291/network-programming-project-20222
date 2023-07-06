#ifndef RANDOM_CHAT_ROOM
#define RANDOM_CHAT_ROOM

#include <vector>

#include "User.h"

struct AnonymousClient_t {
    int conn_fd;
    User* user;
    int random_seed; // match with other client with the same random seed
    int chat_id;
};
typedef struct AnonymousClient_t AnonymousClient;

struct RandomChat_t {
    AnonymousClient client1;
    AnonymousClient client2;

    AnonymousClient get_other_client(int conn_fd) {
        if (client1.conn_fd == conn_fd) return client2;
        return client1;
    }
};
typedef struct RandomChat_t RandomChat;

class AnonymousChatRoom {
public:
    AnonymousChatRoom();

    int add_client(int conn_fd, User* user);
    int get_chat_id(int conn_fd);
    int get_other_client_fd(int chat_id, int conn_fd);
    void remove_client_from_waiting_list(int conn_fd);
    bool end_chat(int chat_id);

private:
    std::vector<AnonymousClient> _waiting_list;
    std::vector<RandomChat> _chatting_list;

    int _max_random_seed; // max random seed for each client
};

#endif // RANDOM_CHAT_ROOM