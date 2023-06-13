#ifndef COMMON_H
#define COMMON_H

const int DATA_SIZE = 50;

enum class MessageType {
    CHAT,
    REQUEST,
    RESPONSE,
    PUSH
};

enum class RequestType {
    SIGNUP,
    LOGIN,
    LOGOUT,
    UPDATE_ACCOUNT,
    ONLINE_USERS,
    CREATE_GROUP,
    INVITE_TO_GROUP,
    LEAVE_GROUP,
    ADD_FRIEND,
    ACCEPT_FRIEND,
    REMOVE_FRIEND,
    EXIT
};

enum class ResponseType {
    SUCCESS,
    FAILURE,
    ERROR,
};

enum class DataType {
    TEXT,
    FILE
};

enum class ChatType {
    PRIVATE_CHAT,
    GROUP_CHAT
};

enum class AccountStatus {
    ACTIVE,
    BLOCKED
};


typedef struct {
    ChatType chat_type;
    DataType data_type;
    int sender;
    int receiver;
    time_t timestamp;
    int fin; // finish flag: 1 if last message, 0 otherwise
    int seq; // sequence number (from 0 to last message)
} ChatHeader;

typedef struct {
    RequestType request_type;
    int sender;
} RequestHeader;

typedef struct {
    ResponseType response_type;
} ResponseHeader;

struct MessagePacket_t {
    MessagePacket_t() : type(), data_length(0) {};
    
    MessagePacket_t(MessageType message_type) : type(message_type), data_length(0) {}

    MessageType type;
    union {
        ChatHeader chat_header;
        RequestHeader request_header;
        ResponseHeader response_header;
    };
    int data_length;
    char data[DATA_SIZE];
};

typedef struct MessagePacket_t MessagePacket;


#endif // COMMON_H
