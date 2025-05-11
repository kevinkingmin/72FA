#include "Components.h"
#include "Valve.h"
#include "Buzzle.h"
#include "MainController.h"
#include "Motor.h"
#include "Camera.h"
#include "Sensor.h"
#include "Temperature.h"
#include "Light.h"
#include "Encoder.h"
#include "RockBed.h"
#include "Fan.h"
#include "Scaner.h"
#include "SampleArm.h"
#include "Liquid.h"
#include "../cmd/Command.h"
#include "../cmd/AnalysisReciveCmd.h"
#include "src/local_log.h"
#include "../Include/Comm/singleton.h"
#include "../Include/Model/baseSet/InstrumentStateModel.h"
#include "ObjectInfo.h"
#include <QQueue>
#include <QtMath>
#include <QDebug>

#define LUMINOUS_PROPORTIONALITY_COEFFICIENT 1.0
#define NEEDLE_BLOCKING_DETECTION 1

QMutex Components::_lock;
Components::Components(QObject *parent) :QObject(parent)
  , _mainctroller(new MainController(this))
  , _camera(new Camera(this))
  , _sensor(new Sensor(this))
  , _buzzle(new Buzzle(this))
  , _temperature(new Temperature(this))
  , _rockBed(new RockBed(this))
  , _fan(new Fan(this))
  , _scaner(new Scaner(this))
  , _sampleArm(new SampleArm(this))
  , _liquid(new Liquid(this))
  , _reciveCmd(AnalysisReciveCmd::instance())
  , _command(nullptr)
  , _size(0)
  ,_cmdFun(nullptr)
{
    initValve();

    for(int i=MOTORSTART;i<=MOTORCOUNT;i++)
        _motors[i]=new Motor(static_cast<MotorAddress>(i),this);

    for(int i=LIGHTSTART;i<LIGHTCOUNT;i++)
        _lights[i]=new Light(static_cast<LightAddress>(i),this);

    for(int i=ENCODERSTART;i<=ENCODERCOUNT;i++)
        _encoders[i]=new Encoder(static_cast<EncoderAddress>(i),this);

	_reciveCmd->setCmdArrivedFun(std::bind(&Components::commandArrived, this, std::placeholders::_1));
}

Components *Components::instance()
{
	return Singleton<Components>::instance();
}

Components::~Components()
{
    for(int i=VALVESTART;i<=VALVECOUNT;i++)
        delete _valves[i];
    //delete _mainctroller;
    delete _camera;
    delete _sensor;

    for(int i=MOTORSTART;i<=MOTORCOUNT;i++)
        delete _motors[i];

    //delete _buzzle;
    delete _temperature;

    for(int i=LIGHTSTART;i<LIGHTCOUNT;i++)
        delete  _lights[i];

    for(int i=ENCODERSTART;i<=ENCODERCOUNT;i++)
        delete _encoders[i];

    //delete _rockBed;
    delete _fan;
    delete _scaner;
    delete _sampleArm;
    delete _liquid;

	if (_command != nullptr)
	{
		delete[] _command;
		_command = nullptr;
	}
}

Valve *Components::getValveByAddress(ValveAddress addr)
{
    for(int i=VALVESTART;i<=VALVECOUNT;i++)
    {
        auto valve= reinterpret_cast<Valve*>(_valves[i]);
        if(valve->getAddress()==addr)
            return valve;
    }
    return nullptr;
}

MainController *Components::get_main_controller()
{
    return reinterpret_cast<MainController*>(_mainctroller);
}

Camera *Components::getCamera()
{
    return  reinterpret_cast<Camera*>(_camera);
}

Sensor *Components::getSensor()
{
    return  reinterpret_cast<Sensor *>(_sensor);
}

Motor *Components::getMotorByAddress(MotorAddress address)
{
    return reinterpret_cast<Motor*>(_motors[address]);
}

Buzzle *Components::getBuzzle()
{
    return reinterpret_cast<Buzzle *>(_buzzle);
}

