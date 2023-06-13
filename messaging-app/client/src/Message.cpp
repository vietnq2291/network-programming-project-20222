#include <cstring>
#include "../include/Message.h"
#include "../../shared/common.h"

Message::Message(std::string data, int sender, int receiver, ChatType chat_type, DataType data_type, time_t timestamp) {
    _current_index = 0;

    // Split the data into Message structs
    int offset = 0;
    int seq = 0;
    int length = data.length();

    while (offset < data.length()) {
        int chunk_size = std::min(length - offset, DATA_SIZE);

        MessagePacket packet;
        packet.type = MessageType::CHAT;
        packet.chat_header.chat_type = chat_type;
        packet.chat_header.data_type = data_type;
        packet.chat_header.sender = sender;
        packet.chat_header.receiver = receiver;
        packet.chat_header.timestamp = timestamp;
        packet.chat_header.fin = (offset + chunk_size == length) ? 1 : 0;
        packet.chat_header.seq = seq;
        memset(packet.data, 0, DATA_SIZE);
        memcpy(packet.data, data.c_str() + offset, chunk_size);
        packet.data_length = chunk_size;

        _packet_list.push_back(packet);
        offset += chunk_size;
        seq++;
    }
}

Message::Message(std::string data, int sender, RequestType request_type) {
    _init_request(sender, request_type);

    MessagePacket& packet = _packet_list.back();
    packet.request_header.request_type = request_type;
    memcpy(packet.data, data.c_str(), data.length());
    packet.data_length = data.length();
}

Message::Message(int sender, RequestType request_type) {
    _init_request(sender, request_type);

    MessagePacket& packet = _packet_list.back();
}

void Message::_init_request(int sender, RequestType request_type){
    _current_index = 0;
    
    MessagePacket packet;
    packet.type = MessageType::REQUEST;
    packet.request_header.request_type = request_type;
    packet.request_header.sender = sender;
    memset(packet.data, 0, DATA_SIZE);
    packet.data_length = 0;
    _packet_list.push_back(packet);
}

bool Message::get_next_packet(MessagePacket& packet) {
    if (_current_index >= _packet_list.size()) {
        return false; // No more messages to send
    }
    packet = _packet_list[_current_index];
    _current_index++;
    return true;
}
