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
#include "../Include/BLL/baseSet/SystemSetBLL.h"
#include "../Include/Model/baseSet/SystemSetModel.h"
#include "../Include/Utilities/async_task.h"
#include "ObjectInfo.h"
#include <QQueue>
#include <QtMath>
#include <QDebug>

#define LUMINOUS_PROPORTIONALITY_COEFFICIENT 1.0
#define NEEDLE_BLOCKING_DETECTION 1

QMap<int,QString> Components::_alphabetMap{{0,"A"},{1,"A"},{2,"B"},{3,"C"},{4,"D"},{5,"E"},{6,"F"},{7,"G"},{8,"H"},
                                           {9,"I"},{10,"J"},{11,"K"},{12,"L"},{13,"M"},{14,"N"},{15,"O"},{16,"P"},
                                           {17,"Q"},{18,"R"},{19,"S"},{20,"T"},{21,"U"},{22,"V"},{23,"W"},{24,"X"},
                                           {25,"Y"},{26,"Z"}
                                          };
QMutex Components::_lock;
Components::Components(QObject *parent) :QObject(parent)
  , _valveVect{}
  , _mainctroller(new MainController(this))
  , _camera(new Camera(this))
  , _sensor(new Sensor(this))
  , _motorVect{}
  , _buzzle(new Buzzle(this))
  , _temperature(new Temperature(this))
  , _lightVect{}
  , _encoderVect{}
  , _rockBed(new RockBed(this))
  , _fan(new Fan(this))
  , _scaner(new Scaner(this))
  , _sampleArm(new SampleArm(this))
  , _liquid(new Liquid(this))
  , _command(nullptr)
  , _size(0)
  , _cmdFun(nullptr)
  , _warnFun(nullptr)
  ,_isRestart(false)
  ,_isPause(false)
  ,_portCom("")
{
	AsyncTask::start(7);
	_reciveCmd = AnalysisReciveCmd::instance();
    initValve();
    initMotor();
    initLight();
    initEncoder();
	_reciveCmd->setCmdArrivedFun(std::bind(&Components::commandArrived, this, std::placeholders::_1));

	/*
	QByteArray recData{};
	auto strToByteArrary = [&recData](QString recStr)
	{
		recData.clear();
		for (int i = 0; i < recStr.length(); i += 2)
		{
			bool b(true);
			uchar ch{ static_cast<uchar>(recStr.mid(i,2).toUShort(&b,16)) };
			recData.push_back(ch);
		}
	};
	QString recStr("7eb5160001100200006095083e083a084200018c73000082bc6116");
    strToByteArrary(recStr);
	analysis(recData, recData.size());
	*/
}

Components *Components::instance()
{
	return Singleton<Components>::instance();
}

Components::~Components()
{
	if (_command != nullptr)
	{
		delete[] _command;
		_command = nullptr;
	}
}

Components::PValve Components::getValveByAddress(ValveAddress addr)
{
NextLabel:
    for(auto pm:_valveVect)
    {
        if(pm.isNull())
        {
            eLog("the memery is error");
            initValve();
            goto NextLabel;
        }

        if(pm->getAddress()==addr)
            return pm;
    }
    eLog("value is not exist,{}",addr);
    return nullptr;
}

Components::PMainController Components::get_main_controller()
{
    return _mainctroller;
}

Components::PCamera Components::getCamera()
{
    return  _camera;
}

Components::PSensor Components::getSensor()
{
    return  _sensor;
}

Components::PMotor Components::getMotorByAddress(MotorAddress address)
{
NextLable:
    for(auto pm:_motorVect)
    {
        if(pm.isNull())
        {
            initMotor();
            eLog("memory is error");
            goto NextLable;
        }
        if(pm->getAddress()==address)
            return pm;
    }
    eLog("motor is not exist,address:{}",address);
    return nullptr;
}

Components::PBuzzle Components::getBuzzle()
{
    return _buzzle;
}

Components::PTemperature Components::getTemperature()
{
    return _temperature;
}

Components::PLight Components::getLightByAddress(Components::LightAddress address)
{
    NextLable:
    for(auto pm:_lightVect)
    {
        if(pm.isNull())
        {
            initLight();
            eLog("memory is error");
            goto NextLable;
        }
        if(pm->address()==address)
            return pm;
    }
    eLog("Light is not exist,address:{}",address);
    return nullptr;
}

Components::PEncoder Components::getEncoderByAddress(Components::EncoderAddress address)
{
NextLable:
    for(auto pm:_encoderVect)
    {
        if(pm.isNull())
        {
            initEncoder();
            eLog("memory is error");
            goto NextLable;
        }
        if(pm->getAddress()==address)
            return pm;
    }
    eLog("encoder is not exist,address:{}",address);
    return nullptr;
}

