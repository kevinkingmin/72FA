/****************************************************************************
** Meta object code from reading C++ file 'MaintainCmdWidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/utility/maintain/MaintainCmdWidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MaintainCmdWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MaintainCmdWidget_t {
    QByteArrayData data[14];
    char stringdata0[287];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MaintainCmdWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MaintainCmdWidget_t qt_meta_stringdata_MaintainCmdWidget = {
    {
QT_MOC_LITERAL(0, 0, 17), // "MaintainCmdWidget"
QT_MOC_LITERAL(1, 18, 21), // "on_btnRunInit_clicked"
QT_MOC_LITERAL(2, 40, 0), // ""
QT_MOC_LITERAL(3, 41, 23), // "on_btnCloseInit_clicked"
QT_MOC_LITERAL(4, 65, 24), // "on_btnSysteReset_clicked"
QT_MOC_LITERAL(5, 90, 23), // "on_btnStartWash_clicked"
QT_MOC_LITERAL(6, 114, 22), // "on_btnWeekWash_clicked"
QT_MOC_LITERAL(7, 137, 19), // "on_btnEmpty_clicked"
QT_MOC_LITERAL(8, 157, 19), // "on_btnFlush_clicked"
QT_MOC_LITERAL(9, 177, 23), // "on_btnCloseWash_clicked"
QT_MOC_LITERAL(10, 201, 19), // "on_btnClose_clicked"
QT_MOC_LITERAL(11, 221, 21), // "on_btnDormant_clicked"
QT_MOC_LITERAL(12, 243, 19), // "on_btnRouse_clicked"
QT_MOC_LITERAL(13, 263, 23) // "on_btnPoolFlush_clicked"

    },
    "MaintainCmdWidget\0on_btnRunInit_clicked\0"
    "\0on_btnCloseInit_clicked\0"
    "on_btnSysteReset_clicked\0"
    "on_btnStartWash_clicked\0on_btnWeekWash_clicked\0"
    "on_btnEmpty_clicked\0on_btnFlush_clicked\0"
    "on_btnCloseWash_clicked\0on_btnClose_clicked\0"
    "on_btnDormant_clicked\0on_btnRouse_clicked\0"
    "on_btnPoolFlush_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MaintainCmdWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   74,    2, 0x08 /* Private */,
       3,    0,   75,    2, 0x08 /* Private */,
       4,    0,   76,    2, 0x08 /* Private */,
       5,    0,   77,    2, 0x08 /* Private */,
       6,    0,   78,    2, 0x08 /* Private */,
       7,    0,   79,    2, 0x08 /* Private */,
       8,    0,   80,    2, 0x08 /* Private */,
       9,    0,   81,    2, 0x08 /* Private */,
      10,    0,   82,    2, 0x08 /* Private */,
      11,    0,   83,    2, 0x08 /* Private */,
      12,    0,   84,    2, 0x08 /* Private */,
      13,    0,   85,    2, 0x08 /* Private */,

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
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MaintainCmdWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MaintainCmdWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_btnRunInit_clicked(); break;
        case 1: _t->on_btnCloseInit_clicked(); break;
        case 2: _t->on_btnSysteReset_clicked(); break;
        case 3: _t->on_btnStartWash_clicked(); break;
        case 4: _t->on_btnWeekWash_clicked(); break;
        case 5: _t->on_btnEmpty_clicked(); break;
        case 6: _t->on_btnFlush_clicked(); break;
        case 7: _t->on_btnCloseWash_clicked(); break;
        case 8: _t->on_btnClose_clicked(); break;
        case 9: _t->on_btnDormant_clicked(); break;
        case 10: _t->on_btnRouse_clicked(); break;
        case 11: _t->on_btnPoolFlush_clicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject MaintainCmdWidget::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_MaintainCmdWidget.data,
    qt_meta_data_MaintainCmdWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MaintainCmdWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MaintainCmdWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MaintainCmdWidget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int MaintainCmdWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
