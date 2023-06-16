#ifndef MESSAGE_H
#define MESSAGE_H

#include <unistd.h>
#include <vector>
#include <string>
#include "../../shared/common.h"

class Message {
public:
    Message(MessageType message_type, ChatType chat_type, DataType data_type, int sender, int chat_id,  time_t timestamp, std::string data);
    Message(MessageType message_type, RequestType request_type, int sender, std::string data);
    Message(MessageType message_type, RequestType request_type, int sender);

    // Get the next MessagePacket struct in the list
    bool get_next_packet(MessagePacket& packet);

private:
    MessagePacket _template_packet;
    std::vector<MessagePacket> _packet_list; // List of MessagePacket structs
    int _current_index; // Index of the next MessagePacket struct in the list

    void _init();
    void _segment_data(std::string data);
};

#endif // MESSAGE_H