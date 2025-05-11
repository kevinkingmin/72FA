#include "Scaner.h"
#include "ObjectInfo.h"
#include <QTime>
#include "src/cmd/Command.h"
#include "src/local_log.h"
#include "../Include/Model/baseSet/InstrumentStateModel.h"

Scaner::Scaner(QObject *parent)
    :Component(parent)
    ,_readCode("")
    ,_checkCode("")
    ,_sampleBarcode("")
{    
}

Scaner::~Scaner()
{
}

int Scaner::scanerRead()
{
    Command cmd;
    if(cmd.generateScannerReadCommand()<0)
    {
        return -1;
    }
    if(InstrumentStateModel::instance()->getMachineState().state==InstrumentStateModel::enumError)
    {
        eLog("program stop");
        return -1;
    }
    setComResponseFlag(FLAG_BUSY);
    if(cmd.send()<0)
    {
        return -2;
    }
    if(waitCompoundCmdAnswer()<0)
        return -3;
    return 0;
}

int Scaner::scanerSelfCheck()
{
    Command cmd;
    if(cmd.generateScannerSelfCheckCommand()<0)
    {
        return -1;
    }
    if(InstrumentStateModel::instance()->getMachineState().state==InstrumentStateModel::enumError)
    {
        eLog("program stop");
        return -1;
    }
    setComResponseFlag(FLAG_BUSY);
    if(cmd.send()<0)
    {
        return -2;
    }
    if(waitCompoundCmdAnswer()<0)
        return -3;
    return 0;
}

int Scaner::scanSampleBarcode(const uchar pos)
{
    Command cmd;
    if(cmd.generateScanSampleCommand(pos)<0)
    {
        return -1;
    }
    if(InstrumentStateModel::instance()->getMachineState().state==InstrumentStateModel::enumError)
    {
        eLog("program stop");
        return -1;
    }
    setComResponseFlag(FLAG_BUSY);
    if(cmd.send()<0)
    {
        return -2;
    }
    if(waitCompoundCmdAnswer()<0)
        return -3;
    return 0;
}

QString Scaner::getReadCode() const
{
    QMutexLocker locker(&_dataLock);
    return _readCode;
}

void Scaner::setReadCode(const QString &readCode)
{
    setComResponseFlag(FLAG_IDLE);
    QMutexLocker locker(&_dataLock);    
    _readCode = readCode;
}

QString Scaner::getCheckCode() const
{
    QMutexLocker locker(&_dataLock);
    return _checkCode;
}

void Scaner::setCheckCode(const QString &checkCode)
{
	setComResponseFlag(FLAG_IDLE);
    QMutexLocker locker(&_dataLock);    
    _checkCode = checkCode;
}

QString Scaner::getSampleBarcode() const
{
    QMutexLocker locker(&_dataLock);
    return _sampleBarcode;
}

void Scaner::setSampleBarcode(const QString &sampleBarcode)
{
    setComResponseFlag(FLAG_IDLE);
    QMutexLocker locker(&_dataLock);
    _sampleBarcode = sampleBarcode;
}

