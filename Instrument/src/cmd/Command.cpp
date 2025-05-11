#include "Command.h"
#include <QString>
#include <QByteArray>
#include "src/local_log.h"
#include "../Include/SerialPortDriver/SerialPortDriver.h"
#include "../Include/Model/baseSet/InstrumentStateModel.h"
#include "../Include/Utilities/async_task.h"
#include <QCoreApplication>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QCryptographicHash>
Command::Command() :
    _size(0)
  , _command(nullptr)
  , _port(SerialPortDriver::instance())
{}

Command::Command(const unsigned char *command, const unsigned int size) :
    _size(0)
  , _command(nullptr)
{
    if ((nullptr != command) && (size > 0))
    {
        _command = new unsigned char[size];
        if (nullptr != _command)
        {
            _size = size;
            memcpy(_command, command, size * sizeof(unsigned char));
        }
    }
}

Command::Command(QByteArray command)
    :_size(0)
    , _command(nullptr)
{
    if (nullptr == command || command.size() <= 0)
    {
        return;
    }
    _size = static_cast<uint>(command.size());
    _command = new unsigned char[_size];
    memcpy(_command, command, _size * sizeof(unsigned char));
}

Command::~Command()
{
    if (_command != nullptr)
    {
        delete[] _command;
    }
}

int Command::calculateParityBit(
        const unsigned char *command,
        const unsigned int length,
        unsigned char &parityBit)
{
    if ((nullptr == command) || (0 == length))
        return(-1);

    unsigned int sum = 0;
    for (unsigned int index = 0; index < length; ++index) {
        sum += command[index];
    }
    parityBit = static_cast<unsigned char>(sum);
    return 0;
}

int Command::send(const QString &name) const
{
    if (isValid() < 0)
        return -1;
    if (requestCommand == nullptr||requestCommand.size()!=1024)
        return(-2);
    Instrument::instance()->sendBySocket(requestCommand);
    return 0;
}

int Command::isValid() const
{
    if ((nullptr == _command) || (0 == _size))
        return(-1);

    if (_size < MIN_LENGTH)
        return(-2);

    if (Command::START_BIT != _command[0])
        return(-3);

    if (_command[2] != static_cast<unsigned char>(_size - 5))
        return(-4);

    if (Command::END_BIT != _command[_size - 1])
        return(-5);

    unsigned char parityBit = 0;
    if (calculateParityBit(_command, _size - 2, parityBit) < 0)
    {
        return(-6);
    }
    if (_command[_size - 2] != parityBit)
    {
        return(-7);
    }
    return(0);
}

void Command::uintToChar(unsigned char *cmd, uint para, int index)
{
    cmd[index] = static_cast<unsigned char>((para >> 24) & 0xFF);
    cmd[++index] = static_cast<unsigned char>((para >> 16) & 0xFF);
    cmd[++index] = static_cast<unsigned char>((para >> 8) & 0xFF);
    cmd[++index] = static_cast<unsigned char>(para & 0xFF);
}

void Command::intToChar(unsigned char *cmd, int para, int index)
{
    cmd[index] = static_cast<unsigned char>((para >> 24) & 0xFF);
    cmd[++index] = static_cast<unsigned char>((para >> 16) & 0xFF);
    cmd[++index] = static_cast<unsigned char>((para >> 8) & 0xFF);
    cmd[++index] = static_cast<unsigned char>(para & 0xFF);
}

void Command::ushortToChar(unsigned char *cmd, ushort para, int index)
{
    cmd[index] = static_cast<unsigned char>((para >> 8) & 0xFF);
    cmd[++index] = static_cast<unsigned char>(para & 0xFF);
}

int Command::generateInitializeMotorCommand(const unsigned char motorNo)
{
    const uint size = 10;
    unsigned char *command = new unsigned char[size];
    command[0] = START_BIT;
    command[1] = 0x25;
    command[2] = 0x05;
    command[3] = 0x00;
    command[4] = 0x00;
    command[5] = 0x10;
    command[6] = 0x01;
    command[7] = motorNo;
    if (calculateParityBit(command, size - 2, command[8]) < 0) {
        delete[] command;
        return -1;
    }
    command[9] = END_BIT;
    if (nullptr != _command) {
        delete[] _command;
    }
    _command = command;
    _size = size;
    return 0;
}

int Command::generateSpecimenArmSuckCommand(
        const ushort suckVolume,
        const bool sensor,
        const unsigned char cupType,
        const unsigned char suckPos)
{
    const uint size = 14;
    unsigned char *command = new unsigned char[size];
    command[0] = START_BIT;
    command[1] = 0x25;
    command[2] = 0x09;
    command[3] = 0x00;
    command[4] = 0x00;
    command[5] = 0x10;
    command[6] = 0x02;
    ushortToChar(command,suckVolume,7);
    command[9]=sensor?1:0;
    command[10]=cupType;
    command[11]=suckPos;
    if (calculateParityBit(command, size - 2, command[12]) < 0) {
        delete[] command;
        return -1;
    }
    command[13] = END_BIT;
    if (nullptr != _command) {
        delete[] _command;
    }
    _command = command;
    _size = size;
    return 0;
}

int Command::generateSpecimenArmWashCommand(const ushort outerWashTime,
                                            const ushort innerWashTime,
                                            const ushort pumpWasteLiquidTime)
{
    const uint size = 15;
    unsigned char *command = new unsigned char[size];
    command[0] = START_BIT;
    command[1] = 0x25;
    command[2] = 0x0A;
    command[3] = 0x00;
    command[4] = 0x00;
    command[5] = 0x10;
    command[6] = 0x03;
    ushortToChar(command,outerWashTime,7);
    ushortToChar(command,innerWashTime,9);
    ushortToChar(command,pumpWasteLiquidTime,11);
    if (calculateParityBit(command, size - 2, command[13]) < 0) {
        delete[] command;
        return -1;
    }
    command[14] = END_BIT;
    if (nullptr != _command) {
        delete[] _command;
    }
    _command = command;
    _size = size;
    return 0;
}
//样本臂吐液
int Command::generateSpecimenArmSpitCommand(const ushort spitVolume,
                                            const bool sensor,
                                            const unsigned char spitPos)
{
    const uint size = 13;
    unsigned char *command = new unsigned char[size];
    command[0] = START_BIT;
    command[1] = 0x25;
    command[2] = 0x08;
    command[3] = 0x00;
    command[4] = 0x00;
    command[5] = 0x10;
    command[6] = 0x04;
    ushortToChar(command,spitVolume,7);
    command[9]=sensor?1:0;
    command[10]=spitPos;
    if (calculateParityBit(command, size - 2, command[11]) < 0) {
        delete[] command;
        return -1;
    }
    command[12] = END_BIT;
    if (nullptr != _command) {
        delete[] _command;
    }
    _command = command;
    _size = size;
    return 0;
}

