/****************************************************************************
** Meta object code from reading C++ file 'LisSettingWidgets.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/main/LisSettingWidgets.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'LisSettingWidgets.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_LisSettingWidgets_t {
    QByteArrayData data[14];
    char stringdata0[258];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_LisSettingWidgets_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_LisSettingWidgets_t qt_meta_stringdata_LisSettingWidgets = {
    {
QT_MOC_LITERAL(0, 0, 17), // "LisSettingWidgets"
QT_MOC_LITERAL(1, 18, 25), // "on_pushButtonSave_clicked"
QT_MOC_LITERAL(2, 44, 0), // ""
QT_MOC_LITERAL(3, 45, 13), // "onSendClicked"
QT_MOC_LITERAL(4, 59, 13), // "updateDisplay"
QT_MOC_LITERAL(5, 73, 4), // "data"
QT_MOC_LITERAL(6, 78, 16), // "onConnectClicked"
QT_MOC_LITERAL(7, 95, 17), // "slotConnectStatus"
QT_MOC_LITERAL(8, 113, 6), // "status"
QT_MOC_LITERAL(9, 120, 25), // "on_pushButtonSend_clicked"
QT_MOC_LITERAL(10, 146, 27), // "on_pushButtonSend_5_clicked"
QT_MOC_LITERAL(11, 174, 27), // "on_pushButtonSend_2_clicked"
QT_MOC_LITERAL(12, 202, 27), // "on_pushButtonSend_3_clicked"
QT_MOC_LITERAL(13, 230, 27) // "on_pushButtonSend_4_clicked"

    },
    "LisSettingWidgets\0on_pushButtonSave_clicked\0"
    "\0onSendClicked\0updateDisplay\0data\0"
    "onConnectClicked\0slotConnectStatus\0"
    "status\0on_pushButtonSend_clicked\0"
    "on_pushButtonSend_5_clicked\0"
    "on_pushButtonSend_2_clicked\0"
    "on_pushButtonSend_3_clicked\0"
    "on_pushButtonSend_4_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_LisSettingWidgets[] = {

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
       4,    1,   66,    2, 0x08 /* Private */,
       6,    0,   69,    2, 0x08 /* Private */,
       7,    1,   70,    2, 0x08 /* Private */,
       9,    0,   73,    2, 0x08 /* Private */,
      10,    0,   74,    2, 0x08 /* Private */,
      11,    0,   75,    2, 0x08 /* Private */,
      12,    0,   76,    2, 0x08 /* Private */,
      13,    0,   77,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    8,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void LisSettingWidgets::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<LisSettingWidgets *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_pushButtonSave_clicked(); break;
        case 1: _t->onSendClicked(); break;
        case 2: _t->updateDisplay((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->onConnectClicked(); break;
        case 4: _t->slotConnectStatus((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: _t->on_pushButtonSend_clicked(); break;
        case 6: _t->on_pushButtonSend_5_clicked(); break;
        case 7: _t->on_pushButtonSend_2_clicked(); break;
        case 8: _t->on_pushButtonSend_3_clicked(); break;
        case 9: _t->on_pushButtonSend_4_clicked(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject LisSettingWidgets::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_LisSettingWidgets.data,
    qt_meta_data_LisSettingWidgets,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *LisSettingWidgets::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *LisSettingWidgets::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_LisSettingWidgets.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int LisSettingWidgets::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
