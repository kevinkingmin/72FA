#ifndef ANALYSISRECIVECMD_H
#define ANALYSISRECIVECMD_H
#include <QObject>
#include <QQueue>
#include <QByteArray>
#include <QMutex>
#include <functional>
#include "../Include/Comm/singleton.h"
#include "src/instrument_global.h"
#include "src/Instrument.h"

class SerialPortDriver;

class INSTRUMENTSHARED_EXPORT AnalysisReciveCmd:public QObject
{
    Q_OBJECT
private:
	AnalysisReciveCmd(QObject *parent = nullptr);
	AnalysisReciveCmd(AnalysisReciveCmd &) = delete;
	AnalysisReciveCmd(AnalysisReciveCmd &&) = delete;
	AnalysisReciveCmd &operator=(const AnalysisReciveCmd&) = delete;
	AnalysisReciveCmd &operator=(AnalysisReciveCmd&&) = delete;
	friend Singleton<AnalysisReciveCmd>;
    
public:
	virtual ~AnalysisReciveCmd();
   QByteArray  getCommandData();
   void setCmdArrivedFun(const std::function<void(uint size)> &cmdArrivedFun);
   static AnalysisReciveCmd *instance();
   std::function<void (uint &size)> getCmdArrivedFun() const;

private:
   void analysisData(unsigned char data);
   void AddCommandData(QByteArray data, uint size);
   void enqueueCmd(QByteArray &data);
   int isValid(QByteArray command, unsigned char startBit, unsigned char endBit) const;
private:
    static QMutex _lock;
    QQueue<QByteArray>_commandData;
	std::function<void(uint &size)>_cmdArrivedFun;
    bool _cmdHandleFinish;
public slots:
      void receiveDatas(QByteArray data);
};

#endif // ANALYSISRECIVECMD_H