int Command::generateScannerReadCommand()
{
    const uint size = 9;
    unsigned char *command = new unsigned char[size];
    command[0] = START_BIT;
    command[1] = 0x25;
    command[2] = 0x04;
    command[3] = 0x00;
    command[4] = 0x00;
    command[5] = 0x10;
    command[6] = 0x05;

    if (calculateParityBit(command, size - 2, command[7]) < 0) {
        delete[] command;
        return -1;
    }
    command[8] = END_BIT;
    if (nullptr != _command) {
        delete[] _command;
    }
    _command = command;
    _size = size;
    return 0;
}

int Command::generateScanSampleCommand(const unsigned char samplePos)
{
    const uint size = 10;
    unsigned char *command = new unsigned char[size];
    command[0] = START_BIT;
    command[1] = 0x25;
    command[2] = 0x05;
    command[3] = 0x00;
    command[4] = 0x00;
    command[5] = 0x10;
    command[6] = 0x06;
    command[7] = samplePos;
    if (calculateParityBit(command, size - 2, command[8]) < 0) {
        delete[] command;
        return -1;
    }
    command[9] = END_BIT;
    if (nullptr != _command) {
        delete[] _command;
    }
    _command = command;
    _size = size;
    return 0;
}

int Command::generateCalibrateCameraCommand()
{
    const uint size = 9;
    unsigned char *command = new unsigned char[size];
    command[0] = START_BIT;
    command[1] = 0x25;
    command[2] = 0x04;
    command[3] = 0x00;
    command[4] = 0x00;
    command[5] = 0x10;
    command[6] = 0x07;
    if (calculateParityBit(command, size - 2, command[7]) < 0) {
        delete[] command;
        return -1;
    }
    command[8] = END_BIT;
    if (nullptr != _command) {
        delete[] _command;
    }
    _command = command;
    _size = size;
    return 0;
}

//吸废液  spitPos为位置
int Command::generateDischargeWasteAndPeristalticPumpSpitLiquidCommand(const uchar reactNO,
                                                                       const unsigned char spitPos,
                                                                       const ushort dischargeTime,
                                                                       const unsigned char liquidType,
                                                                       const ushort volume)
{
    const uint size = 0x0B+5;
    unsigned char *command = new unsigned char[size];
    command[0] = START_BIT;
    command[1] = 0x25;
    command[2] = 0x0B;
    command[3] = 0x00;
    command[4] = 0x00;
    command[5] = 0x10;
    command[6] = 0x08;
    command[7] = reactNO;
    command[8] = spitPos;
    ushortToChar(command,dischargeTime,9);
    command[11]=liquidType;
    ushortToChar(command,volume,12);

    if (calculateParityBit(command, size - 2, command[14]) < 0) {
        delete[] command;
        return -1;
    }
    command[15] = END_BIT;
    if (nullptr != _command) {
        delete[] _command;
    }
    _command = command;
    _size = size;
    return 0;
}
//回流
int Command::generatePeristalticPumpBackFlowCommand(const unsigned char backFlowType, const ushort backFlowVolume)
{
    const uint size = 12;
    unsigned char *command = new unsigned char[size];
    command[0] = START_BIT;
    command[1] = 0x25;
    command[2] = 0x07;
    command[3] = 0x00;
    command[4] = 0x00;
    command[5] = 0x10;
    command[6] = 0x09;
    command[7] = backFlowType;
    ushortToChar(command,backFlowVolume,8);
    if (calculateParityBit(command, size - 2, command[10]) < 0) {
        delete[] command;
        return -1;
    }
    command[11] = END_BIT;
    if (nullptr != _command) {
        delete[] _command;
    }
    _command = command;
    _size = size;
    return 0;
}
//充灌
int Command::generatePeristalticPumpFillLiquidCommand(const unsigned char fillType, const ushort volume)
{
    const uint size = 12;
    unsigned char *command = new unsigned char[size];
    command[0] = START_BIT;
    command[1] = 0x25;
    command[2] = 0x07;
    command[3] = 0x00;
    command[4] = 0x00;
    command[5] = 0x10;
    command[6] = 0x10;
    command[7] = fillType;
    ushortToChar(command,volume,8);
    if (calculateParityBit(command, size - 2, command[10]) < 0) {
        delete[] command;
        return -1;
    }
    command[11] = END_BIT;
    if (nullptr != _command) {
        delete[] _command;
    }
    _command = command;
    _size = size;
    return 0;
}

int Command::generateShakingBedWorkingCommand(const unsigned char workType)
{
    const uint size = 10;
    unsigned char *command = new unsigned char[size];
    command[0] = START_BIT;
    command[1] = 0x25;
    command[2] = 0x05;
    command[3] = 0x00;
    command[4] = 0x00;
    command[5] = 0x10;
    command[6] = 0x11;
    command[7] = workType;
    if (calculateParityBit(command, size - 2, command[8]) < 0) {
        delete[] command;
        return -1;
    }
    command[9] = END_BIT;
    if (nullptr != _command) {
        delete[] _command;
    }
    _command = command;
    _size = size;
    return 0;
}
//风扇控制
int Command::generateFanControlCommand(const unsigned char runType, const unsigned char pos)
{
    const uint size = 0x06+5;
    unsigned char *command = new unsigned char[size];
    command[0] = START_BIT;
    command[1] = 0x25;
    command[2] = 0x06;
    command[3] = 0x00;
    command[4] = 0x00;
    command[5] = 0x10;
    command[6] = 0x12;
    command[7] = runType;
    command[8] = pos;
    if (calculateParityBit(command, size - 2, command[9]) < 0) {
        delete[] command;
        return -1;
    }
    command[10] = END_BIT;
    if (nullptr != _command) {
        delete[] _command;
    }
    _command = command;
    _size = size;
    return 0;
}

int Command::generateScannerSelfCheckCommand()
{
    const uint size = 9;
    unsigned char *command = new unsigned char[size];
    command[0] = START_BIT;
    command[1] = 0x25;
    command[2] = 0x04;
    command[3] = 0x00;
    command[4] = 0x00;
    command[5] = 0x10;
    command[6] = 0x13;
    if (calculateParityBit(command, size - 2, command[7]) < 0) {
        delete[] command;
        return -1;
    }
    command[8] = END_BIT;
    if (nullptr != _command) {
        delete[] _command;
    }
    _command = command;
    _size = size;
    return 0;
}
//蠕动泵加液
int Command::generateCalibratePeristalticPumpCommand(const unsigned char pumpNo, const ushort volume)
{
    const uint size = 12;
    unsigned char *command = new unsigned char[size];
    command[0] = START_BIT;
    command[1] = 0x25;
    command[2] = 0x07;
    command[3] = 0x00;
    command[4] = 0x00;
    command[5] = 0x10;
    command[6] = 0x14;
    command[7] = pumpNo;
    ushortToChar(command,volume,8);
    if (calculateParityBit(command, size - 2, command[10]) < 0) {
        delete[] command;
        return -1;
    }
    command[11] = END_BIT;
    if (nullptr != _command) {
        delete[] _command;
    }
    _command = command;
    _size = size;
    return 0;
}

