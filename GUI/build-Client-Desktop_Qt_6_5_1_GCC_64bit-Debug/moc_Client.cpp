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
    "std::vector<Friend>",
    "friend_list",
    "LogOutSuccess",
    "Authenticate",
    "username",
    "password",
    "SignUp",
    "setChat",
    "chat_name",
    "sendMessage",
    "packet",
    "receive_message",
    "LogOut",
    "connectSuccess",
    "loiSocket",
    "QAbstractSocket::SocketError",
    "err"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSclientENDCLASS_t {
    uint offsetsAndSizes[46];
    char stringdata0[7];
    char stringdata1[16];
    char stringdata2[1];
    char stringdata3[12];
    char stringdata4[8];
    char stringdata5[12];
    char stringdata6[20];
    char stringdata7[12];
    char stringdata8[14];
    char stringdata9[13];
    char stringdata10[9];
    char stringdata11[9];
    char stringdata12[7];
    char stringdata13[8];
    char stringdata14[10];
    char stringdata15[12];
    char stringdata16[7];
    char stringdata17[16];
    char stringdata18[7];
    char stringdata19[15];
    char stringdata20[10];
    char stringdata21[29];
    char stringdata22[4];
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
        QT_MOC_LITERAL(56, 19),  // "std::vector<Friend>"
        QT_MOC_LITERAL(76, 11),  // "friend_list"
        QT_MOC_LITERAL(88, 13),  // "LogOutSuccess"
        QT_MOC_LITERAL(102, 12),  // "Authenticate"
        QT_MOC_LITERAL(115, 8),  // "username"
        QT_MOC_LITERAL(124, 8),  // "password"
        QT_MOC_LITERAL(133, 6),  // "SignUp"
        QT_MOC_LITERAL(140, 7),  // "setChat"
        QT_MOC_LITERAL(148, 9),  // "chat_name"
        QT_MOC_LITERAL(158, 11),  // "sendMessage"
        QT_MOC_LITERAL(170, 6),  // "packet"
        QT_MOC_LITERAL(177, 15),  // "receive_message"
        QT_MOC_LITERAL(193, 6),  // "LogOut"
        QT_MOC_LITERAL(200, 14),  // "connectSuccess"
        QT_MOC_LITERAL(215, 9),  // "loiSocket"
        QT_MOC_LITERAL(225, 28),  // "QAbstractSocket::SocketError"
        QT_MOC_LITERAL(254, 3)   // "err"
    },
    "client",
    "messageReceived",
    "",
    "ChatMessage",
    "Message",
    "authSuccess",
    "std::vector<Friend>",
    "friend_list",
    "LogOutSuccess",
    "Authenticate",
    "username",
    "password",
    "SignUp",
    "setChat",
    "chat_name",
    "sendMessage",
    "packet",
    "receive_message",
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
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   80,    2, 0x06,    1 /* Public */,
       5,    1,   83,    2, 0x06,    3 /* Public */,
       8,    0,   86,    2, 0x06,    5 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       9,    2,   87,    2, 0x08,    6 /* Private */,
      12,    2,   92,    2, 0x08,    9 /* Private */,
      13,    1,   97,    2, 0x08,   12 /* Private */,
      15,    1,  100,    2, 0x08,   14 /* Private */,
      17,    0,  103,    2, 0x08,   16 /* Private */,
      18,    0,  104,    2, 0x08,   17 /* Private */,
      19,    0,  105,    2, 0x08,   18 /* Private */,
      20,    1,  106,    2, 0x08,   19 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   10,   11,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   10,   11,
    QMetaType::Void, QMetaType::QString,   14,
    QMetaType::Void, QMetaType::QString,   16,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 21,   22,

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
        QtPrivate::TypeAndForceComplete<std::vector<Friend>, std::false_type>,
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
        // method 'setChat'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'sendMessage'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'receive_message'
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
        case 1: _t->authSuccess((*reinterpret_cast< std::add_pointer_t<std::vector<Friend>>>(_a[1]))); break;
        case 2: _t->LogOutSuccess(); break;
        case 3: _t->Authenticate((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 4: _t->SignUp((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 5: _t->setChat((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 6: _t->sendMessage((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 7: _t->receive_message(); break;
        case 8: _t->LogOut(); break;
        case 9: _t->connectSuccess(); break;
        case 10: _t->loiSocket((*reinterpret_cast< std::add_pointer_t<QAbstractSocket::SocketError>>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 10:
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
            using _t = void (client::*)(std::vector<Friend> );
            if (_t _q_method = &client::authSuccess; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (client::*)();
            if (_t _q_method = &client::LogOutSuccess; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
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
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
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
void client::authSuccess(std::vector<Friend> _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void client::LogOutSuccess()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}
QT_WARNING_POP
