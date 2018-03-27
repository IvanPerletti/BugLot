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
#include <QString>
#include "mainwindow.h"
using namespace std;

class CrunchLog
{
public:
    CrunchLog();
    void processFile(const char *ucaNameFileIn, const char *ucaNameFileOut);

private:
    void unpackBit(string * pstrOut, unsigned int uiVal);
    unsigned long unpackTimeString(const char * u8aData);
    void removeCharsUntil(string * strProcessed, string strMatchToFind);
    void removeChars( string * strProcessed, string strMatchToFind);
    void finalizeString( string *pStrOut, unsigned long ulTime, long lBitMask, long lMcStatus);
    void strReplaceOccurrence(string *pStrOut,
                              const string csSubStrLook,
                              const string csSubStrSubst );


};

#endif // CRUNCHLOG_H
