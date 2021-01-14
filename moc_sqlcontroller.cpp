/****************************************************************************
** Meta object code from reading C++ file 'sqlcontroller.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../Retele-Server/sqlcontroller.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'sqlcontroller.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_SQLController_t {
    QByteArrayData data[8];
    char stringdata0[63];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SQLController_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SQLController_t qt_meta_stringdata_SQLController = {
    {
QT_MOC_LITERAL(0, 0, 13), // "SQLController"
QT_MOC_LITERAL(1, 14, 6), // "DBTabs"
QT_MOC_LITERAL(2, 21, 5), // "USERS"
QT_MOC_LITERAL(3, 27, 7), // "ACTIVTY"
QT_MOC_LITERAL(4, 35, 5), // "BOOKS"
QT_MOC_LITERAL(5, 41, 7), // "STORAGE"
QT_MOC_LITERAL(6, 49, 6), // "RATING"
QT_MOC_LITERAL(7, 56, 6) // "GENRES"

    },
    "SQLController\0DBTabs\0USERS\0ACTIVTY\0"
    "BOOKS\0STORAGE\0RATING\0GENRES"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SQLController[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       1,   14, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // enums: name, alias, flags, count, data
       1,    1, 0x0,    6,   19,

 // enum data: key, value
       2, uint(SQLController::USERS),
       3, uint(SQLController::ACTIVTY),
       4, uint(SQLController::BOOKS),
       5, uint(SQLController::STORAGE),
       6, uint(SQLController::RATING),
       7, uint(SQLController::GENRES),

       0        // eod
};

void SQLController::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject SQLController::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_SQLController.data,
    qt_meta_data_SQLController,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *SQLController::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SQLController::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SQLController.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int SQLController::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
