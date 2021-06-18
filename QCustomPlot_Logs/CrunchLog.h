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
        unsigned long  ulBitMask    ;
        long           lMcStatus    ;
        unsigned long  ulTableBit   ;
        int            ulGenStat    ;
        int            iDllStat     ;
        unsigned long  ulTableBitExt;
        unsigned char  u8LogicalMode;
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
                        unsigned long ulTime,
                        unsigned long lBitMask,
                        long lMcStatus,
                        unsigned long ulTableBit,
                        int u8GenStat,
                        int iDllStat,
                        unsigned long ulTableBitExt,
                        unsigned char u8LogicalMode);
    static void finalizeString(string *pStrOut,
                        unsigned long ulTime,
                        structLog *pstrLog);
    static void strReplaceOccurrence(string *pStrOut,
                              const string csSubStrLook,
                              const string csSubStrSubst );


};

#endif // CRUNCHLOG_H
