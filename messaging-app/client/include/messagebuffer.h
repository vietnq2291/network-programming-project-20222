#ifndef MESSAGEBUFFER_H
#define MESSAGEBUFFER_H

#include <unistd.h>
#include <vector>
#include <string>
#include "../../shared/common.h"

class MessageBuffer {
public:
    MessageBuffer(std::string data, int sender, int receiver, ChatType chat_type, DataType data_type, time_t timestamp);

    // Get the next Message struct to send over the socket
    bool get_next_message(Message& message);

    // Get the total number of Message structs
    int get_message_count() const;

private:
    std::vector<Message> _messages; // Vector of Message structs
    int _current_index; // Index of the next Message to send
};

#endif // MESSAGEBUFFER_H