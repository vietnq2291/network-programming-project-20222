#include <cstring>
#include "../include/Message.h"
#include "../../shared/common.h"

Message::Message(MessageType message_type, ChatType chat_type, DataType data_type, int sender, int chat_id,  time_t timestamp, std::string data) {
    _init();

    _template_packet.type = message_type;
    _template_packet.chat_header.chat_type = chat_type;
    _template_packet.chat_header.data_type = data_type;
    _template_packet.chat_header.sender = sender;
    _template_packet.chat_header.chat_id = chat_id;
    _template_packet.chat_header.timestamp = timestamp;

    _segment_data(data);
}

Message::Message(MessageType message_type, RequestType request_type, int sender, std::string data) {
    _init();

    _template_packet.type = message_type;
    _template_packet.request_header.request_type = request_type;
    _template_packet.request_header.sender = sender;

    _segment_data(data);
}

Message::Message(MessageType message_type, RequestType request_type, int sender) {
    _init();

    _template_packet.type = message_type;
    _template_packet.request_header.request_type = request_type;
    _template_packet.request_header.sender = sender;

    _template_packet.fin = 1;
    _packet_list.push_back(_template_packet);
}

void Message::_init() {
    _current_index = 0;
    _packet_list.clear();
    memset(&_template_packet, 0, sizeof(_template_packet));
}

void Message::_segment_data(std::string data) {
    int offset = 0;
    int seq = 0;
    int length = data.length();

    while (offset < data.length()) {
        int chunk_size = std::min(length - offset, DATA_SIZE);

        MessagePacket packet;
        packet = _template_packet;
        packet.fin = (offset + chunk_size == length) ? 1 : 0;
        packet.seq = seq;
        packet.data_length = chunk_size;
        memcpy(packet.data, data.c_str() + offset, chunk_size);

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
