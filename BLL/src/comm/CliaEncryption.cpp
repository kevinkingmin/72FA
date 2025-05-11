#include "CliaEncryption.h"
#include <QString>
const char CliaEncryption::_numTable[10]={'8','5','2','9','4','7','6','1','0','3'};
const char CliaEncryption::_ULetterTable[26]={
                                            'X','L','I','H','U','M','A','N','C',
                                            'K','F','O','D','R','J','P','G','B',
                                            'E','Z','T','W','Y','S','V','Q'};
const char CliaEncryption::_LLetterTable[26]={
                                            'h','u','m','a','n','x','l','i','t',
                                            'v','w','y','d','b','g','p','o','j',
                                            'z','c','q','f','s','k','e','r'};
const int CliaEncryption::_posTable[32]={
                                         20,21,6,25,16,18,0,4,11,17,26,12,31,2,3,30,
                                         29,23,1,10,28,27,13,14,9,24,15,7,22,5,8,19};
CliaEncryption::CliaEncryption()
{

}
//加密
int CliaEncryption::encrypt(QString &barcode)
{
    if(barcode.isNull() || barcode.length() != 32)
    {
        return(-1);
    }
    char data_t[32]={0};
    for(int i=0;i!=32;++i)
    {
        char charAt=barcode.at(i).toLatin1();
        if(charAt>='0'&&charAt<='9')
        {
            charAt=encryptNum(charAt);
        }
        else if(charAt>='A'&&charAt<='Z')
        {
            charAt=encryptUpperCase(charAt);
        }
        else if(charAt>='a'&&charAt<='z')
        {
            charAt=encryptLowerCase(charAt);
        }
        data_t[encryptPos(i)]=charAt;
    }
    barcode=QString::fromLocal8Bit(data_t,32);
    return(0);
}
//解密
int CliaEncryption::decrypt(QString &barcode)
{
    if(barcode.isNull()|| barcode.length()!=32)
    {
        return(-1);
    }
    char data_t[32]={0};
    for(int i=0;i!=32;++i)
    {
        char charAt=barcode.at(i).toLatin1();
        if(charAt>='0'&&charAt<='9')
        {
            charAt=decryptNum(charAt);
        }
        else if(charAt>='A'&&charAt<='Z')
        {
            charAt=decryptUpperCase(charAt);
        }
        else if(charAt>='a'&&charAt<='z')
        {
            charAt=decryptLowerCase(charAt);
        }
        data_t[decryptPos(i)]=charAt;
    }
    barcode=QString::fromLocal8Bit(data_t,32);
    return(0);
}

char CliaEncryption::encryptNum(const char num)
{
    assert(num>='0'&&num<='9');
    auto pos = QString(num).toInt();
    return(_numTable[pos]);
}

char CliaEncryption::decryptNum(const char num)
{
    assert(num>='0'&&num<='9');
    for(int i=0;i!=10;++i)
    {
        if(num==_numTable[i])//找到了相对应的数字
        {
            char ch=QString::number(i).toLocal8Bit()[0];
            return(ch);
        }
    }
    return(-1);
}

char CliaEncryption::encryptUpperCase(const char ch)
{
    assert(ch>='A'&&ch<='Z');
    const int i=static_cast<int>(ch-'A');
    return(_ULetterTable[i]);
}

char CliaEncryption::decryptUpperCase(const char ch)
{
    assert(ch>='A'&&ch<='Z');
    for(int i=0;i!=26;++i)
    {
        if(ch==_ULetterTable[i])
        {
            return('A'+static_cast<char>(i));
        }
    }
    return(-1);
}

char CliaEncryption::encryptLowerCase(const char ch)
{
    assert(ch>='a'&&ch<='z');
    const int i=static_cast<int>(ch-'a');
    return(_LLetterTable[i]);
}

char CliaEncryption::decryptLowerCase(const char ch)
{
    assert(ch>='a'&&ch<='z');
    for(int i=0;i!=26;++i)
    {
        if(ch==_LLetterTable[i])
        {
            return('a'+static_cast<char>(i));
        }
    }
    return(-1);
}

int CliaEncryption::encryptPos(const int pos)
{
    assert(pos>=0&&pos<32);
    return(_posTable[pos]);
}

int CliaEncryption::decryptPos(const int pos)
{
    assert(pos>=0&&pos<32);
    for(int i=0;i!=32;++i)
    {
        if(pos==_posTable[i])
        {
            return(i);
        }
    }
    return(-1);
}
