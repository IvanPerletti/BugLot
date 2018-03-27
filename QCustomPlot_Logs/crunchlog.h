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
    string createTimeString(const char * u8aData);
    unsigned long unpackTimeString(const char * u8aData);
    void removeCharsUntil(string * strProcessed, string strMatchToFind);
    void removeChars( string * strProcessed, string strMatchToFind);
    void unPackDataError_Msg(unsigned int* uiDataArray, unsigned int *uiIndex, int *iData1);
    void unPackDataError_LongMsg(unsigned int* uiDataArray, int *iData1);
    void unPackDataError_2Msgs(unsigned int* uiDataArray, int *iData1, int *iData2);
    void unPackDataError_3Msgs(unsigned int* uiDataArray, int *iData1, int *iData2, int *iData3);
    void setLineError(string* strFile, unsigned int* uiDataArray, unsigned int *uiIndex);
    void setNoMotionData(string* strFile, unsigned int* uiDataArray, unsigned int *uiIndex, vector <string> label);
    void setAutoTargetData(string* strFile, unsigned int* uiDataArray);
    void setDirectionData(string* strFile, unsigned int* uiDataArray);
    void setElevixTargetPosData(string* strFile, unsigned int* uiDataArray);
    void setSynchroTargetData(string* strFile, unsigned int* uiDataArray);
    void setDataToErrorType(string* strFile, unsigned int* uiDataArray, unsigned int error);
    void finalizeString( string *pStrOut, unsigned long ulTime, long lBitMask, long lMcStatus);
    void strReplaceOccurrence(string *pStrOut,
                              const string csSubStrLook,
                              const string csSubStrSubst );


};

#endif // CRUNCHLOG_H
