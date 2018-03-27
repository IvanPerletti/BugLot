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
    struct InfoDataStruct {
        vector <unsigned int> uiSize;
        vector <string> strLabel;
    };

    void unpackBit(string * pstrOut, unsigned int uiVal);
    string createTimeString(const char * u8aData);
    unsigned long unpackTimeString(const char * u8aData);
    void removeCharsUntil(string * strProcessed, string strMatchToFind);
    void removeChars( string * strProcessed, string strMatchToFind);
    void unPackDataError_ShortMsg(unsigned int* uiDataArray, unsigned int *uiIndex, int *iData1);
    void unPackDataError_Msg(unsigned int* uiDataArray, unsigned int *uiIndex, int *iData1);
    void unPackDataError_LongMsg(unsigned int* uiDataArray, unsigned int *uiIndex, int *iData1);
    void setLineError(InfoDataStruct *data);
    void setNoMotionData(InfoDataStruct *data);
    bool isFirstMessage(unsigned int *arrVal, int type);
    void setAutoTargetData(InfoDataStruct *data, unsigned int *arrVal);
    void setDirectionData(InfoDataStruct *data, unsigned int *arrVal);
    void setElevixTargetPosData(InfoDataStruct *data);
    void setSynchroTargetData(InfoDataStruct *data);
    void setAutoTargetPosData(InfoDataStruct *data, unsigned int *arrVal);
    void setSynchroTargetPosData(InfoDataStruct *data);
    void setUntimelySynchroData(InfoDataStruct *data);
    void setDataToErrorType(string* strFile, unsigned int* uiDataArray, unsigned int error);
    void finalizeString( string *pStrOut, unsigned long ulTime, long lBitMask, long lMcStatus);
    void strReplaceOccurrence(string *pStrOut,
                              const string csSubStrLook,
                              const string csSubStrSubst );


};

#endif // CRUNCHLOG_H
