/****************************************************************************
** Meta object code from reading C++ file 'MarkerWindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../MarkerWindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MarkerWindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MarkerWindow_t {
    QByteArrayData data[18];
    char stringdata0[204];
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
QT_MOC_LITERAL(4, 33, 15), // "saveMeasurement"
QT_MOC_LITERAL(5, 49, 17), // "saveAsMeasurement"
QT_MOC_LITERAL(6, 67, 17), // "confidenceChanged"
QT_MOC_LITERAL(7, 85, 3), // "val"
QT_MOC_LITERAL(8, 89, 17), // "markerModeChanged"
QT_MOC_LITERAL(9, 107, 15), // "autoCorrChanged"
QT_MOC_LITERAL(10, 123, 9), // "prevImage"
QT_MOC_LITERAL(11, 133, 9), // "skipImage"
QT_MOC_LITERAL(12, 143, 17), // "listDoubleClicked"
QT_MOC_LITERAL(13, 161, 4), // "curr"
QT_MOC_LITERAL(14, 166, 9), // "redoImage"
QT_MOC_LITERAL(15, 176, 12), // "imageClicked"
QT_MOC_LITERAL(16, 189, 1), // "p"
QT_MOC_LITERAL(17, 191, 12) // "imageHovered"

    },
    "MarkerWindow\0newData\0\0dataUpdate\0"
    "saveMeasurement\0saveAsMeasurement\0"
    "confidenceChanged\0val\0markerModeChanged\0"
    "autoCorrChanged\0prevImage\0skipImage\0"
    "listDoubleClicked\0curr\0redoImage\0"
    "imageClicked\0p\0imageHovered"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MarkerWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   79,    2, 0x06 /* Public */,
       3,    0,   80,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   81,    2, 0x08 /* Private */,
       5,    0,   82,    2, 0x08 /* Private */,
       6,    1,   83,    2, 0x08 /* Private */,
       8,    0,   86,    2, 0x08 /* Private */,
       9,    1,   87,    2, 0x08 /* Private */,
      10,    0,   90,    2, 0x08 /* Private */,
      11,    0,   91,    2, 0x08 /* Private */,
      12,    1,   92,    2, 0x08 /* Private */,
      14,    0,   95,    2, 0x08 /* Private */,
      15,    1,   96,    2, 0x08 /* Private */,
      17,    1,   99,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    7,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QModelIndex,   13,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QPoint,   16,
    QMetaType::Void, QMetaType::QPoint,   16,

       0        // eod
};

void MarkerWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MarkerWindow *_t = static_cast<MarkerWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->newData(); break;
        case 1: _t->dataUpdate(); break;
        case 2: _t->saveMeasurement(); break;
        case 3: _t->saveAsMeasurement(); break;
        case 4: _t->confidenceChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->markerModeChanged(); break;
        case 6: _t->autoCorrChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 7: _t->prevImage(); break;
        case 8: _t->skipImage(); break;
        case 9: _t->listDoubleClicked((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        case 10: _t->redoImage(); break;
        case 11: _t->imageClicked((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 12: _t->imageHovered((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (MarkerWindow::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MarkerWindow::newData)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (MarkerWindow::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MarkerWindow::dataUpdate)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject MarkerWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MarkerWindow.data,
      qt_meta_data_MarkerWindow,  qt_static_metacall, nullptr, nullptr}
};


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
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 13;
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