Temperature *Components::getTemperature()
{
    return reinterpret_cast<Temperature *>(_temperature);
}

Light *Components::getLightByAddress(Components::LightAddress address)
{
    return reinterpret_cast<Light *>(_lights[address]);
}

Encoder *Components::getEncoderByAddress(Components::EncoderAddress address)
{
    return reinterpret_cast<Encoder *>(_encoders[address]);
}

RockBed *Components::getRockBed()
{
    return reinterpret_cast<RockBed *>(_rockBed);
}

Fan *Components::getFan()
{
    return reinterpret_cast<Fan *>(_fan);
}

Scaner *Components::getScaner()
{
    return reinterpret_cast<Scaner *>(_scaner);
}

SampleArm *Components::getSampleArm()
{
    return reinterpret_cast<SampleArm *>(_sampleArm);
}

Liquid *Components::getLiquid()
{
    return  reinterpret_cast<Liquid *>(_liquid);
}

void Components::setCmdFun(const funType &cmdFun)
{
    _cmdFun = cmdFun;
}

void Components::initValve()
{
    for(int i=VALVESTART;i<=VALVECOUNT;i++)
    {
        if(i<=3)
            _valves[i]=new Valve(static_cast<ValveAddress>(i),this);
        else
            _valves[i]=new Valve(static_cast<ValveAddress>(i+7),this);
    }
}

Components::funType Components::getCmdFun() const
{
    return _cmdFun;
}

int Components::analysis(QByteArray cmdData, uint size)
{
    size = static_cast<uint>(cmdData.length());
    //dLog("receive cmd:{}", cmdData.toHex());
	if (size < Command::MIN_LENGTH)
		return -2;
	if ((nullptr != cmdData) && (size > 0))
	{
		if (_command != nullptr)
		{
			delete[] _command;
			_command = nullptr;
		}
		_command = new unsigned char[size];
		if (nullptr != _command)
		{
			_size = size;
			memcpy(_command, cmdData, size * sizeof(unsigned char));
		}
	}
	if (_size <= 0 || _command == nullptr)
    {
        eLog("指令生成错误，size:{},cmd:{}", size, QByteArray(reinterpret_cast<char *>(_command),static_cast<int>(_size)).toHex());
		return -3;
    }
	else if (0xB5 == _command[1])
	{
		if (analysis_compound_response_command() < 0)
		{
			return(-4);
		}
		else
		{
			return(0);
		}
	}
	else if (0x8D == _command[1])
	{
		if (analysis_inquire_response_command() < 0)
		{
			return(-6);
		}
		else
		{
			return(0);
		}
	}
	else if (0x9D == _command[1])
	{
		if (analysis_action_response_command() < 0)
		{
			return(-8);
		}
		else
		{
			return(0);
		}
	}
	else if (0xF5 == _command[1])
	{
		if (analysis_report_command() < 0)
		{
			return(-9);
		}
		else
		{
			return(0);
		}
	}
	else
	{
        eLog("未知回复，cmd:{}", QByteArray(reinterpret_cast<char *>(_command),static_cast<int>(_size)).toHex());
		return(-10);
	}
}

