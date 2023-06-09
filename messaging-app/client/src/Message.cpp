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
        packet.type = MessageType::DATA;
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

bool Message::get_next_packet(MessagePacket& packet) {
    if (_current_index >= _packet_list.size()) {
        return false; // No more messages to send
    }
    packet = _packet_list[_current_index];
    _current_index++;
    return true;
}
