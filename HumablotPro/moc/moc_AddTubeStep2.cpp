/****************************************************************************
** Meta object code from reading C++ file 'AddTubeStep2.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/utility/AddTubeStep2.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'AddTubeStep2.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_AddTubeStep2_t {
    QByteArrayData data[8];
    char stringdata0[129];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_AddTubeStep2_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_AddTubeStep2_t qt_meta_stringdata_AddTubeStep2 = {
    {
QT_MOC_LITERAL(0, 0, 12), // "AddTubeStep2"
QT_MOC_LITERAL(1, 13, 9), // "SetCancel"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 5), // "bFlag"
QT_MOC_LITERAL(4, 30, 15), // "getCancelSignal"
QT_MOC_LITERAL(5, 46, 26), // "on_pushButton_Back_clicked"
QT_MOC_LITERAL(6, 73, 26), // "on_pushButton_Next_clicked"
QT_MOC_LITERAL(7, 100, 28) // "on_pushButton_Cancel_clicked"

    },
    "AddTubeStep2\0SetCancel\0\0bFlag\0"
    "getCancelSignal\0on_pushButton_Back_clicked\0"
    "on_pushButton_Next_clicked\0"
    "on_pushButton_Cancel_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AddTubeStep2[] = {

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
       4,    1,   42,    2, 0x08 /* Private */,
       5,    0,   45,    2, 0x08 /* Private */,
       6,    0,   46,    2, 0x08 /* Private */,
       7,    0,   47,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool,    3,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void AddTubeStep2::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<AddTubeStep2 *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->SetCancel((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->getCancelSignal((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->on_pushButton_Back_clicked(); break;
        case 3: _t->on_pushButton_Next_clicked(); break;
        case 4: _t->on_pushButton_Cancel_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (AddTubeStep2::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AddTubeStep2::SetCancel)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject AddTubeStep2::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_AddTubeStep2.data,
    qt_meta_data_AddTubeStep2,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *AddTubeStep2::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AddTubeStep2::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_AddTubeStep2.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int AddTubeStep2::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
void AddTubeStep2::SetCancel(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