int Command::generatePhotographCommand(const unsigned char pos)
{
    const uint size = 10;
    unsigned char *command = new unsigned char[size];
    command[0] = START_BIT;
    command[1] = 0x25;
    command[2] = 0x05;
    command[3] = 0x00;
    command[4] = 0x00;
    command[5] = 0x10;
    command[6] = 0x15;
    command[7] = pos;
    if (calculateParityBit(command, size - 2, command[8]) < 0) {
        delete[] command;
        return -1;
    }
    command[9] = END_BIT;
    if (nullptr != _command) {
        delete[] _command;
    }
    _command = command;
    _size = size;
    return 0;
}

int Command::generateIrrigationSystemLiquidCommand(const ushort volumn)
{
    const uint size = 0x06+5;
    unsigned char *command = new unsigned char[size];
    command[0] = START_BIT;
    command[1] = 0x25;
    command[2] = 0x06;
    command[3] = 0x00;
    command[4] = 0x00;
    command[5] = 0x10;
    command[6] = 0x16;
    ushortToChar(command,volumn,7);
    if (calculateParityBit(command, size - 2, command[9]) < 0) {
        delete[] command;
        return -1;
    }
    command[10] = END_BIT;
    if (nullptr != _command) {
        delete[] _command;
    }
    _command = command;
    _size = size;
    return 0;
}

int Command::generateWashSystemLiquidWayCommand(const ushort volumn)
{
    const uint size = 0x06+5;
    unsigned char *command = new unsigned char[size];
    command[0] = START_BIT;
    command[1] = 0x25;
    command[2] = 0x06;
    command[3] = 0x00;
    command[4] = 0x00;
    command[5] = 0x10;
    command[6] = 0x17;
    ushortToChar(command,volumn,7);
    if (calculateParityBit(command, size - 2, command[9]) < 0) {
        delete[] command;
        return -1;
    }
    command[10] = END_BIT;
    if (nullptr != _command) {
        delete[] _command;
    }
    _command = command;
    _size = size;
    return 0;
}

int Command::generateIndicatorLightOnOffCommand(const unsigned char lightNo, const unsigned char onOffState)
{
    const uint size = 11;
    unsigned char *command = new unsigned char[size];
    command[0] = START_BIT;
    command[1] = 0x25;
    command[2] = 0x06;
    command[3] = 0x00;
    command[4] = 0x00;
    command[5] = 0x10;
    command[6] = 0x18;
    command[7] = lightNo;
    command[8] = onOffState;
    if (calculateParityBit(command, size - 2, command[9]) < 0) {
        delete[] command;
        return -1;
    }
    command[10] = END_BIT;
    if (nullptr != _command) {
        delete[] _command;
    }
    _command = command;
    _size = size;
    return 0;
}

int Command::generateBuzzleOnOffCommand(const unsigned char on_off_state)
{
    const uint size = 10;
    unsigned char *command = new unsigned char[size];
    command[0] = START_BIT;
    command[1] = 0x25;
    command[2] = 0x05;
    command[3] = 0x00;
    command[4] = 0x00;
    command[5] = 0x10;
    command[6] = 0x19;
    command[7] = on_off_state;
    if (calculateParityBit(command, size - 2, command[8]) < 0) {
        delete[] command;
        return -1;
    }
    command[9] = END_BIT;
    if (nullptr != _command) {
        delete[] _command;
    }
    _command = command;
    _size = size;
    return 0;
}

int Command::generateSpecimenArmSuckAndSplitCommand(const ushort suckVolume,
                                                    const uchar sensor,
                                                    const unsigned char cupType,
                                                    const unsigned char suckPos,
                                                    const unsigned char spitPos)
{
    const uint size = 15;
    unsigned char *command = new unsigned char[size];
    command[0] = START_BIT;
    command[1] = 0x25;
    command[2] = 0x0A;
    command[3] = 0x00;
    command[4] = 0x00;
    command[5] = 0x10;
    command[6] = 0x20;
    ushortToChar(command,suckVolume,7);
    command[9] = sensor;
    command[10]=cupType;
    command[11]=suckPos;
    command[12]=spitPos;
    if (calculateParityBit(command, size - 2, command[13]) < 0) {
        delete[] command;
        return -1;
    }
    command[14] = END_BIT;
    if (nullptr != _command) {
        delete[] _command;
    }
    _command = command;
    _size = size;
    return 0;
}

int Command::generateSynchronizedActionCommand()
{
    const uint size = 10;
    unsigned char *command = new unsigned char[size];
    command[0] = START_BIT;
    command[1] = 0x1D;
    command[2] = 0x04;
    command[3] = 0x00;
    command[4] = 0x00;
    command[5] = 0x30;
    command[6] = 0x01;
    if (calculateParityBit(command, size - 2, command[7]) < 0) {
        delete[] command;
        return -1;
    }
    command[8] = END_BIT;
    if (nullptr != _command) {
        delete[] _command;
    }
    _command = command;
    _size = size;
    return 0;
}

int Command::generateMachineNoWriteActionCommand(const uint machineNo)
{
    const uint size = 13;
    unsigned char *command = new unsigned char[size];
    command[0] = START_BIT;
    command[1] = 0x1D;
    command[2] = 0x08;
    command[3] = 0x00;
    command[4] = 0x00;
    command[5] = 0x30;
    command[6] = 0x02;
    uintToChar(command, machineNo, 7);
    if (calculateParityBit(command, size - 2, command[11]) < 0) {
        delete[] command;
        return -1;
    }
    command[12] = END_BIT;
    if (nullptr != _command) {
        delete[] _command;
    }
    _command = command;
    _size = size;
    return 0;
}

int Command::generateTemperatureControlActionCommand(
        const unsigned char device,
        const unsigned char onOffState,
        const float temperture)
{
    const uint size = 15;
    unsigned char *command = new unsigned char[size];
    command[0] = START_BIT;
    command[1] = 0x1D;
    command[2] = 0x0A;
    command[3] = 0x00;
    command[4] = 0x00;
    command[5] = 0x30;
    command[6] = 0x03;
    command[7] = device;
    command[8] = onOffState;

    unsigned char *hex = (unsigned char *)&temperture;
    command[9] = hex[3];
    command[10] = hex[2];
    command[11] = hex[1];
    command[12] = hex[0];

    if (calculateParityBit(command, size - 2, command[13]) < 0) {
        delete[] command;
        return -1;
    }
    command[14] = END_BIT;
    if (nullptr != _command) {
        delete[] _command;
    }
    _command = command;
    _size = size;
    return 0;
}

int Command::generatePIDTemptureWriteActionCommand(unsigned char device,
                                                   const int paraP,
                                                   const int ParaI,
                                                   const int paraD)
{
    const uint size = 22;
    unsigned char *command = new unsigned char[size];
    command[0] = START_BIT;
    command[1] = 0x1D;
    command[2] = 0x11;
    command[3] = 0x00;
    command[4] = 0x00;
    command[5] = 0x30;
    command[6] = 0x04;
    command[7] = device;
    intToChar(command, paraP, 8);
    intToChar(command, ParaI, 12);
    intToChar(command, paraD, 16);
    if (calculateParityBit(command, size - 2, command[20]) < 0) {
        delete[] command;
        return -1;
    }
    command[21] = END_BIT;
    if (nullptr != _command) {
        delete[] _command;
    }
    _command = command;
    _size = size;
    return 0;
}

