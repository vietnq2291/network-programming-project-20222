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
    CREATE_PRIVATE_CHAT,
    CREATE_GROUP_CHAT,
    CREATE_ANONYMOUS_CHAT,
    END_ANONYMOUS_CHAT,
    GET_CHAT_LIST,
    ADD_TO_GROUP_CHAT,
    LEAVE_GROUP_CHAT,
    GET_GROUP_CHAT_MEMBERS,
    GET_FRIEND_LIST,
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
    ADD_TO_GROUP_CHAT_SUCCESS,
    ADD_TO_GROUP_CHAT_FAILURE,
    LEAVE_GROUP_CHAT_SUCCESS,
    GET_GROUP_CHAT_MEMBERS_SUCCESS,
    GET_FRIEND_LIST_SUCCESS,
    GET_CHAT_LIST_SUCCESS,
    WAIT_FOR_ANONYMOUS_CHAT,
    JOIN_ANONYMOUS_CHAT_SUCCESS,
};

enum class PushType {
    FRIEND_REQUEST,
    FRIEND_ACCEPT,
    FRIEND_REJECT,
    ANONYMOUS_CHAT_ENDED,
    GROUP_CHAT_JOINED,
    GROUP_CHAT_LEFT,
    GROUP_CHAT_NEW_MEMBER,
};

enum class DataType {
    TEXT,
    FILE
};

enum class ChatType {
    PRIVATE_CHAT,
    GROUP_CHAT,
    ANONYMOUS_CHAT
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
    MessagePacket_t() : type(), fin(1), seq(0), data_length(0) {}
    
    MessagePacket_t(MessageType message_type) : type(message_type), fin(1), seq(0), data_length(0) {}

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
