/****************************************************************************
** Meta object code from reading C++ file 'clientthread.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../Retele-Client/clientthread.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QVector>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'clientthread.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ClientThread_t {
    QByteArrayData data[11];
    char stringdata0[125];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ClientThread_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ClientThread_t qt_meta_stringdata_ClientThread = {
    {
QT_MOC_LITERAL(0, 0, 12), // "ClientThread"
QT_MOC_LITERAL(1, 13, 8), // "finished"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 14), // "loginSuccesful"
QT_MOC_LITERAL(4, 38, 11), // "loginFailed"
QT_MOC_LITERAL(5, 50, 12), // "ModifyRating"
QT_MOC_LITERAL(6, 63, 9), // "sendBooks"
QT_MOC_LITERAL(7, 73, 13), // "QVector<Book>"
QT_MOC_LITERAL(8, 87, 12), // "sendBooksRec"
QT_MOC_LITERAL(9, 100, 11), // "createBooks"
QT_MOC_LITERAL(10, 112, 12) // "HandleClient"

    },
    "ClientThread\0finished\0\0loginSuccesful\0"
    "loginFailed\0ModifyRating\0sendBooks\0"
    "QVector<Book>\0sendBooksRec\0createBooks\0"
    "HandleClient"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ClientThread[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x06 /* Public */,
       3,    0,   55,    2, 0x06 /* Public */,
       4,    0,   56,    2, 0x06 /* Public */,
       5,    2,   57,    2, 0x06 /* Public */,
       6,    1,   62,    2, 0x06 /* Public */,
       8,    1,   65,    2, 0x06 /* Public */,
       9,    1,   68,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      10,    0,   71,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Double,    2,    2,
    QMetaType::Void, 0x80000000 | 7,    2,
    QMetaType::Void, 0x80000000 | 7,    2,
    QMetaType::Void, 0x80000000 | 7,    2,

 // slots: parameters
    QMetaType::Int,

       0        // eod
};

void ClientThread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ClientThread *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->finished(); break;
        case 1: _t->loginSuccesful(); break;
        case 2: _t->loginFailed(); break;
        case 3: _t->ModifyRating((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 4: _t->sendBooks((*reinterpret_cast< QVector<Book>(*)>(_a[1]))); break;
        case 5: _t->sendBooksRec((*reinterpret_cast< QVector<Book>(*)>(_a[1]))); break;
        case 6: _t->createBooks((*reinterpret_cast< QVector<Book>(*)>(_a[1]))); break;
        case 7: { int _r = _t->HandleClient();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 4:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QVector<Book> >(); break;
            }
            break;
        case 5:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QVector<Book> >(); break;
            }
            break;
        case 6:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QVector<Book> >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ClientThread::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ClientThread::finished)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ClientThread::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ClientThread::loginSuccesful)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (ClientThread::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ClientThread::loginFailed)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (ClientThread::*)(int , double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ClientThread::ModifyRating)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (ClientThread::*)(QVector<Book> );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ClientThread::sendBooks)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (ClientThread::*)(QVector<Book> );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ClientThread::sendBooksRec)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (ClientThread::*)(QVector<Book> );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ClientThread::createBooks)) {
                *result = 6;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ClientThread::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_ClientThread.data,
    qt_meta_data_ClientThread,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ClientThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ClientThread::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ClientThread.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int ClientThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void ClientThread::finished()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void ClientThread::loginSuccesful()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void ClientThread::loginFailed()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void ClientThread::ModifyRating(int _t1, double _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void ClientThread::sendBooks(QVector<Book> _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void ClientThread::sendBooksRec(QVector<Book> _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void ClientThread::createBooks(QVector<Book> _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