int Command::generateAllValveActionControl(const ushort code)
{
    const uint size = 11;
    unsigned char *command = new unsigned char[size];
    command[0] = START_BIT;
    command[1] = 0x1D;
    command[2] = 0x06;
    command[3] = 0x00;
    command[4] = 0x00;
    command[5] = 0x30;
    command[6] = 0x05;
    command[7] = static_cast<unsigned char>((code >> 8) & 0xFF);
    command[8] = static_cast<unsigned char>(code & 0xFF);
    if (calculateParityBit(command, size - 2, command[9]) < 0) {
        delete[] command;
        return -1;
    }
    command[10] = END_BIT;
    if (nullptr != _command) {
        delete[] _command;
    }
    _command = command;
    _size = size;
    return 0;
}

int Command::generateSingleValveActionCommand(const unsigned char valveNo, const unsigned char onOffState)
{
    const uint size = 11;
    unsigned char *command = new unsigned char[size];
    command[0] = START_BIT;
    command[1] = 0x1D;
    command[2] = 0x06;
    command[3] = 0x00;
    command[4] = 0x00;
    command[5] = 0x30;
    command[6] = 0x06;
    command[7] = valveNo;
    command[8] = onOffState;
    if (calculateParityBit(command, size - 2, command[9]) < 0) {
        delete[] command;
        return -1;
    }
    command[10] = END_BIT;
    if (nullptr != _command) {
        delete[] _command;
    }
    _command = command;
    _size = size;
    return 0;
}

int Command::generateIndicatorLightOnOffActionCommand1(const unsigned char lightNo,const unsigned char onOffState)
{
    const uint size = 11;
    unsigned char *command = new unsigned char[size];
    command[0] = START_BIT;
    command[1] = 0x1D;
    command[2] = 0x06;
    command[3] = 0x00;
    command[4] = 0x00;
    command[5] = 0x30;
    command[6] = 0x07;
    command[7] = lightNo;
    command[8] = onOffState;
    if (calculateParityBit(command, size - 2, command[9]) < 0) {
        delete[] command;
        return -1;
    }
    command[10] = END_BIT;
    if (nullptr != _command) {
        delete[] _command;
    }
    _command = command;
    _size = size;
    return 0;
}

int Command::generateBuzzleOnOffActionCommand(const unsigned char on_off_state)
{
    const uint size = 10;
    unsigned char *command = new unsigned char[size];
    command[0] = START_BIT;
    command[1] = 0x1D;
    command[2] = 0x05;
    command[3] = 0x00;
    command[4] = 0x00;
    command[5] = 0x30;
    command[6] = 0x08;
    command[7] = on_off_state;
    if (calculateParityBit(command, size - 2, command[8]) < 0) {
        delete[] command;
        return -1;
    }
    command[9] = END_BIT;
    if (nullptr != _command) {
        delete[] _command;
    }
    _command = command;
    _size = size;
    return 0;
}

int Command::generateSetMotorParameterActionCommand(const unsigned char motorNo,
                                                    const unsigned char current,
                                                    const unsigned char maxCurrent,
                                                    const ushort acceleration,
                                                    const ushort acceleration2,
                                                    const ushort DAcceleration,
                                                    const ushort DAcceleration2,
                                                    const uint maxSpeed,
                                                    const uint speed,
                                                    const uint stopSpeed,
                                                    const unsigned char subdivision,
                                                    const bool leftSensor,
                                                    const bool rightSensor,
                                                    const uchar currentScale)
{
    const uint size = 36;
    unsigned char *command = new unsigned char[size];
    command[0] = START_BIT;
    command[1] = 0x1D;
    command[2] = 0x1F;
    command[3] = 0x00;
    command[4] = 0x00;
    command[5] = 0x30;
    command[6] = 0x06;
    command[7] = motorNo;
    command[8] = current;
    command[9] = maxCurrent;
    ushortToChar(command,acceleration,10);
    ushortToChar(command,acceleration2,12);
    ushortToChar(command,DAcceleration,14);
    ushortToChar(command,DAcceleration2,16);

    uintToChar(command,maxSpeed,18);
    uintToChar(command,speed,22);
    uintToChar(command,stopSpeed,26);

    command[30] = subdivision;
    command[31] = leftSensor?1:0;
    command[32] = rightSensor?1:0;
    command[33] = currentScale;
    if (calculateParityBit(command, size - 2, command[34]) < 0) {
        delete[] command;
        return -1;
    }

    command[35] = END_BIT;
    if (nullptr != _command) {
        delete[] _command;
    }
    _command = command;
    _size = size;
    return 0;
}

int Command::generateWriteSampleNeedleDetectLiquidSpeedCommand(const ushort speed)
{
    const uint size = 11;
    unsigned char *command = new unsigned char[size];
    command[0] = START_BIT;
    command[1] = 0x1D;
    command[2] = 0x06;
    command[3] = 0x00;
    command[4] = 0x00;
    command[5] = 0x30;
    command[6] = 0x10;
    ushortToChar(command,speed,7);
    if (calculateParityBit(command, size - 2, command[9]) < 0) {
        delete[] command;
        return -1;
    }
    command[10] = END_BIT;
    if (nullptr != _command) {
        delete[] _command;
    }
    _command = command;
    _size = size;
    return 0;
}

int Command::generateSetMotorZeroActionCommand(unsigned char motor)
{
    const uint size = 10;
    unsigned char *command = new unsigned char[size];
    command[0] = START_BIT;
    command[1] = 0x1D;
    command[2] = 0x05;
    command[3] = 0x00;
    command[4] = 0x00;
    command[5] = 0x30;
    command[6] = 0x11;
    command[7] = motor;
    if (calculateParityBit(command, size - 2, command[8]) < 0) {
        delete[] command;
        return -1;
    }
    command[9] = END_BIT;
    if (nullptr != _command) {
        delete[] _command;
    }
    _command = command;
    _size = size;
    return 0;
}

int Command::generateMotorStopActionCommand(const unsigned char motorNo)
{
    const uint size = 10;
    unsigned char *command = new unsigned char[size];
    command[0] = START_BIT;
    command[1] = 0x1D;
    command[2] = 0x05;
    command[3] = 0x00;
    command[4] = 0x00;
    command[5] = 0x30;
    command[6] = 0x12;
    command[7] = motorNo;
    if (calculateParityBit(command, size - 2, command[8]) < 0) {
        delete[] command;
        return -1;
    }
    command[9] = END_BIT;
    if (nullptr != _command) {
        delete[] _command;
    }
    _command = command;
    _size = size;
    return 0;
}

