#ifndef MESSAGE_H
#define MESSAGE_H

#include <unistd.h>
#include <vector>
#include <string>
#include "../../shared/common.h"

class Message {
public:
    Message(std::string data, int sender, int receiver, ChatType chat_type, DataType data_type, time_t timestamp);

    // Get the next MessagePacket struct in the list
    bool get_next_packet(MessagePacket& packet);

private:
    std::vector<MessagePacket> _packet_list; // List of MessagePacket structs
    int _current_index; // Index of the next MessagePacket struct in the list
};

#endif // MESSAGE_H