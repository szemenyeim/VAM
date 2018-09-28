/****************************************************************************
** Meta object code from reading C++ file 'PlaniWindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../PlaniWindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'PlaniWindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_PlaniWindow_t {
    QByteArrayData data[32];
    char stringdata0[348];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PlaniWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PlaniWindow_t qt_meta_stringdata_PlaniWindow = {
    {
QT_MOC_LITERAL(0, 0, 11), // "PlaniWindow"
QT_MOC_LITERAL(1, 12, 8), // "segmDone"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 9), // "savePlani"
QT_MOC_LITERAL(4, 32, 11), // "exportPlani"
QT_MOC_LITERAL(5, 44, 12), // "computeAreas"
QT_MOC_LITERAL(6, 57, 15), // "getSegmentation"
QT_MOC_LITERAL(7, 73, 13), // "weightChanged"
QT_MOC_LITERAL(8, 87, 3), // "val"
QT_MOC_LITERAL(9, 91, 16), // "brushSizeChanged"
QT_MOC_LITERAL(10, 108, 13), // "threshChanged"
QT_MOC_LITERAL(11, 122, 13), // "methodChanged"
QT_MOC_LITERAL(12, 136, 12), // "applyPolygon"
QT_MOC_LITERAL(13, 149, 7), // "segment"
QT_MOC_LITERAL(14, 157, 16), // "segmentationImpl"
QT_MOC_LITERAL(15, 174, 20), // "segmentationFinished"
QT_MOC_LITERAL(16, 195, 9), // "floodFill"
QT_MOC_LITERAL(17, 205, 13), // "floodFillImpl"
QT_MOC_LITERAL(18, 219, 9), // "cv::Point"
QT_MOC_LITERAL(19, 229, 2), // "pt"
QT_MOC_LITERAL(20, 232, 6), // "backUp"
QT_MOC_LITERAL(21, 239, 6), // "setROI"
QT_MOC_LITERAL(22, 246, 4), // "help"
QT_MOC_LITERAL(23, 251, 11), // "clearPoints"
QT_MOC_LITERAL(24, 263, 16), // "eraseModeChanged"
QT_MOC_LITERAL(25, 280, 9), // "prevImage"
QT_MOC_LITERAL(26, 290, 9), // "skipImage"
QT_MOC_LITERAL(27, 300, 17), // "listDoubleClicked"
QT_MOC_LITERAL(28, 318, 4), // "curr"
QT_MOC_LITERAL(29, 323, 9), // "redoImage"
QT_MOC_LITERAL(30, 333, 12), // "imageClicked"
QT_MOC_LITERAL(31, 346, 1) // "p"

    },
    "PlaniWindow\0segmDone\0\0savePlani\0"
    "exportPlani\0computeAreas\0getSegmentation\0"
    "weightChanged\0val\0brushSizeChanged\0"
    "threshChanged\0methodChanged\0applyPolygon\0"
    "segment\0segmentationImpl\0segmentationFinished\0"
    "floodFill\0floodFillImpl\0cv::Point\0pt\0"
    "backUp\0setROI\0help\0clearPoints\0"
    "eraseModeChanged\0prevImage\0skipImage\0"
    "listDoubleClicked\0curr\0redoImage\0"
    "imageClicked\0p"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PlaniWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      24,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,  134,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,  135,    2, 0x08 /* Private */,
       4,    0,  136,    2, 0x08 /* Private */,
       5,    0,  137,    2, 0x08 /* Private */,
       6,    0,  138,    2, 0x08 /* Private */,
       7,    1,  139,    2, 0x08 /* Private */,
       9,    1,  142,    2, 0x08 /* Private */,
      10,    1,  145,    2, 0x08 /* Private */,
      11,    1,  148,    2, 0x08 /* Private */,
      12,    0,  151,    2, 0x08 /* Private */,
      13,    0,  152,    2, 0x08 /* Private */,
      14,    0,  153,    2, 0x08 /* Private */,
      15,    0,  154,    2, 0x08 /* Private */,
      16,    0,  155,    2, 0x08 /* Private */,
      17,    2,  156,    2, 0x08 /* Private */,
      21,    0,  161,    2, 0x08 /* Private */,
      22,    0,  162,    2, 0x08 /* Private */,
      23,    0,  163,    2, 0x08 /* Private */,
      24,    0,  164,    2, 0x08 /* Private */,
      25,    0,  165,    2, 0x08 /* Private */,
      26,    0,  166,    2, 0x08 /* Private */,
      27,    1,  167,    2, 0x08 /* Private */,
      29,    0,  170,    2, 0x08 /* Private */,
      30,    1,  171,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Double,    8,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 18, QMetaType::Bool,   19,   20,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QModelIndex,   28,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QPoint,   31,

       0        // eod
};

void PlaniWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        PlaniWindow *_t = static_cast<PlaniWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->segmDone(); break;
        case 1: _t->savePlani(); break;
        case 2: _t->exportPlani(); break;
        case 3: _t->computeAreas(); break;
        case 4: _t->getSegmentation(); break;
        case 5: _t->weightChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 6: _t->brushSizeChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->threshChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->methodChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->applyPolygon(); break;
        case 10: _t->segment(); break;
        case 11: _t->segmentationImpl(); break;
        case 12: _t->segmentationFinished(); break;
        case 13: _t->floodFill(); break;
        case 14: _t->floodFillImpl((*reinterpret_cast< const cv::Point(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 15: _t->setROI(); break;
        case 16: _t->help(); break;
        case 17: _t->clearPoints(); break;
        case 18: _t->eraseModeChanged(); break;
        case 19: _t->prevImage(); break;
        case 20: _t->skipImage(); break;
        case 21: _t->listDoubleClicked((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        case 22: _t->redoImage(); break;
        case 23: _t->imageClicked((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (PlaniWindow::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PlaniWindow::segmDone)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject PlaniWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_PlaniWindow.data,
      qt_meta_data_PlaniWindow,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *PlaniWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PlaniWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_PlaniWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int PlaniWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 24)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 24;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 24)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 24;
    }
    return _id;
}

// SIGNAL 0
void PlaniWindow::segmDone()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
