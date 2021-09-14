#ifndef CRUNCHLOGC_ARM_H
#define CRUNCHLOGC_ARM_H

#include <QString>
#include <QMap>
#include <QFile>
#include <string>
#include "CrunchLog.h"

using namespace std;

class CrunchLogC_Arm: public CrunchLog
{
protected:
    bool mbPerformance;
    long mlRowCounter;
public:
    typedef enum {
        ID_CAN_CONTR    = 0x5A0,
        ID_CAN_INV_A    = 0x6A0,
        ID_CAN_INV_B    = 0x6A1
    } enumIdCAN;

    CrunchLogC_Arm();
    void setPerformance(bool bFlad){mbPerformance = bFlad;}
    bool isPerformanceOn(){return mbPerformance ;}
    void processFile(QString strFileNameIn,
                     QList<enumIdCAN> iDs,
                     const unsigned long ulTimeStart = 0,
                     const unsigned long ulTimeStop = 24*60*60);
private:
    typedef struct
    {
        uint32_t ulBitMask    ;
        int32_t  lMcStatus    ;
        uint32_t ulTableBit   ;
        int32_t  ulGenStat    ;
        int32_t  iDllStat     ;
        uint32_t ulTableBitExt;
        uint8_t  u8LogicalMode;
    } structLogContr;

    typedef struct
    {
        uint8_t  u8Kv0        ;
        uint8_t  u8KvPlus     ;
        uint8_t  u8KvMinus    ;
        uint8_t  u8MaGain     ;
        uint8_t  u8Ma0        ;
        uint8_t  u8Ma         ;
        uint8_t  u8FilGain    ;
        uint8_t  u8Fil0       ;
        uint8_t  u8Fil        ;
        uint8_t  u8IOBit      ;
        uint8_t  u8EnumBit    ;
        uint8_t  u8StatusBit  ;
    } structLogInv;


#define FOCUS_BIT_SHIFT     0
#define FOCUS_BIT_MASK      0x1
#define FLUOMODE_BIT_SHIFT  1
#define FLUOMODE_BIT_MASK   0x7
#define EXPTECH_BIT_SHIFT   4
#define EXPTECH_BIT_MASK    0x3

    typedef void (*PF_ProcessPayload)(string *pStrOut, unsigned long ulTime, unsigned int *pPayload);

    typedef struct
    {
        PF_ProcessPayload processPayload;
        QFile *outFile;
        QStringList legendList;
        QStringList typeList;
    } structOutFile;

    QMap<enumIdCAN, structOutFile> outFile;

    static void processPayloadContr(string *pStrOut, unsigned long ulTime, unsigned int *pPayload);
    static void processPayloadInvA(string *pStrOut, unsigned long ulTime, unsigned int *pPayload);
    static void processPayloadInvB(string *pStrOut, unsigned long ulTime, unsigned int *pPayload);
};

#endif // CRUNCHLOGC_ARM_H
