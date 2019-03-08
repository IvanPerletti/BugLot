#ifndef CPROCESSKALOSLOGS_H
#define CPROCESSKALOSLOGS_H


#include "cprocesslogs.h"
#include "ceepromprocess.h"

using namespace std;

class CProcessKalosLogs: public CProcessLogs
{
public:
    CProcessKalosLogs(const char * ucaNameFileIn, const char * ucaNameFileOut);
    void processFile(const char *ucaNameFileIn, const char *ucaNameFileOut);

private:
    char strData[1024];
    static bool bFirstEEprom;

    void set_log_char(char *cDataArr, unsigned int* uiDataArray);
    string createTimeString(const char * u8aData);
    unsigned long unpackTimeString(const char * u8aData);
    void removeCharsUntil(string * strProcessed, string strMatchToFind);
    void removeChars( string * strProcessed, string strMatchToFind);

    // Orobix
    void setCanLogEsBkData(string *strFile, unionDataInfo *infoStruct);
    void setCanLogAutoData1(string *strFile, unionDataInfo *infoStruct);
    void setCanLogVertData1(string *strFile, unionDataInfo *infoStruct);
    void setCanLogVertData2(string *strFile, unionDataInfo *infoStruct);
    void setCanLogVertData3(string *strFile, unionDataInfo *infoStruct);
    void setCanLogVertData4(string *strFile, unionDataInfo *infoStruct);
    void setCanLogLatData1(string *strFile, unionDataInfo *infoStruct);
    void setCanLogLatData2(string *strFile, unionDataInfo *infoStruct);
    void setCanLogLongData1(string *strFile, unionDataInfo *infoStruct);
    void setCanLogLongData2(string *strFile, unionDataInfo *infoStruct);
    void setCanLogRotData1(string *strFile, unionDataInfo *infoStruct);
    void setCanLogRotData2(string *strFile, unionDataInfo *infoStruct);
    void setCanLogIncData1(string *strFile, unionDataInfo *infoStruct);
    void setCanLogIncData2(string *strFile, unionDataInfo *infoStruct);
    void setCanLogDetLatData1(string *strFile, unionDataInfo *infoStruct);
    void setCanLogDetLatData2(string *strFile, unionDataInfo *infoStruct);
    void setCanLogDetLongData1(string *strFile, unionDataInfo *infoStruct);
    void setCanLogDetLongData2(string *strFile, unionDataInfo *infoStruct);
    void setCanLogSyncData(string *strFile, unionDataInfo *infoStruct);
    void setCanLogTargetData1(string *strFile, unionDataInfo *infoStruct);
    void setCanLogTargetData2(string *strFile, unionDataInfo *infoStruct);
    void setInterlockData(string *strFile, unionDataInfo *infoStruct);
    void setBrakesBlockData(string *strFile, unionDataInfo *infoStruct);
    void setCanLogDetLatSyncData(string *strFile, unionDataInfo *infoStruct);
    void setCanLogDetLongSyncData(string *strFile, unionDataInfo *infoStruct);

    // Motion Monitoring Info
    void setCanLogMotionMonitoringInfo(string *strFile, unionDataInfo *infoStruct);

    // Motion Monitoring Error
    void setLineError(string *strFile, unionDataInfo *infoStruct);
    void setNoMotionData(string *strFile, unionDataInfo *infoStruct);
    bool isFirstMessage(signed char *arrVal, int freeSlots);
    void setAutoTargetData(string *strFile, unionDataInfo *infoStruct);
    void setDirectionData(string *strFile, unionDataInfo *infoStruct);
    void setElevixTargetPosData(string *strFile, unionDataInfo *infoStruct);
    void setSynchroTargetData(string *strFile, unionDataInfo *infoStruct);
    void setAutoTargetPosData(string *strFile, unionDataInfo *infoStruct);
    void setSynchroTargetPosData(string *strFile, unionDataInfo *infoStruct);
    void setUntimelySynchroData(string *strFile, unionDataInfo *infoStruct);
    void setChangeAccessoryData(string *strFile, unionDataInfo *infoStruct);
    void setAxesDriverData(string *strFile, unionDataInfo *infoStruct);
    void setDataToErrorType(string *strFile, unionDataInfo *infoStruct, unsigned int error);

};

#endif // CPROCESSKALOSLOGS_H
