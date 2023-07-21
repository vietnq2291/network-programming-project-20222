/****************************************************************************
** Meta object code from reading C++ file 'Client.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Client/Client.h"
#include <QtNetwork/QSslPreSharedKeyAuthenticator>
#include <QtNetwork/QSslError>
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Client.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSclientENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSclientENDCLASS = QtMocHelpers::stringData(
    "client",
    "messageReceived",
    "",
    "ChatMessage",
    "Message",
    "authSuccess",
    "std::vector<Chat>",
    "chat_list",
    "std::vector<Friend>",
    "friend_list",
    "authSuccess1st",
    "resetUI",
    "recvFriendRequest",
    "std::string",
    "dispname",
    "id",
    "chatHistory",
    "message",
    "sender",
    "anonymousJoined",
    "LogOutSuccess",
    "Authenticate",
    "username",
    "password",
    "SignUp",
    "setChat",
    "chat_name",
    "sendMessage",
    "packet",
    "addGroup",
    "gname",
    "std::vector<QString>",
    "userList",
    "receive_message",
    "addFriend",
    "name",
    "accFriend",
    "denyFriend",
    "anonymousChatInit",
    "LogOut",
    "connectSuccess",
    "loiSocket",
    "QAbstractSocket::SocketError",
    "err"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSclientENDCLASS_t {
    uint offsetsAndSizes[88];
    char stringdata0[7];
    char stringdata1[16];
    char stringdata2[1];
    char stringdata3[12];
    char stringdata4[8];
    char stringdata5[12];
    char stringdata6[18];
    char stringdata7[10];
    char stringdata8[20];
    char stringdata9[12];
    char stringdata10[15];
    char stringdata11[8];
    char stringdata12[18];
    char stringdata13[12];
    char stringdata14[9];
    char stringdata15[3];
    char stringdata16[12];
    char stringdata17[8];
    char stringdata18[7];
    char stringdata19[16];
    char stringdata20[14];
    char stringdata21[13];
    char stringdata22[9];
    char stringdata23[9];
    char stringdata24[7];
    char stringdata25[8];
    char stringdata26[10];
    char stringdata27[12];
    char stringdata28[7];
    char stringdata29[9];
    char stringdata30[6];
    char stringdata31[21];
    char stringdata32[9];
    char stringdata33[16];
    char stringdata34[10];
    char stringdata35[5];
    char stringdata36[10];
    char stringdata37[11];
    char stringdata38[18];
    char stringdata39[7];
    char stringdata40[15];
    char stringdata41[10];
    char stringdata42[29];
    char stringdata43[4];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSclientENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSclientENDCLASS_t qt_meta_stringdata_CLASSclientENDCLASS = {
    {
        QT_MOC_LITERAL(0, 6),  // "client"
        QT_MOC_LITERAL(7, 15),  // "messageReceived"
        QT_MOC_LITERAL(23, 0),  // ""
        QT_MOC_LITERAL(24, 11),  // "ChatMessage"
        QT_MOC_LITERAL(36, 7),  // "Message"
        QT_MOC_LITERAL(44, 11),  // "authSuccess"
        QT_MOC_LITERAL(56, 17),  // "std::vector<Chat>"
        QT_MOC_LITERAL(74, 9),  // "chat_list"
        QT_MOC_LITERAL(84, 19),  // "std::vector<Friend>"
        QT_MOC_LITERAL(104, 11),  // "friend_list"
        QT_MOC_LITERAL(116, 14),  // "authSuccess1st"
        QT_MOC_LITERAL(131, 7),  // "resetUI"
        QT_MOC_LITERAL(139, 17),  // "recvFriendRequest"
        QT_MOC_LITERAL(157, 11),  // "std::string"
        QT_MOC_LITERAL(169, 8),  // "dispname"
        QT_MOC_LITERAL(178, 2),  // "id"
        QT_MOC_LITERAL(181, 11),  // "chatHistory"
        QT_MOC_LITERAL(193, 7),  // "message"
        QT_MOC_LITERAL(201, 6),  // "sender"
        QT_MOC_LITERAL(208, 15),  // "anonymousJoined"
        QT_MOC_LITERAL(224, 13),  // "LogOutSuccess"
        QT_MOC_LITERAL(238, 12),  // "Authenticate"
        QT_MOC_LITERAL(251, 8),  // "username"
        QT_MOC_LITERAL(260, 8),  // "password"
        QT_MOC_LITERAL(269, 6),  // "SignUp"
        QT_MOC_LITERAL(276, 7),  // "setChat"
        QT_MOC_LITERAL(284, 9),  // "chat_name"
        QT_MOC_LITERAL(294, 11),  // "sendMessage"
        QT_MOC_LITERAL(306, 6),  // "packet"
        QT_MOC_LITERAL(313, 8),  // "addGroup"
        QT_MOC_LITERAL(322, 5),  // "gname"
        QT_MOC_LITERAL(328, 20),  // "std::vector<QString>"
        QT_MOC_LITERAL(349, 8),  // "userList"
        QT_MOC_LITERAL(358, 15),  // "receive_message"
        QT_MOC_LITERAL(374, 9),  // "addFriend"
        QT_MOC_LITERAL(384, 4),  // "name"
        QT_MOC_LITERAL(389, 9),  // "accFriend"
        QT_MOC_LITERAL(399, 10),  // "denyFriend"
        QT_MOC_LITERAL(410, 17),  // "anonymousChatInit"
        QT_MOC_LITERAL(428, 6),  // "LogOut"
        QT_MOC_LITERAL(435, 14),  // "connectSuccess"
        QT_MOC_LITERAL(450, 9),  // "loiSocket"
        QT_MOC_LITERAL(460, 28),  // "QAbstractSocket::SocketError"
        QT_MOC_LITERAL(489, 3)   // "err"
    },
    "client",
    "messageReceived",
    "",
    "ChatMessage",
    "Message",
    "authSuccess",
    "std::vector<Chat>",
    "chat_list",
    "std::vector<Friend>",
    "friend_list",
    "authSuccess1st",
    "resetUI",
    "recvFriendRequest",
    "std::string",
    "dispname",
    "id",
    "chatHistory",
    "message",
    "sender",
    "anonymousJoined",
    "LogOutSuccess",
    "Authenticate",
    "username",
    "password",
    "SignUp",
    "setChat",
    "chat_name",
    "sendMessage",
    "packet",
    "addGroup",
    "gname",
    "std::vector<QString>",
    "userList",
    "receive_message",
    "addFriend",
    "name",
    "accFriend",
    "denyFriend",
    "anonymousChatInit",
    "LogOut",
    "connectSuccess",
    "loiSocket",
    "QAbstractSocket::SocketError",
    "err"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSclientENDCLASS[] = {

 // content:
      11,       // revision
       0,       // classname
       0,    0, // classinfo
      21,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       8,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,  140,    2, 0x06,    1 /* Public */,
       5,    2,  143,    2, 0x06,    3 /* Public */,
      10,    0,  148,    2, 0x06,    6 /* Public */,
      11,    0,  149,    2, 0x06,    7 /* Public */,
      12,    2,  150,    2, 0x06,    8 /* Public */,
      16,    2,  155,    2, 0x06,   11 /* Public */,
      19,    0,  160,    2, 0x06,   14 /* Public */,
      20,    0,  161,    2, 0x06,   15 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
      21,    2,  162,    2, 0x08,   16 /* Private */,
      24,    3,  167,    2, 0x08,   19 /* Private */,
      25,    1,  174,    2, 0x08,   23 /* Private */,
      27,    1,  177,    2, 0x08,   25 /* Private */,
      29,    2,  180,    2, 0x08,   27 /* Private */,
      33,    0,  185,    2, 0x08,   30 /* Private */,
      34,    1,  186,    2, 0x08,   31 /* Private */,
      36,    1,  189,    2, 0x08,   33 /* Private */,
      37,    1,  192,    2, 0x08,   35 /* Private */,
      38,    0,  195,    2, 0x08,   37 /* Private */,
      39,    0,  196,    2, 0x08,   38 /* Private */,
      40,    0,  197,    2, 0x08,   39 /* Private */,
      41,    1,  198,    2, 0x08,   40 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 6, 0x80000000 | 8,    7,    9,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 13, QMetaType::Int,   14,   15,
    QMetaType::Void, 0x80000000 | 3, QMetaType::QString,   17,   18,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   22,   23,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString,   22,   23,   14,
    QMetaType::Void, QMetaType::QString,   26,
    QMetaType::Void, QMetaType::QString,   28,
    QMetaType::Void, QMetaType::QString, 0x80000000 | 31,   30,   32,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   35,
    QMetaType::Void, QMetaType::Int,   15,
    QMetaType::Void, QMetaType::Int,   15,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 42,   43,

       0        // eod
};

