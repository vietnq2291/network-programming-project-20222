/****************************************************************************
** Meta object code from reading C++ file 'Views.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Client/Views.h"
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
    "recvAuth",
    "switchToChat",
    "switchToLogin",
    "initChat",
    "std::vector<Friend>"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSviewsENDCLASS_t {
    uint offsetsAndSizes[22];
    char stringdata0[6];
    char stringdata1[13];
    char stringdata2[1];
    char stringdata3[17];
    char stringdata4[5];
    char stringdata5[5];
    char stringdata6[9];
    char stringdata7[13];
    char stringdata8[14];
    char stringdata9[9];
    char stringdata10[20];
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
        QT_MOC_LITERAL(47, 8),  // "recvAuth"
        QT_MOC_LITERAL(56, 12),  // "switchToChat"
        QT_MOC_LITERAL(69, 13),  // "switchToLogin"
        QT_MOC_LITERAL(83, 8),  // "initChat"
        QT_MOC_LITERAL(92, 19)   // "std::vector<Friend>"
    },
    "views",
    "loggedInView",
    "",
    "recievedAuthView",
    "user",
    "pass",
    "recvAuth",
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
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   50,    2, 0x06,    1 /* Public */,
       3,    2,   51,    2, 0x06,    2 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       6,    2,   56,    2, 0x08,    5 /* Private */,
       7,    0,   61,    2, 0x08,    8 /* Private */,
       8,    0,   62,    2, 0x08,    9 /* Private */,
       9,    1,   63,    2, 0x08,   10 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    4,    5,

 // slots: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    4,    5,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 10,    2,

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
        // method 'recvAuth'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
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
        case 2: _t->recvAuth((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 3: _t->switchToChat(); break;
        case 4: _t->switchToLogin(); break;
        case 5: _t->initChat((*reinterpret_cast< std::add_pointer_t<std::vector<Friend>>>(_a[1]))); break;
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
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 6;
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
QT_WARNING_POP