int Components::analysis_compound_response_command()
{
	auto fun = [this](int &para, int index)
	{
		para |= _command[index];
		para <<= 8;
		para |= _command[++index];
		para <<= 8;
		para |= _command[++index];
		para <<= 8;
		para |= _command[++index];
	};

	if ((0x00 == _command[3]) && (0x01 == _command[4]) && (0x10 == _command[5]) && (0x01 == _command[6]))
    {
        getMotorByAddress(static_cast<MotorAddress>(_command[7]))->setComResponseFlag(Component::FLAG_IDLE);
	}
	else if ((0x00 == _command[3]) && (0x01 == _command[4]) && (0x10 == _command[5]) && (0x02 == _command[6]))
    {
        int steps=0;
        fun(steps,7);
        getSampleArm()->setComResponseFlag(Component::FLAG_IDLE);
	}
	else if ((0x00 == _command[3]) && (0x01 == _command[4]) && (0x10 == _command[5]) && (0x03 == _command[6]))
    {
        getSampleArm()->setComResponseFlag(Component::FLAG_IDLE);
	}
	else if ((0x00 == _command[3]) && (0x01 == _command[4]) && (0x10 == _command[5]) && (0x04 == _command[6]))
    {
        int steps=0;
        fun(steps,7);
        getSampleArm()->setComResponseFlag(Component::FLAG_IDLE);
	}
	else if ((0x00 == _command[3]) && (0x01 == _command[4]) && (0x10 == _command[5]) && (0x05 == _command[6]))
    {
        const int barcode_size = static_cast<int>(_command[2]) - 4;
        if (barcode_size < 0)
        {
            eLog("收到异常的样本盘扫描回复指令,_command:{}", _command);
            return(-1);
        }
        QString barcode("");
        for (int index = 0; index < barcode_size; ++index)
        {
            barcode.append(_command[7 + index]);
        }

        if(barcode.length()>=2)
        {
            barcode = barcode.mid(1);
            barcode = barcode.left(barcode.length() - 1);
        }
        getScaner()->setReadCode(barcode);
	}
	else if ((0x00 == _command[3]) && (0x01 == _command[4]) && (0x10 == _command[5]) && (0x06 == _command[6]))
    {
        const int barcode_size = static_cast<int>(_command[2]) - 4;
        if (barcode_size < 0)
        {
            eLog("收到异常的样本盘扫描回复指令,_command:{}", _command);
            return(-1);
        }
        QString barcode("");
        for (int index = 0; index < barcode_size; ++index)
        {
            barcode.append(_command[7 + index]);
        }

        if(barcode.length()>=2)
        {
            barcode = barcode.mid(1);
            barcode = barcode.left(barcode.length() - 1);
        }
        getScaner()->setSampleBarcode(barcode);
	}
	else if ((0x00 == _command[3]) && (0x01 == _command[4]) && (0x10 == _command[5]) && (0x07 == _command[6]))
    {
        getCamera()->setComResponseFlag(Camera::FLAG_IDLE);
	}
	else if ((0x00 == _command[3]) && (0x01 == _command[4]) && (0x10 == _command[5]) && (0x08 == _command[6]))
    {
        getLiquid()->setComResponseFlag(Component::FLAG_IDLE);
	}
	else if ((0x00 == _command[3]) && (0x01 == _command[4]) && (0x10 == _command[5]) && (0x09 == _command[6]))
    {
        getLiquid()->setComResponseFlag(Component::FLAG_IDLE);
	}
	else if ((0x00 == _command[3]) && (0x01 == _command[4]) && (0x10 == _command[5]) && (0x10 == _command[6]))
    {
        getLiquid()->setComResponseFlag(Component::FLAG_IDLE);
	}
	else if ((0x00 == _command[3]) && (0x01 == _command[4]) && (0x10 == _command[5]) && (0x11 == _command[6]))
    {
        getRockBed()->setComResponseFlag(Component::FLAG_IDLE);
	}
	else if ((0x00 == _command[3]) && (0x01 == _command[4]) && (0x10 == _command[5]) && (0x12 == _command[6]))
    {
        getFan()->setComResponseFlag(Component::FLAG_IDLE);
	}
	else if ((0x00 == _command[3]) && (0x01 == _command[4]) && (0x10 == _command[5]) && (0x13 == _command[6]))
    {
        const int barcode_size = static_cast<int>(_command[2]) - 4;
        if (barcode_size < 0)
        {
			getScaner()->setComResponseFlag(Component::FLAG_IDLE);
            eLog("收到异常的样本盘扫描回复指令,_command:{}", _command);
            return(-1);
        }
        QString barcode("");
        for (int index = 0; index < barcode_size; ++index)
        {
            barcode.append(_command[7 + index]);
        }

        if(barcode.length()>=2)
        {
            barcode = barcode.mid(1);
            barcode = barcode.left(barcode.length() - 1);
        }
        getScaner()->setCheckCode(barcode);
	}
	else if ((0x00 == _command[3]) && (0x01 == _command[4]) && (0x10 == _command[5]) && (0x14 == _command[6]))
    {
        int fstSteps=0;
        int sndSteps=0;

        fun(fstSteps,7);
        fun(sndSteps,11);
        getLiquid()->setCalibrateSteps(fstSteps,sndSteps);
	}
	else if ((0x00 == _command[3]) && (0x01 == _command[4]) && (0x10 == _command[5]) && (0x15 == _command[6]))
    {
        getCamera()->setComResponseFlag(Component::FLAG_IDLE);
    }
    else if ((0x00 == _command[3]) && (0x01 == _command[4]) && (0x10 == _command[5]) && (0x16 == _command[6]))
    {
        getLiquid()->setComResponseFlag(Component::FLAG_IDLE);
    }
    else if ((0x00 == _command[3]) && (0x01 == _command[4]) && (0x10 == _command[5]) && (0x17 == _command[6]))
    {
        getLiquid()->setComResponseFlag(Component::FLAG_IDLE);
    }
	else
	{
		eLog("函数中，收到非法指令,_command:{}", QByteArray(reinterpret_cast<char *>(_command), static_cast<int>(_size)).toHex());
		return(-2);
	}
    return 0;
}

