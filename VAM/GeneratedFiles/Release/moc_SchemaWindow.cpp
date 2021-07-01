/****************************************************************************
** Meta object code from reading C++ file 'SchemaWindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../SchemaWindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SchemaWindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_SchemaWindow_t {
    QByteArrayData data[21];
    char stringdata0[196];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SchemaWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SchemaWindow_t qt_meta_stringdata_SchemaWindow = {
    {
QT_MOC_LITERAL(0, 0, 12), // "SchemaWindow"
QT_MOC_LITERAL(1, 13, 7), // "newData"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 10), // "dataUpdate"
QT_MOC_LITERAL(4, 33, 6), // "closed"
QT_MOC_LITERAL(5, 40, 13), // "setCorrection"
QT_MOC_LITERAL(6, 54, 10), // "openImages"
QT_MOC_LITERAL(7, 65, 10), // "saveSchema"
QT_MOC_LITERAL(8, 76, 12), // "saveAsSchema"
QT_MOC_LITERAL(9, 89, 9), // "newAngleC"
QT_MOC_LITERAL(10, 99, 13), // "VAMImageIndex"
QT_MOC_LITERAL(11, 113, 3), // "idx"
QT_MOC_LITERAL(12, 117, 8), // "newDistC"
QT_MOC_LITERAL(13, 126, 8), // "newPoint"
QT_MOC_LITERAL(14, 135, 8), // "delPoint"
QT_MOC_LITERAL(15, 144, 7), // "delMeas"
QT_MOC_LITERAL(16, 152, 8), // "renPoint"
QT_MOC_LITERAL(17, 161, 7), // "renMeas"
QT_MOC_LITERAL(18, 169, 11), // "listClicked"
QT_MOC_LITERAL(19, 181, 12), // "imageClicked"
QT_MOC_LITERAL(20, 194, 1) // "p"

    },
    "SchemaWindow\0newData\0\0dataUpdate\0"
    "closed\0setCorrection\0openImages\0"
    "saveSchema\0saveAsSchema\0newAngleC\0"
    "VAMImageIndex\0idx\0newDistC\0newPoint\0"
    "delPoint\0delMeas\0renPoint\0renMeas\0"
    "listClicked\0imageClicked\0p"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SchemaWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   94,    2, 0x06 /* Public */,
       3,    0,   95,    2, 0x06 /* Public */,
       4,    0,   96,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   97,    2, 0x08 /* Private */,
       6,    0,   98,    2, 0x08 /* Private */,
       7,    0,   99,    2, 0x08 /* Private */,
       8,    0,  100,    2, 0x08 /* Private */,
       9,    1,  101,    2, 0x08 /* Private */,
      12,    1,  104,    2, 0x08 /* Private */,
      13,    1,  107,    2, 0x08 /* Private */,
      14,    1,  110,    2, 0x08 /* Private */,
      15,    1,  113,    2, 0x08 /* Private */,
      16,    1,  116,    2, 0x08 /* Private */,
      17,    1,  119,    2, 0x08 /* Private */,
      18,    1,  122,    2, 0x08 /* Private */,
      19,    2,  125,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Bool,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 10,   11,
    QMetaType::Void, 0x80000000 | 10,   11,
    QMetaType::Void, 0x80000000 | 10,   11,
    QMetaType::Void, 0x80000000 | 10,   11,
    QMetaType::Void, 0x80000000 | 10,   11,
    QMetaType::Void, 0x80000000 | 10,   11,
    QMetaType::Void, 0x80000000 | 10,   11,
    QMetaType::Void, 0x80000000 | 10,   11,
    QMetaType::Void, QMetaType::QPoint, 0x80000000 | 10,   20,   11,

       0        // eod
};

void SchemaWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SchemaWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->newData(); break;
        case 1: _t->dataUpdate(); break;
        case 2: _t->closed(); break;
        case 3: _t->setCorrection(); break;
        case 4: _t->openImages(); break;
        case 5: { bool _r = _t->saveSchema();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 6: _t->saveAsSchema(); break;
        case 7: _t->newAngleC((*reinterpret_cast< VAMImageIndex(*)>(_a[1]))); break;
        case 8: _t->newDistC((*reinterpret_cast< VAMImageIndex(*)>(_a[1]))); break;
        case 9: _t->newPoint((*reinterpret_cast< VAMImageIndex(*)>(_a[1]))); break;
        case 10: _t->delPoint((*reinterpret_cast< VAMImageIndex(*)>(_a[1]))); break;
        case 11: _t->delMeas((*reinterpret_cast< VAMImageIndex(*)>(_a[1]))); break;
        case 12: _t->renPoint((*reinterpret_cast< VAMImageIndex(*)>(_a[1]))); break;
        case 13: _t->renMeas((*reinterpret_cast< VAMImageIndex(*)>(_a[1]))); break;
        case 14: _t->listClicked((*reinterpret_cast< VAMImageIndex(*)>(_a[1]))); break;
        case 15: _t->imageClicked((*reinterpret_cast< const QPoint(*)>(_a[1])),(*reinterpret_cast< VAMImageIndex(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (SchemaWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SchemaWindow::newData)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (SchemaWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SchemaWindow::dataUpdate)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (SchemaWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SchemaWindow::closed)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject SchemaWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_SchemaWindow.data,
    qt_meta_data_SchemaWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *SchemaWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SchemaWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SchemaWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int SchemaWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 16;
    }
    return _id;
}

// SIGNAL 0
void SchemaWindow::newData()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void SchemaWindow::dataUpdate()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void SchemaWindow::closed()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