Components::PRockBed Components::getRockBed()
{
    return _rockBed;
}

Components::PFan Components::getFan()
{
    return _fan;
}

Components::PScaner Components::getScaner()
{
    return _scaner;
}

Components::PSampleArm Components::getSampleArm()
{
    return _sampleArm;
}

Components::PLiquid Components::getLiquid()
{
    return  _liquid;
}

void Components::warnAlarm(const EAlarm level)
{
    auto sysPm{SystemSetBLL().getRowById(20001)};
    auto buzzleOpen(sysPm.isNull()?true:sysPm->getSaveSet()!=0);
    if(level==EError)
    {
        getLightByAddress(Component::LIGHT_WARNING)->lightControl(02);
        if(buzzleOpen)
            getBuzzle()->setBuzzleOnOff(Buzzle::STATE_ALARM1);
    }
    else if(level==EPause)
    {
        getLightByAddress(Component::LIGHT_WARNING)->lightControl(03);
        if(buzzleOpen)
            getBuzzle()->setBuzzleOnOff(Buzzle::STATE_ALARM2);
    }
}

void Components::setCmdFun(const funType &cmdFun)
{
    _cmdFun = cmdFun;
}

void Components::initValve()
{
    _valveVect.clear();
    for(int i=VALVESTART;i<=VALVECOUNT;i++)
    {
        if(i<=3)
        {
            PValve pm{new Valve(static_cast<ValveAddress>(i))};
            _valveVect.push_back(pm);
        }
        else
        {
            PValve pm{new Valve(static_cast<ValveAddress>(i+7))};
            _valveVect.push_back(pm);
        }
    }
}

void Components::initMotor()
{
    _motorVect.clear();
    for(int i=MOTORSTART;i<=MOTORCOUNT;i++)
    {
        PMotor pm{new Motor(static_cast<MotorAddress>(i))};
        _motorVect.push_back(pm);
    }
}

void Components::initLight()
{
    _lightVect.clear();
    for(int i=LIGHTSTART;i<LIGHTCOUNT;i++)
    {
        PLight pm{new Light(static_cast<LightAddress>(i))};
        _lightVect.push_back(pm);
    }
}

void Components::initEncoder()
{
    _encoderVect.clear();
    for(int i=ENCODERSTART;i<=ENCODERCOUNT;i++)
    {
        PEncoder pm{new Encoder(static_cast<EncoderAddress>(i))};
        _encoderVect.push_back(pm);
    }
}

Components::funType Components::getCmdFun() const
{
    return _cmdFun;
}

