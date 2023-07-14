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
    "LogOut",
    "pressSendButton",
    "pressSendEnter",
    "recvMsg",
    "ChatMessage",
    "on_listWidget_itemClicked",
    "QListWidgetItem*",
    "chat",
    "on_LogOutButton_clicked"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSChatWindowENDCLASS_t {
    uint offsetsAndSizes[30];
    char stringdata0[11];
    char stringdata1[11];
    char stringdata2[1];
    char stringdata3[10];
    char stringdata4[12];
    char stringdata5[8];
    char stringdata6[7];
    char stringdata7[16];
    char stringdata8[15];
    char stringdata9[8];
    char stringdata10[12];
    char stringdata11[26];
    char stringdata12[17];
    char stringdata13[5];
    char stringdata14[24];
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
        QT_MOC_LITERAL(53, 6),  // "LogOut"
        QT_MOC_LITERAL(60, 15),  // "pressSendButton"
        QT_MOC_LITERAL(76, 14),  // "pressSendEnter"
        QT_MOC_LITERAL(91, 7),  // "recvMsg"
        QT_MOC_LITERAL(99, 11),  // "ChatMessage"
        QT_MOC_LITERAL(111, 25),  // "on_listWidget_itemClicked"
        QT_MOC_LITERAL(137, 16),  // "QListWidgetItem*"
        QT_MOC_LITERAL(154, 4),  // "chat"
        QT_MOC_LITERAL(159, 23)   // "on_LogOutButton_clicked"
    },
    "ChatWindow",
    "chooseChat",
    "",
    "chat_name",
    "sendMessage",
    "message",
    "LogOut",
    "pressSendButton",
    "pressSendEnter",
    "recvMsg",
    "ChatMessage",
    "on_listWidget_itemClicked",
    "QListWidgetItem*",
    "chat",
    "on_LogOutButton_clicked"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSChatWindowENDCLASS[] = {

 // content:
      11,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   62,    2, 0x06,    1 /* Public */,
       4,    1,   65,    2, 0x06,    3 /* Public */,
       6,    0,   68,    2, 0x06,    5 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       7,    0,   69,    2, 0x08,    6 /* Private */,
       8,    0,   70,    2, 0x08,    7 /* Private */,
       9,    1,   71,    2, 0x08,    8 /* Private */,
      11,    1,   74,    2, 0x08,   10 /* Private */,
      14,    0,   77,    2, 0x08,   12 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 10,    5,
    QMetaType::Void, 0x80000000 | 12,   13,
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
        // method 'LogOut'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'pressSendButton'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'pressSendEnter'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'recvMsg'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<ChatMessage, std::false_type>,
        // method 'on_listWidget_itemClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QListWidgetItem *, std::false_type>,
        // method 'on_LogOutButton_clicked'
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
        case 2: _t->LogOut(); break;
        case 3: _t->pressSendButton(); break;
        case 4: _t->pressSendEnter(); break;
        case 5: _t->recvMsg((*reinterpret_cast< std::add_pointer_t<ChatMessage>>(_a[1]))); break;
        case 6: _t->on_listWidget_itemClicked((*reinterpret_cast< std::add_pointer_t<QListWidgetItem*>>(_a[1]))); break;
        case 7: _t->on_LogOutButton_clicked(); break;
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
            using _t = void (ChatWindow::*)();
            if (_t _q_method = &ChatWindow::LogOut; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
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
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 8;
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
void ChatWindow::LogOut()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}
QT_WARNING_POP
