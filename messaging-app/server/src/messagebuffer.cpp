#include <cstring>
#include "../include/messagebuffer.h"
#include "../../shared/common.h"

MessageBuffer::MessageBuffer(Message message) {
    _current_index = 0;
    _chat_type = message.chat_header.chat_type;
    _data_type = message.chat_header.data_type;
    _sender = message.chat_header.sender;
    _receiver = message.chat_header.receiver;
    _timestamp = message.chat_header.timestamp;

    add_message(message);
}

void MessageBuffer::add_message(Message message) {
    _messages.push_back(message);
    _fin = message.chat_header.fin;
}

bool MessageBuffer::get_next_message(Message& message) {
    if (_current_index >= _messages.size()) {
        _current_index = 0; // Reset the index for the next time this MessageBuffer is used
        return false; // No more messages to send
    }
    message = _messages[_current_index];
    _current_index++;
    return true;
}

int MessageBuffer::get_message_count() const {
    return _messages.size();
}

bool MessageBuffer::find(const Message& message) const {
    if (get_sender() == message.chat_header.sender &&
        get_receiver() == message.chat_header.receiver &&
        get_chat_type() == message.chat_header.chat_type &&
        get_data_type() == message.chat_header.data_type &&
        get_timestamp() == message.chat_header.timestamp) {
        return true;
    }
    return false;
}
