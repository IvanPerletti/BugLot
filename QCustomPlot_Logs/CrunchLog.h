/*
#ifndef CRUNCHLOG_H
#define CRUNCHLOG_H

#include <QDialog>

namespace Ui {
class CrunchLog;
}

class CrunchLog : public QDialog
{
    Q_OBJECT

public:
    explicit CrunchLog(QWidget *parent = 0);
    ~CrunchLog();

private:
    Ui::CrunchLog *ui;
};
 */
#ifndef CRUNCHLOG_H
#define CRUNCHLOG_H
#include <string>
using namespace std;

class CrunchLog
{
public:
    typedef struct
    {
        uint32_t ulBitMask    ;
        int32_t  lMcStatus    ;
        uint32_t ulTableBit   ;
        int32_t  ulGenStat    ;
        int32_t  iDllStat     ;
        uint32_t ulTableBitExt;
        uint8_t  u8LogicalMode;
    } structLog;


public:
    CrunchLog();
    void extractLog (const char * ucaNameFileIn,
                     const char * ucaNameFileOut,
                     const char * ucaStrToSearch,
                     const unsigned long ulNumLineNext);


protected:
    static void unpackBit8(string * pstrOut, unsigned char u8Val);
    static void unpackBit32(string * pstrOut, unsigned int uiVal);
    static unsigned long unpackTimeString(const char * u8aData);
    static void removeCharsUntil(string * strProcessed, string strMatchToFind);
    static void removeChars( string * strProcessed, string strMatchToFind);
    static void finalizeString2(string *pStrOut,
                        float ulTime,
                        unsigned long lBitMask,
                        long lMcStatus,
                        unsigned long ulTableBit,
                        int u8GenStat,
                        int iDllStat,
                        unsigned long ulTableBitExt,
                        unsigned char u8LogicalMode);
    static void finalizeString(string *pStrOut,
                        float ulTime,
                        structLog *pstrLog);
    static void strReplaceOccurrence(string *pStrOut,
                              const string csSubStrLook,
                              const string csSubStrSubst );


};

#endif // CRUNCHLOG_H
