#ifndef GLOBALDATA_H
#define GLOBALDATA_H
#include<QMap>
#include<QString>
#include <QObject>
#include <QSharedPointer>
#include<QColor>
#define FIRSTPAPERRACK "#C1C1C1"
#define SECONDPAPERRACK "#BAB7B7"
#define THIRDPAPERRACK "#A8A8A8"
#include "../Include/TCPClient/TcpClient.h"

class UserModel;
class UserGroupModel;
class GlobalData:public QObject
{
public:
    enum PumpPosState
    {
        enumEmpty=0,
        enumFlush=1,
        enumReady=2,
        enumDelay=3
    };

    GlobalData();
    using ptrUser=QSharedPointer<UserModel>;
    using ptrGroup=QSharedPointer<UserGroupModel>;

    struct UGStuct
    {
        ptrUser pUser;
        ptrGroup pGroup;
        UGStuct()
        {
            pUser=nullptr;
            pGroup=nullptr;
        }
    };

    static QMap<ushort, QString> mapSampleType();
    static QMap<int, QString> mapSampleCupType();
	static QMap<int, QString> mapSexType();
    static QMap<ushort, QString> mapClinicType();
    static QMap<ushort, QString> mapSampleState();
    static void setMapMechanism(const QMap<ushort, QString> &mapMechanism);
    static QMap<ushort, QString> getMapMechanism();
    static QMap<ushort,QString> mapTestState();
    static QMap<ushort,QString> mapIsUpload();

    static QString getUserName();
    static QString getGroupName();
    static uint getGruopId();
	static void setGroupId(const QString &exePath);
    static UGStuct loginUser();
    static void setLoginUser(const UGStuct &loginUser);
    static QString getExePath();
    static void setExePath(const QString &exePath);
	static void  setMapSampleCupType(QMap<int, QString> data_map);
	static void setMapSexType(QMap<int, QString> data_map);

	static QString getLoginName1();
	static void setLoginName1(const QString &exePath);

    static QString converRGB2HexStr(QColor rgb);
    static QByteArray getPropertyName();

	static QString LoadLanguageInfo(QString language_type, QString language_code);
    static QString LoadLanguageInfo(QString language_code);

	static QString getLanguageType();
	static void setLanguageType(const QString &language_type);

    static TcpClient *getTcpClient();
    static void setTcpClient(TcpClient *tcpClient);

    static bool reconnect();
private:
    static QMap<ushort,QString>_mapSampleType;
    static QMap<int,QString>_mapSampleCupType;

	static QMap<int, QString>_mapSexType;
	
    static QMap<ushort,QString>_mapClinicType;
    static QMap<ushort,QString>_mapSampleState;
    static QMap<ushort,QString>_mapMechanism;    
    static QMap<ushort,QString>_mapTestState;
    static QMap<ushort,QString>_mapIsUpload;
    static UGStuct _loginUser;
    static QString _exePath;
    static QString _propertyName;
	static QString _LoginName;
	static QString _UserType;
	static QString _g_language_type;
    static TcpClient *m_tcpClient;
};

#endif // GLOBALDATA_H
