/****************************************************************************
** Meta object code from reading C++ file 'IrrigationSystemLiquidWidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/sample/IrrigationSystemLiquidWidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'IrrigationSystemLiquidWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_IrrigationSystemLiquidWidget_t {
    QByteArrayData data[7];
    char stringdata0[117];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_IrrigationSystemLiquidWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_IrrigationSystemLiquidWidget_t qt_meta_stringdata_IrrigationSystemLiquidWidget = {
    {
QT_MOC_LITERAL(0, 0, 28), // "IrrigationSystemLiquidWidget"
QT_MOC_LITERAL(1, 29, 19), // "ChangeBtnNextSignal"
QT_MOC_LITERAL(2, 49, 0), // ""
QT_MOC_LITERAL(3, 50, 5), // "flage"
QT_MOC_LITERAL(4, 56, 22), // "on_btnIrrigate_clicked"
QT_MOC_LITERAL(5, 79, 18), // "on_btnWash_clicked"
QT_MOC_LITERAL(6, 98, 18) // "on_btnFill_clicked"

    },
    "IrrigationSystemLiquidWidget\0"
    "ChangeBtnNextSignal\0\0flage\0"
    "on_btnIrrigate_clicked\0on_btnWash_clicked\0"
    "on_btnFill_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_IrrigationSystemLiquidWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   37,    2, 0x08 /* Private */,
       5,    0,   38,    2, 0x08 /* Private */,
       6,    0,   39,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool,    3,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void IrrigationSystemLiquidWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<IrrigationSystemLiquidWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->ChangeBtnNextSignal((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->on_btnIrrigate_clicked(); break;
        case 2: _t->on_btnWash_clicked(); break;
        case 3: _t->on_btnFill_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (IrrigationSystemLiquidWidget::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&IrrigationSystemLiquidWidget::ChangeBtnNextSignal)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject IrrigationSystemLiquidWidget::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_IrrigationSystemLiquidWidget.data,
    qt_meta_data_IrrigationSystemLiquidWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *IrrigationSystemLiquidWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *IrrigationSystemLiquidWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_IrrigationSystemLiquidWidget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int IrrigationSystemLiquidWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void IrrigationSystemLiquidWidget::ChangeBtnNextSignal(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
