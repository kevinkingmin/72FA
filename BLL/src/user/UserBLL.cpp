#include "UserBLL.h"
#include <QByteArray>
#include <QCryptographicHash>
#include "../Include/Model/user/UserGroupModel.h"
#include "../Include/Model/user/UserModel.h"
#include "../Include/DAO/user/UserDao.h"
#include "../Include/DAO/user/UserGroupDao.h"

UserBLL::UserBLL()
    :_privateKey("HUMANXingLiu")
{}

QVector<UserBLL::UserStruct> UserBLL::getAllRows()
{
    QVector<UserStruct>outVect;
    auto userVect=UserDao::instance()->getAllRows();
    auto groupVect=UserGroupDao::instance()->getAllRows();
    for(auto user:userVect)
    {
        if(user->getIsDelete())
            continue;
        UserStruct ugSt;
        ugSt.pUser=user;
        for(auto group:groupVect)
        {
            if(user->getGroupID()==group->getID())
            {
                ugSt.pGroup=group;
                outVect.push_back(ugSt);
                break;
            }
        }
        //outVect.push_back(ugSt);//这是无效的用户信息(无归属组)，可以不用。
    }
    return outVect;
}

UserBLL::UserStruct UserBLL::getRowById(uint id)
{
    auto vect=getAllRows();
    QVector<UserStruct>outVect;
    for(auto it:vect)
    {
        if(id==it.pUser->getID())
            return it;
    }
    return UserStruct();
}

UserBLL::UserStruct UserBLL::login(QString loginName, QString password)
{
    auto vect = getAllRows();
    UserStruct us;
    for(auto it:vect)
    {
        if(!loginName.compare(it.pUser->getLoginName(),Qt::CaseInsensitive))
        {
            us.pUser=it.pUser;
            us.pGroup=it.pGroup;
            break;
        }
    }

    if(us.pUser==nullptr || us.pGroup==nullptr)
    {
        us.pUser=nullptr;
        return  us;
    }
    QString strPas= getMd5Str(loginName,password);
    if(us.pUser->getUPassword()==strPas)
        return us;
    us.pUser=nullptr;
    us.pGroup=nullptr;
    return us;
}

bool UserBLL::deleteById(uint id)
{
    auto pm=getUserById(id);
    if(pm==nullptr)
        return false;
    pm->setIsDelete(true);
    return UserDao::instance()->updateModel(pm);
}

int UserBLL::updateByModel(UserBLL::ptrUser pm)
{
    if(pm==nullptr || pm->getID()<=0||pm->getGroupID()<=0)
        return -1;
    if(pm->getLoginName().isEmpty()||pm->getUPassword().isEmpty())
        return -2;
    QString pas=getMd5Str(pm->getLoginName(),pm->getUPassword());
    pm->setUPassword(pas);
    return UserDao::instance()->updateModel(pm)?1:-3;
}

int UserBLL::insertModel(UserBLL::ptrUser pm)
{
    if(pm==nullptr)
        return -1;
    if(pm->getLoginName().isEmpty()||pm->getUPassword().isEmpty()||pm->getGroupID()<=0)
        return -2;

    QString pas=getMd5Str(pm->getLoginName(),pm->getUPassword());
    pm->setUPassword(pas);
    return UserDao::instance()->insertModel(pm)?1:-3;
}

const QString UserBLL::getMd5Str(const QString loginName, const QString password)
{
    QString strPas= loginName+password+_privateKey;
    QByteArray bytePwd = strPas.toLatin1();
    QByteArray bytePwdMd5 = QCryptographicHash::hash(bytePwd, QCryptographicHash::Md5);
    return bytePwdMd5.toHex();
}

UserBLL::ptrUser UserBLL::getUserById(const uint id)
{
    auto vect = UserDao::instance()->getAllRows();
    for(auto it:vect)
    {
        if(it->getID()==id)
            return it;
    }
    return nullptr;
}
