/****************************************************************************
** Meta object code from reading C++ file 'MarkerWindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../MarkerWindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MarkerWindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MarkerWindow_t {
    QByteArrayData data[20];
    char stringdata0[223];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MarkerWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MarkerWindow_t qt_meta_stringdata_MarkerWindow = {
    {
QT_MOC_LITERAL(0, 0, 12), // "MarkerWindow"
QT_MOC_LITERAL(1, 13, 7), // "newData"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 10), // "dataUpdate"
QT_MOC_LITERAL(4, 33, 6), // "closed"
QT_MOC_LITERAL(5, 40, 15), // "saveMeasurement"
QT_MOC_LITERAL(6, 56, 17), // "saveAsMeasurement"
QT_MOC_LITERAL(7, 74, 17), // "confidenceChanged"
QT_MOC_LITERAL(8, 92, 3), // "val"
QT_MOC_LITERAL(9, 96, 17), // "markerModeChanged"
QT_MOC_LITERAL(10, 114, 15), // "autoCorrChanged"
QT_MOC_LITERAL(11, 130, 9), // "prevImage"
QT_MOC_LITERAL(12, 140, 9), // "skipImage"
QT_MOC_LITERAL(13, 150, 17), // "listDoubleClicked"
QT_MOC_LITERAL(14, 168, 11), // "QModelIndex"
QT_MOC_LITERAL(15, 180, 4), // "curr"
QT_MOC_LITERAL(16, 185, 9), // "redoImage"
QT_MOC_LITERAL(17, 195, 12), // "imageClicked"
QT_MOC_LITERAL(18, 208, 1), // "p"
QT_MOC_LITERAL(19, 210, 12) // "imageHovered"

    },
    "MarkerWindow\0newData\0\0dataUpdate\0"
    "closed\0saveMeasurement\0saveAsMeasurement\0"
    "confidenceChanged\0val\0markerModeChanged\0"
    "autoCorrChanged\0prevImage\0skipImage\0"
    "listDoubleClicked\0QModelIndex\0curr\0"
    "redoImage\0imageClicked\0p\0imageHovered"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MarkerWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   84,    2, 0x06 /* Public */,
       3,    0,   85,    2, 0x06 /* Public */,
       4,    0,   86,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   87,    2, 0x08 /* Private */,
       6,    0,   88,    2, 0x08 /* Private */,
       7,    1,   89,    2, 0x08 /* Private */,
       9,    0,   92,    2, 0x08 /* Private */,
      10,    1,   93,    2, 0x08 /* Private */,
      11,    0,   96,    2, 0x08 /* Private */,
      12,    0,   97,    2, 0x08 /* Private */,
      13,    1,   98,    2, 0x08 /* Private */,
      16,    0,  101,    2, 0x08 /* Private */,
      17,    1,  102,    2, 0x08 /* Private */,
      19,    1,  105,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    8,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 14,   15,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QPoint,   18,
    QMetaType::Void, QMetaType::QPoint,   18,

       0        // eod
};

void MarkerWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MarkerWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->newData(); break;
        case 1: _t->dataUpdate(); break;
        case 2: _t->closed(); break;
        case 3: _t->saveMeasurement(); break;
        case 4: _t->saveAsMeasurement(); break;
        case 5: _t->confidenceChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->markerModeChanged(); break;
        case 7: _t->autoCorrChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 8: _t->prevImage(); break;
        case 9: _t->skipImage(); break;
        case 10: _t->listDoubleClicked((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        case 11: _t->redoImage(); break;
        case 12: _t->imageClicked((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 13: _t->imageHovered((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (MarkerWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MarkerWindow::newData)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (MarkerWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MarkerWindow::dataUpdate)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (MarkerWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MarkerWindow::closed)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MarkerWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_MarkerWindow.data,
    qt_meta_data_MarkerWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MarkerWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MarkerWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MarkerWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MarkerWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 14;
    }
    return _id;
}

// SIGNAL 0
void MarkerWindow::newData()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void MarkerWindow::dataUpdate()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void MarkerWindow::closed()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
