/****************************************************************************
** Meta object code from reading C++ file 'MyMessageBox.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/main/subDialog/MyMessageBox.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MyMessageBox.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MyMessageBox_t {
    QByteArrayData data[35];
    char stringdata0[299];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MyMessageBox_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MyMessageBox_t qt_meta_stringdata_MyMessageBox = {
    {
QT_MOC_LITERAL(0, 0, 12), // "MyMessageBox"
QT_MOC_LITERAL(1, 13, 21), // "slotPushButtonClicked"
QT_MOC_LITERAL(2, 35, 0), // ""
QT_MOC_LITERAL(3, 36, 16), // "QAbstractButton*"
QT_MOC_LITERAL(4, 53, 6), // "button"
QT_MOC_LITERAL(5, 60, 4), // "Icon"
QT_MOC_LITERAL(6, 65, 6), // "NoIcon"
QT_MOC_LITERAL(7, 72, 11), // "Information"
QT_MOC_LITERAL(8, 84, 8), // "Question"
QT_MOC_LITERAL(9, 93, 7), // "Success"
QT_MOC_LITERAL(10, 101, 7), // "Warning"
QT_MOC_LITERAL(11, 109, 8), // "Critical"
QT_MOC_LITERAL(12, 118, 14), // "StandardButton"
QT_MOC_LITERAL(13, 133, 8), // "NoButton"
QT_MOC_LITERAL(14, 142, 2), // "Ok"
QT_MOC_LITERAL(15, 145, 4), // "Save"
QT_MOC_LITERAL(16, 150, 7), // "SaveAll"
QT_MOC_LITERAL(17, 158, 4), // "Open"
QT_MOC_LITERAL(18, 163, 3), // "Yes"
QT_MOC_LITERAL(19, 167, 8), // "YesToAll"
QT_MOC_LITERAL(20, 176, 2), // "No"
QT_MOC_LITERAL(21, 179, 7), // "NoToAll"
QT_MOC_LITERAL(22, 187, 5), // "Abort"
QT_MOC_LITERAL(23, 193, 5), // "Retry"
QT_MOC_LITERAL(24, 199, 6), // "Ignore"
QT_MOC_LITERAL(25, 206, 5), // "Close"
QT_MOC_LITERAL(26, 212, 6), // "Cancel"
QT_MOC_LITERAL(27, 219, 7), // "Discard"
QT_MOC_LITERAL(28, 227, 4), // "Help"
QT_MOC_LITERAL(29, 232, 5), // "Apply"
QT_MOC_LITERAL(30, 238, 5), // "Reset"
QT_MOC_LITERAL(31, 244, 15), // "RestoreDefaults"
QT_MOC_LITERAL(32, 260, 11), // "FirstButton"
QT_MOC_LITERAL(33, 272, 10), // "LastButton"
QT_MOC_LITERAL(34, 283, 15) // "StandardButtons"

    },
    "MyMessageBox\0slotPushButtonClicked\0\0"
    "QAbstractButton*\0button\0Icon\0NoIcon\0"
    "Information\0Question\0Success\0Warning\0"
    "Critical\0StandardButton\0NoButton\0Ok\0"
    "Save\0SaveAll\0Open\0Yes\0YesToAll\0No\0"
    "NoToAll\0Abort\0Retry\0Ignore\0Close\0"
    "Cancel\0Discard\0Help\0Apply\0Reset\0"
    "RestoreDefaults\0FirstButton\0LastButton\0"
    "StandardButtons"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MyMessageBox[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       3,   22, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   19,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,

 // enums: name, alias, flags, count, data
       5,    5, 0x0,    6,   37,
      12,   12, 0x0,   21,   49,
      34,   12, 0x1,   21,   91,

 // enum data: key, value
       6, uint(MyMessageBox::NoIcon),
       7, uint(MyMessageBox::Information),
       8, uint(MyMessageBox::Question),
       9, uint(MyMessageBox::Success),
      10, uint(MyMessageBox::Warning),
      11, uint(MyMessageBox::Critical),
      13, uint(MyMessageBox::NoButton),
      14, uint(MyMessageBox::Ok),
      15, uint(MyMessageBox::Save),
      16, uint(MyMessageBox::SaveAll),
      17, uint(MyMessageBox::Open),
      18, uint(MyMessageBox::Yes),
      19, uint(MyMessageBox::YesToAll),
      20, uint(MyMessageBox::No),
      21, uint(MyMessageBox::NoToAll),
      22, uint(MyMessageBox::Abort),
      23, uint(MyMessageBox::Retry),
      24, uint(MyMessageBox::Ignore),
      25, uint(MyMessageBox::Close),
      26, uint(MyMessageBox::Cancel),
      27, uint(MyMessageBox::Discard),
      28, uint(MyMessageBox::Help),
      29, uint(MyMessageBox::Apply),
      30, uint(MyMessageBox::Reset),
      31, uint(MyMessageBox::RestoreDefaults),
      32, uint(MyMessageBox::FirstButton),
      33, uint(MyMessageBox::LastButton),
      13, uint(MyMessageBox::NoButton),
      14, uint(MyMessageBox::Ok),
      15, uint(MyMessageBox::Save),
      16, uint(MyMessageBox::SaveAll),
      17, uint(MyMessageBox::Open),
      18, uint(MyMessageBox::Yes),
      19, uint(MyMessageBox::YesToAll),
      20, uint(MyMessageBox::No),
      21, uint(MyMessageBox::NoToAll),
      22, uint(MyMessageBox::Abort),
      23, uint(MyMessageBox::Retry),
      24, uint(MyMessageBox::Ignore),
      25, uint(MyMessageBox::Close),
      26, uint(MyMessageBox::Cancel),
      27, uint(MyMessageBox::Discard),
      28, uint(MyMessageBox::Help),
      29, uint(MyMessageBox::Apply),
      30, uint(MyMessageBox::Reset),
      31, uint(MyMessageBox::RestoreDefaults),
      32, uint(MyMessageBox::FirstButton),
      33, uint(MyMessageBox::LastButton),

       0        // eod
};

void MyMessageBox::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MyMessageBox *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->slotPushButtonClicked((*reinterpret_cast< QAbstractButton*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAbstractButton* >(); break;
            }
            break;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MyMessageBox::staticMetaObject = { {
    &QDialog::staticMetaObject,
    qt_meta_stringdata_MyMessageBox.data,
    qt_meta_data_MyMessageBox,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MyMessageBox::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MyMessageBox::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MyMessageBox.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int MyMessageBox::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
