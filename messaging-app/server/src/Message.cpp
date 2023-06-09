#include <cstring>
#include "../include/Message.h"
#include "../../shared/common.h"

Message::Message(MessagePacket packet) {
    _current_index = 0;

    _chat_type = packet.chat_header.chat_type;
    _data_type = packet.chat_header.data_type;
    _sender = packet.chat_header.sender;
    _receiver = packet.chat_header.receiver;
    _timestamp = packet.chat_header.timestamp;

    add_packet(packet);
}

void Message::add_packet(MessagePacket packet) {
    _packet_list.push_back(packet);
    _fin = packet.chat_header.fin;
}

bool Message::get_next_packet(MessagePacket& packet) {
    if (_current_index >= _packet_list.size()) {
        _current_index = 0; // Reset the index for the next time this Message is used
        return false; // No more packet to send
    }
    packet = _packet_list[_current_index];
    _current_index++;
    return true;
}

bool Message::find(const MessagePacket packet) const {
    if (get_sender() == packet.chat_header.sender &&
        get_receiver() == packet.chat_header.receiver &&
        get_chat_type() == packet.chat_header.chat_type &&
        get_data_type() == packet.chat_header.data_type &&
        get_timestamp() == packet.chat_header.timestamp) {
        return true;
    }
    return false;
}
