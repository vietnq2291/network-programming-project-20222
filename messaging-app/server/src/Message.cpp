#include <cstring>
#include <iostream>

#include "../include/Message.h"
#include "../include/SQLQuery.h"
#include "../../shared/common.h"


Message::Message() {
    _current_index = 0;
    _is_complete = false;
}

Message::Message(MessagePacket packet) {
    _template_packet = packet;
    _current_index = 0;
    _is_complete = false;

    add_packet(packet);
}

void Message::add_packet(MessagePacket packet) {
    _packet_list.push_back(packet);
    if (packet.fin == 1) {
        _is_complete = true;
        _join_data();
    }
}

void Message::set_template_packet(MessagePacket packet) {
    _template_packet = packet;
    _current_index = 0;
    _is_complete = false;

    _packet_list.clear();
    add_packet(packet);
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

bool Message::is_match_header(const MessagePacket packet) {
    if (packet.type != _template_packet.type) {
        return false;
    }

    if (packet.type == MessageType::CHAT) {
        if (memcmp(&packet.chat_header, &_template_packet.chat_header, sizeof(ChatHeader)) == 0) {
            return true;
        }
    } else if (packet.type == MessageType::REQUEST) {
        if (memcmp(&packet.request_header, &_template_packet.request_header, sizeof(RequestHeader)) == 0) {
            return true;
        }
    } else if (packet.type == MessageType::RESPONSE) {
        if (memcmp(&packet.response_header, &_template_packet.response_header, sizeof(ResponseHeader)) == 0) {
            return true;
        }
    }

    return false;
}

void Message::_join_data() {
    _data = "";
    for (int i = 0; i < _packet_list.size(); i++) {
        _data += _packet_list[i].data;
    }
}

bool Message::save(SQLQuery sql_query, MessagePacket& response_packet) {
    /* Save the Chat Message to the database */
    if (_template_packet.type != MessageType::CHAT) {
        return false;
    }

    // search for chat_id
    std::string query = "SELECT `id` FROM `Chat` WHERE `id` = " + std::to_string(_template_packet.chat_header.chat_id) + ";";
    MYSQL_RES *result;

    sql_query.query(query, response_packet);
    if (sql_query.is_select_successful() == true) {
        if (sql_query.is_result_empty() == true) {
            response_packet.response_header.response_type = ResponseType::FAILURE;
            strcpy(response_packet.data, "Chat ID not found");
            response_packet.data_length = strlen(response_packet.data);
            return false;
        } else {
            // chat_id found, save message
            std::string data_type;
            if (_template_packet.chat_header.data_type == DataType::TEXT)
                data_type = "TEXT";
            else if (_template_packet.chat_header.data_type == DataType::FILE)
                data_type = "FILE";

            query  = "INSERT INTO `Message` (`chat_id`, `type`, `content`, `time_created`, `sender_id`) VALUES ("
                    + std::to_string(_template_packet.chat_header.chat_id) + ", '"
                    + data_type + "', '"
                    + _data + "', FROM_UNIXTIME("
                    + std::to_string(_template_packet.chat_header.timestamp) + "), "
                    + std::to_string(_template_packet.chat_header.sender) + ");";

            sql_query.query(query, response_packet);
            if (sql_query.is_insert_successful() == true) {
                response_packet.response_header.response_type = ResponseType::SUCCESS;
                strcpy(response_packet.data, "Message saved to database");
                response_packet.data_length = strlen(response_packet.data);
                return true;
            } else {
                response_packet.response_header.response_type = ResponseType::FAILURE;
                strcpy(response_packet.data, "Failed to save message to database");
                response_packet.data_length = strlen(response_packet.data);
                return false;
            }
        }
    } else {
        return false;
    }
}
