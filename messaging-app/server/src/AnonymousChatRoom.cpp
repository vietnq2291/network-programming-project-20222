#include <iostream>
#include <vector>

#include "../include/AnonymousChatRoom.h"

AnonymousChatRoom::AnonymousChatRoom() {
    _waiting_list = std::vector<AnonymousClient>();
    _chatting_list = std::vector<RandomChat>();
    _max_random_seed = 3;
}

int AnonymousChatRoom::add_client(int conn_fd, User* user) {
    /* 
     * Return -1 if the client is added to the waiting list
     * Return -2 if the client is already in the waiting list
     * Return chat_id if the client is added to the chatting list
     */

    AnonymousClient client = {conn_fd, user, rand() % _max_random_seed};

    // check if client is already in the waiting list
    for (int i = 0; i < _waiting_list.size(); i++) {
        if (_waiting_list[i].conn_fd == client.conn_fd) {
            return -2;
        }
    }

    std::cout << "Waiting list:" << std::endl;
    for (int i = 0; i < _waiting_list.size(); i++) {
        std::cout << _waiting_list[i].conn_fd << " " << _waiting_list[i].random_seed << std::endl;
    }
    std::cout << client.conn_fd << " " << client.random_seed << std::endl;

    for (int i = 0; i < _waiting_list.size(); i++) {
        if (_waiting_list[i].random_seed == client.random_seed) {
            AnonymousClient client1 = _waiting_list[i];
            AnonymousClient client2 = client;
            _waiting_list.erase(_waiting_list.begin() + i);
            
            RandomChat chat = {client1, client2};
            int chat_id = _chatting_list.size();
            client1.chat_id = chat_id;
            client2.chat_id = chat_id;
            _chatting_list.push_back(chat);
            return chat_id;
        }
    }

    // no client with the same random seed
    _waiting_list.push_back(client);
    return -1;
}

int AnonymousChatRoom::get_other_client_fd(int chat_id, int conn_fd) {
    if (chat_id >= _chatting_list.size()) return -1;

    RandomChat chat = _chatting_list[chat_id];
    AnonymousClient other_client = chat.get_other_client(conn_fd);

    return other_client.conn_fd;
}

void AnonymousChatRoom::remove_client_from_waiting_list(int conn_fd) {
    for (int i = 0; i < _waiting_list.size(); i++) {
        if (_waiting_list[i].conn_fd == conn_fd) {
            _waiting_list.erase(_waiting_list.begin() + i);
            return;
        }
    }
}

bool AnonymousChatRoom::end_chat(int chat_id) {
    if (chat_id >= _chatting_list.size()) return false;

    _chatting_list.erase(_chatting_list.begin() + chat_id);
    return true;
}

int AnonymousChatRoom::get_chat_id(int conn_fd) {
    for (int i = 0; i < _chatting_list.size(); i++) {
        RandomChat chat = _chatting_list[i];
        if (chat.client1.conn_fd == conn_fd || chat.client2.conn_fd == conn_fd) {
            return i;
        }
    }
    
    return -1;
}
