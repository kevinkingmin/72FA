/****************************************************************************
** Meta object code from reading C++ file 'PrepareReagentDialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/sample/subDialog/PrepareReagentDialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'PrepareReagentDialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_PrepareReagentDialog_t {
    QByteArrayData data[11];
    char stringdata0[214];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PrepareReagentDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PrepareReagentDialog_t qt_meta_stringdata_PrepareReagentDialog = {
    {
QT_MOC_LITERAL(0, 0, 20), // "PrepareReagentDialog"
QT_MOC_LITERAL(1, 21, 18), // "sglPumpStateChange"
QT_MOC_LITERAL(2, 40, 0), // ""
QT_MOC_LITERAL(3, 41, 26), // "on_pushButtonClose_clicked"
QT_MOC_LITERAL(4, 68, 20), // "on_btnConfig_clicked"
QT_MOC_LITERAL(5, 89, 19), // "on_btnFlash_clicked"
QT_MOC_LITERAL(6, 109, 19), // "on_btnReady_clicked"
QT_MOC_LITERAL(7, 129, 19), // "on_btnDelay_clicked"
QT_MOC_LITERAL(8, 149, 26), // "on_pushButtonSmall_clicked"
QT_MOC_LITERAL(9, 176, 19), // "on_btnSmall_clicked"
QT_MOC_LITERAL(10, 196, 17) // "on_btnBig_clicked"

    },
    "PrepareReagentDialog\0sglPumpStateChange\0"
    "\0on_pushButtonClose_clicked\0"
    "on_btnConfig_clicked\0on_btnFlash_clicked\0"
    "on_btnReady_clicked\0on_btnDelay_clicked\0"
    "on_pushButtonSmall_clicked\0"
    "on_btnSmall_clicked\0on_btnBig_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PrepareReagentDialog[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   59,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   60,    2, 0x08 /* Private */,
       4,    0,   61,    2, 0x08 /* Private */,
       5,    0,   62,    2, 0x08 /* Private */,
       6,    0,   63,    2, 0x08 /* Private */,
       7,    0,   64,    2, 0x08 /* Private */,
       8,    0,   65,    2, 0x08 /* Private */,
       9,    0,   66,    2, 0x08 /* Private */,
      10,    0,   67,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
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

void PrepareReagentDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<PrepareReagentDialog *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sglPumpStateChange(); break;
        case 1: _t->on_pushButtonClose_clicked(); break;
        case 2: _t->on_btnConfig_clicked(); break;
        case 3: _t->on_btnFlash_clicked(); break;
        case 4: _t->on_btnReady_clicked(); break;
        case 5: _t->on_btnDelay_clicked(); break;
        case 6: _t->on_pushButtonSmall_clicked(); break;
        case 7: _t->on_btnSmall_clicked(); break;
        case 8: _t->on_btnBig_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (PrepareReagentDialog::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PrepareReagentDialog::sglPumpStateChange)) {
                *result = 0;
                return;
            }
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject PrepareReagentDialog::staticMetaObject = { {
    &BaseDialog::staticMetaObject,
    qt_meta_stringdata_PrepareReagentDialog.data,
    qt_meta_data_PrepareReagentDialog,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *PrepareReagentDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PrepareReagentDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_PrepareReagentDialog.stringdata0))
        return static_cast<void*>(this);
    return BaseDialog::qt_metacast(_clname);
}

int PrepareReagentDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = BaseDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void PrepareReagentDialog::sglPumpStateChange()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
