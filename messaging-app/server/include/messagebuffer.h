#ifndef MESSAGEBUFFER_H
#define MESSAGEBUFFER_H

#include <unistd.h>
#include <vector>
#include <string>
#include "../../shared/common.h"


class MessageBuffer {
public:
    MessageBuffer(Message message);

    void add_message(Message message);

    // Get the next Message struct to send over the socket
    bool get_next_message(Message& message);

    // Get the total number of Message structs
    int get_message_count() const; 

    // Check if the MessageBuffer contains a Message with the same header
    bool find(const Message& message) const;

    // Getters
    ChatType get_chat_type() const { return _chat_type; }
    DataType get_data_type() const { return _data_type; }
    int get_sender() const { return _sender; }
    int get_receiver() const { return _receiver; }
    int get_fin() const { return _fin; }
    time_t get_timestamp() const { return _timestamp; }


private:
    std::vector<Message> _messages; // Vector of Message structs
    int _current_index; // Index of the next Message to send

    ChatType _chat_type;
    DataType _data_type;
    int _sender; // user id
    int _receiver; // user id or group id
    time_t _timestamp;
    int _fin; // finish flag: 1 if last message received, 0 otherwise
};

#endif // MESSAGEBUFFER_H