Q_CONSTINIT const QMetaObject client::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_CLASSclientENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSclientENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSclientENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<client, std::true_type>,
        // method 'messageReceived'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<ChatMessage, std::false_type>,
        // method 'authSuccess'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const std::vector<Chat> &, std::false_type>,
        QtPrivate::TypeAndForceComplete<const std::vector<Friend> &, std::false_type>,
        // method 'authSuccess1st'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'resetUI'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'recvFriendRequest'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<std::string, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'chatHistory'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<ChatMessage, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'anonymousJoined'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'LogOutSuccess'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'Authenticate'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'SignUp'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'setChat'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'sendMessage'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'addGroup'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        QtPrivate::TypeAndForceComplete<std::vector<QString>, std::false_type>,
        // method 'receive_message'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'addFriend'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'accFriend'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'denyFriend'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'anonymousChatInit'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'LogOut'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'connectSuccess'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'loiSocket'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QAbstractSocket::SocketError, std::false_type>
    >,
    nullptr
} };

void client::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<client *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->messageReceived((*reinterpret_cast< std::add_pointer_t<ChatMessage>>(_a[1]))); break;
        case 1: _t->authSuccess((*reinterpret_cast< std::add_pointer_t<std::vector<Chat>>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<std::vector<Friend>>>(_a[2]))); break;
        case 2: _t->authSuccess1st(); break;
        case 3: _t->resetUI(); break;
        case 4: _t->recvFriendRequest((*reinterpret_cast< std::add_pointer_t<std::string>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2]))); break;
        case 5: _t->chatHistory((*reinterpret_cast< std::add_pointer_t<ChatMessage>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 6: _t->anonymousJoined(); break;
        case 7: _t->LogOutSuccess(); break;
        case 8: _t->Authenticate((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 9: _t->SignUp((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[3]))); break;
        case 10: _t->setChat((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 11: _t->sendMessage((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 12: _t->addGroup((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<std::vector<QString>>>(_a[2]))); break;
        case 13: _t->receive_message(); break;
        case 14: _t->addFriend((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 15: _t->accFriend((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 16: _t->denyFriend((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 17: _t->anonymousChatInit(); break;
        case 18: _t->LogOut(); break;
        case 19: _t->connectSuccess(); break;
        case 20: _t->loiSocket((*reinterpret_cast< std::add_pointer_t<QAbstractSocket::SocketError>>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< std::vector<Chat> >(); break;
            }
            break;
        case 20:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QAbstractSocket::SocketError >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (client::*)(ChatMessage );
            if (_t _q_method = &client::messageReceived; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (client::*)(const std::vector<Chat> & , const std::vector<Friend> & );
            if (_t _q_method = &client::authSuccess; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (client::*)();
            if (_t _q_method = &client::authSuccess1st; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (client::*)();
            if (_t _q_method = &client::resetUI; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (client::*)(std::string , int );
            if (_t _q_method = &client::recvFriendRequest; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (client::*)(ChatMessage , QString );
            if (_t _q_method = &client::chatHistory; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (client::*)();
            if (_t _q_method = &client::anonymousJoined; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (client::*)();
            if (_t _q_method = &client::LogOutSuccess; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 7;
                return;
            }
        }
    }
}

const QMetaObject *client::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *client::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSclientENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int client::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 21)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 21;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 21)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 21;
    }
    return _id;
}

// SIGNAL 0
void client::messageReceived(ChatMessage _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void client::authSuccess(const std::vector<Chat> & _t1, const std::vector<Friend> & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void client::authSuccess1st()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void client::resetUI()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void client::recvFriendRequest(std::string _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void client::chatHistory(ChatMessage _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void client::anonymousJoined()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}

// SIGNAL 7
void client::LogOutSuccess()
{
    QMetaObject::activate(this, &staticMetaObject, 7, nullptr);
}
QT_WARNING_POP
