/****************************************************************************
** Meta object code from reading C++ file 'ReagentManager.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/utility/ReagentManager.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ReagentManager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ReagentManager_t {
    QByteArrayData data[15];
    char stringdata0[317];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ReagentManager_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ReagentManager_t qt_meta_stringdata_ReagentManager = {
    {
QT_MOC_LITERAL(0, 0, 14), // "ReagentManager"
QT_MOC_LITERAL(1, 15, 41), // "on_tableWidget_Company_curren..."
QT_MOC_LITERAL(2, 57, 0), // ""
QT_MOC_LITERAL(3, 58, 10), // "currentRow"
QT_MOC_LITERAL(4, 69, 13), // "currentColumn"
QT_MOC_LITERAL(5, 83, 11), // "previousRow"
QT_MOC_LITERAL(6, 95, 14), // "previousColumn"
QT_MOC_LITERAL(7, 110, 34), // "on_tableWidget_Company_cellCl..."
QT_MOC_LITERAL(8, 145, 34), // "on_tableWidget_Reagent_cellCl..."
QT_MOC_LITERAL(9, 180, 21), // "on_Add_Button_clicked"
QT_MOC_LITERAL(10, 202, 24), // "on_Modify_Button_clicked"
QT_MOC_LITERAL(11, 227, 24), // "on_Delete_Button_clicked"
QT_MOC_LITERAL(12, 252, 25), // "getRefreshTableWidgetFlag"
QT_MOC_LITERAL(13, 278, 5), // "bFlag"
QT_MOC_LITERAL(14, 284, 32) // "getRefreshCompanyTableWidgetFlag"

    },
    "ReagentManager\0on_tableWidget_Company_currentCellChanged\0"
    "\0currentRow\0currentColumn\0previousRow\0"
    "previousColumn\0on_tableWidget_Company_cellClicked\0"
    "on_tableWidget_Reagent_cellClicked\0"
    "on_Add_Button_clicked\0on_Modify_Button_clicked\0"
    "on_Delete_Button_clicked\0"
    "getRefreshTableWidgetFlag\0bFlag\0"
    "getRefreshCompanyTableWidgetFlag"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ReagentManager[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    4,   54,    2, 0x08 /* Private */,
       7,    0,   63,    2, 0x08 /* Private */,
       8,    0,   64,    2, 0x08 /* Private */,
       9,    0,   65,    2, 0x08 /* Private */,
      10,    0,   66,    2, 0x08 /* Private */,
      11,    0,   67,    2, 0x08 /* Private */,
      12,    1,   68,    2, 0x08 /* Private */,
      14,    1,   71,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int,    3,    4,    5,    6,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   13,
    QMetaType::Void, QMetaType::Bool,   13,

       0        // eod
};

void ReagentManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ReagentManager *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_tableWidget_Company_currentCellChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        case 1: _t->on_tableWidget_Company_cellClicked(); break;
        case 2: _t->on_tableWidget_Reagent_cellClicked(); break;
        case 3: _t->on_Add_Button_clicked(); break;
        case 4: _t->on_Modify_Button_clicked(); break;
        case 5: _t->on_Delete_Button_clicked(); break;
        case 6: _t->getRefreshTableWidgetFlag((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 7: _t->getRefreshCompanyTableWidgetFlag((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ReagentManager::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_ReagentManager.data,
    qt_meta_data_ReagentManager,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ReagentManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ReagentManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ReagentManager.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int ReagentManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
