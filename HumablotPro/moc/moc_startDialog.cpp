/****************************************************************************
** Meta object code from reading C++ file 'startDialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../72fa_acon_final/HumaBlotPro/src/main/subDialog/startDialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'startDialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_StartDialog_t {
    QByteArrayData data[13];
    char stringdata0[248];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_StartDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_StartDialog_t qt_meta_stringdata_StartDialog = {
    {
QT_MOC_LITERAL(0, 0, 11), // "StartDialog"
QT_MOC_LITERAL(1, 12, 14), // "sglCurrentPage"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 4), // "page"
QT_MOC_LITERAL(4, 33, 26), // "on_pushButtonClose_clicked"
QT_MOC_LITERAL(5, 60, 20), // "on_btnCancel_clicked"
QT_MOC_LITERAL(6, 81, 25), // "on_btnReagentInfo_clicked"
QT_MOC_LITERAL(7, 107, 23), // "on_btnCalibrate_clicked"
QT_MOC_LITERAL(8, 131, 16), // "on_btnQC_clicked"
QT_MOC_LITERAL(9, 148, 24), // "on_btnStatistics_clicked"
QT_MOC_LITERAL(10, 173, 26), // "on_btnChangeSample_clicked"
QT_MOC_LITERAL(11, 200, 27), // "on_btnAddConsumable_clicked"
QT_MOC_LITERAL(12, 228, 19) // "on_btnStart_clicked"

    },
    "StartDialog\0sglCurrentPage\0\0page\0"
    "on_pushButtonClose_clicked\0"
    "on_btnCancel_clicked\0on_btnReagentInfo_clicked\0"
    "on_btnCalibrate_clicked\0on_btnQC_clicked\0"
    "on_btnStatistics_clicked\0"
    "on_btnChangeSample_clicked\0"
    "on_btnAddConsumable_clicked\0"
    "on_btnStart_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_StartDialog[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   64,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   67,    2, 0x08 /* Private */,
       5,    0,   68,    2, 0x08 /* Private */,
       6,    0,   69,    2, 0x08 /* Private */,
       7,    0,   70,    2, 0x08 /* Private */,
       8,    0,   71,    2, 0x08 /* Private */,
       9,    0,   72,    2, 0x08 /* Private */,
      10,    0,   73,    2, 0x08 /* Private */,
      11,    0,   74,    2, 0x08 /* Private */,
      12,    0,   75,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,

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

       0        // eod
};

void StartDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<StartDialog *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sglCurrentPage((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->on_pushButtonClose_clicked(); break;
        case 2: _t->on_btnCancel_clicked(); break;
        case 3: _t->on_btnReagentInfo_clicked(); break;
        case 4: _t->on_btnCalibrate_clicked(); break;
        case 5: _t->on_btnQC_clicked(); break;
        case 6: _t->on_btnStatistics_clicked(); break;
        case 7: _t->on_btnChangeSample_clicked(); break;
        case 8: _t->on_btnAddConsumable_clicked(); break;
        case 9: _t->on_btnStart_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (StartDialog::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StartDialog::sglCurrentPage)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject StartDialog::staticMetaObject = { {
    &BaseDialog::staticMetaObject,
    qt_meta_stringdata_StartDialog.data,
    qt_meta_data_StartDialog,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *StartDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *StartDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_StartDialog.stringdata0))
        return static_cast<void*>(this);
    return BaseDialog::qt_metacast(_clname);
}

int StartDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = BaseDialog::qt_metacall(_c, _id, _a);
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
void StartDialog::sglCurrentPage(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
