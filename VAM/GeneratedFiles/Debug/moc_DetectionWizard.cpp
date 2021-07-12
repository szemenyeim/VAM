/****************************************************************************
** Meta object code from reading C++ file 'DetectionWizard.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../DetectionWizard.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'DetectionWizard.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_DetectionWizard_t {
    QByteArrayData data[1];
    char stringdata0[16];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DetectionWizard_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DetectionWizard_t qt_meta_stringdata_DetectionWizard = {
    {
QT_MOC_LITERAL(0, 0, 15) // "DetectionWizard"

    },
    "DetectionWizard"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DetectionWizard[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

void DetectionWizard::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject DetectionWizard::staticMetaObject = { {
    QMetaObject::SuperData::link<QWizard::staticMetaObject>(),
    qt_meta_stringdata_DetectionWizard.data,
    qt_meta_data_DetectionWizard,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *DetectionWizard::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DetectionWizard::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_DetectionWizard.stringdata0))
        return static_cast<void*>(this);
    return QWizard::qt_metacast(_clname);
}

int DetectionWizard::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWizard::qt_metacall(_c, _id, _a);
    return _id;
}
struct qt_meta_stringdata_IntroPage_2_t {
    QByteArrayData data[1];
    char stringdata0[12];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_IntroPage_2_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_IntroPage_2_t qt_meta_stringdata_IntroPage_2 = {
    {
QT_MOC_LITERAL(0, 0, 11) // "IntroPage_2"

    },
    "IntroPage_2"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_IntroPage_2[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

void IntroPage_2::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject IntroPage_2::staticMetaObject = { {
    QMetaObject::SuperData::link<QWizardPage::staticMetaObject>(),
    qt_meta_stringdata_IntroPage_2.data,
    qt_meta_data_IntroPage_2,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *IntroPage_2::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *IntroPage_2::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_IntroPage_2.stringdata0))
        return static_cast<void*>(this);
    return QWizardPage::qt_metacast(_clname);
}

int IntroPage_2::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWizardPage::qt_metacall(_c, _id, _a);
    return _id;
}
struct qt_meta_stringdata_VideoPage_2_t {
    QByteArrayData data[14];
    char stringdata0[161];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_VideoPage_2_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_VideoPage_2_t qt_meta_stringdata_VideoPage_2 = {
    {
QT_MOC_LITERAL(0, 0, 11), // "VideoPage_2"
QT_MOC_LITERAL(1, 12, 8), // "computed"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 13), // "videoComputed"
QT_MOC_LITERAL(4, 36, 13), // "getActiveArea"
QT_MOC_LITERAL(5, 50, 6), // "detect"
QT_MOC_LITERAL(6, 57, 13), // "detect_thread"
QT_MOC_LITERAL(7, 71, 9), // "imageDone"
QT_MOC_LITERAL(8, 81, 9), // "videoDone"
QT_MOC_LITERAL(9, 91, 18), // "areaSelectFinished"
QT_MOC_LITERAL(10, 110, 21), // "std::vector<cv::Rect>"
QT_MOC_LITERAL(11, 132, 5), // "_RoIs"
QT_MOC_LITERAL(12, 138, 8), // "canceled"
QT_MOC_LITERAL(13, 147, 13) // "finished_slot"

    },
    "VideoPage_2\0computed\0\0videoComputed\0"
    "getActiveArea\0detect\0detect_thread\0"
    "imageDone\0videoDone\0areaSelectFinished\0"
    "std::vector<cv::Rect>\0_RoIs\0canceled\0"
    "finished_slot"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_VideoPage_2[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   64,    2, 0x06 /* Public */,
       3,    0,   65,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   66,    2, 0x08 /* Private */,
       5,    0,   67,    2, 0x08 /* Private */,
       6,    0,   68,    2, 0x08 /* Private */,
       7,    0,   69,    2, 0x08 /* Private */,
       8,    0,   70,    2, 0x08 /* Private */,
       9,    1,   71,    2, 0x08 /* Private */,
      12,    0,   74,    2, 0x08 /* Private */,
      13,    0,   75,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 10,   11,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void VideoPage_2::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<VideoPage_2 *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->computed(); break;
        case 1: _t->videoComputed(); break;
        case 2: _t->getActiveArea(); break;
        case 3: _t->detect(); break;
        case 4: _t->detect_thread(); break;
        case 5: _t->imageDone(); break;
        case 6: _t->videoDone(); break;
        case 7: _t->areaSelectFinished((*reinterpret_cast< std::vector<cv::Rect>(*)>(_a[1]))); break;
        case 8: _t->canceled(); break;
        case 9: _t->finished_slot(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (VideoPage_2::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&VideoPage_2::computed)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (VideoPage_2::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&VideoPage_2::videoComputed)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject VideoPage_2::staticMetaObject = { {
    QMetaObject::SuperData::link<QWizardPage::staticMetaObject>(),
    qt_meta_stringdata_VideoPage_2.data,
    qt_meta_data_VideoPage_2,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *VideoPage_2::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *VideoPage_2::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_VideoPage_2.stringdata0))
        return static_cast<void*>(this);
    return QWizardPage::qt_metacast(_clname);
}

