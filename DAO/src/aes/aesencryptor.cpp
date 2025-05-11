
#include "aesencryptor.h"
#include "aes.h"
#include <fstream>
#include <iostream>

using namespace std;
AesEncryptor::AesEncryptor(unsigned char* key)
{
    m_pEncryptor = new AES(key);
}


AesEncryptor::~AesEncryptor(void)
{
    delete m_pEncryptor;
}

void AesEncryptor::Byte2Hex(const unsigned char* src, int len, char* dest) {
    if (nullptr == src || nullptr == dest){
        return;
    }
    for (int i=0; i<len; ++i) {
        sprintf(dest + i * 2,"%02X", src[i]);
    }
}

void AesEncryptor::Hex2Byte(const char* src, int len, unsigned char* dest) {
    if (nullptr == src || nullptr == dest){
        return;
    }
    int length = len / 2;
    for (int i=0; i<length; ++i) {
        dest[i] = Char2Int(src[i * 2]) * 16 + Char2Int(src[i * 2 + 1]);
    }
}

int AesEncryptor::Char2Int(char c) {
    if ('0' <= c && c <= '9') {
        return (c - '0');
    }
    else if ('a' <= c && c<= 'f') {
        return (c - 'a' + 10);
    }
    else if ('A' <= c && c<= 'F') {
        return (c - 'A' + 10);
    }
    return -1;
}

string AesEncryptor::EncryptString(string strInfor) {
    if (16 < strInfor.length()){
        return "";
    }
    int nLength = strInfor.length();
    int spaceLength = 16 - (nLength % 16);
    int pBufferLength = nLength + spaceLength;
    unsigned char* pBuffer = new unsigned char[pBufferLength];
    memset(pBuffer, '\0', pBufferLength);
    memcpy_s(pBuffer, pBufferLength, strInfor.c_str(), nLength);
    m_pEncryptor->Cipher(pBuffer, pBufferLength);

    // 这里需要把得到的字符数组转换成十六进制字符串
    char* pOut = new char[2*pBufferLength+1];
    memset(pOut, '\0', (2*pBufferLength));
    Byte2Hex(pBuffer, pBufferLength, pOut);

    string retValue(pOut);
    delete[] pBuffer;
    delete[] pOut;
    return retValue;
}

string AesEncryptor::DecryptString(string strMessage) {
    if (32 != strMessage.length()){
        return "";
    }
    int nLength = strMessage.length() / 2;
    unsigned char* pBuffer = new unsigned char[nLength];
    memset(pBuffer, '\0', nLength);
    Hex2Byte(strMessage.c_str(), strMessage.length(), pBuffer);

    m_pEncryptor->InvCipher(pBuffer, nLength);
    string retValue((char*)pBuffer);
    delete[] pBuffer;
    return retValue;
}

void AesEncryptor::EncryptTxtFile(const char* inputFileName, const char* outputFileName) {
    ifstream ifs;

    // Open file:
    ifs.open(inputFileName);
    if (!ifs) {
        return ;
    }

    // Read config data:
    string strInfor;
    string strLine;
    while (!ifs.eof()) {
        char temp[1024];
        memset(temp, '\0', 1024);
        ifs.read(temp, 1000);
        strInfor += temp;
    }
    ifs.close();

    // Encrypt
    strLine = EncryptString(strInfor);

    // Writefile
    ofstream ofs;
    ofs.open(outputFileName);
    if (!ofs) {
        return ;
    }
    ofs << strLine;
    ofs.close();
}

void AesEncryptor::DecryptTxtFile(const char* inputFile, const char* outputFile) {
    ifstream ifs;

    // Open file:
    ifs.open(inputFile);
    if (!ifs) {
        return ;
    }

    // Read config data:
    string strInfor;
    string strLine;
    while (!ifs.eof()) {
        char temp[1024];
        memset(temp, '\0', 1024);
        ifs.read(temp, 1000);
        strInfor += temp;
    }
    ifs.close();

    // Encrypt
    strLine = DecryptString(strInfor);

    // Writefile
    ofstream ofs;
    ofs.open(outputFile);
    if (!ofs) {
        return ;
    }
    ofs << strLine;
    ofs.close();
}
