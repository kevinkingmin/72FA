/****************************************************************************
** Meta object code from reading C++ file 'MaintainSystem.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/function/maintain/MaintainSystem.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MaintainSystem.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MaintainSystem_t {
    QByteArrayData data[16];
    char stringdata0[167];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MaintainSystem_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MaintainSystem_t qt_meta_stringdata_MaintainSystem = {
    {
QT_MOC_LITERAL(0, 0, 14), // "MaintainSystem"
QT_MOC_LITERAL(1, 15, 12), // "sglRunResult"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 9), // "resultStr"
QT_MOC_LITERAL(4, 39, 16), // "sglMonthMaintain"
QT_MOC_LITERAL(5, 56, 6), // "result"
QT_MOC_LITERAL(6, 63, 22), // "sglPumpCalibrateFinish"
QT_MOC_LITERAL(7, 86, 6), // "pumpNo"
QT_MOC_LITERAL(8, 93, 8), // "fstSteps"
QT_MOC_LITERAL(9, 102, 8), // "SndSteps"
QT_MOC_LITERAL(10, 111, 16), // "sglSampleBatchNo"
QT_MOC_LITERAL(11, 128, 3), // "pos"
QT_MOC_LITERAL(12, 132, 8), // "sampleNo"
QT_MOC_LITERAL(13, 141, 15), // "sglMaintainStep"
QT_MOC_LITERAL(14, 157, 5), // "index"
QT_MOC_LITERAL(15, 163, 3) // "des"

    },
    "MaintainSystem\0sglRunResult\0\0resultStr\0"
    "sglMonthMaintain\0result\0sglPumpCalibrateFinish\0"
    "pumpNo\0fstSteps\0SndSteps\0sglSampleBatchNo\0"
    "pos\0sampleNo\0sglMaintainStep\0index\0"
    "des"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MaintainSystem[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x06 /* Public */,
       4,    1,   42,    2, 0x06 /* Public */,
       6,    3,   45,    2, 0x06 /* Public */,
      10,    2,   52,    2, 0x06 /* Public */,
      13,    2,   57,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,    7,    8,    9,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,   11,   12,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,   14,   15,

       0        // eod
};

void MaintainSystem::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MaintainSystem *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sglRunResult((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->sglMonthMaintain((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->sglPumpCalibrateFinish((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 3: _t->sglSampleBatchNo((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 4: _t->sglMaintainStep((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (MaintainSystem::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MaintainSystem::sglRunResult)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (MaintainSystem::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MaintainSystem::sglMonthMaintain)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (MaintainSystem::*)(int , int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MaintainSystem::sglPumpCalibrateFinish)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (MaintainSystem::*)(int , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MaintainSystem::sglSampleBatchNo)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (MaintainSystem::*)(int , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MaintainSystem::sglMaintainStep)) {
                *result = 4;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MaintainSystem::staticMetaObject = { {
    &Function::staticMetaObject,
    qt_meta_stringdata_MaintainSystem.data,
    qt_meta_data_MaintainSystem,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MaintainSystem::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MaintainSystem::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MaintainSystem.stringdata0))
        return static_cast<void*>(this);
    return Function::qt_metacast(_clname);
}

int MaintainSystem::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Function::qt_metacall(_c, _id, _a);
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
void MaintainSystem::sglRunResult(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MaintainSystem::sglMonthMaintain(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void MaintainSystem::sglPumpCalibrateFinish(int _t1, int _t2, int _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void MaintainSystem::sglSampleBatchNo(int _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void MaintainSystem::sglMaintainStep(int _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
