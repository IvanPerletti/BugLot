#ifndef CPROCESSKALOSLOGS_H
#define CPROCESSKALOSLOGS_H

#include "cprocesslogs.h"
using namespace std;

class CProcessKalosLogs: public CProcessLogs
{
public:
    CProcessKalosLogs(const char * ucaNameFileIn, const char * ucaNameFileOut);
    void processFile(const char *ucaNameFileIn, const char *ucaNameFileOut);

private:
    struct InfoDataStruct {
        vector <unsigned int> uiSize;
        vector <string> strLabel;
    };

    string createTimeString(const char * u8aData);
    unsigned long unpackTimeString(const char * u8aData);
    void removeCharsUntil(string * strProcessed, string strMatchToFind);
    void removeChars( string * strProcessed, string strMatchToFind);
    void unPackDataError_OneSlotMsg(unsigned int* uiDataArray, unsigned int *uiIndex, int *iData1);
    void unPackDataError_TwoSlotsMsg(unsigned int* uiDataArray, unsigned int *uiIndex, int *iData1);
    void unPackDataError_FourSlotsMsg(unsigned int* uiDataArray, unsigned int *uiIndex, int *iData1);
    // Orobix
    void setCanLogEsBkData(InfoDataStruct *infoStruct);
    void setCanLogAutoData1(InfoDataStruct *infoStruct);
    void setCanLogVertData1(InfoDataStruct *infoStruct);
    void setCanLogVertData2(InfoDataStruct *infoStruct);
    void setCanLogVertData3(InfoDataStruct *infoStruct);
    void setCanLogVertData4(InfoDataStruct *infoStruct);
    void setCanLogLatData1(InfoDataStruct *infoStruct);
    void setCanLogLatData2(InfoDataStruct *infoStruct);
    void setCanLogLongData1(InfoDataStruct *infoStruct);
    void setCanLogLongData2(InfoDataStruct *infoStruct);
    void setCanLogRotData1(InfoDataStruct *infoStruct);
    void setCanLogRotData2(InfoDataStruct *infoStruct);
    void setCanLogIncData1(InfoDataStruct *infoStruct);
    void setCanLogIncData2(InfoDataStruct *infoStruct);
    void setCanLogDetLatData1(InfoDataStruct *infoStruct);
    void setCanLogDetLatData2(InfoDataStruct *infoStruct);
    void setCanLogDetLongData1(InfoDataStruct *infoStruct);
    void setCanLogDetLongData2(InfoDataStruct *infoStruct);
    void setCanLogSyncData(InfoDataStruct *infoStruct);
    void setCanLogTargetData1(InfoDataStruct *infoStruct);
    void setCanLogTargetData2(InfoDataStruct *infoStruct);
    void setCanLogDetLatSyncData(InfoDataStruct *infoStruct);
    void setCanLogDetLongSyncData(InfoDataStruct *infoStruct);

    // Motion Monitoring
    void setLineError(InfoDataStruct *data);
    void setNoMotionData(InfoDataStruct *data);
    bool isFirstMessage(unsigned int *arrVal, int freeSlots);
    void setAutoTargetData(InfoDataStruct *data, unsigned int *arrVal);
    void setDirectionData(InfoDataStruct *data, unsigned int *arrVal);
    void setElevixTargetPosData(InfoDataStruct *data);
    void setSynchroTargetData(InfoDataStruct *data);
    void setAutoTargetPosData(InfoDataStruct *data, unsigned int *arrVal);
    void setSynchroTargetPosData(InfoDataStruct *data);
    void setUntimelySynchroData(InfoDataStruct *data);
    InfoDataStruct setDataToErrorType(unsigned int* uiDataArray, unsigned int error);
    void composeLineLog(string *strFile, InfoDataStruct *infoData, unsigned int dataID, unsigned int *uiDataArray);
};

#endif // CPROCESSKALOSLOGS_H
