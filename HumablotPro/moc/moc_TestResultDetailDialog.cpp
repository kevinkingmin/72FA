/****************************************************************************
** Meta object code from reading C++ file 'TestResultDetailDialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/sample/TestResultDetailDialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'TestResultDetailDialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_TestResultDetailDialog_t {
    QByteArrayData data[8];
    char stringdata0[120];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TestResultDetailDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TestResultDetailDialog_t qt_meta_stringdata_TestResultDetailDialog = {
    {
QT_MOC_LITERAL(0, 0, 22), // "TestResultDetailDialog"
QT_MOC_LITERAL(1, 23, 11), // "sglUpdateUI"
QT_MOC_LITERAL(2, 35, 0), // ""
QT_MOC_LITERAL(3, 36, 26), // "OnClickModifyOneTestResult"
QT_MOC_LITERAL(4, 63, 21), // "paintRequestedHandler"
QT_MOC_LITERAL(5, 85, 9), // "QPrinter*"
QT_MOC_LITERAL(6, 95, 13), // "printerPixmap"
QT_MOC_LITERAL(7, 109, 10) // "exportSlot"

    },
    "TestResultDetailDialog\0sglUpdateUI\0\0"
    "OnClickModifyOneTestResult\0"
    "paintRequestedHandler\0QPrinter*\0"
    "printerPixmap\0exportSlot"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TestResultDetailDialog[] = {

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
       1,    0,   34,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   35,    2, 0x0a /* Public */,
       4,    1,   36,    2, 0x0a /* Public */,
       7,    0,   39,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void,

       0        // eod
};

void TestResultDetailDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<TestResultDetailDialog *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sglUpdateUI(); break;
        case 1: _t->OnClickModifyOneTestResult(); break;
        case 2: _t->paintRequestedHandler((*reinterpret_cast< QPrinter*(*)>(_a[1]))); break;
        case 3: _t->exportSlot(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (TestResultDetailDialog::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TestResultDetailDialog::sglUpdateUI)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject TestResultDetailDialog::staticMetaObject = { {
    &QDialog::staticMetaObject,
    qt_meta_stringdata_TestResultDetailDialog.data,
    qt_meta_data_TestResultDetailDialog,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *TestResultDetailDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TestResultDetailDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_TestResultDetailDialog.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int TestResultDetailDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
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
void TestResultDetailDialog::sglUpdateUI()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
