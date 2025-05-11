#include "InstrumentStateModel.h"
#include "../Include/Comm/singleton.h"

InstrumentStateModel::~InstrumentStateModel()
{
}

InstrumentStateModel::InstrumentStateModel():_machineStates{}
{
    init();
}

void InstrumentStateModel::init()
{
    paraStrc mUnConn;
    mUnConn.state=enumUnConn;
    mUnConn.nameStr="通信失败";
    mUnConn.prioty=1;
    mUnConn.canInit=false;
    _machineStates.push_back(mUnConn);

    paraStrc mConn;
    mConn.state=enumConn;
    mConn.nameStr="通信成功";
    mConn.prioty=1;
    mConn.canInit=true;
    _machineStates.push_back(mConn);

    paraStrc mUnInit;
    mUnInit.state=enumUnInit;
    mUnInit.nameStr="未初始化";
    mUnInit.prioty=2;
    mUnInit.canInit=true;
    _machineStates.push_back(mUnInit);

    paraStrc mIniting;
    mIniting.state=enumIniting;
    mIniting.nameStr="初始化中";
    mIniting.prioty=2;
    mIniting.canInit=false;
    _machineStates.push_back(mIniting);

    paraStrc mRuning;
    mRuning.state=enumRuning;
    mRuning.nameStr="测试中";
    mRuning.prioty=2;
    mRuning.canInit=false;
	mRuning.canRun = true;
    _machineStates.push_back(mRuning);

    paraStrc mStandby;
    mStandby.state=enumStandby;
    mStandby.nameStr="待机状态";
    mStandby.prioty=2;
    mStandby.canInit=true;
	mStandby.canRun = true;
    _machineStates.push_back(mStandby);

    paraStrc mPause;
    mPause.state=enumPause;
    mPause.nameStr="暂停状态";
    mPause.prioty=2;
    mPause.canInit=false;
	mStandby.canRun = true;
    _machineStates.push_back(mPause);

    paraStrc mDormant;
    mDormant.state=enumDormant;
    mDormant.nameStr="休眠状态";
	mDormant.prioty = 2;
	mDormant.canInit = true;
	mDormant.canRun = true;
    _machineStates.push_back(mDormant);

    paraStrc mMaintain;
    mMaintain.state=enumMaintain;
    mMaintain.nameStr="维护状态";
    mMaintain.prioty=2;
	mMaintain.canInit = false;
    _machineStates.push_back(mMaintain);

    paraStrc mError;
    mError.state = enumError;
    mError.nameStr = "错误状态";
    mError.prioty = 2;
    mError.canInit=true;
    _machineStates.push_back(mError);

	paraStrc mCloseSoft;
	mCloseSoft.state = enumCloseSoft;
	mCloseSoft.nameStr = "关机状态";
	mCloseSoft.prioty = 2;
    mCloseSoft.canInit=false;
	_machineStates.push_back(mCloseSoft);
}

InstrumentStateModel::paraStrc InstrumentStateModel::getMachineState()
{
    paraStrc retValue;
    for(auto it:_machineStates)
    {
        if(it.isInState)
        {
            retValue=it;
            break;
        }
    }
    return retValue;
}

void InstrumentStateModel::setMachineState(InstrumentStateModel::enumState state)
{
    QVector<paraStrc>tempVect;
    int prioty=0;
    for(auto it : _machineStates)
    {
        if(it.isInState)
            tempVect.push_back(it);
        if(it.state==state)
            prioty=it.prioty;
    }

    if(tempVect.isEmpty())
    {
        for(auto &it : _machineStates)
        {
            if(it.state==state)
            {
                it.isInState=true;
                return;
            }
        }
    }

    auto lastIt=tempVect.last();
    if(lastIt.prioty<=prioty)
    {
        for(auto &m:_machineStates)
        {
            if(m.state==state)
            {
                m.isInState=true;
            }
            else
            {
                m.isInState=false;
            }
        }
    }
    else
    {
        for(auto &m:_machineStates)
        {
            if(lastIt.state==m.state)
                m.isInState=true;
            else
                m.isInState=false;
        }
    }
}

InstrumentStateModel *InstrumentStateModel::instance()
{
    return Singleton<InstrumentStateModel>::instance();
}