int Command::generateMotorMoveToAbsolutePosActionCommand(const unsigned char motorNo,
                                                         const bool sensor,
                                                         const bool direction,
                                                         const int pulse)
{
    const uint size = 16;
    unsigned char *command = new unsigned char[size];
    command[0] = START_BIT;
    command[1] = 0x1D;
    command[2] = 0x0B;
    command[3] = 0x00;
    command[4] = 0x00;
    command[5] = 0x30;
    command[6] = 0x13;
    command[7] = motorNo;
    command[8] = sensor?1:0;
    command[9] = direction?1:0;
    uintToChar(command, static_cast<uint>(pulse), 10);

    if (calculateParityBit(command, size - 2, command[14]) < 0) {
        delete[] command;
        return -1;
    }
    command[15] = END_BIT;
    if (nullptr != _command) {
        delete[] _command;
    }
    _command = command;
    _size = size;
    return 0;
}

int Command::generateMotorMoveToRelativePosActionCommand(const unsigned char motorNo,
                                                         const bool sensor,
                                                         const bool direction,
                                                         const int pulse)
{
    const uint size = 16;
    unsigned char *command = new unsigned char[size];
    command[0] = START_BIT;
    command[1] = 0x1D;
    command[2] = 0x0B;
    command[3] = 0x00;
    command[4] = 0x00;
    command[5] = 0x30;
    command[6] = 0x14;
    command[7] = motorNo;
    command[8] = sensor?1:0;
    command[9] = direction?1:0;
    uintToChar(command, static_cast<uint>(pulse), 10);

    if (calculateParityBit(command, size - 2, command[14]) < 0) {
        delete[] command;
        return -1;
    }
    command[15] = END_BIT;
    if (nullptr != _command) {
        delete[] _command;
    }
    _command = command;
    _size = size;
    return 0;
}
//电机以恒定速度转动
int Command::generateMotorTurnConstSpeedActionControl(const unsigned char motorNo,
                                                      const bool sensor,
                                                      const bool direction,
                                                      const uint speed)
{
    const uint size = 16;
    unsigned char *command = new unsigned char[size];
    command[0] = START_BIT;
    command[1] = 0x1D;
    command[2] = 0x0B;
    command[3] = 0x00;
    command[4] = 0x00;
    command[5] = 0x30;
    command[6] = 0x15;
    command[7] = motorNo;
    command[8] = sensor?1:0;
    command[9] = direction?1:0;
    uintToChar(command, speed, 10);

    if (calculateParityBit(command, size - 2, command[14]) < 0) {
        delete[] command;
        return -1;
    }
    command[15] = END_BIT;
    if (nullptr != _command) {
        delete[] _command;
    }
    _command = command;
    _size = size;
    return 0;
}

int Command::generateMotorReleaseMomentActionCommand(const unsigned char motorNo, const unsigned char onOffState)
{
    const uint size = 11;
    unsigned char *command = new unsigned char[size];
    command[0] = START_BIT;
    command[1] = 0x1D;
    command[2] = 0x06;
    command[3] = 0x00;
    command[4] = 0x00;
    command[5] = 0x30;
    command[6] = 0x16;
    command[7] = motorNo;
    command[8] = onOffState;
    if (calculateParityBit(command, size - 2, command[9]) < 0) {
        delete[] command;
        return -1;
    }
    command[10] = END_BIT;
    if (nullptr != _command) {
        delete[] _command;
    }
    _command = command;
    _size = size;
    return 0;
}

int Command::generateEncoderParameterWriteActionCommand(const unsigned char motor, const uint value)
{
    const uint size = 14;
    unsigned char *command = new unsigned char[size];
    command[0] = START_BIT;
    command[1] = 0x1D;
    command[2] = 0x09;
    command[3] = 0x00;
    command[4] = 0x00;
    command[5] = 0x30;
    command[6] = 0x17;
    command[7] = motor;
    uintToChar(command, value, 8);
    if (calculateParityBit(command, size - 2, command[12]) < 0) {
        delete[] command;
        return -1;
    }
    command[13] = END_BIT;
    if (nullptr != _command) {
        delete[] _command;
    }
    _command = command;
    _size = size;
    return 0;
}

int Command::generateSpecimenLiquidLevelProbeSwitchAction(bool sensor)
{
    const uint size = 10;
    unsigned char *command = new unsigned char[size];
    command[0] = START_BIT;
    command[1] = 0x1D;
    command[2] = 0x05;
    command[3] = 0x00;
    command[4] = 0x00;
    command[5] = 0x30;
    command[6] = 0x18;
    command[7] = sensor?1:0;
    if (calculateParityBit(command, size - 2, command[8]) < 0) {
        delete[] command;
        return -1;
    }
    command[9] = END_BIT;
    if (nullptr != _command) {
        delete[] _command;
    }
    _command = command;
    _size = size;
    return 0;
}

int Command::generateMainControlParameterResetActionCommand()
{
    const uint size = 9;
    unsigned char *command = new unsigned char[size];
    command[0] = START_BIT;
    command[1] = 0x1D;
    command[2] = 0x04;
    command[3] = 0x00;
    command[4] = 0x00;
    command[5] = 0x30;
    command[6] = 0x19;
    if (calculateParityBit(command, size - 2, command[7]) < 0) {
        delete[] command;
        return -1;
    }
    command[8] = END_BIT;
    if (nullptr != _command) {
        delete[] _command;
    }
    _command = command;
    _size = size;
    return 0;
}

int Command::generateBlockNeedleParameterActionCommand(const ushort maxValue, const ushort minValue)
{
    if (maxValue < minValue)
        return -2;
    const uint size = 13;
    unsigned char *command = new unsigned char[size];
    command[0] = START_BIT;
    command[1] = 0x1D;
    command[2] = 0x08;
    command[3] = 0x00;
    command[4] = 0x00;
    command[5] = 0x30;
    command[6] = 0x20;
    ushortToChar(command, maxValue, 7);
    ushortToChar(command, minValue, 9);

    if (calculateParityBit(command, size - 2, command[11]) < 0) {
        delete[] command;
        return -1;
    }
    command[12] = END_BIT;
    if (nullptr != _command) {
        delete[] _command;
    }
    _command = command;
    _size = size;
    return 0;
}