int Components::analysis_inquire_response_command()
{
	auto fun = [this](int &para, int index)
	{
		para |= _command[index];
		para <<= 8;
		para |= _command[++index];
		para <<= 8;
		para |= _command[++index];
		para <<= 8;
		para |= _command[++index];
	};
	auto ufun = [this](uint &para, int index)
	{
		para |= _command[index];
		para <<= 8;
		para |= _command[++index];
		para <<= 8;
		para |= _command[++index];
		para <<= 8;
		para |= _command[++index];
	};

    auto ushortFun=[this](ushort &para, int index)
    {
        para |= _command[index];
        para <<= 8;
        para |= _command[++index];
    };

    if ((0x00 == _command[3]) && (0x01 == _command[4]) && (0x20 == _command[5]) && (0x01 == _command[6]))
    {
        ushort hardware_version = 0;
        ushortFun(hardware_version,7);
        ushort software_version = 0;
        ushortFun(software_version,9);
        get_main_controller()->set_main_controller_version(hardware_version,software_version);
    }
    else if ((0x00 == _command[3]) && (0x01 == _command[4]) && (0x20 == _command[5]) && (0x02 == _command[6]))
    {
        int machine_no = 0;
        fun(machine_no, 7);
        get_main_controller()->set_machine_no(machine_no);
        get_main_controller()->setInquireResponseFlag(Component::FLAG_IDLE);
    }
    else if ((0x00 == _command[3]) && (0x01 == _command[4]) && (0x20 == _command[5]) && (0x03 == _command[6]))
    {
        unsigned char hex[] = { _command[7], _command[8], _command[9], _command[10]};
        float f = *reinterpret_cast<float *>(hex);
        getTemperature()->setDSTTemperature(f);
    }
    else if ((0x00 == _command[3]) && (0x01 == _command[4]) && (0x20 == _command[5]) && (0x04 == _command[6]))
    {
        unsigned char hex[] = { _command[7], _command[8], _command[9], _command[10]};
        float f = *reinterpret_cast<float *>(hex);
        getTemperature()->setRealTimeTemperature(f);
	}
    else if ((0x00 == _command[3]) && (0x01 == _command[4]) && (0x20 == _command[5]) && (0x05 == _command[6]))
    {
        Temperature::PIDStruct para;
        TemperatureAddress address=static_cast<TemperatureAddress>(_command[7]);
        fun(para.paraP,8);
        fun(para.paraI,12);
        fun(para.paraD,16);
        getTemperature()->setPIDPara(para,address);
	}
    else if ((0x00 == _command[3]) && (0x01 == _command[4]) && (0x20 == _command[5]) && (0x06 == _command[6]))
    {
        auto motor =  getMotorByAddress(static_cast<MotorAddress>(_command[7]));
        motor->setInquireResponseFlag(Component::FLAG_IDLE);
        if(_command[8]==0)//左光电
        {
            if(_command[9]==0)//未遮挡
                motor->setLeftPhotoelectricFlag(Component::FLAG_EMPTY);
            else
                motor->setLeftPhotoelectricFlag(Component::FLAG_USED);
        }
        else//右光电
        {
            if(_command[9]==0)//未遮挡
                motor->setRightPhotoelectricFlag(Component::FLAG_EMPTY);
            else
                motor->setRightPhotoelectricFlag(Component::FLAG_USED);
        }
	}
    else if ((0x00 == _command[3]) && (0x01 == _command[4]) && (0x20 == _command[5]) && (0x07 == _command[6]))
    {
        ushort data=0;
        ushortFun(data,7);
        getSensor()->setInquireResponseFlag(Component::FLAG_IDLE);
        getSensor()->setSensorData(data);
	}
    else if ((0x00 == _command[3]) && (0x01 == _command[4]) && (0x20 == _command[5]) && (0x08 == _command[6]))
    {
        Motor::MotorPara para;
        para.holddingCurrent=_command[8];
        para.maxCurrent=_command[9];
        ushortFun(para.accelerateMax,10);
        ushortFun(para.accelerateA1,12);
        ushortFun(para.accelerateDMax,14);
        ushortFun(para.accelerateD1,16);
        ufun(para.vmaxSpeed,18);
        ufun(para.v1Speed,22);
        ufun(para.vStopSpeed,26);
        para.subdividing=_command[30];
        para.leftSensorEnable=_command[31]>0?true:false;
        para.rightSensorEnable=_command[32]>0?true:false;
        para.currentScale=_command[33];
        getMotorByAddress(static_cast<MotorAddress>(_command[7]))->setMotorPara(para);
	}
    else if ((0x00 == _command[3]) && (0x01 == _command[4]) && (0x20 == _command[5]) && (0x09 == _command[6]))
    {
        int pos=0;
        fun(pos,8);
        getMotorByAddress(static_cast<MotorAddress>(_command[7]))->setCurrentPosition(pos);
	}
    else if ((0x00 == _command[3]) && (0x01 == _command[4]) && (0x20 == _command[5]) && (0x11 == _command[6]))
    {

	}
    else if ((0x00 == _command[3]) && (0x01 == _command[4]) && (0x20 == _command[5]) && (0x12 == _command[6]))
    {
        int prescale=0;
        fun(prescale,8);
        getEncoderByAddress(static_cast<EncoderAddress>(_command[7]))->setPrescale(prescale);
	}
    else if ((0x00 == _command[3]) && (0x01 == _command[4]) && (0x20 == _command[5]) && (0x13 == _command[6]))
    {
        int val=0;
        fun(val,8);
        getEncoderByAddress(static_cast<EncoderAddress>(_command[7]))->setEncoderValue(val);
	}
    else if ((0x00 == _command[3]) && (0x01 == _command[4]) && (0x20 == _command[5]) && (0x14 == _command[6]))
    {
        SampleArm::NeedleBlockPara para;
        ushortFun(para.minValue,7);
        ushortFun(para.maxValue,9);
        getSampleArm()->setBlockPara(para);
	}
    else if ((0x00 == _command[3]) && (0x01 == _command[4]) && (0x20 == _command[5]) && (0x15 == _command[6]))
    {
        SampleArm::XMotorPara para;
        fun(para.cupSpace,7);//样本杯间距
        fun(para.rackSSpace,11);//样本架小间距
        fun(para.rackLSpace,15);//样本架大间距
        fun(para.rackPos,19);//样本架位置
        fun(para.rectSlotSpace,23);//反应槽间距
        fun(para.rectDiscSpace,27);//反应盘间距
        fun(para.sNeedleSpitXPos,31);//样本针加样X轴位置
        fun(para.suckLiquidPos,35);//抽液位置
        fun(para.photographPos,39);//拍照位置
        fun(para.scanerXPos,43);//扫码器X轴位置
        fun(para.scanerChangePos,47);//扫码器换向位置
        fun(para.cameraCalibratePos,51);//相机校准位
        getSampleArm()->setXMotorPara(para);
	}
    else if ((0x00 == _command[3]) && (0x01 == _command[4]) && (0x20 == _command[5]) && (0x16 == _command[6]))
    {
        SampleArm::YMotorPara para;
        fun(para.fstRackPos,7);//第一排样本架位置
        fun(para.scdRackPos,11);//第二排样本架位置
        fun(para.needleWashPos,15);//样本针清洗位置
        fun(para.startDrawWastePos,19);//触发抽废液位置
        fun(para.spitYPos,23);//样本针加样Y轴位置
        fun(para.startWasteSlotPos,27);
        getSampleArm()->setYMotorPara(para);
	}
    else if ((0x00 == _command[3]) && (0x01 == _command[4]) && (0x20 == _command[5]) && (0x17 == _command[6]))
    {
        SampleArm::ZMotorPara para;
        fun(para.washHeight,7);//清洗位高度
        fun(para.standartCupHeight,11);//标准品杯高度
        fun(para.bloodingCupHeight,15);//采血管高度
        fun(para.microCupHeight,19);//微量杯高度
        fun(para.startDetectLevelHeight,23);//液位探测起始高度
        fun(para.spitHeight,27);//吐液高度
        fun(para.detectLevel2ndDescendHeight,31);//液位探测二次下降高度
        fun(para.wasteSlotHeight,35);//废液槽高度
        getSampleArm()->setZMotorPara(para);
	}
    else if ((0x00 == _command[3]) && (0x01 == _command[4]) && (0x20 == _command[5]) && (0x18 == _command[6]))
    {
        int steps=0;
        fun(steps,7);
        getSampleArm()->setStepsFrom1ul(steps);
	}
    else if ((0x00 == _command[3]) && (0x01 == _command[4]) && (0x20 == _command[5]) && (0x19 == _command[6]))
    {
        int steps=0;
        fun(steps,8);
        getMotorByAddress(static_cast<MotorAddress>(_command[7]))->set50ulSteps(steps);
	}
    else if ((0x00 == _command[3]) && (0x01 == _command[4]) && (0x20 == _command[5]) && (0x20 == _command[6]))
    {
        ushort volumn=0;
        ushortFun(volumn,7);
        getSampleArm()->setNeedleAirColumn(volumn);
	}
    else if ((0x00 == _command[3]) && (0x01 == _command[4]) && (0x20 == _command[5]) && (0x21 == _command[6]))
    {
        RockBed::SpeedStruct para;
        ushortFun(para.lSpeed,7);
        ushortFun(para.mSpeed,9);
        ushortFun(para.hSpeed,11);
        getRockBed()->setSpeedPara(para);
    }
    else if ((0x00 == _command[3]) && (0x01 == _command[4]) && (0x20 == _command[5]) && (0x22 == _command[6]))
    {
        int pos=0;
        fun(pos,7);
        getRockBed()->setCameraPos(pos);
    }
	else
	{
        eLog("收到非法指令,cmd:{}", QByteArray(reinterpret_cast<char *>(_command),static_cast<int>(_size)).toHex());
		return(-1);
	}
    return 0;
}