int Components::analysis(QByteArray cmdData, uint size)
{
    size = static_cast<uint>(cmdData.length());

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
        eLog("command error，size:{},cmd:{}", size, QByteArray(reinterpret_cast<char *>(_command),static_cast<int>(_size)).toHex());
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
        eLog("unknown command，cmd:{}", QByteArray(reinterpret_cast<char *>(_command),static_cast<int>(_size)).toHex());
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
        auto motor{getMotorByAddress(static_cast<MotorAddress>(_command[7]))};
        if(motor.isNull())
        {
            eLog("motor not exist,address:{}",_command[7]);
            return -1;
        }
        getMotorByAddress(static_cast<MotorAddress>(_command[7]))->setComResponseFlag(Component::FLAG_IDLE);
	}
	else if ((0x00 == _command[3]) && (0x01 == _command[4]) && (0x10 == _command[5]) && (0x02 == _command[6]))
    {
        int steps=0;
        fun(steps,7);

        getSampleArm()->setSampleSuckPos(steps);
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
            eLog("error command,_command:{}", _command);
            return(-1);
        }
        QString barcode("");
        for (int index = 0; index < barcode_size; ++index)
        {
            barcode.append(_command[7 + index]);
        }

        /*
        if(barcode.length()>=2)
        {
            barcode = barcode.mid(1);
            barcode = barcode.left(barcode.length() - 1);
        }
        */
        getScaner()->setReadCode(barcode);
	}
	else if ((0x00 == _command[3]) && (0x01 == _command[4]) && (0x10 == _command[5]) && (0x06 == _command[6]))
    {
        const int barcode_size = static_cast<int>(_command[2]) - 4;
        if (barcode_size < 0)
        {
            eLog("error command,_command:{}", _command);
            return(-1);
        }
        QString barcode("");
        for (int index = 0; index < barcode_size; ++index)
        {
            barcode.append(_command[7 + index]);
        }
        /*
        if(barcode.length()>=2)
        {
            barcode = barcode.mid(1);
            barcode = barcode.left(barcode.length() - 1);
        }
        */
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
            eLog("error command,_command:{}", _command);
            return(-1);
        }
        QString barcode("");
        for (int index = 0; index < barcode_size; ++index)
        {
            barcode.append(_command[7 + index]);
        }
        /*
        if(barcode.length()>=2)
        {
            barcode = barcode.mid(1);
            barcode = barcode.left(barcode.length() - 1);
        }
        */
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

    else if ((0x00 == _command[3]) && (0x01 == _command[4]) && (0x10 == _command[5]) && (0x18 == _command[6]))
    {
        auto light{getLightByAddress(static_cast<LightAddress>(_command[7]))};
        if(light.isNull())
        {
            eLog("light not exist,address:{}",_command[7]);
            return -1;
        }
        light->setInquireResponseFlag(Component::FLAG_IDLE);
    }

    else if ((0x00 == _command[3]) && (0x01 == _command[4]) && (0x10 == _command[5]) && (0x19 == _command[6]))
    {
        getBuzzle()->setInquireResponseFlag(Component::FLAG_IDLE);
    }
    else if ((0x00 == _command[3]) && (0x01 == _command[4]) && (0x10 == _command[5]) && (0x20 == _command[6]))
    {
        int steps=0;
        fun(steps,7);
        getSampleArm()->setSampleSuckPos(steps);
        getSampleArm()->setComResponseFlag(Component::FLAG_IDLE);
    }
	else
	{
        eLog("error command,_command:{}", QByteArray(reinterpret_cast<char *>(_command), static_cast<int>(_size)).toHex());
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
        ushort year{_command[7]};
        QString yearStr{("00"+QString::number(year)).right(2)};
        QString machine_no{yearStr};

        ushort month{_command[8]};
        QString monthStr{("00"+QString::number(month)).right(2)};
        machine_no+=monthStr;

        ushort machineType{0b11110000};
        machineType &=_command[9];
        machineType>>=4;
        machine_no+=QString::number(machineType);

        ushort serialNo{0b00001111};
        serialNo &=_command[9];
        serialNo<<=8;
        serialNo |= _command[10];
        QString serialNoStr{("000"+QString::number(serialNo)).right(3)};
        machine_no += serialNoStr;
        get_main_controller()->set_machine_no(machine_no);


        QString letter1("");
        QString letter2("");
        /*
        uchar index(static_cast<ushort>(_command[11])>26?26:_command[11]);
        letter1=_alphabetMap[index];

        index=(static_cast<ushort>(_command[12])>26?26:_command[12]);
        letter2=_alphabetMap[index];
        */

        ushort data=0;
        ushortFun(data,11);
        auto index1{data/27};
        auto index2{data%27};
        index1=(index1>26?26:index1);
        index2=(index2>26?26:index2);
        letter1=_alphabetMap[index1];
        letter2=_alphabetMap[index2];

        ushort PCBNum(0);
        PCBNum|= _command[13];
        PCBNum <<= 8;
        PCBNum |= _command[14];
        PCBNum=PCBNum>999?999:PCBNum;
        QString strPCBNum{("000"+QString::number(PCBNum,16)).right(3)};
        QString PCB_version{letter1+letter2+strPCBNum};

        get_main_controller()->set_MCB_Version(PCB_version);
        get_main_controller()->setInquireResponseFlag(Component::FLAG_IDLE);
    }
    else if ((0x00 == _command[3]) && (0x01 == _command[4]) && (0x20 == _command[5]) && (0x03 == _command[6]))
    {
		uint tmp = 0;
		ufun(tmp, 7);
		float *temperature = (float*)&tmp;
        getTemperature()->setDSTTemperature(*temperature);
    }
    else if ((0x00 == _command[3]) && (0x01 == _command[4]) && (0x20 == _command[5]) && (0x04 == _command[6]))
    {
		uint tmp = 0;
		ufun(tmp, 7);
        float *temperature = (float*)&tmp;
        getTemperature()->setRealTimeTemperature(*temperature);
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
        if(_command[8]==0)
        {
            if(_command[9]==0)
                motor->setLeftPhotoelectricFlag(Component::FLAG_EMPTY);
            else
                motor->setLeftPhotoelectricFlag(Component::FLAG_USED);
        }
        else
        {
            if(_command[9]==0)
                motor->setRightPhotoelectricFlag(Component::FLAG_EMPTY);
            else
                motor->setRightPhotoelectricFlag(Component::FLAG_USED);
        }
	}
    else if ((0x00 == _command[3]) && (0x01 == _command[4]) && (0x20 == _command[5]) && (0x07 == _command[6]))
    {
        ushort data=0;
        ushortFun(data,7);
        getSensor()->setSensorData(data);
        getSensor()->setInquireResponseFlag(Component::FLAG_IDLE);
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
        fun(para.cupSpace,7);
        fun(para.rackSSpace,11);
        fun(para.rackLSpace,15);
        fun(para.rackPos,19);
        fun(para.rectSlotSpace,23);
        fun(para.rectDiscSpace,27);
        fun(para.sNeedleSpitXPos,31);
        fun(para.suckLiquidPos,35);
        fun(para.photographPos,39);
        fun(para.scanerXPos,43);
        fun(para.scanerChangePos,47);
        fun(para.cameraCalibratePos,51);
        fun(para.liquidDetectCalibratePos,55);
        fun(para.scanerSelfCheckPos,59);
        fun(para.scanerXPos2nd,63);
        getSampleArm()->setXMotorPara(para);
	}
    else if ((0x00 == _command[3]) && (0x01 == _command[4]) && (0x20 == _command[5]) && (0x16 == _command[6]))
    {
        SampleArm::YMotorPara para;
        fun(para.fstRackPos,7);
        fun(para.scdRackPos,11);
        fun(para.needleWashPos,15);
        fun(para.startDrawWastePos,19);
        fun(para.spitYPos,23);
        fun(para.startWasteSlotPos,27);
        getSampleArm()->setYMotorPara(para);
	}
    else if ((0x00 == _command[3]) && (0x01 == _command[4]) && (0x20 == _command[5]) && (0x17 == _command[6]))
    {
        SampleArm::ZMotorPara para;
        fun(para.washHeight,7);
        fun(para.standartCupHeight,11);
        fun(para.bloodingCupHeight,15);
        fun(para.microCupHeight,19);
        fun(para.startDetectLevelHeight,23);
        fun(para.spitHeight,27);
        fun(para.detectLevel2ndDescendHeight,31);
        fun(para.wasteSlotHeight,35);
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
        int steps(0);
        fun(steps,8);
        getLiquid()->set50ulSteps(steps);
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
        eLog("error command,cmd:{}", QByteArray(reinterpret_cast<char *>(_command),static_cast<int>(_size)).toHex());
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
        auto motor{getMotorByAddress(static_cast<MotorAddress>(_command[7]))};
        if(!motor.isNull())
            motor->setInquireResponseFlag(Component::FLAG_IDLE);
        //getLightByAddress(static_cast<LightAddress>(_command[7]))->setInquireResponseFlag(Component::FLAG_IDLE);
        getLiquid()->setInquireResponseFlag(Component::FLAG_IDLE);
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
        getLiquid()->setInquireResponseFlag(Component::FLAG_IDLE);
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
        eLog("error command:{}", QByteArray(reinterpret_cast<char *>(_command),static_cast<int>(_size)).toHex(), _size);
		return 0;
	}
    return 0;
}

