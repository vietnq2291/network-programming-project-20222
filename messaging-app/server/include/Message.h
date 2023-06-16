#ifndef MESSAGE_H
#define MESSAGE_H

#include <vector>
#include <string>
#include "../../shared/common.h"
#include "SQLQuery.h"


class Message {
public:
    Message();
    Message(MessagePacket packet);

    void add_packet(MessagePacket packet);

    // Get the next MessagePacket struct to send over the socket
    bool get_next_packet(MessagePacket& packet);

    // Check if the MessagePacket should be added to the Message (ie: same header)
    bool is_match_header(MessagePacket packet);

    // save the Message to the database
    bool save(SQLQuery sql_query, MessagePacket& response_packet);

    // Getters
    bool is_complete() const { return _is_complete; }
    MessageType get_message_type() const { return _template_packet.type; }
    ChatType get_chat_type() const { return _template_packet.chat_header.chat_type; }
    RequestType get_request_type() const { return _template_packet.request_header.request_type; }
    int get_request_sender() const { return _template_packet.request_header.sender; }
    int get_chat_sender() const { return _template_packet.chat_header.sender; }
    int get_chat_id() const { return _template_packet.chat_header.chat_id; }

    std::string get_data() const { return _data; }

    // Setters
    void set_template_packet(MessagePacket packet);


private:
    std::vector<MessagePacket> _packet_list; // List of MessagePacket structs
    int _current_index; // Index of the next Message to send
    bool _is_complete;
    std::string _data;

    MessagePacket _template_packet;
    void _join_data();
};

#endif // MESSAGE_H