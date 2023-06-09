#ifndef MESSAGE_H
#define MESSAGE_H

#include <vector>
#include <string>
#include "../../shared/common.h"


class Message {
public:
    Message(MessagePacket packet);

    void add_packet(MessagePacket packet);

    // Get the next MessagePacket struct to send over the socket
    bool get_next_packet(MessagePacket& packet);

    // Check if the Message contains a Message with the same header
    bool find(MessagePacket packet) const;

    // Getters
    ChatType get_chat_type() const { return _chat_type; }
    DataType get_data_type() const { return _data_type; }
    int get_sender() const { return _sender; }
    int get_receiver() const { return _receiver; }
    int get_fin() const { return _fin; }
    time_t get_timestamp() const { return _timestamp; }


private:
    std::vector<MessagePacket> _packet_list; // List of MessagePacket structs
    int _current_index; // Index of the next Message to send

    ChatType _chat_type;
    DataType _data_type;
    int _sender; // user id
    int _receiver; // user id or group id
    time_t _timestamp;
    int _fin; // finish flag: 1 if last message received, 0 otherwise
};

#endif // MESSAGE_H