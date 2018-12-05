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
    char strData[1024];

    typedef union {
        struct s_msg1 {
            short int iData1;             // Byte[0] + Byte [1]
            short int iData2;             // Byte[2] + Byte [3]
            short int iData3;             // Byte[4] + Byte [5]
            short int iData4;             // Byte[6] + Byte [7]
        }msg1;
        struct s_msg2 {
            __int8 i8Data1;         // Byte[0]
            __int8 i8Data2;         // Byte[1]
            __int8 i8Data3;         // Byte[2]
            __int8 i8Data4;         // Byte[3]
            __int8 i8Data5;         // Byte[4]
            __int8 i8Data6;         // Byte[5]
            __int8 i8Data7;         // Byte[6]
            __int8 i8Data8;         // Byte[7]
        }msg2;
        struct s_msg3 {
            long lData1;            // Byte[0] + Byte[1] + Byte[2] + Byte[3]
            long lData2;            // Byte[4] + Byte[5] + Byte[6] + Byte[7]
        }msg3;
        struct s_msg4 {
            short int iData1;             // Byte[0] + Byte[1]
            __int8 i8Data2;         // Byte[2]
            __int8 i8Data3;         // Byte[3]
            short int iData4;             // Byte[4] + Byte[5]
            short int iData5;             // Byte[6] + Byte[7]
        }msg4;
        struct s_msg5 {
            long lData1;            // Byte[0] + Byte[1] + Byte[2] + Byte[3]
            short int iData2;             // Byte[4]
            __int8 i8Data3;         // Byte[5]
            __int8 i8Data4;         // Byte[6]
            __int8 i8Data5;         // Byte[7]
            __int8 i8Data6;         // Byte[8]
        }msg5;
        struct s_msg6 {
            short int iData1;             // Byte[0] + Byte[1]
            short int iData2;             // Byte[2] + Byte[3]
            short int iData3;             // Byte[4] + Byte[5]
            __int8 i8Data4;         // Byte[6]
            __int8 i8Data5;         // Byte[7]
        }msg6;
        struct s_msg7 {
            short int iData1;             // Byte[0] + Byte[1]
            short int iData2;             // Byte[2] + Byte[3]
            long lData3;            // Byte[4] + Byte[5] + byte[6] + Byte[7]
        }msg7;
        struct s_msg8 {
            short int iData1;             // Byte[0] + Byte[1]
            __int8 i8Data2;         // Byte[2]
            __int8 i8Data3;         // Byte[3]
            __int8 i8Data4;         // Byte[4]
            __int8 i8Data5;         // Byte[5]
            __int8 i8Data6;         // Byte[6]
            __int8 i8Data7;         // Byte[7]
        }msg8;
        struct s_msg9 {
            short int iData1;             // Byte[0] + Byte[1]
            __int8 i8Data2;         // Byte[2]
            __int8 i8Data3;         // Byte[3]
            __int8 i8Data4;         // Byte[4]
            __int8 i8Data5;         // Byte[5]
            short int iData6;             // Byte[6] + Byte[7]
        }msg9;
        struct s_msgMM_1{
            short int iErrorID;           // Byte[0] + Byte[1]
            long lData1;            // Byte[2] + Byte[3] + byte[4] + Byte[5]
            int iData2;             // Byte[6] + Byte[7]
        }msgMM_1;
        struct s_msgMM_2{
            short int iErrorID;           // Byte[0] + Byte[1]
            __int8 i8Data1;         // Byte[2]
            __int8 i8Data2;         // Byte[3]
            short int iData3;             // Byte[4] + Byte[5]
            __int8 i8Data4;         // Byte[6]
            __int8 i8Data5;         // Byte[7]
        }msgMM_2;
        struct s_msgMM_3{
            short int iErrorID;           // Byte[0] + Byte [1]
            short int iData1;             // Byte[2] + Byte [3]
            short int iData2;             // Byte[4] + Byte [5]
            short int iData3;             // Byte[6] + Byte [7]
        }msgMM_3;
        struct s_msgMM_4{
            short int iErrorID;           // Byte[0] + Byte [1]
            __int8 i8Data1;         // Byte[2]
            short int iData2;             // Byte[3] + Byte[4]
            short int iData3;             // Byte[5] + Byte[6]
        }msgMM_4;
        struct s_msgMM_5{
            short int iErrorID;           // Byte[0] + Byte [1]
            __int8 i8Data1;         // Byte[2]
            __int8 i8Data2;         // Byte[3]
            __int8 i8Data3;         // Byte[4]
            __int8 i8Data4;         // Byte[5]
            short int iData5;             // Byte[6] + Byte[7]
        }msgMM_5;
        struct s_msgMM_6{
            short int iErrorID;           // Byte[0] + Byte [1]
            short int iData1;             // Byte[2] + Byte [3]
            __int8 i8Data2;         // Byte[4]
            __int8 i8Data3;         // Byte[5]
            __int8 i8Data4;         // Byte[6]
            __int8 i8Data5;         // Byte[7]
        }msgMM_6;

        signed char caAllData[8];
    } unionDataInfo;

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
    bool isFirstMessage(unsigned int *arrVal, int freeSlots);
    void setAutoTargetData(string *strFile, unionDataInfo *infoStruct);
    void setDirectionData(string *strFile, unionDataInfo *infoStruct);
    void setElevixTargetPosData(string *strFile, unionDataInfo *infoStruct);
    void setSynchroTargetData(string *strFile, unionDataInfo *infoStruct);
    void setAutoTargetPosData(string *strFile, unionDataInfo *infoStruct);
    void setSynchroTargetPosData(string *strFile, unionDataInfo *infoStruct);
    void setUntimelySynchroData(string *strFile, unionDataInfo *infoStruct);
    void setChangeAccessoryData(string *strFile, unionDataInfo *infoStruct);
    void setAxesDriverData(string *strFile, unionDataInfo *infoStruct);
    InfoDataStruct setDataToErrorType(string *strFile, unionDataInfo *infoStruct, unsigned int error);
};

#endif // CPROCESSKALOSLOGS_H
