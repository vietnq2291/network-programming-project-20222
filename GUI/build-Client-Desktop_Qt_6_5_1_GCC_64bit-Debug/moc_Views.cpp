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
    "setChatView",
    "chat_name",
    "sendMessageView",
    "packet",
    "recvMessage",
    "ChatMessage",
    "message",
    "recvAuth",
    "recvMsg",
    "setToChat",
    "sendMessage",
    "switchToChat",
    "switchToLogin",
    "initChat",
    "std::vector<Friend>"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSviewsENDCLASS_t {
    uint offsetsAndSizes[42];
    char stringdata0[6];
    char stringdata1[13];
    char stringdata2[1];
    char stringdata3[17];
    char stringdata4[5];
    char stringdata5[5];
    char stringdata6[12];
    char stringdata7[10];
    char stringdata8[16];
    char stringdata9[7];
    char stringdata10[12];
    char stringdata11[12];
    char stringdata12[8];
    char stringdata13[9];
    char stringdata14[8];
    char stringdata15[10];
    char stringdata16[12];
    char stringdata17[13];
    char stringdata18[14];
    char stringdata19[9];
    char stringdata20[20];
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
        QT_MOC_LITERAL(47, 11),  // "setChatView"
        QT_MOC_LITERAL(59, 9),  // "chat_name"
        QT_MOC_LITERAL(69, 15),  // "sendMessageView"
        QT_MOC_LITERAL(85, 6),  // "packet"
        QT_MOC_LITERAL(92, 11),  // "recvMessage"
        QT_MOC_LITERAL(104, 11),  // "ChatMessage"
        QT_MOC_LITERAL(116, 7),  // "message"
        QT_MOC_LITERAL(124, 8),  // "recvAuth"
        QT_MOC_LITERAL(133, 7),  // "recvMsg"
        QT_MOC_LITERAL(141, 9),  // "setToChat"
        QT_MOC_LITERAL(151, 11),  // "sendMessage"
        QT_MOC_LITERAL(163, 12),  // "switchToChat"
        QT_MOC_LITERAL(176, 13),  // "switchToLogin"
        QT_MOC_LITERAL(190, 8),  // "initChat"
        QT_MOC_LITERAL(199, 19)   // "std::vector<Friend>"
    },
    "views",
    "loggedInView",
    "",
    "recievedAuthView",
    "user",
    "pass",
    "setChatView",
    "chat_name",
    "sendMessageView",
    "packet",
    "recvMessage",
    "ChatMessage",
    "message",
    "recvAuth",
    "recvMsg",
    "setToChat",
    "sendMessage",
    "switchToChat",
    "switchToLogin",
    "initChat",
    "std::vector<Friend>"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSviewsENDCLASS[] = {

 // content:
      11,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   86,    2, 0x06,    1 /* Public */,
       3,    2,   87,    2, 0x06,    2 /* Public */,
       6,    1,   92,    2, 0x06,    5 /* Public */,
       8,    1,   95,    2, 0x06,    7 /* Public */,
      10,    1,   98,    2, 0x06,    9 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
      13,    2,  101,    2, 0x08,   11 /* Private */,
      14,    1,  106,    2, 0x08,   14 /* Private */,
      15,    1,  109,    2, 0x08,   16 /* Private */,
      16,    1,  112,    2, 0x08,   18 /* Private */,
      17,    0,  115,    2, 0x08,   20 /* Private */,
      18,    0,  116,    2, 0x08,   21 /* Private */,
      19,    1,  117,    2, 0x08,   22 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    4,    5,
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void, QMetaType::QString,    9,
    QMetaType::Void, 0x80000000 | 11,   12,

 // slots: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    4,    5,
    QMetaType::Void, 0x80000000 | 11,   12,
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void, QMetaType::QString,    9,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 20,    2,

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
        // method 'setChatView'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'sendMessageView'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'recvMessage'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<ChatMessage, std::false_type>,
        // method 'recvAuth'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
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
        // method 'switchToChat'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'switchToLogin'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'initChat'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
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
        case 2: _t->setChatView((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 3: _t->sendMessageView((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 4: _t->recvMessage((*reinterpret_cast< std::add_pointer_t<ChatMessage>>(_a[1]))); break;
        case 5: _t->recvAuth((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 6: _t->recvMsg((*reinterpret_cast< std::add_pointer_t<ChatMessage>>(_a[1]))); break;
        case 7: _t->setToChat((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 8: _t->sendMessage((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 9: _t->switchToChat(); break;
        case 10: _t->switchToLogin(); break;
        case 11: _t->initChat((*reinterpret_cast< std::add_pointer_t<std::vector<Friend>>>(_a[1]))); break;
        default: ;
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
            using _t = void (views::*)(QString );
            if (_t _q_method = &views::setChatView; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (views::*)(QString );
            if (_t _q_method = &views::sendMessageView; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (views::*)(ChatMessage );
            if (_t _q_method = &views::recvMessage; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 4;
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
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 12;
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
void views::setChatView(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void views::sendMessageView(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void views::recvMessage(ChatMessage _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_WARNING_POP
