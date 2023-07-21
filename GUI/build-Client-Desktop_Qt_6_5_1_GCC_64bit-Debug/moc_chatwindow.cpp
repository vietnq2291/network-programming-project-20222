/****************************************************************************
** Meta object code from reading C++ file 'chatwindow.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Client/chatwindow.h"
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
#error "The header file 'chatwindow.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_CLASSChatWindowENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSChatWindowENDCLASS = QtMocHelpers::stringData(
    "ChatWindow",
    "chooseChat",
    "",
    "chat_name",
    "sendMessage",
    "message",
    "addGroup",
    "gname",
    "std::vector<QString>",
    "userList",
    "addFriend",
    "name",
    "acceptFriendRequest",
    "id",
    "denyFriendRequest",
    "anonymousRequire",
    "LogOut",
    "pressSendButton",
    "pressSendEnter",
    "recvMsg",
    "ChatMessage",
    "checkUser",
    "username",
    "addToGroup",
    "on_LogOutButton_clicked",
    "on_listChat_itemClicked",
    "QListWidgetItem*",
    "item",
    "on_AddFriendButton_clicked",
    "on_ChatWindow_destroyed",
    "on_AddGroupButton_clicked",
    "on_pushButton_clicked"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSChatWindowENDCLASS_t {
    uint offsetsAndSizes[64];
    char stringdata0[11];
    char stringdata1[11];
    char stringdata2[1];
    char stringdata3[10];
    char stringdata4[12];
    char stringdata5[8];
    char stringdata6[9];
    char stringdata7[6];
    char stringdata8[21];
    char stringdata9[9];
    char stringdata10[10];
    char stringdata11[5];
    char stringdata12[20];
    char stringdata13[3];
    char stringdata14[18];
    char stringdata15[17];
    char stringdata16[7];
    char stringdata17[16];
    char stringdata18[15];
    char stringdata19[8];
    char stringdata20[12];
    char stringdata21[10];
    char stringdata22[9];
    char stringdata23[11];
    char stringdata24[24];
    char stringdata25[24];
    char stringdata26[17];
    char stringdata27[5];
    char stringdata28[27];
    char stringdata29[24];
    char stringdata30[26];
    char stringdata31[22];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSChatWindowENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSChatWindowENDCLASS_t qt_meta_stringdata_CLASSChatWindowENDCLASS = {
    {
        QT_MOC_LITERAL(0, 10),  // "ChatWindow"
        QT_MOC_LITERAL(11, 10),  // "chooseChat"
        QT_MOC_LITERAL(22, 0),  // ""
        QT_MOC_LITERAL(23, 9),  // "chat_name"
        QT_MOC_LITERAL(33, 11),  // "sendMessage"
        QT_MOC_LITERAL(45, 7),  // "message"
        QT_MOC_LITERAL(53, 8),  // "addGroup"
        QT_MOC_LITERAL(62, 5),  // "gname"
        QT_MOC_LITERAL(68, 20),  // "std::vector<QString>"
        QT_MOC_LITERAL(89, 8),  // "userList"
        QT_MOC_LITERAL(98, 9),  // "addFriend"
        QT_MOC_LITERAL(108, 4),  // "name"
        QT_MOC_LITERAL(113, 19),  // "acceptFriendRequest"
        QT_MOC_LITERAL(133, 2),  // "id"
        QT_MOC_LITERAL(136, 17),  // "denyFriendRequest"
        QT_MOC_LITERAL(154, 16),  // "anonymousRequire"
        QT_MOC_LITERAL(171, 6),  // "LogOut"
        QT_MOC_LITERAL(178, 15),  // "pressSendButton"
        QT_MOC_LITERAL(194, 14),  // "pressSendEnter"
        QT_MOC_LITERAL(209, 7),  // "recvMsg"
        QT_MOC_LITERAL(217, 11),  // "ChatMessage"
        QT_MOC_LITERAL(229, 9),  // "checkUser"
        QT_MOC_LITERAL(239, 8),  // "username"
        QT_MOC_LITERAL(248, 10),  // "addToGroup"
        QT_MOC_LITERAL(259, 23),  // "on_LogOutButton_clicked"
        QT_MOC_LITERAL(283, 23),  // "on_listChat_itemClicked"
        QT_MOC_LITERAL(307, 16),  // "QListWidgetItem*"
        QT_MOC_LITERAL(324, 4),  // "item"
        QT_MOC_LITERAL(329, 26),  // "on_AddFriendButton_clicked"
        QT_MOC_LITERAL(356, 23),  // "on_ChatWindow_destroyed"
        QT_MOC_LITERAL(380, 25),  // "on_AddGroupButton_clicked"
        QT_MOC_LITERAL(406, 21)   // "on_pushButton_clicked"
    },
    "ChatWindow",
    "chooseChat",
    "",
    "chat_name",
    "sendMessage",
    "message",
    "addGroup",
    "gname",
    "std::vector<QString>",
    "userList",
    "addFriend",
    "name",
    "acceptFriendRequest",
    "id",
    "denyFriendRequest",
    "anonymousRequire",
    "LogOut",
    "pressSendButton",
    "pressSendEnter",
    "recvMsg",
    "ChatMessage",
    "checkUser",
    "username",
    "addToGroup",
    "on_LogOutButton_clicked",
    "on_listChat_itemClicked",
    "QListWidgetItem*",
    "item",
    "on_AddFriendButton_clicked",
    "on_ChatWindow_destroyed",
    "on_AddGroupButton_clicked",
    "on_pushButton_clicked"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSChatWindowENDCLASS[] = {

 // content:
      11,       // revision
       0,       // classname
       0,    0, // classinfo
      19,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       8,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,  128,    2, 0x06,    1 /* Public */,
       4,    1,  131,    2, 0x06,    3 /* Public */,
       6,    2,  134,    2, 0x06,    5 /* Public */,
      10,    1,  139,    2, 0x06,    8 /* Public */,
      12,    1,  142,    2, 0x06,   10 /* Public */,
      14,    1,  145,    2, 0x06,   12 /* Public */,
      15,    0,  148,    2, 0x06,   14 /* Public */,
      16,    0,  149,    2, 0x06,   15 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
      17,    0,  150,    2, 0x08,   16 /* Private */,
      18,    0,  151,    2, 0x08,   17 /* Private */,
      19,    1,  152,    2, 0x08,   18 /* Private */,
      21,    1,  155,    2, 0x08,   20 /* Private */,
      23,    2,  158,    2, 0x08,   22 /* Private */,
      24,    0,  163,    2, 0x08,   25 /* Private */,
      25,    1,  164,    2, 0x08,   26 /* Private */,
      28,    0,  167,    2, 0x08,   28 /* Private */,
      29,    0,  168,    2, 0x08,   29 /* Private */,
      30,    0,  169,    2, 0x08,   30 /* Private */,
      31,    0,  170,    2, 0x08,   31 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void, QMetaType::QString, 0x80000000 | 8,    7,    9,
    QMetaType::Void, QMetaType::QString,   11,
    QMetaType::Void, QMetaType::Int,   13,
    QMetaType::Void, QMetaType::Int,   13,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 20,    5,
    QMetaType::Void, QMetaType::QString,   22,
    QMetaType::Void, QMetaType::QString, 0x80000000 | 8,    7,    9,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 26,   27,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject ChatWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_CLASSChatWindowENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSChatWindowENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSChatWindowENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<ChatWindow, std::true_type>,
        // method 'chooseChat'
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
        // method 'acceptFriendRequest'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'denyFriendRequest'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'anonymousRequire'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'LogOut'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'pressSendButton'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'pressSendEnter'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'recvMsg'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<ChatMessage, std::false_type>,
        // method 'checkUser'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'addToGroup'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        QtPrivate::TypeAndForceComplete<std::vector<QString>, std::false_type>,
        // method 'on_LogOutButton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_listChat_itemClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QListWidgetItem *, std::false_type>,
        // method 'on_AddFriendButton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_ChatWindow_destroyed'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_AddGroupButton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_pushButton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void ChatWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ChatWindow *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->chooseChat((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 1: _t->sendMessage((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 2: _t->addGroup((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<std::vector<QString>>>(_a[2]))); break;
        case 3: _t->addFriend((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 4: _t->acceptFriendRequest((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 5: _t->denyFriendRequest((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 6: _t->anonymousRequire(); break;
        case 7: _t->LogOut(); break;
        case 8: _t->pressSendButton(); break;
        case 9: _t->pressSendEnter(); break;
        case 10: _t->recvMsg((*reinterpret_cast< std::add_pointer_t<ChatMessage>>(_a[1]))); break;
        case 11: _t->checkUser((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 12: _t->addToGroup((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<std::vector<QString>>>(_a[2]))); break;
        case 13: _t->on_LogOutButton_clicked(); break;
        case 14: _t->on_listChat_itemClicked((*reinterpret_cast< std::add_pointer_t<QListWidgetItem*>>(_a[1]))); break;
        case 15: _t->on_AddFriendButton_clicked(); break;
        case 17: _t->on_AddGroupButton_clicked(); break;
        case 18: _t->on_pushButton_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ChatWindow::*)(QString );
            if (_t _q_method = &ChatWindow::chooseChat; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ChatWindow::*)(QString );
            if (_t _q_method = &ChatWindow::sendMessage; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (ChatWindow::*)(QString , std::vector<QString> );
            if (_t _q_method = &ChatWindow::addGroup; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (ChatWindow::*)(QString );
            if (_t _q_method = &ChatWindow::addFriend; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (ChatWindow::*)(int );
            if (_t _q_method = &ChatWindow::acceptFriendRequest; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (ChatWindow::*)(int );
            if (_t _q_method = &ChatWindow::denyFriendRequest; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (ChatWindow::*)();
            if (_t _q_method = &ChatWindow::anonymousRequire; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (ChatWindow::*)();
            if (_t _q_method = &ChatWindow::LogOut; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 7;
                return;
            }
        }
    }
}

const QMetaObject *ChatWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ChatWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSChatWindowENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int ChatWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 19)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 19;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 19)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 19;
    }
    return _id;
}

// SIGNAL 0
void ChatWindow::chooseChat(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ChatWindow::sendMessage(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ChatWindow::addGroup(QString _t1, std::vector<QString> _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void ChatWindow::addFriend(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void ChatWindow::acceptFriendRequest(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void ChatWindow::denyFriendRequest(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void ChatWindow::anonymousRequire()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}

// SIGNAL 7
void ChatWindow::LogOut()
{
    QMetaObject::activate(this, &staticMetaObject, 7, nullptr);
}
QT_WARNING_POP
