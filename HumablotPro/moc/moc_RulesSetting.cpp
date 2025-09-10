/****************************************************************************
** Meta object code from reading C++ file 'RulesSetting.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/utility/RulesSetting.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'RulesSetting.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_RulesSetting_t {
    QByteArrayData data[17];
    char stringdata0[293];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_RulesSetting_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_RulesSetting_t qt_meta_stringdata_RulesSetting = {
    {
QT_MOC_LITERAL(0, 0, 12), // "RulesSetting"
QT_MOC_LITERAL(1, 13, 18), // "on_btnRule_clicked"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 19), // "on_btnCurve_clicked"
QT_MOC_LITERAL(4, 53, 21), // "on_btnAddRule_clicked"
QT_MOC_LITERAL(5, 75, 17), // "on_tbRule_clicked"
QT_MOC_LITERAL(6, 93, 11), // "QModelIndex"
QT_MOC_LITERAL(7, 105, 5), // "index"
QT_MOC_LITERAL(8, 111, 24), // "on_btnDeleteRule_clicked"
QT_MOC_LITERAL(9, 136, 21), // "on_btnAddItem_clicked"
QT_MOC_LITERAL(10, 158, 22), // "on_btnSaveItem_clicked"
QT_MOC_LITERAL(11, 181, 20), // "on_btnDelete_clicked"
QT_MOC_LITERAL(12, 202, 19), // "slotFitCurveChanged"
QT_MOC_LITERAL(13, 222, 25), // "on_tbRuleItem_itemChanged"
QT_MOC_LITERAL(14, 248, 17), // "QTableWidgetItem*"
QT_MOC_LITERAL(15, 266, 4), // "item"
QT_MOC_LITERAL(16, 271, 21) // "on_tbRule_itemChanged"

    },
    "RulesSetting\0on_btnRule_clicked\0\0"
    "on_btnCurve_clicked\0on_btnAddRule_clicked\0"
    "on_tbRule_clicked\0QModelIndex\0index\0"
    "on_btnDeleteRule_clicked\0on_btnAddItem_clicked\0"
    "on_btnSaveItem_clicked\0on_btnDelete_clicked\0"
    "slotFitCurveChanged\0on_tbRuleItem_itemChanged\0"
    "QTableWidgetItem*\0item\0on_tbRule_itemChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_RulesSetting[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   69,    2, 0x08 /* Private */,
       3,    0,   70,    2, 0x08 /* Private */,
       4,    0,   71,    2, 0x08 /* Private */,
       5,    1,   72,    2, 0x08 /* Private */,
       8,    0,   75,    2, 0x08 /* Private */,
       9,    0,   76,    2, 0x08 /* Private */,
      10,    0,   77,    2, 0x08 /* Private */,
      11,    0,   78,    2, 0x08 /* Private */,
      12,    1,   79,    2, 0x08 /* Private */,
      13,    1,   82,    2, 0x08 /* Private */,
      16,    1,   85,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void, 0x80000000 | 14,   15,
    QMetaType::Void, 0x80000000 | 14,   15,

       0        // eod
};

void RulesSetting::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<RulesSetting *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_btnRule_clicked(); break;
        case 1: _t->on_btnCurve_clicked(); break;
        case 2: _t->on_btnAddRule_clicked(); break;
        case 3: _t->on_tbRule_clicked((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 4: _t->on_btnDeleteRule_clicked(); break;
        case 5: _t->on_btnAddItem_clicked(); break;
        case 6: _t->on_btnSaveItem_clicked(); break;
        case 7: _t->on_btnDelete_clicked(); break;
        case 8: _t->slotFitCurveChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->on_tbRuleItem_itemChanged((*reinterpret_cast< QTableWidgetItem*(*)>(_a[1]))); break;
        case 10: _t->on_tbRule_itemChanged((*reinterpret_cast< QTableWidgetItem*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject RulesSetting::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_RulesSetting.data,
    qt_meta_data_RulesSetting,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *RulesSetting::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *RulesSetting::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_RulesSetting.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int RulesSetting::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