int VideoPage_2::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWizardPage::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void VideoPage_2::computed()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void VideoPage_2::videoComputed()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
struct qt_meta_stringdata_AreaSelectWindow_t {
    QByteArrayData data[12];
    char stringdata0[125];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_AreaSelectWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_AreaSelectWindow_t qt_meta_stringdata_AreaSelectWindow = {
    {
QT_MOC_LITERAL(0, 0, 16), // "AreaSelectWindow"
QT_MOC_LITERAL(1, 17, 8), // "finished"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 21), // "std::vector<cv::Rect>"
QT_MOC_LITERAL(4, 49, 4), // "RoIs"
QT_MOC_LITERAL(5, 54, 10), // "donePushed"
QT_MOC_LITERAL(6, 65, 12), // "imageClicked"
QT_MOC_LITERAL(7, 78, 1), // "p"
QT_MOC_LITERAL(8, 80, 13), // "VAMImageIndex"
QT_MOC_LITERAL(9, 94, 3), // "idx"
QT_MOC_LITERAL(10, 98, 12), // "imageHovered"
QT_MOC_LITERAL(11, 111, 13) // "imageReleased"

    },
    "AreaSelectWindow\0finished\0\0"
    "std::vector<cv::Rect>\0RoIs\0donePushed\0"
    "imageClicked\0p\0VAMImageIndex\0idx\0"
    "imageHovered\0imageReleased"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AreaSelectWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   42,    2, 0x08 /* Private */,
       6,    2,   43,    2, 0x08 /* Private */,
      10,    2,   48,    2, 0x08 /* Private */,
      11,    2,   53,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QPoint, 0x80000000 | 8,    7,    9,
    QMetaType::Void, QMetaType::QPoint, 0x80000000 | 8,    7,    9,
    QMetaType::Void, QMetaType::QPoint, 0x80000000 | 8,    7,    9,

       0        // eod
};

void AreaSelectWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<AreaSelectWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->finished((*reinterpret_cast< std::vector<cv::Rect>(*)>(_a[1]))); break;
        case 1: _t->donePushed(); break;
        case 2: _t->imageClicked((*reinterpret_cast< const QPoint(*)>(_a[1])),(*reinterpret_cast< VAMImageIndex(*)>(_a[2]))); break;
        case 3: _t->imageHovered((*reinterpret_cast< const QPoint(*)>(_a[1])),(*reinterpret_cast< VAMImageIndex(*)>(_a[2]))); break;
        case 4: _t->imageReleased((*reinterpret_cast< const QPoint(*)>(_a[1])),(*reinterpret_cast< VAMImageIndex(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (AreaSelectWindow::*)(std::vector<cv::Rect> );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AreaSelectWindow::finished)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject AreaSelectWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QDialog::staticMetaObject>(),
    qt_meta_stringdata_AreaSelectWindow.data,
    qt_meta_data_AreaSelectWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *AreaSelectWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AreaSelectWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_AreaSelectWindow.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int AreaSelectWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void AreaSelectWindow::finished(std::vector<cv::Rect> _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
