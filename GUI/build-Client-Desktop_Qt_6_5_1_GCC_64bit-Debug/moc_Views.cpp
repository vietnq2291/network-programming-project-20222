/****************************************************************************
** Meta object code from reading C++ file 'Views.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Client/Views.h"
#include <QtGui/qtextcursor.h>
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
#error "The header file 'Views.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_CLASSviewsENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSviewsENDCLASS = QtMocHelpers::stringData(
    "views",
    "loggedInView",
    "",
    "recievedAuthView",
    "user",
    "pass",
    "recievedSignUpView",
    "username",
    "password",
    "dispname",
    "setChatView",
    "chat_name",
    "sendMessageView",
    "packet",
    "addGroupView",
    "gname",
    "std::vector<QString>",
    "userList",
    "recvMessage",
    "ChatMessage",
    "message",
    "addFriendView",
    "name",
    "denyFRView",
    "id",
    "accFRView",
    "initThread",
    "anonymousRequireView",
    "LogOutView",
    "recvAuth",
    "recvSignUp",
    "recvMsg",
    "setToChat",
    "sendMessage",
    "addGroup",
    "addFriend",
    "RequestFriend",
    "std::string",
    "denyFR",
    "accFR",
    "resetUI",
    "loadChatHistory",
    "sender",
    "setupAnonymous",
    "anonymousRequire",
    "LogOut",
    "switchToChat",
    "switchToLogin",
    "initChat",
    "std::vector<Chat>",
    "chatList",
    "std::vector<Friend>",
    "friendList"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSviewsENDCLASS_t {
    uint offsetsAndSizes[106];
    char stringdata0[6];
    char stringdata1[13];
    char stringdata2[1];
    char stringdata3[17];
    char stringdata4[5];
    char stringdata5[5];
    char stringdata6[19];
    char stringdata7[9];
    char stringdata8[9];
    char stringdata9[9];
    char stringdata10[12];
    char stringdata11[10];
    char stringdata12[16];
    char stringdata13[7];
    char stringdata14[13];
    char stringdata15[6];
    char stringdata16[21];
    char stringdata17[9];
    char stringdata18[12];
    char stringdata19[12];
    char stringdata20[8];
    char stringdata21[14];
    char stringdata22[5];
    char stringdata23[11];
    char stringdata24[3];
    char stringdata25[10];
    char stringdata26[11];
    char stringdata27[21];
    char stringdata28[11];
    char stringdata29[9];
    char stringdata30[11];
    char stringdata31[8];
    char stringdata32[10];
    char stringdata33[12];
    char stringdata34[9];
    char stringdata35[10];
    char stringdata36[14];
    char stringdata37[12];
    char stringdata38[7];
    char stringdata39[6];
    char stringdata40[8];
    char stringdata41[16];
    char stringdata42[7];
    char stringdata43[15];
    char stringdata44[17];
    char stringdata45[7];
    char stringdata46[13];
    char stringdata47[14];
    char stringdata48[9];
    char stringdata49[18];
    char stringdata50[9];
    char stringdata51[20];
    char stringdata52[11];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSviewsENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSviewsENDCLASS_t qt_meta_stringdata_CLASSviewsENDCLASS = {
    {
        QT_MOC_LITERAL(0, 5),  // "views"
        QT_MOC_LITERAL(6, 12),  // "loggedInView"
        QT_MOC_LITERAL(19, 0),  // ""
        QT_MOC_LITERAL(20, 16),  // "recievedAuthView"
        QT_MOC_LITERAL(37, 4),  // "user"
        QT_MOC_LITERAL(42, 4),  // "pass"
        QT_MOC_LITERAL(47, 18),  // "recievedSignUpView"
        QT_MOC_LITERAL(66, 8),  // "username"
        QT_MOC_LITERAL(75, 8),  // "password"
        QT_MOC_LITERAL(84, 8),  // "dispname"
        QT_MOC_LITERAL(93, 11),  // "setChatView"
        QT_MOC_LITERAL(105, 9),  // "chat_name"
        QT_MOC_LITERAL(115, 15),  // "sendMessageView"
        QT_MOC_LITERAL(131, 6),  // "packet"
        QT_MOC_LITERAL(138, 12),  // "addGroupView"
        QT_MOC_LITERAL(151, 5),  // "gname"
        QT_MOC_LITERAL(157, 20),  // "std::vector<QString>"
        QT_MOC_LITERAL(178, 8),  // "userList"
        QT_MOC_LITERAL(187, 11),  // "recvMessage"
        QT_MOC_LITERAL(199, 11),  // "ChatMessage"
        QT_MOC_LITERAL(211, 7),  // "message"
        QT_MOC_LITERAL(219, 13),  // "addFriendView"
        QT_MOC_LITERAL(233, 4),  // "name"
        QT_MOC_LITERAL(238, 10),  // "denyFRView"
        QT_MOC_LITERAL(249, 2),  // "id"
        QT_MOC_LITERAL(252, 9),  // "accFRView"
        QT_MOC_LITERAL(262, 10),  // "initThread"
        QT_MOC_LITERAL(273, 20),  // "anonymousRequireView"
        QT_MOC_LITERAL(294, 10),  // "LogOutView"
        QT_MOC_LITERAL(305, 8),  // "recvAuth"
        QT_MOC_LITERAL(314, 10),  // "recvSignUp"
        QT_MOC_LITERAL(325, 7),  // "recvMsg"
        QT_MOC_LITERAL(333, 9),  // "setToChat"
        QT_MOC_LITERAL(343, 11),  // "sendMessage"
        QT_MOC_LITERAL(355, 8),  // "addGroup"
        QT_MOC_LITERAL(364, 9),  // "addFriend"
        QT_MOC_LITERAL(374, 13),  // "RequestFriend"
        QT_MOC_LITERAL(388, 11),  // "std::string"
        QT_MOC_LITERAL(400, 6),  // "denyFR"
        QT_MOC_LITERAL(407, 5),  // "accFR"
        QT_MOC_LITERAL(413, 7),  // "resetUI"
        QT_MOC_LITERAL(421, 15),  // "loadChatHistory"
        QT_MOC_LITERAL(437, 6),  // "sender"
        QT_MOC_LITERAL(444, 14),  // "setupAnonymous"
        QT_MOC_LITERAL(459, 16),  // "anonymousRequire"
        QT_MOC_LITERAL(476, 6),  // "LogOut"
        QT_MOC_LITERAL(483, 12),  // "switchToChat"
        QT_MOC_LITERAL(496, 13),  // "switchToLogin"
        QT_MOC_LITERAL(510, 8),  // "initChat"
        QT_MOC_LITERAL(519, 17),  // "std::vector<Chat>"
        QT_MOC_LITERAL(537, 8),  // "chatList"
        QT_MOC_LITERAL(546, 19),  // "std::vector<Friend>"
        QT_MOC_LITERAL(566, 10)   // "friendList"
    },
    "views",
    "loggedInView",
    "",
    "recievedAuthView",
    "user",
    "pass",
    "recievedSignUpView",
    "username",
    "password",
    "dispname",
    "setChatView",
    "chat_name",
    "sendMessageView",
    "packet",
    "addGroupView",
    "gname",
    "std::vector<QString>",
    "userList",
    "recvMessage",
    "ChatMessage",
    "message",
    "addFriendView",
    "name",
    "denyFRView",
    "id",
    "accFRView",
    "initThread",
    "anonymousRequireView",
    "LogOutView",
    "recvAuth",
    "recvSignUp",
    "recvMsg",
    "setToChat",
    "sendMessage",
    "addGroup",
    "addFriend",
    "RequestFriend",
    "std::string",
    "denyFR",
    "accFR",
    "resetUI",
    "loadChatHistory",
    "sender",
    "setupAnonymous",
    "anonymousRequire",
    "LogOut",
    "switchToChat",
    "switchToLogin",
    "initChat",
    "std::vector<Chat>",
    "chatList",
    "std::vector<Friend>",
    "friendList"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSviewsENDCLASS[] = {

 // content:
      11,       // revision
       0,       // classname
       0,    0, // classinfo
      31,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      13,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,  200,    2, 0x06,    1 /* Public */,
       3,    2,  201,    2, 0x06,    2 /* Public */,
       6,    3,  206,    2, 0x06,    5 /* Public */,
      10,    1,  213,    2, 0x06,    9 /* Public */,
      12,    1,  216,    2, 0x06,   11 /* Public */,
      14,    2,  219,    2, 0x06,   13 /* Public */,
      18,    1,  224,    2, 0x06,   16 /* Public */,
      21,    1,  227,    2, 0x06,   18 /* Public */,
      23,    1,  230,    2, 0x06,   20 /* Public */,
      25,    1,  233,    2, 0x06,   22 /* Public */,
      26,    0,  236,    2, 0x06,   24 /* Public */,
      27,    0,  237,    2, 0x06,   25 /* Public */,
      28,    0,  238,    2, 0x06,   26 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
      29,    2,  239,    2, 0x08,   27 /* Private */,
      30,    3,  244,    2, 0x08,   30 /* Private */,
      31,    1,  251,    2, 0x08,   34 /* Private */,
      32,    1,  254,    2, 0x08,   36 /* Private */,
      33,    1,  257,    2, 0x08,   38 /* Private */,
      34,    2,  260,    2, 0x08,   40 /* Private */,
      35,    1,  265,    2, 0x08,   43 /* Private */,
      36,    2,  268,    2, 0x08,   45 /* Private */,
      38,    1,  273,    2, 0x08,   48 /* Private */,
      39,    1,  276,    2, 0x08,   50 /* Private */,
      40,    0,  279,    2, 0x08,   52 /* Private */,
      41,    2,  280,    2, 0x08,   53 /* Private */,
      43,    0,  285,    2, 0x08,   56 /* Private */,
      44,    0,  286,    2, 0x08,   57 /* Private */,
      45,    0,  287,    2, 0x08,   58 /* Private */,
      46,    0,  288,    2, 0x08,   59 /* Private */,
      47,    0,  289,    2, 0x08,   60 /* Private */,
      48,    2,  290,    2, 0x08,   61 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    4,    5,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString,    7,    8,    9,
    QMetaType::Void, QMetaType::QString,   11,
    QMetaType::Void, QMetaType::QString,   13,
    QMetaType::Void, QMetaType::QString, 0x80000000 | 16,   15,   17,
    QMetaType::Void, 0x80000000 | 19,   20,
    QMetaType::Void, QMetaType::QString,   22,
    QMetaType::Void, QMetaType::Int,   24,
    QMetaType::Void, QMetaType::Int,   24,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    4,    5,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString,    7,    8,    9,
    QMetaType::Void, 0x80000000 | 19,   20,
    QMetaType::Void, QMetaType::QString,   11,
    QMetaType::Void, QMetaType::QString,   13,
    QMetaType::Void, QMetaType::QString, 0x80000000 | 16,   15,   17,
    QMetaType::Void, QMetaType::QString,   22,
    QMetaType::Void, 0x80000000 | 37, QMetaType::Int,    9,   24,
    QMetaType::Void, QMetaType::Int,   24,
    QMetaType::Void, QMetaType::Int,   24,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 19, QMetaType::QString,   20,   42,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 49, 0x80000000 | 51,   50,   52,

       0        // eod
};

