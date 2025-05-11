/****************************************************************************
** Meta object code from reading C++ file 'BatchAddSampleWidgets.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/sample/BatchAddSampleWidgets.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'BatchAddSampleWidgets.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_BatchAddSampleWidgets_t {
    QByteArrayData data[9];
    char stringdata0[188];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_BatchAddSampleWidgets_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_BatchAddSampleWidgets_t qt_meta_stringdata_BatchAddSampleWidgets = {
    {
QT_MOC_LITERAL(0, 0, 21), // "BatchAddSampleWidgets"
QT_MOC_LITERAL(1, 22, 18), // "sglFromBatchSample"
QT_MOC_LITERAL(2, 41, 0), // ""
QT_MOC_LITERAL(3, 42, 9), // "confition"
QT_MOC_LITERAL(4, 52, 24), // "on_pushButtonAdd_clicked"
QT_MOC_LITERAL(5, 77, 27), // "on_pushButtonDelete_clicked"
QT_MOC_LITERAL(6, 105, 30), // "on_pushButtonDeleteAll_clicked"
QT_MOC_LITERAL(7, 136, 27), // "on_pushButtonUpdate_clicked"
QT_MOC_LITERAL(8, 164, 23) // "on_pushButtonOk_clicked"

    },
    "BatchAddSampleWidgets\0sglFromBatchSample\0"
    "\0confition\0on_pushButtonAdd_clicked\0"
    "on_pushButtonDelete_clicked\0"
    "on_pushButtonDeleteAll_clicked\0"
    "on_pushButtonUpdate_clicked\0"
    "on_pushButtonOk_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_BatchAddSampleWidgets[] = {

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
       7,    0,   50,    2, 0x0a /* Public */,
       8,    0,   51,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void BatchAddSampleWidgets::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<BatchAddSampleWidgets *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sglFromBatchSample((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->on_pushButtonAdd_clicked(); break;
        case 2: _t->on_pushButtonDelete_clicked(); break;
        case 3: _t->on_pushButtonDeleteAll_clicked(); break;
        case 4: _t->on_pushButtonUpdate_clicked(); break;
        case 5: _t->on_pushButtonOk_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (BatchAddSampleWidgets::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&BatchAddSampleWidgets::sglFromBatchSample)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject BatchAddSampleWidgets::staticMetaObject = { {
    &QMainWindow::staticMetaObject,
    qt_meta_stringdata_BatchAddSampleWidgets.data,
    qt_meta_data_BatchAddSampleWidgets,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *BatchAddSampleWidgets::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *BatchAddSampleWidgets::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_BatchAddSampleWidgets.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int BatchAddSampleWidgets::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
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
void BatchAddSampleWidgets::sglFromBatchSample(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
