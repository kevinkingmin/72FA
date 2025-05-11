/****************************************************************************
** Meta object code from reading C++ file 'SampleWidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/sample/SampleWidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SampleWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_SampleWidget_t {
    QByteArrayData data[22];
    char stringdata0[392];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SampleWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SampleWidget_t qt_meta_stringdata_SampleWidget = {
    {
QT_MOC_LITERAL(0, 0, 12), // "SampleWidget"
QT_MOC_LITERAL(1, 13, 12), // "sglAlarmInfo"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 4), // "info"
QT_MOC_LITERAL(4, 32, 9), // "code_type"
QT_MOC_LITERAL(5, 42, 17), // "slotReFreshListUi"
QT_MOC_LITERAL(6, 60, 14), // "slotAlarmInfo1"
QT_MOC_LITERAL(7, 75, 10), // "alarm_info"
QT_MOC_LITERAL(8, 86, 17), // "on_btnPre_clicked"
QT_MOC_LITERAL(9, 104, 18), // "on_btnNext_clicked"
QT_MOC_LITERAL(10, 123, 20), // "on_btnCancel_clicked"
QT_MOC_LITERAL(11, 144, 20), // "on_btnReTest_clicked"
QT_MOC_LITERAL(12, 165, 22), // "on_changebtnNextEnable"
QT_MOC_LITERAL(13, 188, 12), // "enable_flage"
QT_MOC_LITERAL(14, 201, 22), // "on_changebtnSaveEnable"
QT_MOC_LITERAL(15, 224, 20), // "on_btnDelete_clicked"
QT_MOC_LITERAL(16, 245, 23), // "on_btnDeleteAll_clicked"
QT_MOC_LITERAL(17, 269, 21), // "on_btnSaveAdd_clicked"
QT_MOC_LITERAL(18, 291, 27), // "on_btnReQuestLisAll_clicked"
QT_MOC_LITERAL(19, 319, 24), // "on_btnRequestLis_clicked"
QT_MOC_LITERAL(20, 344, 24), // "on_btnIncubation_clicked"
QT_MOC_LITERAL(21, 369, 22) // "on_btnBatchAdd_clicked"

    },
    "SampleWidget\0sglAlarmInfo\0\0info\0"
    "code_type\0slotReFreshListUi\0slotAlarmInfo1\0"
    "alarm_info\0on_btnPre_clicked\0"
    "on_btnNext_clicked\0on_btnCancel_clicked\0"
    "on_btnReTest_clicked\0on_changebtnNextEnable\0"
    "enable_flage\0on_changebtnSaveEnable\0"
    "on_btnDelete_clicked\0on_btnDeleteAll_clicked\0"
    "on_btnSaveAdd_clicked\0on_btnReQuestLisAll_clicked\0"
    "on_btnRequestLis_clicked\0"
    "on_btnIncubation_clicked\0"
    "on_btnBatchAdd_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SampleWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   94,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   99,    2, 0x0a /* Public */,
       6,    2,  100,    2, 0x0a /* Public */,
       8,    0,  105,    2, 0x08 /* Private */,
       9,    0,  106,    2, 0x08 /* Private */,
      10,    0,  107,    2, 0x08 /* Private */,
      11,    0,  108,    2, 0x08 /* Private */,
      12,    1,  109,    2, 0x08 /* Private */,
      14,    1,  112,    2, 0x08 /* Private */,
      15,    0,  115,    2, 0x08 /* Private */,
      16,    0,  116,    2, 0x08 /* Private */,
      17,    0,  117,    2, 0x08 /* Private */,
      18,    0,  118,    2, 0x08 /* Private */,
      19,    0,  119,    2, 0x08 /* Private */,
      20,    0,  120,    2, 0x08 /* Private */,
      21,    0,  121,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    3,    4,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    7,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   13,
    QMetaType::Void, QMetaType::Bool,   13,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void SampleWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SampleWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sglAlarmInfo((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 1: _t->slotReFreshListUi(); break;
        case 2: _t->slotAlarmInfo1((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 3: _t->on_btnPre_clicked(); break;
        case 4: _t->on_btnNext_clicked(); break;
        case 5: _t->on_btnCancel_clicked(); break;
        case 6: _t->on_btnReTest_clicked(); break;
        case 7: _t->on_changebtnNextEnable((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 8: _t->on_changebtnSaveEnable((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 9: _t->on_btnDelete_clicked(); break;
        case 10: _t->on_btnDeleteAll_clicked(); break;
        case 11: _t->on_btnSaveAdd_clicked(); break;
        case 12: _t->on_btnReQuestLisAll_clicked(); break;
        case 13: _t->on_btnRequestLis_clicked(); break;
        case 14: _t->on_btnIncubation_clicked(); break;
        case 15: _t->on_btnBatchAdd_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (SampleWidget::*)(QString , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SampleWidget::sglAlarmInfo)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject SampleWidget::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_SampleWidget.data,
    qt_meta_data_SampleWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *SampleWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SampleWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SampleWidget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int SampleWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 16;
    }
    return _id;
}

// SIGNAL 0
void SampleWidget::sglAlarmInfo(QString _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
