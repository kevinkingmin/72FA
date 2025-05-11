#include "Encoder.h"
#include "ObjectInfo.h"
#include <QTime>
#include "src/cmd/Command.h"
#include "src/local_log.h"

Encoder::Encoder(EncoderAddress address, QObject *parent)
    :Component(parent)
    ,_address(address)
    ,_encoderValue(0)
{    
}

Encoder::~Encoder()
{
}

int Encoder::inquireParameter()
{
    Command cmd;
    if(cmd.generateInquireEncoderParameterCommand(_address)<0)
    {
        return -1;
    }
    setInquireResponseFlag(FLAG_BUSY);
    if(cmd.send()<0)
    {
        return -2;
    }
    return waitMachineAnswer();
}

int Encoder::inquireValue()
{
    Command cmd;
    if(cmd.generateInquireEncoderValueCommand(_address)<0)
    {
        return -1;
    }
    setInquireResponseFlag(FLAG_BUSY);
    if(cmd.send()<0)
    {
        return -2;
    }
    return waitMachineAnswer();
}

int Encoder::writeParasToEncoder(const uint para)
{
    Command cmd;
    if(cmd.generateEncoderParameterWriteActionCommand(_address,para)<0)
    {
        return -1;
    }
    setInquireResponseFlag(FLAG_BUSY);
    if(cmd.send()<0)
    {
        return -2;
    }

    return waitMachineAnswer();
}

Encoder::EncoderAddress Encoder::getAddress() const
{
    return _address;
}

int Encoder::getPrescale() const
{
    return _prescale;
}

void Encoder::setPrescale(int prescale)
{
    setInquireResponseFlag(FLAG_IDLE);
    _prescale = prescale;
}

int Encoder::getEncoderValue() const
{
    return _encoderValue;
}

void Encoder::setEncoderValue(int value)
{
    setInquireResponseFlag(FLAG_IDLE);
    _encoderValue = value;
}
