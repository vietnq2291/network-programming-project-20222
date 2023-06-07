#ifndef COMMON_H
#define COMMON_H

const int DATA_SIZE = 5;

enum class MessageType {
    DATA,
    REQUEST,
    RESPONSE
};

enum class RequestType {
    SIGNUP,
    LOGIN,
    LOGOUT,
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
    ERROR
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

typedef struct {
    MessageType type;
    union {
        ChatHeader chat_header;
        RequestHeader request_header;
        ResponseHeader response_header;
    };
    int data_length;
    char data[DATA_SIZE];
} Message;


#endif // COMMON_H
