#ifndef COMMAND_H
#define COMMAND_H
#include <QString>
#include "../Instrument/src/Instrument.h"
class SerialPortDriver;

class Command
{
public:
    Command();
    Command(const unsigned char *command,const unsigned int size);
    Command(QByteArray command);
    ~Command();
public:
    enum
    {
        START_BIT=0x01,
        END_BIT=0x04,
        MIN_LENGTH=9,
    };

public:

    static int calculateParityBit(const unsigned char *command,
                                  const unsigned int length,
                                  unsigned char &parityBit);

    int send(const QString &name="") const;

    int isValid() const;
private:
    inline void uintToChar(unsigned char *cmd,uint para,int index);
    inline void intToChar(unsigned char *cmd,int para,int index);
    inline void ushortToChar(unsigned char *cmd, ushort para, int index);

public:

    int generateInitializeMotorCommand(const unsigned char motorNo);

    int generateSpecimenArmSuckCommand(const ushort suckVolume,
                                       const bool sensor,
                                       const unsigned char cupType,
                                       const unsigned char suckPos);

    int generateSpecimenArmWashCommand(const ushort outerWashTime,
                                       const ushort innerWashTime,
                                       const ushort pumpWasteLiquidTime);

    int generateSpecimenArmSpitCommand(const ushort spitVolume,
                                       const bool sensor,
                                       const unsigned char spitPos);

    int generateScannerReadCommand();

    int generateScanSampleCommand(const unsigned char samplePos);

    int generateCalibrateCameraCommand();

    int generateDischargeWasteAndPeristalticPumpSpitLiquidCommand(const uchar reactNO,
                                                                  const unsigned char spitPos,
                                                                  const ushort dischargeTime,
                                                                  const unsigned char liquidType,
                                                                  const ushort volume);

    int generatePeristalticPumpBackFlowCommand(const unsigned char backFlowType,const ushort backFlowVolume);

    int generatePeristalticPumpFillLiquidCommand(const unsigned char fillType,
                                                 const ushort volume);

    int generateShakingBedWorkingCommand(const unsigned char workType);

    int generateFanControlCommand(const unsigned char runType,const unsigned char pos);

    int generateScannerSelfCheckCommand();

    int generateCalibratePeristalticPumpCommand(const unsigned char pumpNo,const ushort volume);

    int generatePhotographCommand(const unsigned char pos);

    int generateIrrigationSystemLiquidCommand(const ushort volumn);

    int generateWashSystemLiquidWayCommand(const ushort volumn);

    int generateIndicatorLightOnOffCommand(const unsigned char lightNo,const unsigned char onOffState);

    int generateBuzzleOnOffCommand(const unsigned char on_off_state);

