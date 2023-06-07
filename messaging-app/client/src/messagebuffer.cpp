#include <cstring>
#include "../include/messagebuffer.h"
#include "../../shared/common.h"

MessageBuffer::MessageBuffer(std::string data, int sender, int receiver, ChatType chat_type, DataType data_type, time_t timestamp) {
    _current_index = 0;

    // Split the data into Message structs
    int offset = 0;
    int seq = 0;
    int length = data.length();

    while (offset < data.length()) {
        int chunk_size = std::min(length - offset, DATA_SIZE);

        Message message;
        message.type = MessageType::DATA;
        message.chat_header.chat_type = chat_type;
        message.chat_header.data_type = data_type;
        message.chat_header.sender = sender;
        message.chat_header.receiver = receiver;
        message.chat_header.timestamp = timestamp;
        message.chat_header.fin = (offset + chunk_size == length) ? 1 : 0;
        message.chat_header.seq = seq;
        memset(message.data, 0, DATA_SIZE);
        memcpy(message.data, data.c_str() + offset, chunk_size);
        message.data_length = chunk_size;

        _messages.push_back(message);
        offset += chunk_size;
        seq++;
    }
}

bool MessageBuffer::get_next_message(Message& message) {
    if (_current_index >= _messages.size()) {
        return false; // No more messages to send
    }
    message = _messages[_current_index];
    _current_index++;
    return true;
}

int MessageBuffer::get_message_count() const {
    return _messages.size();
}