int Components::analysis_action_response_command()
{
	if ((0x00 == _command[3]) && (0x01 == _command[4]) && (0x30 == _command[5]) && (0x01 == _command[6]))
    {
        get_main_controller()->setInquireResponseFlag(Component::FLAG_IDLE);
	}
	else if ((0x00 == _command[3]) && (0x01 == _command[4]) && (0x30 == _command[5]) && (0x02 == _command[6]))
    {
        get_main_controller()->setInquireResponseFlag(Component::FLAG_IDLE);
	}
	else if ((0x00 == _command[3]) && (0x01 == _command[4]) && (0x30 == _command[5]) && (0x03 == _command[6]))
    {
        getTemperature()->setInquireResponseFlag(Component::FLAG_IDLE);
	}
	else if ((0x00 == _command[3]) && (0x01 == _command[4]) && (0x30 == _command[5]) && (0x04 == _command[6]))
    {
        getTemperature()->setInquireResponseFlag(Component::FLAG_IDLE);
    }
	else if ((0x00 == _command[3]) && (0x01 == _command[4]) && (0x30 == _command[5]) && (0x05 == _command[6]))
    {
        get_main_controller()->setInquireResponseFlag(Component::FLAG_IDLE);
	}
	else if ((0x00 == _command[3]) && (0x01 == _command[4]) && (0x30 == _command[5]) && (0x06 == _command[6]))
    {
        getValveByAddress(static_cast<ValveAddress>(_command[7]))->setInquireResponseFlag(Component::FLAG_IDLE);
	}
	else if ((0x00 == _command[3]) && (0x01 == _command[4]) && (0x30 == _command[5]) && (0x07 == _command[6]))
    {
        getLightByAddress(static_cast<LightAddress>(_command[7]))->setInquireResponseFlag(Component::FLAG_IDLE);
	}
	else if ((0x00 == _command[3]) && (0x01 == _command[4]) && (0x30 == _command[5]) && (0x08 == _command[6]))
    {
        getBuzzle()->setInquireResponseFlag(Component::FLAG_IDLE);
	}
    else if (0x00 == _command[3] && 0x01 == _command[4] && 0x30 == _command[5] && 0x09 == _command[6])
    {
        getMotorByAddress(static_cast<MotorAddress>(_command[7]))->setInquireResponseFlag(Component::FLAG_IDLE);
	}
    else if ((0x00 == _command[3]) && (0x01 == _command[4]) && (0x30 == _command[5]) && (0x10 == _command[6]))
    {

	}
    else if ((0x00 == _command[3]) && (0x01 == _command[4]) && (0x30 == _command[5]) && (0x11 == _command[6]))
    {
        getMotorByAddress(static_cast<MotorAddress>(_command[7]))->setInquireResponseFlag(Component::FLAG_IDLE);
	}
    else if ((0x00 == _command[3]) && (0x01 == _command[4]) && (0x30 == _command[5]) && (0x12 == _command[6]))
    {
        getMotorByAddress(static_cast<MotorAddress>(_command[7]))->setMoveResponseFlag(Component::FLAG_IDLE);
    }
    else if ((0x00 == _command[3]) && (0x01 == _command[4]) && (0x30 == _command[5]) && (0x13 == _command[6]))
    {
        getMotorByAddress(static_cast<MotorAddress>(_command[7]))->setMoveResponseFlag(Component::FLAG_IDLE);
	}
    else if ((0x00 == _command[3]) && (0x01 == _command[4]) && (0x30 == _command[5]) && (0x14 == _command[6]))
    {
        getMotorByAddress(static_cast<MotorAddress>(_command[7]))->setMoveResponseFlag(Component::FLAG_IDLE);
	}
    else if ((0x00 == _command[3]) && (0x01 == _command[4]) && (0x30 == _command[5]) && (0x15 == _command[6]))
    {
        getMotorByAddress(static_cast<MotorAddress>(_command[7]))->setMoveResponseFlag(Component::FLAG_IDLE);
    }
    else if ((0x00 == _command[3]) && (0x01 == _command[4]) && (0x30 == _command[5]) && (0x16 == _command[6]))
    {
        getMotorByAddress(static_cast<MotorAddress>(_command[7]))->setInquireResponseFlag(Component::FLAG_IDLE);
	}
    else if ((0x00 == _command[3]) && (0x01 == _command[4]) && (0x30 == _command[5]) && (0x17 == _command[6]))
    {
        getEncoderByAddress(static_cast<EncoderAddress>(_command[7]))->setInquireResponseFlag(Component::FLAG_IDLE);
	}
    else if ((0x00 == _command[3]) && (0x01 == _command[4]) && (0x30 == _command[5]) && (0x18 == _command[6]))
    {
        getSampleArm()->setInquireResponseFlag(Component::FLAG_IDLE);
	}
    else if ((0x00 == _command[3]) && (0x01 == _command[4]) && (0x30 == _command[5]) && (0x19 == _command[6]))
    {
        get_main_controller()->setInquireResponseFlag(Component::FLAG_IDLE);
	}
    else if ((0x00 == _command[3]) && (0x01 == _command[4]) && (0x30 == _command[5]) && (0x20 == _command[6]))
    {
        getSampleArm()->setInquireResponseFlag(Component::FLAG_IDLE);
	}
    else if ((0x00 == _command[3]) && (0x01 == _command[4]) && (0x30 == _command[5]) && (0x21 == _command[6]))
    {
        getSampleArm()->setInquireResponseFlag(Component::FLAG_IDLE);
	}
    else if ((0x00 == _command[3]) && (0x01 == _command[4]) && (0x30 == _command[5]) &&(0x22 == _command[6]))
    {
        getSampleArm()->setInquireResponseFlag(Component::FLAG_IDLE);
	}
    else if ((0x00 == _command[3]) && (0x01 == _command[4]) && (0x30 == _command[5]) &&(0x23 == _command[6]))
    {
        getSampleArm()->setInquireResponseFlag(Component::FLAG_IDLE);
	}
    else if ((0x00 == _command[3]) && (0x01 == _command[4]) && (0x30 == _command[5]) && (0x24 == _command[6]))
    {
        getSampleArm()->setInquireResponseFlag(Component::FLAG_IDLE);
	}
    else if ((0x00 == _command[3]) && (0x01 == _command[4]) && (0x30 == _command[5]) && (0x25 == _command[6]))
    {
        getMotorByAddress(static_cast<MotorAddress>(_command[7]))->setInquireResponseFlag(Component::FLAG_IDLE);
	}
    else if ((0x00 == _command[3]) && (0x01 == _command[4]) && (0x30 == _command[5]) && (0x26 == _command[6]))
    {
        getSampleArm()->setInquireResponseFlag(Component::FLAG_IDLE);
	}
    else if ((0x00 == _command[3]) && (0x01 == _command[4]) && (0x30 == _command[5]) && (0x27 == _command[6]))
    {
        getRockBed()->setInquireResponseFlag(Component::FLAG_IDLE);
    }
    else if ((0x00 == _command[3]) && (0x01 == _command[4]) && (0x30 == _command[5]) && (0x28 == _command[6]))
    {
        getRockBed()->setInquireResponseFlag(Component::FLAG_IDLE);
    }
	else
	{
        eLog("收到未解析到的指令:{}", QByteArray(reinterpret_cast<char *>(_command),static_cast<int>(_size)).toHex(), _size);
		return 0;
	}
    return 0;
}

int Components::analysis_report_command()
{
	if ((0x00 == _command[3]) && (0x01 == _command[4]) && (0x40 == _command[5]) && (0x01 == _command[6]))
	{
		unsigned int warning_code = _command[7];
		warning_code <<= 8;
		warning_code |= _command[8];
		if (WARNING_LOAD_TONG_PUT_TUBE_IN_TIMEOUT == warning_code)
		{
		}		
		else
		{
			eLog("收到未知警报上报指令");
			return(-1);
		}
		dLog("收到{}主动上报警报信息", warning_code);
		return(0);
	}
	else
	{
        eLog("收到非法指令,cmd:{}", QByteArray(reinterpret_cast<char *>(_command),static_cast<int>(_size)).toHex());
		return(-2);
	}
}

void Components::commandArrived(uint size)
{
    std::thread th([&size, this]()
    {
		QByteArray data = nullptr;
		while (!(data = _reciveCmd->getCommandData()).isNull())
		{
			analysis(data, size);

            if(getCmdFun() != nullptr)
                getCmdFun()(data);
		}
	});
	th.detach();
}
