#include "GlobalData.h"
#include "../Include/Model/user/UserGroupModel.h"
#include "../Include/Model/user/UserModel.h"
#include "../Include/BLL/comm/GetLanguageClsBLL.h"
#include "../model/GetLanguageCls.h"
#include "../Include/Model/baseSet/SystemSetModel.h"
#include "../Include/BLL/baseSet/SystemSetBLL.h"
#include "../Include/Utilities/log.h"


QMap<ushort,QString> GlobalData::_mapSampleType({
                                                    {1, tr("血清/血浆")}
                                                });

QMap<int,QString> GlobalData::_mapSampleCupType({
                                                       {0, tr("标准杯")},
                                                       {1, tr("采血管")},
                                                       {2, tr("微量杯")}
                                                   });


QMap<int, QString> GlobalData::_mapSexType({
                                                       {0, tr("男")},
                                                       {1, tr("女")}});


QMap<ushort,QString>GlobalData::_mapClinicType({
                                                   {1, tr("常规")},
                                                   {2, tr("急诊")}/*,
                                                   {3, tr("定标")},
                                                   {4, tr("质控")}*/
                                               });

QMap<ushort,QString>GlobalData::_mapSampleState({
													{0,tr("未保存")},
                                                    {1, tr("保存")},
                                                    {2, tr("待测")},
                                                    {3, tr("测试")},
                                                    {4, tr("完成")},
                                                    {5, tr("结束")}
                                                });

QMap<ushort,QString>GlobalData::_mapMechanism({
                                                  {1, tr("加样机构")},
                                                  {2, tr("试剂机构")},
                                                  {3, tr("孵育机构")},
                                                  {4, tr("清洗机构")},
                                                  {5, tr("加底物机构")},
                                                  {6, tr("检测机构")}
                                              });

QMap<ushort,QString>GlobalData::_mapTestState({
												  {0,tr("未保存")},
                                                  {1,tr("保存")},
                                                  {2,tr("待测")},
                                                  {3,tr("测试")},
                                                  {4,tr("完成")},
                                                  {5,tr("失败")},
                                                  {6,tr("撤销")},
                                                  {7,tr("终止")},
                                                  {8,tr("屏蔽")}
                                              });

QMap<ushort,QString> GlobalData::_mapIsUpload({
                                                 {0,tr("未上传")},
                                                 {1,tr("已上传")}
                                              });

GlobalData::UGStuct GlobalData::_loginUser;
QString GlobalData::_exePath("");
QString GlobalData::_LoginName("");
QString GlobalData::_UserType("");
QString GlobalData::_g_language_type("");
QString GlobalData::_propertyName("pumpState");
TcpClient *GlobalData::m_tcpClient(nullptr);
GlobalData::GlobalData()
{   
}

QMap<ushort, QString> GlobalData::mapSampleType()
{
    return _mapSampleType;
}

QMap<int, QString> GlobalData::mapSampleCupType()
{
    return _mapSampleCupType;
}

void GlobalData::setMapSampleCupType(QMap<int, QString> data_map)
{
	_mapSampleCupType = data_map;
}

void GlobalData::setMapSexType(QMap<int, QString> data_map)
{
	_mapSexType = data_map;
}


QMap<int, QString>  GlobalData::mapSexType()
{
	return _mapSexType;
}

QMap<ushort, QString> GlobalData::mapClinicType()
{
    return _mapClinicType;
}

QMap<ushort, QString> GlobalData::mapSampleState()
{
    return _mapSampleState;
}

void GlobalData::setMapMechanism(const QMap<ushort, QString> &mapMechanism)
{
    _mapMechanism = mapMechanism;
}

QMap<ushort, QString> GlobalData::mapTestState()
{
    return _mapTestState;
}

QMap<ushort, QString> GlobalData::mapIsUpload()
{
    return _mapIsUpload;
}

GlobalData::UGStuct GlobalData::loginUser()
{
    return _loginUser;
}

void GlobalData::setLoginUser(const UGStuct &loginUser)
{
    _loginUser = loginUser;
}



QString GlobalData::getExePath()
{
    return _exePath;
}

void GlobalData::setExePath(const QString &exePath)
{
    _exePath = exePath;
}

QString GlobalData::converRGB2HexStr(QColor rgb)
{
    QString redStr = QString("%1").arg(rgb.red(),2,16,QChar('0'));
    QString greenStr = QString("%1").arg(rgb.green(),2,16,QChar('0'));
    QString blueStr = QString("%1").arg(rgb.blue(),2,16,QChar('0'));
    QString hexStr = "#"+redStr+greenStr+blueStr;
    return hexStr;
}

QByteArray GlobalData::getPropertyName()
{
    return _propertyName.toLocal8Bit();
}

QString GlobalData::getUserName()
{
    if(_loginUser.pUser==nullptr)
        return "";
    if(!_loginUser.pUser->getShowName().isEmpty())
        return _loginUser.pUser->getShowName();
    return _loginUser.pUser->getLoginName();
}

QString GlobalData::getGroupName()
{
    if(_loginUser.pGroup==nullptr)
        return "";
    return _loginUser.pGroup->getGroupName();
}

uint GlobalData::getGruopId()
{
    //if(_loginUser.pGroup==nullptr)
    //    return 0;
    //return _loginUser.pGroup->getID();
	return _UserType.toInt();
}

QString GlobalData::LoadLanguageInfo(QString language_type,QString language_code)
{
	QString str = "";
	GetLanguageCls  language_info ;
	if (language_type != "")
	{
		language_info.LoadLanguageInfoList(language_type.toInt());
		str = language_info.GetLanguagInfo(language_code);
	}
	return str;
}

QString GlobalData::LoadLanguageInfo(QString language_code)
{
    return GetLanguageClsBLL::getlangValue(language_code);
}

QMap<ushort, QString> GlobalData::getMapMechanism()
{
    return _mapMechanism;
}

QString GlobalData::getLoginName1()
{
	return _LoginName;
}

void GlobalData::setLoginName1(const QString &user_name)
{
	_LoginName = user_name;
}

void GlobalData::setGroupId(const QString &group_id)
{
	_UserType = group_id;
}

QString GlobalData::getLanguageType()
{
	return _g_language_type;
}

void GlobalData::setLanguageType(const QString &language_type)
{
	_g_language_type = language_type;
}

TcpClient *GlobalData::getTcpClient()
{
    return m_tcpClient;
}

void GlobalData::setTcpClient(TcpClient *tcpClient)
{
    m_tcpClient = tcpClient;
}

bool GlobalData::reconnect()
{
	auto lisStartPm{ SystemSetBLL().getRowById(9993) };
	bool isNeedConnect = (lisStartPm.isNull() ? false : lisStartPm->getSaveDes().toInt() > 0);
	if (m_tcpClient == nullptr)
	{
		eLog("tcpClient is nullptr");
		return isNeedConnect;
	}
    
    if (!isNeedConnect)
    {
        m_tcpClient->m_connectedState=false;
		return isNeedConnect;
    }
    m_tcpClient->reconnect();
	return isNeedConnect;
}



