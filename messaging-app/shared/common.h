#ifndef COMMON_H
#define COMMON_H

const int DEFAULT_PORT = 5050;
const char DEFAULT_IP[] = "127.0.0.1";

const int DEFAULT_BACKLOG = 10;
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
    CREATE_PRIVATE_CHAT,
    CREATE_GROUP_CHAT,
    INVITE_TO_GROUP,
    LEAVE_GROUP,
    ADD_FRIEND,
    ACCEPT_FRIEND,
    REJECT_FRIEND,
    REMOVE_FRIEND,
    EXIT
};

enum class ResponseType {
    SUCCESS,
    FAILURE,
    ERROR,
    LOGIN_SUCCESS,
    CREATE_PRIVATE_CHAT_SUCCESS,
    CREATE_GROUP_CHAT_SUCCESS,
};

enum class PushType {
    FRIEND_REQUEST,
    FRIEND_ACCEPT,
    FRIEND_REJECT,
    GROUP_INVITE,
    GROUP_LEAVE,
    GROUP_REMOVE
};

enum class DataType {
    TEXT,
    FILE
};

enum class ChatType {
    PRIVATE_CHAT,
    GROUP_CHAT
};

typedef struct {
    ChatType chat_type;
    DataType data_type;
    int sender;
    int chat_id;
    time_t timestamp;
} ChatHeader;

typedef struct {
    RequestType request_type;
    int sender;
} RequestHeader;

typedef struct {
    ResponseType response_type;
} ResponseHeader;

typedef struct {
    PushType push_type;
    int sender;
} PushHeader;

struct MessagePacket_t {
    MessagePacket_t() : type(), data_length(0) {};
    
    MessagePacket_t(MessageType message_type) : type(message_type), data_length(0) {};

    MessageType type;
    union {
        ChatHeader chat_header;
        RequestHeader request_header;
        ResponseHeader response_header;
        PushHeader push_header;
    };
    int fin; // finish flag: 1 if last message, 0 otherwise
    int seq; // sequence number (from 0 to last message)
    int data_length;
    char data[DATA_SIZE];
};

typedef struct MessagePacket_t MessagePacket;


#endif // COMMON_H