    int generateSpecimenArmSuckAndSplitCommand(const ushort suckVolume,
                                               const uchar sensor,
                                               const unsigned char cupType,
                                               const unsigned char suckPos,
                                               const unsigned char spitPos);
public:
    int generateSynchronizedActionCommand();
    int generateMachineNoWriteActionCommand(const uint machineNo);
    int generateTemperatureControlActionCommand(const unsigned char device,
                                                const unsigned char onOffState,
                                                const float temperture);
    int generatePIDTemptureWriteActionCommand(unsigned char device,
                                              const int paraP,
                                              const int ParaI,
                                              const int paraD);
    int generateAllValveActionControl(const ushort code);
    int generateSingleValveActionCommand(const unsigned char valveNo,const unsigned char onOffState);
    int generateIndicatorLightOnOffActionCommand1(const unsigned char lightNo,const unsigned char onOffState);
    int generateBuzzleOnOffActionCommand(const unsigned char on_off_state);
    int generateSetMotorParameterActionCommand(const unsigned char motorNo,
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
                                               const uchar currentScale);
    int generateWriteSampleNeedleDetectLiquidSpeedCommand(const ushort speed);
    int generateSetMotorZeroActionCommand(unsigned char motor);
    int generateMotorStopActionCommand(const unsigned char motorNo);
    int generateMotorMoveToAbsolutePosActionCommand(const unsigned char motorNo,
                                                    const bool sensor,
                                                    const bool direction,
                                                    const int pulse);
    int generateMotorMoveToRelativePosActionCommand(const unsigned char motorNo,
                                                    const bool sensor,
                                                    const bool direction,
                                                    const int pulse);
    int generateMotorTurnConstSpeedActionControl(const unsigned char motorNo,
                                                 const bool sensor,
                                                 const bool direction,
                                                 const uint speed);
    int generateMotorReleaseMomentActionCommand(const unsigned char motorNo,const unsigned char onOffState);
    int generateEncoderParameterWriteActionCommand(const unsigned char motor,const uint value);
    int generateSpecimenLiquidLevelProbeSwitchAction(bool sensor);
    int generateMainControlParameterResetActionCommand();
    int generateBlockNeedleParameterActionCommand(const ushort maxValue,
                                                  const ushort minValue);
    int generateWriteMotorXAxisPositionCommand(const int cupSpace,
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
                                               const int scanerXPos2nd);
    int generateWriteMotorYAxisPositionCommand(const int fstRowRackPos,
                                               const int sndRowRackPos,
                                               const int sampleNeedleWashPos,
                                               const int startDrainagePos,
                                               const int sNeedleSpitHeight,
                                               const int startWasteSlotPos);

    int generateWriteMotorZAxisPositionCommand(const int washHeight,
                                               const int sCupHeight,
                                               const int bCupHeight,
                                               const int mCupHeight,
                                               const int startDetectHeight,
                                               const int spitHeight,
                                               const int detect2ndDescendHeight,
                                               const int wasteTankHeight);

    int generateWritePlungerPumpVolumeValueConvertToStepsValueCommand(const int volumToSteps);

    int generateWritePeristalticPumpVolumeValueConvertToStepsValueCommand(const unsigned char pump,const int volumToSteps);

    int generateSampleAirColumnParameterWriteActionCommand(const ushort value);

    int generateWriteSpeedToRockBedCommand(const ushort lSpeed,
                                           const ushort mSpeed,
                                           const ushort hSpeed);

    int generateWritePosToRockBedCommand(const int cameraPos);

    int generate_inquire_maincontrol_version_command();

    int generate_inquire_machine_no_command();

    int generateInquireDstTemperatureCommand();

    int generateInquireTemperatureCommand();

    int generateInquireTemperatureControlPIDParameterCommand(const unsigned char objective);

    int generateInquirePhotoelectricCommand(const unsigned char motorNo,const bool photoelectricPos);

    int generateInquireSensorsCommand();

    int generateInquireMotorParameterCommand(const unsigned char motorNo);

    int generateInquireMotorCurrentPositionCommand(const unsigned char motorNo);

    int generateInquireSampleNeedleDetectLiquidSpeedCommand();

    int generateInquireEncoderParameterCommand(const unsigned char encoder);

    int generateInquireEncoderValueCommand(const unsigned char encoder);

    int generateInquireNeedleBlockReferanceValueCommand();

    int generateInquireMotorXAxisPositionCommand();

    int generateInquireMotorYAxisPositionCommand();

    int generateInquireMotorZAxisPositionCommand();

    int generateInquirePlungerPumpVolumeValueConvertToStepsValueCommand();

    int generateInquirePeristalticPumpVolumeValueConvertToStepsValueCommand(const unsigned char pump);

    int generateInquireSampleAirColumnParameterCommand();

    int generateInquireRockBedSpeedCommand();

    int generateInquireRockBedPosCommand();

    int generateSetDryPaperRockBedPosCommand(const int pos);
private:
    unsigned int _size;
    unsigned char *_command;
    QByteArray requestCommand;
    SerialPortDriver *_port;


    int getMessageId();
};

#endif // COMMAND_H
