/****************************************************************************
** Meta object code from reading C++ file 'CameraCheckWidgets.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/utility/maintain/CameraCheckWidgets.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CameraCheckWidgets.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CameraCheckWidgets_t {
    QByteArrayData data[10];
    char stringdata0[149];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CameraCheckWidgets_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CameraCheckWidgets_t qt_meta_stringdata_CameraCheckWidgets = {
    {
QT_MOC_LITERAL(0, 0, 18), // "CameraCheckWidgets"
QT_MOC_LITERAL(1, 19, 11), // "test_signal"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 11), // "preper_save"
QT_MOC_LITERAL(4, 44, 19), // "CameraCheckWidgets*"
QT_MOC_LITERAL(5, 64, 21), // "on_pushButton_clicked"
QT_MOC_LITERAL(6, 86, 23), // "on_pushButton_2_clicked"
QT_MOC_LITERAL(7, 110, 23), // "on_pushButton_3_clicked"
QT_MOC_LITERAL(8, 134, 10), // "UpdateSlot"
QT_MOC_LITERAL(9, 145, 3) // "num"

    },
    "CameraCheckWidgets\0test_signal\0\0"
    "preper_save\0CameraCheckWidgets*\0"
    "on_pushButton_clicked\0on_pushButton_2_clicked\0"
    "on_pushButton_3_clicked\0UpdateSlot\0"
    "num"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CameraCheckWidgets[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x06 /* Public */,
       3,    1,   45,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   48,    2, 0x0a /* Public */,
       6,    0,   49,    2, 0x0a /* Public */,
       7,    0,   50,    2, 0x0a /* Public */,
       8,    1,   51,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    9,

       0        // eod
};

void CameraCheckWidgets::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<CameraCheckWidgets *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->test_signal(); break;
        case 1: _t->preper_save((*reinterpret_cast< CameraCheckWidgets*(*)>(_a[1]))); break;
        case 2: _t->on_pushButton_clicked(); break;
        case 3: _t->on_pushButton_2_clicked(); break;
        case 4: _t->on_pushButton_3_clicked(); break;
        case 5: _t->UpdateSlot((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< CameraCheckWidgets* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (CameraCheckWidgets::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CameraCheckWidgets::test_signal)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (CameraCheckWidgets::*)(CameraCheckWidgets * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CameraCheckWidgets::preper_save)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject CameraCheckWidgets::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_CameraCheckWidgets.data,
    qt_meta_data_CameraCheckWidgets,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *CameraCheckWidgets::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CameraCheckWidgets::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CameraCheckWidgets.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int CameraCheckWidgets::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void CameraCheckWidgets::test_signal()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void CameraCheckWidgets::preper_save(CameraCheckWidgets * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