int Command::generateWriteMotorXAxisPositionCommand(const int cupSpace,
                                                    const int rackSSpace,
                                                    const int rackLSpace,
                                                    const int rackPos,
                                                    const int reactRoughSpace,
                                                    const int reactDiscSpace,
                                                    const int sampleNeedleXPos,
                                                    const int drainagePos,
                                                    const int photographPos,
                                                    const int scanXPos,
                                                    const int scandirectionChangingPos,
                                                    const int camerCalPos,
                                                    const int liquidDetectCalibratePos,
                                                    const int scanerSelfCheckPos,
                                                    const int scanerXPos2nd)
{
    const uint size = 0x40+5;
    unsigned char *command = new unsigned char[size];
    command[0] = START_BIT;
    command[1] = 0x1D;
    command[2] = 0x34;
    command[3] = 0x00;
    command[4] = 0x00;
    command[5] = 0x30;
    command[6] = 0x21;
    intToChar(command,cupSpace,7);
    intToChar(command,rackSSpace,11);
    intToChar(command,rackLSpace,15);
    intToChar(command,rackPos,19);
    intToChar(command,reactRoughSpace,23);
    intToChar(command,reactDiscSpace,27);
    intToChar(command,sampleNeedleXPos,31);
    intToChar(command,drainagePos,35);
    intToChar(command,photographPos,39);
    intToChar(command,scanXPos,43);
    intToChar(command,scandirectionChangingPos,47);
    intToChar(command,camerCalPos,51);
    intToChar(command,liquidDetectCalibratePos,55);
    intToChar(command,scanerSelfCheckPos,59);
    intToChar(command,scanerXPos2nd,63);
    if (calculateParityBit(command, size - 2, command[67]) < 0) {
        delete[] command;
        return -1;
    }
    command[68] = END_BIT;
    if (nullptr != _command) {
        delete[] _command;
    }
    _command = command;
    _size = size;
    return 0;
}

int Command::generateWriteMotorYAxisPositionCommand(const int fstRowRackPos,
                                                    const int sndRowRackPos,
                                                    const int sampleNeedleWashPos,
                                                    const int startDrainagePos,
                                                    const int sNeedleSpitHeight,
                                                    const int startWasteSlotPos)
{
    const uint size = 0x1C+5;
    unsigned char *command = new unsigned char[size];
    command[0] = START_BIT;
    command[1] = 0x1D;
    command[2] = 0x1C;
    command[3] = 0x00;
    command[4] = 0x00;
    command[5] = 0x30;
    command[6] = 0x22;
    intToChar(command,fstRowRackPos,7);
    intToChar(command,sndRowRackPos,11);
    intToChar(command,sampleNeedleWashPos,15);
    intToChar(command,startDrainagePos,19);
    intToChar(command,sNeedleSpitHeight,23);
    intToChar(command,startWasteSlotPos,27);
    if (calculateParityBit(command, size - 2, command[31]) < 0) {
        delete[] command;
        return -1;
    }
    command[32] = END_BIT;
    if (nullptr != _command) {
        delete[] _command;
    }
    _command = command;
    _size = size;
    return 0;
}

int Command::generateWriteMotorZAxisPositionCommand(const int washHeight,
                                                    const int sCupHeight,
                                                    const int bCupHeight,
                                                    const int mCupHeight,
                                                    const int startDetectHeight,
                                                    const int spitHeight,
                                                    const int detect2ndDescendHeight,
                                                    const int wasteTankHeight)
{
    const uint size = 41;
    unsigned char *command = new unsigned char[size];
    command[0] = START_BIT;
    command[1] = 0x1D;
    command[2] = 0x24;
    command[3] = 0x00;
    command[4] = 0x00;
    command[5] = 0x30;
    command[6] = 0x23;
    intToChar(command,washHeight,7);
    intToChar(command,sCupHeight,11);
    intToChar(command,bCupHeight,15);
    intToChar(command,mCupHeight,19);
    intToChar(command,startDetectHeight,23);
    intToChar(command,spitHeight,27);
    intToChar(command,detect2ndDescendHeight,31);
    intToChar(command,wasteTankHeight,35);
    if (calculateParityBit(command, size - 2, command[39]) < 0) {
        delete[] command;
        return -1;
    }
    command[40] = END_BIT;
    if (nullptr != _command) {
        delete[] _command;
    }
    _command = command;
    _size = size;
    return 0;
}

int Command::generateWritePlungerPumpVolumeValueConvertToStepsValueCommand(const int volumToSteps)
{
    const uint size = 13;
    unsigned char *command = new unsigned char[size];
    command[0] = START_BIT;
    command[1] = 0x1D;
    command[2] = 0x08;
    command[3] = 0x00;
    command[4] = 0x00;
    command[5] = 0x30;
    command[6] = 0x24;
    intToChar(command,volumToSteps,7);
    if (calculateParityBit(command, size - 2, command[11]) < 0) {
        delete[] command;
        return -1;
    }
    command[12] = END_BIT;
    if (nullptr != _command) {
        delete[] _command;
    }
    _command = command;
    _size = size;
    return 0;
}

int Command::generateWritePeristalticPumpVolumeValueConvertToStepsValueCommand(const unsigned char pump,
                                                                               const int volumToSteps)
{
    const uint size = 14;
    unsigned char *command = new unsigned char[size];
    command[0] = START_BIT;
    command[1] = 0x1D;
    command[2] = 0x09;
    command[3] = 0x00;
    command[4] = 0x00;
    command[5] = 0x30;
    command[6] = 0x25;
    command[7] = pump;
    intToChar(command,volumToSteps,8);
    if (calculateParityBit(command, size - 2, command[12]) < 0) {
        delete[] command;
        return -1;
    }
    command[13] = END_BIT;
    if (nullptr != _command) {
        delete[] _command;
    }
    _command = command;
    _size = size;
    return 0;
}

int Command::generateSampleAirColumnParameterWriteActionCommand(const ushort value)
{
    const uint size = 11;
    unsigned char *command = new unsigned char[size];
    command[0] = START_BIT;
    command[1] = 0x1D;
    command[2] = 0x06;
    command[3] = 0x00;
    command[4] = 0x00;
    command[5] = 0x30;
    command[6] = 0x26;
    ushortToChar(command, value, 7);
    if (calculateParityBit(command, size - 2, command[9]) < 0) {
        delete[] command;
        return -1;
    }
    command[10] = END_BIT;
    if (nullptr != _command) {
        delete[] _command;
    }
    _command = command;
    _size = size;
    return 0;
}

int Command::generateWriteSpeedToRockBedCommand(const ushort lSpeed,
                                                const ushort mSpeed,
                                                const ushort hSpeed)
{
    const uint size = 15;
    unsigned char *command = new unsigned char[size];
    command[0] = START_BIT;
    command[1] = 0x1D;
    command[2] = 0x0A;
    command[3] = 0x00;
    command[4] = 0x00;
    command[5] = 0x30;
    command[6] = 0x27;
    ushortToChar(command, lSpeed, 7);
    ushortToChar(command, mSpeed, 9);
    ushortToChar(command, hSpeed, 11);
    if (calculateParityBit(command, size - 2, command[13]) < 0) {
        delete[] command;
        return -1;
    }
    command[14] = END_BIT;
    if (nullptr != _command) {
        delete[] _command;
    }
    _command = command;
    _size = size;
    return 0;
}

int Command::generateWritePosToRockBedCommand(const int cameraPos)
{
    const uint size = 0x08+5;
    unsigned char *command = new unsigned char[size];
    command[0] = START_BIT;
    command[1] = 0x1D;
    command[2] = 0x08;
    command[3] = 0x00;
    command[4] = 0x00;
    command[5] = 0x30;
    command[6] = 0x28;
    intToChar(command,cameraPos,7);
    if (calculateParityBit(command, size - 2, command[11]) < 0) {
        delete[] command;
        return -1;
    }
    command[12] = END_BIT;
    if (nullptr != _command) {
        delete[] _command;
    }
    _command = command;
    _size = size;
    return 0;
}

