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
    QByteArrayData data[11];
    char stringdata0[198];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TestResultDetailDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TestResultDetailDialog_t qt_meta_stringdata_TestResultDetailDialog = {
    {
QT_MOC_LITERAL(0, 0, 22), // "TestResultDetailDialog"
QT_MOC_LITERAL(1, 23, 34), // "UpdateTestResultTableOneTypeS..."
QT_MOC_LITERAL(2, 58, 0), // ""
QT_MOC_LITERAL(3, 59, 6), // "testId"
QT_MOC_LITERAL(4, 66, 26), // "OnClickModifyOneTestResult"
QT_MOC_LITERAL(5, 93, 24), // "on_pdfSaveButton_clicked"
QT_MOC_LITERAL(6, 118, 22), // "on_printButton_clicked"
QT_MOC_LITERAL(7, 141, 21), // "paintRequestedHandler"
QT_MOC_LITERAL(8, 163, 9), // "QPrinter*"
QT_MOC_LITERAL(9, 173, 13), // "printerPixmap"
QT_MOC_LITERAL(10, 187, 10) // "exportSlot"

    },
    "TestResultDetailDialog\0"
    "UpdateTestResultTableOneTypeSignal\0\0"
    "testId\0OnClickModifyOneTestResult\0"
    "on_pdfSaveButton_clicked\0"
    "on_printButton_clicked\0paintRequestedHandler\0"
    "QPrinter*\0printerPixmap\0exportSlot"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TestResultDetailDialog[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   47,    2, 0x0a /* Public */,
       5,    0,   48,    2, 0x0a /* Public */,
       6,    0,   49,    2, 0x0a /* Public */,
       7,    1,   50,    2, 0x0a /* Public */,
      10,    0,   53,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void,

       0        // eod
};

void TestResultDetailDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<TestResultDetailDialog *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->UpdateTestResultTableOneTypeSignal((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->OnClickModifyOneTestResult(); break;
        case 2: _t->on_pdfSaveButton_clicked(); break;
        case 3: _t->on_printButton_clicked(); break;
        case 4: _t->paintRequestedHandler((*reinterpret_cast< QPrinter*(*)>(_a[1]))); break;
        case 5: _t->exportSlot(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (TestResultDetailDialog::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TestResultDetailDialog::UpdateTestResultTableOneTypeSignal)) {
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
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void TestResultDetailDialog::UpdateTestResultTableOneTypeSignal(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
