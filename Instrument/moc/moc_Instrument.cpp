/****************************************************************************
** Meta object code from reading C++ file 'Instrument.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/Instrument.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Instrument.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Instrument_t {
    QByteArrayData data[66];
    char stringdata0[936];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Instrument_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Instrument_t qt_meta_stringdata_Instrument = {
    {
QT_MOC_LITERAL(0, 0, 10), // "Instrument"
QT_MOC_LITERAL(1, 11, 13), // "sglDataArrive"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 5), // "datas"
QT_MOC_LITERAL(4, 32, 14), // "sglScanReagent"
QT_MOC_LITERAL(5, 47, 14), // "sglLiquidState"
QT_MOC_LITERAL(6, 62, 5), // "state"
QT_MOC_LITERAL(7, 68, 24), // "sglCurrentGroupIdChanged"
QT_MOC_LITERAL(8, 93, 7), // "groupId"
QT_MOC_LITERAL(9, 101, 8), // "realTime"
QT_MOC_LITERAL(10, 110, 16), // "sglMaintainInfor"
QT_MOC_LITERAL(11, 127, 9), // "strResult"
QT_MOC_LITERAL(12, 137, 17), // "sglHandelStepName"
QT_MOC_LITERAL(13, 155, 8), // "stepName"
QT_MOC_LITERAL(14, 164, 19), // "sglHandleStepDetail"
QT_MOC_LITERAL(15, 184, 6), // "stepId"
QT_MOC_LITERAL(16, 191, 5), // "index"
QT_MOC_LITERAL(17, 197, 8), // "isSucess"
QT_MOC_LITERAL(18, 206, 16), // "sglMonthMaintain"
QT_MOC_LITERAL(19, 223, 6), // "result"
QT_MOC_LITERAL(20, 230, 22), // "sglPumpCalibrateResult"
QT_MOC_LITERAL(21, 253, 6), // "pumpNo"
QT_MOC_LITERAL(22, 260, 8), // "fstSteps"
QT_MOC_LITERAL(23, 269, 8), // "SndSteps"
QT_MOC_LITERAL(24, 278, 26), // "sglAutoPumpCalibrateResult"
QT_MOC_LITERAL(25, 305, 3), // "ret"
QT_MOC_LITERAL(26, 309, 12), // "sglAlarmInfo"
QT_MOC_LITERAL(27, 322, 8), // "warnCode"
QT_MOC_LITERAL(28, 331, 21), // "sglMinitorTemperature"
QT_MOC_LITERAL(29, 353, 11), // "temperature"
QT_MOC_LITERAL(30, 365, 21), // "sglMinitorSensorState"
QT_MOC_LITERAL(31, 387, 4), // "code"
QT_MOC_LITERAL(32, 392, 19), // "sglGetSampleBatchNo"
QT_MOC_LITERAL(33, 412, 3), // "pos"
QT_MOC_LITERAL(34, 416, 7), // "batchNo"
QT_MOC_LITERAL(35, 424, 15), // "sglMaintainStep"
QT_MOC_LITERAL(36, 440, 3), // "des"
QT_MOC_LITERAL(37, 444, 12), // "sglIsStepSuc"
QT_MOC_LITERAL(38, 457, 14), // "sglPopUpWindow"
QT_MOC_LITERAL(39, 472, 9), // "windowDes"
QT_MOC_LITERAL(40, 482, 19), // "onSocketDataReceive"
QT_MOC_LITERAL(41, 502, 5), // "bytes"
QT_MOC_LITERAL(42, 508, 18), // "sglSelfCheckResult"
QT_MOC_LITERAL(43, 527, 23), // "sglGetMachineCodeResult"
QT_MOC_LITERAL(44, 551, 21), // "sglMonthMaintenResult"
QT_MOC_LITERAL(45, 573, 24), // "sglShutdownMaintenResult"
QT_MOC_LITERAL(46, 598, 20), // "sglWeekMaintenResult"
QT_MOC_LITERAL(47, 619, 22), // "sglSystemPipWashResult"
QT_MOC_LITERAL(48, 642, 16), // "sglPipWashResult"
QT_MOC_LITERAL(49, 659, 20), // "sglPipFlowbackResult"
QT_MOC_LITERAL(50, 680, 23), // "sglDetectionStartResult"
QT_MOC_LITERAL(51, 704, 11), // "messageType"
QT_MOC_LITERAL(52, 716, 6), // "sample"
QT_MOC_LITERAL(53, 723, 4), // "slot"
QT_MOC_LITERAL(54, 728, 4), // "step"
QT_MOC_LITERAL(55, 733, 4), // "time"
QT_MOC_LITERAL(56, 738, 23), // "sglDetectionPauseResult"
QT_MOC_LITERAL(57, 762, 26), // "sglDetectionContinueResult"
QT_MOC_LITERAL(58, 789, 22), // "sglDetectionStopResult"
QT_MOC_LITERAL(59, 812, 23), // "sglPrepareReagentResult"
QT_MOC_LITERAL(60, 836, 16), // "sglOnTemperature"
QT_MOC_LITERAL(61, 853, 23), // "sglScanSampleCodeResult"
QT_MOC_LITERAL(62, 877, 10), // "resultData"
QT_MOC_LITERAL(63, 888, 14), // "connected_SLOT"
QT_MOC_LITERAL(64, 903, 17), // "disconnected_SLOT"
QT_MOC_LITERAL(65, 921, 14) // "readyRead_Slot"

    },
    "Instrument\0sglDataArrive\0\0datas\0"
    "sglScanReagent\0sglLiquidState\0state\0"
    "sglCurrentGroupIdChanged\0groupId\0"
    "realTime\0sglMaintainInfor\0strResult\0"
    "sglHandelStepName\0stepName\0"
    "sglHandleStepDetail\0stepId\0index\0"
    "isSucess\0sglMonthMaintain\0result\0"
    "sglPumpCalibrateResult\0pumpNo\0fstSteps\0"
    "SndSteps\0sglAutoPumpCalibrateResult\0"
    "ret\0sglAlarmInfo\0warnCode\0"
    "sglMinitorTemperature\0temperature\0"
    "sglMinitorSensorState\0code\0"
    "sglGetSampleBatchNo\0pos\0batchNo\0"
    "sglMaintainStep\0des\0sglIsStepSuc\0"
    "sglPopUpWindow\0windowDes\0onSocketDataReceive\0"
    "bytes\0sglSelfCheckResult\0"
    "sglGetMachineCodeResult\0sglMonthMaintenResult\0"
    "sglShutdownMaintenResult\0sglWeekMaintenResult\0"
    "sglSystemPipWashResult\0sglPipWashResult\0"
    "sglPipFlowbackResult\0sglDetectionStartResult\0"
    "messageType\0sample\0slot\0step\0time\0"
    "sglDetectionPauseResult\0"
    "sglDetectionContinueResult\0"
    "sglDetectionStopResult\0sglPrepareReagentResult\0"
    "sglOnTemperature\0sglScanSampleCodeResult\0"
    "resultData\0connected_SLOT\0disconnected_SLOT\0"
    "readyRead_Slot"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Instrument[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      36,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      33,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,  194,    2, 0x06 /* Public */,
       4,    0,  197,    2, 0x06 /* Public */,
       5,    1,  198,    2, 0x06 /* Public */,
       7,    2,  201,    2, 0x06 /* Public */,
      10,    1,  206,    2, 0x06 /* Public */,
      12,    1,  209,    2, 0x06 /* Public */,
      14,    4,  212,    2, 0x06 /* Public */,
      18,    1,  221,    2, 0x06 /* Public */,
      20,    3,  224,    2, 0x06 /* Public */,
      24,    4,  231,    2, 0x06 /* Public */,
      26,    1,  240,    2, 0x06 /* Public */,
      28,    1,  243,    2, 0x06 /* Public */,
      30,    2,  246,    2, 0x06 /* Public */,
      32,    2,  251,    2, 0x06 /* Public */,
      35,    2,  256,    2, 0x06 /* Public */,
      37,    1,  261,    2, 0x06 /* Public */,
      38,    1,  264,    2, 0x06 /* Public */,
      40,    1,  267,    2, 0x06 /* Public */,
      42,    1,  270,    2, 0x06 /* Public */,
      43,    1,  273,    2, 0x06 /* Public */,
      44,    1,  276,    2, 0x06 /* Public */,
      45,    1,  279,    2, 0x06 /* Public */,
      46,    1,  282,    2, 0x06 /* Public */,
      47,    1,  285,    2, 0x06 /* Public */,
      48,    1,  288,    2, 0x06 /* Public */,
      49,    1,  291,    2, 0x06 /* Public */,
      50,    6,  294,    2, 0x06 /* Public */,
      56,    1,  307,    2, 0x06 /* Public */,
      57,    1,  310,    2, 0x06 /* Public */,
      58,    1,  313,    2, 0x06 /* Public */,
      59,    1,  316,    2, 0x06 /* Public */,
      60,    1,  319,    2, 0x06 /* Public */,
      61,    1,  322,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      63,    0,  325,    2, 0x08 /* Private */,
      64,    0,  326,    2, 0x08 /* Private */,
      65,    0,  327,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QByteArray,    3,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    8,    9,
    QMetaType::Void, QMetaType::QString,   11,
    QMetaType::Void, QMetaType::QString,   13,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Bool, QMetaType::QString,   15,   16,   17,   13,
    QMetaType::Void, QMetaType::Int,   19,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,   21,   22,   23,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int,   25,   21,   22,   23,
    QMetaType::Void, QMetaType::Int,   27,
    QMetaType::Void, QMetaType::Float,   29,
    QMetaType::Void, QMetaType::UShort, QMetaType::Bool,   31,   17,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,   33,   34,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,   16,   36,
    QMetaType::Void, QMetaType::Int,   25,
    QMetaType::Void, QMetaType::QString,   39,
    QMetaType::Void, QMetaType::QByteArray,   41,
    QMetaType::Void, QMetaType::QString,   31,
    QMetaType::Void, QMetaType::QString,   31,
    QMetaType::Void, QMetaType::QString,   31,
    QMetaType::Void, QMetaType::QString,   31,
    QMetaType::Void, QMetaType::QString,   31,
    QMetaType::Void, QMetaType::QString,   31,
    QMetaType::Void, QMetaType::QString,   31,
    QMetaType::Void, QMetaType::QString,   31,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString,   51,   52,   53,   54,   31,   55,
    QMetaType::Void, QMetaType::QString,   31,
    QMetaType::Void, QMetaType::QString,   31,
    QMetaType::Void, QMetaType::QString,   31,
    QMetaType::Void, QMetaType::QString,   31,
    QMetaType::Void, QMetaType::Float,   31,
    QMetaType::Void, QMetaType::QByteArray,   62,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Instrument::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Instrument *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sglDataArrive((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 1: _t->sglScanReagent(); break;
        case 2: _t->sglLiquidState((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->sglCurrentGroupIdChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 4: _t->sglMaintainInfor((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: _t->sglHandelStepName((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 6: _t->sglHandleStepDetail((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3])),(*reinterpret_cast< const QString(*)>(_a[4]))); break;
        case 7: _t->sglMonthMaintain((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->sglPumpCalibrateResult((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 9: _t->sglAutoPumpCalibrateResult((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        case 10: _t->sglAlarmInfo((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: _t->sglMinitorTemperature((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 12: _t->sglMinitorSensorState((*reinterpret_cast< ushort(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 13: _t->sglGetSampleBatchNo((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 14: _t->sglMaintainStep((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 15: _t->sglIsStepSuc((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 16: _t->sglPopUpWindow((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 17: _t->onSocketDataReceive((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 18: _t->sglSelfCheckResult((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 19: _t->sglGetMachineCodeResult((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 20: _t->sglMonthMaintenResult((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 21: _t->sglShutdownMaintenResult((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 22: _t->sglWeekMaintenResult((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 23: _t->sglSystemPipWashResult((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 24: _t->sglPipWashResult((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 25: _t->sglPipFlowbackResult((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 26: _t->sglDetectionStartResult((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4])),(*reinterpret_cast< QString(*)>(_a[5])),(*reinterpret_cast< QString(*)>(_a[6]))); break;
        case 27: _t->sglDetectionPauseResult((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 28: _t->sglDetectionContinueResult((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 29: _t->sglDetectionStopResult((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 30: _t->sglPrepareReagentResult((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 31: _t->sglOnTemperature((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 32: _t->sglScanSampleCodeResult((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 33: _t->connected_SLOT(); break;
        case 34: _t->disconnected_SLOT(); break;
        case 35: _t->readyRead_Slot(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Instrument::*)(QByteArray );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Instrument::sglDataArrive)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Instrument::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Instrument::sglScanReagent)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (Instrument::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Instrument::sglLiquidState)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (Instrument::*)(int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Instrument::sglCurrentGroupIdChanged)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (Instrument::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Instrument::sglMaintainInfor)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (Instrument::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Instrument::sglHandelStepName)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (Instrument::*)(int , int , bool , const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Instrument::sglHandleStepDetail)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (Instrument::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Instrument::sglMonthMaintain)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (Instrument::*)(int , int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Instrument::sglPumpCalibrateResult)) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (Instrument::*)(int , int , int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Instrument::sglAutoPumpCalibrateResult)) {
                *result = 9;
                return;
            }
        }
        {
            using _t = void (Instrument::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Instrument::sglAlarmInfo)) {
                *result = 10;
                return;
            }
        }
        {
            using _t = void (Instrument::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Instrument::sglMinitorTemperature)) {
                *result = 11;
                return;
            }
        }
        {
            using _t = void (Instrument::*)(ushort , bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Instrument::sglMinitorSensorState)) {
                *result = 12;
                return;
            }
        }
        {
            using _t = void (Instrument::*)(int , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Instrument::sglGetSampleBatchNo)) {
                *result = 13;
                return;
            }
        }
        {
            using _t = void (Instrument::*)(int , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Instrument::sglMaintainStep)) {
                *result = 14;
                return;
            }
        }
        {
            using _t = void (Instrument::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Instrument::sglIsStepSuc)) {
                *result = 15;
                return;
            }
        }
        {
            using _t = void (Instrument::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Instrument::sglPopUpWindow)) {
                *result = 16;
                return;
            }
        }
        {
            using _t = void (Instrument::*)(QByteArray );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Instrument::onSocketDataReceive)) {
                *result = 17;
                return;
            }
        }
        {
            using _t = void (Instrument::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Instrument::sglSelfCheckResult)) {
                *result = 18;
                return;
            }
        }
        {
            using _t = void (Instrument::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Instrument::sglGetMachineCodeResult)) {
                *result = 19;
                return;
            }
        }
        {
            using _t = void (Instrument::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Instrument::sglMonthMaintenResult)) {
                *result = 20;
                return;
            }
        }
        {
            using _t = void (Instrument::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Instrument::sglShutdownMaintenResult)) {
                *result = 21;
                return;
            }
        }
        {
            using _t = void (Instrument::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Instrument::sglWeekMaintenResult)) {
                *result = 22;
                return;
            }
        }
        {
            using _t = void (Instrument::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Instrument::sglSystemPipWashResult)) {
                *result = 23;
                return;
            }
        }
        {
            using _t = void (Instrument::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Instrument::sglPipWashResult)) {
                *result = 24;
                return;
            }
        }
        {
            using _t = void (Instrument::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Instrument::sglPipFlowbackResult)) {
                *result = 25;
                return;
            }
        }
        {
            using _t = void (Instrument::*)(QString , QString , QString , QString , QString , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Instrument::sglDetectionStartResult)) {
                *result = 26;
                return;
            }
        }
        {
            using _t = void (Instrument::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Instrument::sglDetectionPauseResult)) {
                *result = 27;
                return;
            }
        }
        {
            using _t = void (Instrument::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Instrument::sglDetectionContinueResult)) {
                *result = 28;
                return;
            }
        }
        {
            using _t = void (Instrument::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Instrument::sglDetectionStopResult)) {
                *result = 29;
                return;
            }
        }
        {
            using _t = void (Instrument::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Instrument::sglPrepareReagentResult)) {
                *result = 30;
                return;
            }
        }
        {
            using _t = void (Instrument::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Instrument::sglOnTemperature)) {
                *result = 31;
                return;
            }
        }
        {
            using _t = void (Instrument::*)(QByteArray );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Instrument::sglScanSampleCodeResult)) {
                *result = 32;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Instrument::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_Instrument.data,
    qt_meta_data_Instrument,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Instrument::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Instrument::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Instrument.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Instrument::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 36)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 36;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 36)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 36;
    }
    return _id;
}

// SIGNAL 0
void Instrument::sglDataArrive(QByteArray _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Instrument::sglScanReagent()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void Instrument::sglLiquidState(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void Instrument::sglCurrentGroupIdChanged(int _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void Instrument::sglMaintainInfor(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void Instrument::sglHandelStepName(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void Instrument::sglHandleStepDetail(int _t1, int _t2, bool _t3, const QString & _t4)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void Instrument::sglMonthMaintain(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void Instrument::sglPumpCalibrateResult(int _t1, int _t2, int _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void Instrument::sglAutoPumpCalibrateResult(int _t1, int _t2, int _t3, int _t4)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void Instrument::sglAlarmInfo(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}

// SIGNAL 11
void Instrument::sglMinitorTemperature(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 11, _a);
}

// SIGNAL 12
void Instrument::sglMinitorSensorState(ushort _t1, bool _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 12, _a);
}

// SIGNAL 13
void Instrument::sglGetSampleBatchNo(int _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 13, _a);
}

// SIGNAL 14
void Instrument::sglMaintainStep(int _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 14, _a);
}

// SIGNAL 15
void Instrument::sglIsStepSuc(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 15, _a);
}

// SIGNAL 16
void Instrument::sglPopUpWindow(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 16, _a);
}

// SIGNAL 17
void Instrument::onSocketDataReceive(QByteArray _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 17, _a);
}

// SIGNAL 18
void Instrument::sglSelfCheckResult(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 18, _a);
}

// SIGNAL 19
void Instrument::sglGetMachineCodeResult(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 19, _a);
}

// SIGNAL 20
void Instrument::sglMonthMaintenResult(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 20, _a);
}

// SIGNAL 21
void Instrument::sglShutdownMaintenResult(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 21, _a);
}

// SIGNAL 22
void Instrument::sglWeekMaintenResult(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 22, _a);
}

// SIGNAL 23
void Instrument::sglSystemPipWashResult(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 23, _a);
}

// SIGNAL 24
void Instrument::sglPipWashResult(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 24, _a);
}

// SIGNAL 25
void Instrument::sglPipFlowbackResult(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 25, _a);
}

// SIGNAL 26
void Instrument::sglDetectionStartResult(QString _t1, QString _t2, QString _t3, QString _t4, QString _t5, QString _t6)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)), const_cast<void*>(reinterpret_cast<const void*>(&_t5)), const_cast<void*>(reinterpret_cast<const void*>(&_t6)) };
    QMetaObject::activate(this, &staticMetaObject, 26, _a);
}

// SIGNAL 27
void Instrument::sglDetectionPauseResult(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 27, _a);
}

// SIGNAL 28
void Instrument::sglDetectionContinueResult(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 28, _a);
}

// SIGNAL 29
void Instrument::sglDetectionStopResult(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 29, _a);
}

// SIGNAL 30
void Instrument::sglPrepareReagentResult(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 30, _a);
}

// SIGNAL 31
void Instrument::sglOnTemperature(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 31, _a);
}

// SIGNAL 32
void Instrument::sglScanSampleCodeResult(QByteArray _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 32, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
