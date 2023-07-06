/****************************************************************************
** Meta object code from reading C++ file 'clientwindow.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Client/clientwindow.h"
#include <QtNetwork/QSslPreSharedKeyAuthenticator>
#include <QtNetwork/QSslError>
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'clientwindow.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_CLASSClientWindowENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSClientWindowENDCLASS = QtMocHelpers::stringData(
    "ClientWindow",
    "pressConnect",
    "",
    "pressSendButton",
    "pressSendEnter",
    "recvMsg",
    "Conn",
    "closeConn",
    "socketErr",
    "QAbstractSocket::SocketError",
    "err"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSClientWindowENDCLASS_t {
    uint offsetsAndSizes[22];
    char stringdata0[13];
    char stringdata1[13];
    char stringdata2[1];
    char stringdata3[16];
    char stringdata4[15];
    char stringdata5[8];
    char stringdata6[5];
    char stringdata7[10];
    char stringdata8[10];
    char stringdata9[29];
    char stringdata10[4];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSClientWindowENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSClientWindowENDCLASS_t qt_meta_stringdata_CLASSClientWindowENDCLASS = {
    {
        QT_MOC_LITERAL(0, 12),  // "ClientWindow"
        QT_MOC_LITERAL(13, 12),  // "pressConnect"
        QT_MOC_LITERAL(26, 0),  // ""
        QT_MOC_LITERAL(27, 15),  // "pressSendButton"
        QT_MOC_LITERAL(43, 14),  // "pressSendEnter"
        QT_MOC_LITERAL(58, 7),  // "recvMsg"
        QT_MOC_LITERAL(66, 4),  // "Conn"
        QT_MOC_LITERAL(71, 9),  // "closeConn"
        QT_MOC_LITERAL(81, 9),  // "socketErr"
        QT_MOC_LITERAL(91, 28),  // "QAbstractSocket::SocketError"
        QT_MOC_LITERAL(120, 3)   // "err"
    },
    "ClientWindow",
    "pressConnect",
    "",
    "pressSendButton",
    "pressSendEnter",
    "recvMsg",
    "Conn",
    "closeConn",
    "socketErr",
    "QAbstractSocket::SocketError",
    "err"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSClientWindowENDCLASS[] = {

 // content:
      11,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   56,    2, 0x08,    1 /* Private */,
       3,    0,   57,    2, 0x08,    2 /* Private */,
       4,    0,   58,    2, 0x08,    3 /* Private */,
       5,    0,   59,    2, 0x08,    4 /* Private */,
       6,    0,   60,    2, 0x08,    5 /* Private */,
       7,    0,   61,    2, 0x08,    6 /* Private */,
       8,    1,   62,    2, 0x08,    7 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 9,   10,

       0        // eod
};

Q_CONSTINIT const QMetaObject ClientWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_CLASSClientWindowENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSClientWindowENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSClientWindowENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<ClientWindow, std::true_type>,
        // method 'pressConnect'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'pressSendButton'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'pressSendEnter'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'recvMsg'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'Conn'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'closeConn'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'socketErr'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QAbstractSocket::SocketError, std::false_type>
    >,
    nullptr
} };

void ClientWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ClientWindow *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->pressConnect(); break;
        case 1: _t->pressSendButton(); break;
        case 2: _t->pressSendEnter(); break;
        case 3: _t->recvMsg(); break;
        case 4: _t->Conn(); break;
        case 5: _t->closeConn(); break;
        case 6: _t->socketErr((*reinterpret_cast< std::add_pointer_t<QAbstractSocket::SocketError>>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 6:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QAbstractSocket::SocketError >(); break;
            }
            break;
        }
    }
}

const QMetaObject *ClientWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ClientWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSClientWindowENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int ClientWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}
QT_WARNING_POP
