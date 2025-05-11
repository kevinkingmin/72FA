#include "AnalysisReciveCmd.h"
#include <functional>
#include <QThread>
#include "Command.h"
#include "../Include/SerialPortDriver/SerialPortDriver.h"
#include "src/local_log.h"

QMutex AnalysisReciveCmd::_lock;
AnalysisReciveCmd::AnalysisReciveCmd(QObject *parent) :QObject(parent)
, _commandData()
, _cmdArrivedFun(nullptr)
  ,_cmdHandleFinish(true)
{	
    //_port->setRecieveFun(std::bind(&AnalysisReciveCmd::receiveDatas, this, std::placeholders::_1));
    //connect(Instrument::instance(),&Instrument::onSocketDataReceive, this,&AnalysisReciveCmd::receiveDatas);
}

AnalysisReciveCmd::~AnalysisReciveCmd()
{
}

void AnalysisReciveCmd::analysisData(unsigned char data)
{
	static std::vector<unsigned char> command_container;
	if (Command::START_BIT == data)
	{
        if (command_container.empty())
		{
			command_container.push_back(data);
			return;
		}

        if (Command::START_BIT == command_container[0])
		{
            if (command_container.size() <= 3)
			{
				command_container.push_back(data);
				return;
			}
			if (command_container.size() >= static_cast<unsigned int>(command_container[2]) + 4)
			{
                command_container.clear();
				command_container.push_back(data);
				return;
			}
			command_container.push_back(data);
			return;
        }
        command_container.clear();
        command_container.push_back(data);
        return;
	}
    else if (Command::END_BIT == data)
	{
		if (command_container.empty())
		{
			return;
		}
		if (Command::START_BIT == command_container[0])
		{
			if (command_container.size() < 3)
			{
				command_container.push_back(data);
				return;
			}
			if (command_container.size() < (static_cast<unsigned int>(command_container[2]) + 4))
			{
				command_container.push_back(data);
				return;
			}
			else if (command_container.size() == (static_cast<unsigned int>(command_container[2]) + 4))
			{
				command_container.push_back(data);
                auto usize=static_cast<int>(command_container.size());
                auto data = QByteArray(reinterpret_cast<char *>(command_container.data()),usize);
                AddCommandData(data, static_cast<uint>(usize));
				command_container.clear();
				return;
			}
			command_container.clear();
			return;
		}
		command_container.clear();
		return;
	}
	if (command_container.empty())
	{
		return;
	}
	if (Command::START_BIT == command_container[0])
	{
		if (command_container.size() < 3)
		{
			command_container.push_back(data);
			return;
		}
		else if (command_container.size() <= (static_cast<unsigned int>(command_container[2]) + 3))
		{
			command_container.push_back(data);
			return;
		}
		command_container.clear();
		return;
	}
	command_container.clear();
	return;
}
void AnalysisReciveCmd::AddCommandData(QByteArray data, uint size)
{
	if (data == nullptr)
		return;

	enqueueCmd(data);
    if (getCmdArrivedFun() != nullptr && _cmdHandleFinish)
        getCmdArrivedFun()(size);
}
void AnalysisReciveCmd::enqueueCmd(QByteArray &data)
{
	QMutexLocker locker(&_lock);
    _commandData.enqueue(data);
}

int AnalysisReciveCmd::isValid(QByteArray command, unsigned char startBit, unsigned char endBit) const
{
    int size = command.size();
    if (size != 1024)
        return -1;

    if (startBit != command[0])
        return -2;

    if (static_cast<unsigned char>(command[2]) != size - 5)
        return -3;

    if (endBit != command[size - 1])
        return -4;

    unsigned char parityBit = 0;
    for (int index = 0; index < size - 2; ++index) {
        parityBit += command[index];
    }

    if (static_cast<unsigned char>(command[size - 2]) != parityBit)
    {
        return -5;
    }
    return 0;
}

std::function<void (uint &size)> AnalysisReciveCmd::getCmdArrivedFun() const
{
    return _cmdArrivedFun;
}
QByteArray AnalysisReciveCmd::getCommandData()
{
    QMutexLocker locker(&_lock);
    if (!_commandData.isEmpty())
    {
        _cmdHandleFinish=false;
        return _commandData.dequeue();
    }
    _cmdHandleFinish=true;
	return nullptr;
}
void AnalysisReciveCmd::setCmdArrivedFun(const std::function<void(uint size)>& cmdArrivedFun)
{
	_cmdArrivedFun = cmdArrivedFun;
}

AnalysisReciveCmd * AnalysisReciveCmd::instance()
{
	return Singleton<AnalysisReciveCmd>::instance();
}

void AnalysisReciveCmd::receiveDatas(QByteArray datas)
{
    //
    if (isValid(datas, Command::START_BIT, Command::END_BIT) >= 0)
    {
        AddCommandData(datas, static_cast<uint>(datas.size()));
        return;
    }

    for (auto it : datas)
    {
        analysisData(static_cast<unsigned char>(it));
    }
}
