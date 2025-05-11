/****************************************************************************
** Meta object code from reading C++ file 'Camera.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/Camera/Camera.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Camera.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Camera_t {
    QByteArrayData data[12];
    char stringdata0[308];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Camera_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Camera_t qt_meta_stringdata_Camera = {
    {
QT_MOC_LITERAL(0, 0, 6), // "Camera"
QT_MOC_LITERAL(1, 7, 11), // "updateImage"
QT_MOC_LITERAL(2, 19, 0), // ""
QT_MOC_LITERAL(3, 20, 26), // "on_pushButton_Open_clicked"
QT_MOC_LITERAL(4, 47, 29), // "on_pushButton_Display_clicked"
QT_MOC_LITERAL(5, 77, 34), // "on_pushButton_Display_clicked..."
QT_MOC_LITERAL(6, 112, 27), // "on_pushButton_Close_clicked"
QT_MOC_LITERAL(7, 140, 30), // "on_pushButton_SaveFile_clicked"
QT_MOC_LITERAL(8, 171, 37), // "on_PushButton_PictureAnalysis..."
QT_MOC_LITERAL(9, 209, 32), // "on_PushButton_ResultList_clicked"
QT_MOC_LITERAL(10, 242, 29), // "on_pushButtonCutImage_clicked"
QT_MOC_LITERAL(11, 272, 35) // "on_pushButton_CameraSetting_c..."

    },
    "Camera\0updateImage\0\0on_pushButton_Open_clicked\0"
    "on_pushButton_Display_clicked\0"
    "on_pushButton_Display_clicked_back\0"
    "on_pushButton_Close_clicked\0"
    "on_pushButton_SaveFile_clicked\0"
    "on_PushButton_PictureAnalysis_clicked\0"
    "on_PushButton_ResultList_clicked\0"
    "on_pushButtonCutImage_clicked\0"
    "on_pushButton_CameraSetting_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Camera[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   64,    2, 0x08 /* Private */,
       3,    0,   65,    2, 0x08 /* Private */,
       4,    0,   66,    2, 0x08 /* Private */,
       5,    0,   67,    2, 0x08 /* Private */,
       6,    0,   68,    2, 0x08 /* Private */,
       7,    0,   69,    2, 0x08 /* Private */,
       8,    0,   70,    2, 0x08 /* Private */,
       9,    0,   71,    2, 0x08 /* Private */,
      10,    0,   72,    2, 0x08 /* Private */,
      11,    0,   73,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Camera::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Camera *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->updateImage(); break;
        case 1: _t->on_pushButton_Open_clicked(); break;
        case 2: _t->on_pushButton_Display_clicked(); break;
        case 3: _t->on_pushButton_Display_clicked_back(); break;
        case 4: _t->on_pushButton_Close_clicked(); break;
        case 5: _t->on_pushButton_SaveFile_clicked(); break;
        case 6: _t->on_PushButton_PictureAnalysis_clicked(); break;
        case 7: _t->on_PushButton_ResultList_clicked(); break;
        case 8: _t->on_pushButtonCutImage_clicked(); break;
        case 9: _t->on_pushButton_CameraSetting_clicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject Camera::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_Camera.data,
    qt_meta_data_Camera,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Camera::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Camera::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Camera.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int Camera::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