Q_CONSTINIT const QMetaObject views::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_CLASSviewsENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSviewsENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSviewsENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<views, std::true_type>,
        // method 'loggedInView'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'recievedAuthView'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'recievedSignUpView'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'setChatView'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'sendMessageView'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'addGroupView'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        QtPrivate::TypeAndForceComplete<std::vector<QString>, std::false_type>,
        // method 'recvMessage'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<ChatMessage, std::false_type>,
        // method 'addFriendView'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'denyFRView'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'accFRView'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'initThread'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'anonymousRequireView'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'LogOutView'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'recvAuth'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'recvSignUp'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'recvMsg'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<ChatMessage, std::false_type>,
        // method 'setToChat'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'sendMessage'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'addGroup'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        QtPrivate::TypeAndForceComplete<std::vector<QString>, std::false_type>,
        // method 'addFriend'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'RequestFriend'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<std::string, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'denyFR'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'accFR'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'resetUI'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'loadChatHistory'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<ChatMessage, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'setupAnonymous'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'anonymousRequire'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'LogOut'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'switchToChat'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'switchToLogin'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'initChat'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<std::vector<Chat>, std::false_type>,
        QtPrivate::TypeAndForceComplete<std::vector<Friend>, std::false_type>
    >,
    nullptr
} };

