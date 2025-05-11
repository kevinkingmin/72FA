#ifndef CLIAENCRYPTION_H
#define CLIAENCRYPTION_H
#include "../bll.h"

class BLLSHARED_EXPORT CliaEncryption
{
public:
    CliaEncryption();
public:
    static int encrypt(QString &barcode);
    static int decrypt(QString &barcode);
private:
    static char encryptNum(const char num);
    static char decryptNum(const char num);
    static char encryptUpperCase(const char ch);
    static char decryptUpperCase(const char ch);
    static char encryptLowerCase(const char ch);
    static char decryptLowerCase(const char ch);
    static int encryptPos(const int pos);
    static int decryptPos(const int pos);
private:
    static const char _numTable[10];
    static const char _ULetterTable[26];
    static const char _LLetterTable[26];
    static const int _posTable[32];
};

#endif // CLIAENCRYPTION_H