int Command::generate_inquire_maincontrol_version_command()
{
    const uint size = 9;
    unsigned char *command = new unsigned char[size];
    command[0] = START_BIT;
    command[1] = 0x0D;
    command[2] = 0x04;
    command[3] = 0x00;
    command[4] = 0x00;
    command[5] = 0x20;
    command[6] = 0x01;
    if (calculateParityBit(command, size - 2, command[7]) < 0) {
        delete[] command;
        return -1;
    }
    command[8] = END_BIT;
    if (nullptr != _command) {
        delete[] _command;
    }
    _command = command;
    _size = size;
    return 0;
}




int Command::generate_inquire_machine_no_command()
{
return 0;
}

int Command::generateInquireDstTemperatureCommand()
{
    const uint size = 9;
    unsigned char *command = new unsigned char[size];
    command[0] = START_BIT;
    command[1] = 0x0D;
    command[2] = 0x04;
    command[3] = 0x00;
    command[4] = 0x00;
    command[5] = 0x20;
    command[6] = 0x03;
    if (calculateParityBit(command, size - 2, command[7]) < 0) {
        delete[] command;
        return -1;
    }
    command[8] = END_BIT;
    if (nullptr != _command) {
        delete[] _command;
    }
    _command = command;
    _size = size;
    return 0;
}

int Command::generateInquireTemperatureCommand()
{
    const uint size = 9;
    unsigned char *command = new unsigned char[size];
    command[0] = START_BIT;
    command[1] = 0x0D;
    command[2] = 0x04;
    command[3] = 0x00;
    command[4] = 0x00;
    command[5] = 0x20;
    command[6] = 0x04;
    if (calculateParityBit(command, size - 2, command[7]) < 0) {
        delete[] command;
        return -1;
    }
    command[8] = END_BIT;
    if (nullptr != _command) {
        delete[] _command;
    }
    _command = command;
    _size = size;
    return 0;
}

int Command::generateInquireTemperatureControlPIDParameterCommand(const unsigned char objective)
{
    const uint size = 10;
    unsigned char *command = new unsigned char[size];
    command[0] = START_BIT;
    command[1] = 0x0D;
    command[2] = 0x05;
    command[3] = 0x00;
    command[4] = 0x00;
    command[5] = 0x20;
    command[6] = 0x05;
    command[7] = objective;
    if (calculateParityBit(command, size - 2, command[8]) < 0) {
        delete[] command;
        return -1;
    }
    command[9] = END_BIT;
    if (nullptr != _command) {
        delete[] _command;
    }
    _command = command;
    _size = size;
    return 0;
}

int Command::generateInquirePhotoelectricCommand(const unsigned char motorNo,
                                                 const bool photoelectricPos)
{
    const uint size = 11;
    unsigned char *command = new unsigned char[size];
    command[0] = START_BIT;
    command[1] = 0x0D;
    command[2] = 0x06;
    command[3] = 0x00;
    command[4] = 0x00;
    command[5] = 0x20;
    command[6] = 0x06;
    command[7] = motorNo;
    command[8]=photoelectricPos?1:0;

    if (calculateParityBit(command, size - 2, command[9]) < 0) {
        delete[] command;
        return -1;
    }
    command[10] = END_BIT;
    if (nullptr != _command) {
        delete[] _command;
    }
    _command = command;
    _size = size;
    return 0;
}

int Command::generateInquireSensorsCommand()
{
    const uint size = 9;
    unsigned char *command = new unsigned char[size];
    command[0] = START_BIT;
    command[1] = 0x0D;
    command[2] = 0x04;
    command[3] = 0x00;
    command[4] = 0x00;
    command[5] = 0x20;
    command[6] = 0x07;
    if (calculateParityBit(command, size - 2, command[7]) < 0) {
        delete[] command;
        return -1;
    }
    command[8] = END_BIT;
    if (nullptr != _command) {
        delete[] _command;
    }
    _command = command;
    _size = size;
    return 0;
}

int Command::generateInquireMotorParameterCommand(const unsigned char motorNo)
{
    const uint size = 10;
    unsigned char *command = new unsigned char[size];
    command[0] = START_BIT;
    command[1] = 0x0D;
    command[2] = 0x05;
    command[3] = 0x00;
    command[4] = 0x00;
    command[5] = 0x20;
    command[6] = 0x08;
    command[7] = motorNo;
    if (calculateParityBit(command, size - 2, command[8]) < 0) {
        delete[] command;
        return -1;
    }
    command[9] = END_BIT;
    if (nullptr != _command) {
        delete[] _command;
    }
    _command = command;
    _size = size;
    return 0;
}

int Command::generateInquireMotorCurrentPositionCommand(const unsigned char motorNo)
{
    const uint size = 10;
    unsigned char *command = new unsigned char[size];
    command[0] = START_BIT;
    command[1] = 0x0D;
    command[2] = 0x05;
    command[3] = 0x00;
    command[4] = 0x00;
    command[5] = 0x20;
    command[6] = 0x09;
    command[7] = motorNo;
    if (calculateParityBit(command, size - 2, command[8]) < 0) {
        delete[] command;
        return -1;
    }
    command[9] = END_BIT;
    if (nullptr != _command) {
        delete[] _command;
    }
    _command = command;
    _size = size;
    return 0;
}

int Command::generateInquireSampleNeedleDetectLiquidSpeedCommand()
{
    const uint size = 9;
    unsigned char *command = new unsigned char[size];
    command[0] = START_BIT;
    command[1] = 0x0D;
    command[2] = 0x04;
    command[3] = 0x00;
    command[4] = 0x00;
    command[5] = 0x20;
    command[6] = 0x11;
    if (calculateParityBit(command, size - 2, command[7]) < 0) {
        delete[] command;
        return -1;
    }
    command[8] = END_BIT;
    if (nullptr != _command) {
        delete[] _command;
    }
    _command = command;
    _size = size;
    return 0;
}

int Command::generateInquireEncoderParameterCommand(const unsigned char encoder)
{
    const uint size = 10;
    unsigned char *command = new unsigned char[size];
    command[0] = START_BIT;
    command[1] = 0x0D;
    command[2] = 0x05;
    command[3] = 0x00;
    command[4] = 0x00;
    command[5] = 0x20;
    command[6] = 0x12;
    command[7] = static_cast<unsigned char>(encoder);
    if (calculateParityBit(command, size - 2, command[8]) < 0) {
        delete[] command;
        return -1;
    }
    command[9] = END_BIT;
    if (nullptr != _command) {
        delete[] _command;
    }
    _command = command;
    _size = size;
    return 0;
}

