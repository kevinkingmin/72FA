/****************************************************************************
** Meta object code from reading C++ file 'freezetableview.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/comm/freezetableview.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'freezetableview.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_FreezeTableView_t {
    QByteArrayData data[11];
    char stringdata0[135];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_FreezeTableView_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_FreezeTableView_t qt_meta_stringdata_FreezeTableView = {
    {
QT_MOC_LITERAL(0, 0, 15), // "FreezeTableView"
QT_MOC_LITERAL(1, 16, 15), // "signalBlankArea"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 12), // "QMouseEvent*"
QT_MOC_LITERAL(4, 46, 5), // "event"
QT_MOC_LITERAL(5, 52, 14), // "signalDataArea"
QT_MOC_LITERAL(6, 67, 18), // "updateSectionWidth"
QT_MOC_LITERAL(7, 86, 12), // "logicalIndex"
QT_MOC_LITERAL(8, 99, 7), // "oldSize"
QT_MOC_LITERAL(9, 107, 7), // "newSize"
QT_MOC_LITERAL(10, 115, 19) // "updateSectionHeight"

    },
    "FreezeTableView\0signalBlankArea\0\0"
    "QMouseEvent*\0event\0signalDataArea\0"
    "updateSectionWidth\0logicalIndex\0oldSize\0"
    "newSize\0updateSectionHeight"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_FreezeTableView[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x06 /* Public */,
       5,    1,   37,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    3,   40,    2, 0x08 /* Private */,
      10,    3,   47,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,    7,    8,    9,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,    7,    8,    9,

       0        // eod
};

void FreezeTableView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<FreezeTableView *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signalBlankArea((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 1: _t->signalDataArea((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 2: _t->updateSectionWidth((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 3: _t->updateSectionHeight((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (FreezeTableView::*)(QMouseEvent * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FreezeTableView::signalBlankArea)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (FreezeTableView::*)(QMouseEvent * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FreezeTableView::signalDataArea)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject FreezeTableView::staticMetaObject = { {
    &QTableView::staticMetaObject,
    qt_meta_stringdata_FreezeTableView.data,
    qt_meta_data_FreezeTableView,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *FreezeTableView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FreezeTableView::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_FreezeTableView.stringdata0))
        return static_cast<void*>(this);
    return QTableView::qt_metacast(_clname);
}

int FreezeTableView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTableView::qt_metacall(_c, _id, _a);
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
void FreezeTableView::signalBlankArea(QMouseEvent * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void FreezeTableView::signalDataArea(QMouseEvent * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
