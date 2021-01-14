/****************************************************************************
** Meta object code from reading C++ file 'bookinspect.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../Retele-Client/bookinspect.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'bookinspect.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_BookInspect_t {
    QByteArrayData data[11];
    char stringdata0[160];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_BookInspect_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_BookInspect_t qt_meta_stringdata_BookInspect = {
    {
QT_MOC_LITERAL(0, 0, 11), // "BookInspect"
QT_MOC_LITERAL(1, 12, 8), // "Download"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 12), // "ChangeRating"
QT_MOC_LITERAL(4, 35, 17), // "ChangeRatingToOne"
QT_MOC_LITERAL(5, 53, 17), // "ChangeRatingToTwo"
QT_MOC_LITERAL(6, 71, 19), // "ChangeRatingToThree"
QT_MOC_LITERAL(7, 91, 18), // "ChangeRatingToFour"
QT_MOC_LITERAL(8, 110, 18), // "ChangeRatingToFive"
QT_MOC_LITERAL(9, 129, 19), // "RequestRatingChange"
QT_MOC_LITERAL(10, 149, 10) // "UpdateData"

    },
    "BookInspect\0Download\0\0ChangeRating\0"
    "ChangeRatingToOne\0ChangeRatingToTwo\0"
    "ChangeRatingToThree\0ChangeRatingToFour\0"
    "ChangeRatingToFive\0RequestRatingChange\0"
    "UpdateData"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_BookInspect[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   59,    2, 0x08 /* Private */,
       3,    2,   60,    2, 0x08 /* Private */,
       4,    0,   65,    2, 0x08 /* Private */,
       5,    0,   66,    2, 0x08 /* Private */,
       6,    0,   67,    2, 0x08 /* Private */,
       7,    0,   68,    2, 0x08 /* Private */,
       8,    0,   69,    2, 0x08 /* Private */,
       9,    0,   70,    2, 0x08 /* Private */,
      10,    0,   71,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Double,    2,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void BookInspect::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<BookInspect *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->Download(); break;
        case 1: _t->ChangeRating((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 2: _t->ChangeRatingToOne(); break;
        case 3: _t->ChangeRatingToTwo(); break;
        case 4: _t->ChangeRatingToThree(); break;
        case 5: _t->ChangeRatingToFour(); break;
        case 6: _t->ChangeRatingToFive(); break;
        case 7: _t->RequestRatingChange(); break;
        case 8: _t->UpdateData(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject BookInspect::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_BookInspect.data,
    qt_meta_data_BookInspect,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *BookInspect::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *BookInspect::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_BookInspect.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int BookInspect::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