int Components::analysis_report_command()
{
	if ((0x00 == _command[3]) && (0x01 == _command[4]) && (0x40 == _command[5]) && (0x01 == _command[6]))
	{
        int level{_command[8]};
        int warning_code { _command[9]};
        warning_code <<= 8;
        warning_code |= _command[10];
        if(_warnFun!=nullptr)
            _warnFun(warning_code);
        if(level==0xFF || level == 0xE0)
            return 0;

        QString warnCodeStr{"0X"+QString::number(warning_code,16).toUpper()};
        if(level==01)
        {
            eLog("receive stop machine error,warnCode:0x{}!",warnCodeStr.toStdString());
            InstrumentStateModel::instance()->setMachineState(InstrumentStateModel::enumError);

            return 0;
        }
        else if(level==02)
        {
            //setIsPause(true);
        }
        //warnAlarm(EPause);
		return(0);
	}
	else
	{
        return -2;
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

void Components::setWarnFun(const funWarn &fun)
{
    _warnFun = fun;
}


bool Components::getIsPause() const
{
    QMutexLocker locker(&_lock);
    return _isPause;
}

void Components::setIsPause(bool isPause)
{
    QMutexLocker locker(&_lock);
    _isPause = isPause;
}

bool Components::getIsRestart() const
{
    QMutexLocker locker(&_lock);
    return _isRestart;
}

void Components::setIsRestart(bool isRestart)
{
    QMutexLocker locker(&_lock);
    dLog("set machine restart");
    _isRestart = isRestart;
}