void views::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<views *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->loggedInView(); break;
        case 1: _t->recievedAuthView((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 2: _t->recievedSignUpView((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[3]))); break;
        case 3: _t->setChatView((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 4: _t->sendMessageView((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 5: _t->addGroupView((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<std::vector<QString>>>(_a[2]))); break;
        case 6: _t->recvMessage((*reinterpret_cast< std::add_pointer_t<ChatMessage>>(_a[1]))); break;
        case 7: _t->addFriendView((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 8: _t->denyFRView((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 9: _t->accFRView((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 10: _t->initThread(); break;
        case 11: _t->anonymousRequireView(); break;
        case 12: _t->LogOutView(); break;
        case 13: _t->recvAuth((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 14: _t->recvSignUp((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[3]))); break;
        case 15: _t->recvMsg((*reinterpret_cast< std::add_pointer_t<ChatMessage>>(_a[1]))); break;
        case 16: _t->setToChat((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 17: _t->sendMessage((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 18: _t->addGroup((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<std::vector<QString>>>(_a[2]))); break;
        case 19: _t->addFriend((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 20: _t->RequestFriend((*reinterpret_cast< std::add_pointer_t<std::string>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2]))); break;
        case 21: _t->denyFR((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 22: _t->accFR((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 23: _t->resetUI(); break;
        case 24: _t->loadChatHistory((*reinterpret_cast< std::add_pointer_t<ChatMessage>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 25: _t->setupAnonymous(); break;
        case 26: _t->anonymousRequire(); break;
        case 27: _t->LogOut(); break;
        case 28: _t->switchToChat(); break;
        case 29: _t->switchToLogin(); break;
        case 30: _t->initChat((*reinterpret_cast< std::add_pointer_t<std::vector<Chat>>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<std::vector<Friend>>>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 30:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< std::vector<Chat> >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (views::*)();
            if (_t _q_method = &views::loggedInView; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (views::*)(QString , QString );
            if (_t _q_method = &views::recievedAuthView; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (views::*)(QString , QString , QString );
            if (_t _q_method = &views::recievedSignUpView; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (views::*)(QString );
            if (_t _q_method = &views::setChatView; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (views::*)(QString );
            if (_t _q_method = &views::sendMessageView; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (views::*)(QString , std::vector<QString> );
            if (_t _q_method = &views::addGroupView; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (views::*)(ChatMessage );
            if (_t _q_method = &views::recvMessage; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (views::*)(QString );
            if (_t _q_method = &views::addFriendView; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (views::*)(int );
            if (_t _q_method = &views::denyFRView; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (views::*)(int );
            if (_t _q_method = &views::accFRView; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 9;
                return;
            }
        }
        {
            using _t = void (views::*)();
            if (_t _q_method = &views::initThread; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 10;
                return;
            }
        }
        {
            using _t = void (views::*)();
            if (_t _q_method = &views::anonymousRequireView; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 11;
                return;
            }
        }
        {
            using _t = void (views::*)();
            if (_t _q_method = &views::LogOutView; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 12;
                return;
            }
        }
    }
}

const QMetaObject *views::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *views::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSviewsENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int views::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 31)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 31;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 31)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 31;
    }
    return _id;
}

// SIGNAL 0
void views::loggedInView()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void views::recievedAuthView(QString _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void views::recievedSignUpView(QString _t1, QString _t2, QString _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void views::setChatView(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void views::sendMessageView(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void views::addGroupView(QString _t1, std::vector<QString> _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void views::recvMessage(ChatMessage _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void views::addFriendView(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void views::denyFRView(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void views::accFRView(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void views::initThread()
{
    QMetaObject::activate(this, &staticMetaObject, 10, nullptr);
}

// SIGNAL 11
void views::anonymousRequireView()
{
    QMetaObject::activate(this, &staticMetaObject, 11, nullptr);
}

// SIGNAL 12
void views::LogOutView()
{
    QMetaObject::activate(this, &staticMetaObject, 12, nullptr);
}
QT_WARNING_POP