int Command::generateInquireEncoderValueCommand(const unsigned char encoder)
{
    const uint size = 10;
    unsigned char *command = new unsigned char[size];
    command[0] = START_BIT;
    command[1] = 0x0D;
    command[2] = 0x05;
    command[3] = 0x00;
    command[4] = 0x00;
    command[5] = 0x20;
    command[6] = 0x13;
    command[7] = static_cast<unsigned char>(encoder);
    if (calculateParityBit(command, size - 2, command[8]) < 0) {
        delete[] command;
        return -1;
    }
    command[9] = END_BIT;
    if (nullptr != _command) {
        delete[] _command;
    }
    _command = command;
    _size = size;
    return 0;
}

int Command::generateInquireNeedleBlockReferanceValueCommand()
{
    const unsigned int size = 9;
    unsigned char *command = new unsigned char[size];
    command[0] = START_BIT;
    command[1] = 0x0D;
    command[2] = 0x04;
    command[3] = 0x00;
    command[4] = 0x00;
    command[5] = 0x20;
    command[6] = 0x14;
    if (calculateParityBit(command, size - 2, command[7]) < 0) {
        delete[] command;
        return -1;
    }
    command[8] = END_BIT;
    if (nullptr != _command) {
        delete[] _command;
    }
    _command = command;
    _size = size;
    return 0;
}

int Command::generateInquireMotorXAxisPositionCommand()
{
    const unsigned int size = 9;
    unsigned char *command = new unsigned char[size];
    command[0] = START_BIT;
    command[1] = 0x0D;
    command[2] = 0x04;
    command[3] = 0x00;
    command[4] = 0x00;
    command[5] = 0x20;
    command[6] = 0x15;
    if (calculateParityBit(command, size - 2, command[7]) < 0) {
        delete[] command;
        return -1;
    }
    command[8] = END_BIT;
    if (nullptr != _command) {
        delete[] _command;
    }
    _command = command;
    _size = size;
    return 0;
}

int Command::generateInquireMotorYAxisPositionCommand()
{
    const unsigned int size = 9;
    unsigned char *command = new unsigned char[size];
    command[0] = START_BIT;
    command[1] = 0x0D;
    command[2] = 0x04;
    command[3] = 0x00;
    command[4] = 0x00;
    command[5] = 0x20;
    command[6] = 0x16;
    if (calculateParityBit(command, size - 2, command[7]) < 0) {
        delete[] command;
        return -1;
    }
    command[8] = END_BIT;
    if (nullptr != _command) {
        delete[] _command;
    }
    _command = command;
    _size = size;
    return 0;
}

int Command::generateInquireMotorZAxisPositionCommand()
{
    const unsigned int size = 9;
    unsigned char *command = new unsigned char[size];
    command[0] = START_BIT;
    command[1] = 0x0D;
    command[2] = 0x04;
    command[3] = 0x00;
    command[4] = 0x00;
    command[5] = 0x20;
    command[6] = 0x17;
    if (calculateParityBit(command, size - 2, command[7]) < 0) {
        delete[] command;
        return -1;
    }
    command[8] = END_BIT;
    if (nullptr != _command) {
        delete[] _command;
    }
    _command = command;
    _size = size;
    return 0;
}
//获取1微升液体等于电机的多少步
int Command::generateInquirePlungerPumpVolumeValueConvertToStepsValueCommand()
{
    const uint size = 9;
    unsigned char *command = new unsigned char[size];
    command[0] = START_BIT;
    command[1] = 0x0D;
    command[2] = 0x04;
    command[3] = 0x00;
    command[4] = 0x00;
    command[5] = 0x20;
    command[6] = 0x18;
    if (calculateParityBit(command, size - 2, command[7]) < 0) {
        delete[] command;
        return -1;
    }
    command[8] = END_BIT;
    if (nullptr != _command) {
        delete[] _command;
    }
    _command = command;
    _size = size;
    return 0;
}

int Command::generateInquirePeristalticPumpVolumeValueConvertToStepsValueCommand(const unsigned char pump)
{
    const uint size = 10;
    unsigned char *command = new unsigned char[size];
    command[0] = START_BIT;
    command[1] = 0x0D;
    command[2] = 0x05;
    command[3] = 0x00;
    command[4] = 0x00;
    command[5] = 0x20;
    command[6] = 0x19;
    command[7] = pump;
    if (calculateParityBit(command, size - 2, command[8]) < 0) {
        delete[] command;
        return -1;
    }
    command[9] = END_BIT;
    if (nullptr != _command) {
        delete[] _command;
    }
    _command = command;
    _size = size;
    return 0;
}

int Command::generateInquireSampleAirColumnParameterCommand()
{
    const uint size = 9;
    unsigned char *command = new unsigned char[size];
    command[0] = START_BIT;
    command[1] = 0x0D;
    command[2] = 0x04;
    command[3] = 0x00;
    command[4] = 0x00;
    command[5] = 0x20;
    command[6] = 0x20;
    if (calculateParityBit(command, size - 2, command[7]) < 0) {
        delete[] command;
        return -1;
    }
    command[8] = END_BIT;
    if (nullptr != _command) {
        delete[] _command;
    }
    _command = command;
    _size = size;
    return 0;
}

int Command::generateInquireRockBedSpeedCommand()
{
    const uint size = 9;
    unsigned char *command = new unsigned char[size];
    command[0] = START_BIT;
    command[1] = 0x0D;
    command[2] = 0x04;
    command[3] = 0x00;
    command[4] = 0x00;
    command[5] = 0x20;
    command[6] = 0x21;
    if (calculateParityBit(command, size - 2, command[7]) < 0) {
        delete[] command;
        return -1;
    }
    command[8] = END_BIT;
    if (nullptr != _command) {
        delete[] _command;
    }
    _command = command;
    _size = size;
    return 0;
}

int Command::generateInquireRockBedPosCommand()
{
    const uint size = 9;
    unsigned char *command = new unsigned char[size];
    command[0] = START_BIT;
    command[1] = 0x0D;
    command[2] = 0x04;
    command[3] = 0x00;
    command[4] = 0x00;
    command[5] = 0x20;
    command[6] = 0x22;
    if (calculateParityBit(command, size - 2, command[7]) < 0) {
        delete[] command;
        return -1;
    }
    command[8] = END_BIT;
    if (nullptr != _command) {
        delete[] _command;
    }
    _command = command;
    _size = size;
    return 0;
}

int Command::generateSetDryPaperRockBedPosCommand(const int pos)
{
    const uint size = 0x08+5;
    unsigned char *command = new unsigned char[size];
    command[0] = START_BIT;
    command[1] = 0x1D;
    command[2] = 0x08;
    command[3] = 0x00;
    command[4] = 0x00;
    command[5] = 0x30;
    command[6] = 0x31;
    intToChar(command,pos,7);
    if (calculateParityBit(command, size - 2, command[11]) < 0) {
        delete[] command;
        return -1;
    }
    command[12] = END_BIT;
    if (nullptr != _command) {
        delete[] _command;
    }
    _command = command;
    _size = size;
    return 0;
}
