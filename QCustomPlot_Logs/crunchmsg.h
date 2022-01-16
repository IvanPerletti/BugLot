#ifndef CRUNCHMSG_H
#define CRUNCHMSG_H

#include <QString>
#include <QMap>
#include <QFile>
#include <QObject>
#include <string>

using namespace std;

class CrunchMsg
{
public:
    typedef enum {
        ID_CAN_ARCO_CONTR       = 0x6A0,
        ID_CAN_ARCO_INV_A       = 0x5A0,
        ID_CAN_ARCO_INV_B       = 0x5A1,
        ID_CAN_MAMMO_TO_INV_A   = 0x201,
        ID_CAN_MAMMO_TO_INV_B   = 0x202,
        ID_CAN_MAMMO_TO_INV_C   = 0x203,
        ID_CAN_MAMMO_FROM_INV_A = 0x181,
        ID_CAN_MAMMO_FROM_INV_B = 0x182,
        ID_CAN_MAMMO_FROM_INV_C = 0x183
    } enumIdCAN;

    CrunchMsg(QString, enumIdCAN idCAN);
    virtual ~CrunchMsg();
    void processMsg(float fTime, unsigned int *pPayload);
    virtual void processPayload(string *pStrOut, float fTime, unsigned int *pPayload) = 0;

private:
#define HEADER_PREFIX   "%"
#define LEGENDS_TAG     "Legends:"
#define TYPES_TAG       "Types:"
#define TYPE_INT        "I"
#define TYPE_BIT        "B"

#define PAYLOAD_SIZE    6

protected:
    enumIdCAN idCAN;
    QFile *outFile;
    QStringList legendList;
    QStringList typeList;
    unsigned int payloadPrev[PAYLOAD_SIZE];

    void unpackBit8(string * pstrOut, unsigned char u8Val, int iNbit = 8, unsigned char u8Mask = 0xFF);
    void unpackBit32(string * pstrOut, unsigned int uiVal, int iNbit = 32);
    void intToStr(string *pStrOut, unsigned int uiVal, string sfx = " ");
    void floatToStr(string *pStrOut, float fVal, string sfx = " ");
    unsigned long unpackTimeString(const char * u8aData);
    bool decodeTimeString(const char * u8aData, unsigned long &ulTime);
    void removeCharsUntil(string * strProcessed, string strMatchToFind);
    void removeChars( string * strProcessed, string strMatchToFind);
    void strReplaceOccurrence(string *pStrOut,
                              const string csSubStrLook,
                              const string csSubStrSubst );
};

class CrunchMsg_0x6A0 : public CrunchMsg
{
public:
    CrunchMsg_0x6A0(QString);
    void processPayload(string *pStrOut, float fTime, unsigned int *pPayload);

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
    } structLog;
};

class CrunchMsg_0x5A0 : public CrunchMsg
{
public:
    CrunchMsg_0x5A0(QString);
    void processPayload(string *pStrOut, float fTime, unsigned int *pPayload);

private:
    typedef struct
    {
        uint8_t  u8Kv0        ;
        uint8_t  u8KvPlus     ;
        uint8_t  u8KvMinus    ;
        uint8_t  u8MaGain     ;
        uint8_t  u8Ma0        ;
        uint8_t  u8Ma         ;
    } structLog;
};

class CrunchMsg_0x5A1 : public CrunchMsg
{
public:
    CrunchMsg_0x5A1(QString);
    void processPayload(string *pStrOut, float fTime, unsigned int *pPayload);

private:

#define FOCUS_BIT_SHIFT     0
#define FOCUS_BIT_MASK      0x1
#define FLUOMODE_BIT_SHIFT  1
#define FLUOMODE_BIT_MASK   0x7
#define EXPTECH_BIT_SHIFT   4
#define EXPTECH_BIT_MASK    0x3

    typedef struct
    {
        uint8_t  u8FilGain    ;
        uint8_t  u8Fil0       ;
        uint8_t  u8Fil        ;
        uint8_t  u8IOBit      ;
        uint8_t  u8EnumBit    ;
        uint8_t  u8StatusBit  ;
    } structLog;
};

class CrunchMsg_0x201 : public CrunchMsg
{
public:
    CrunchMsg_0x201(QString);
    void processPayload(string *pStrOut, float fTime, unsigned int *pPayload);

private:
#define ENABLE_BIT          (1 << 0)
#define PREP_BIT            (1 << 1)
#define RESET_BIT           (1 << 3)

    typedef struct
    {
        uint16_t u16Kv      ;
        uint16_t u16MaS     ;
        uint8_t ulBitMask   ;
    } structLog;
};

class CrunchMsg_0x202 : public CrunchMsg
{
public:
    CrunchMsg_0x202(QString);
    void processPayload(string *pStrOut, float fTime, unsigned int *pPayload);

private:
#define BRAKE_BIT           (1 << 0)
#define SPEED_BIT           (1 << 4)
#define MA_STAB_BIT         (1 << 5)

    typedef struct
    {
        uint16_t u16Ma        ;
        uint16_t u16Fil       ;
        uint8_t ulBitMask     ;
    } structLog;
};

class CrunchMsg_0x203 : public CrunchMsg
{
public:
    CrunchMsg_0x203(QString);
    void processPayload(string *pStrOut, float fTime, unsigned int *pPayload);

private:
};

class CrunchMsg_0x181 : public CrunchMsg
{
public:
    CrunchMsg_0x181(QString);
    void processPayload(string *pStrOut, float fTime, unsigned int *pPayload);

private:
#define FAULT_BIT_SHIFT     3
#define FAULT_BIT_MASK      0xF

    typedef struct
    {
        uint16_t u16Kv      ;
        uint16_t u16Ma      ;
        uint16_t u16MaS     ;
        uint8_t ulBitState  ;
        uint8_t u8Ver       ;
    } structLog;
};

class CrunchMsg_0x182 : public CrunchMsg
{
public:
    CrunchMsg_0x182(QString);
    void processPayload(string *pStrOut, float fTime, unsigned int *pPayload);

private:

    typedef struct
    {
        uint16_t u16Fil     ;
        uint8_t ulBitState  ;
        uint8_t u8TempTube  ;
        uint8_t u8TempInv   ;
        uint8_t u8PercTube  ;
        uint8_t u8ContMax   ;
    } structLog;
};

class CrunchMsg_0x183 : public CrunchMsg
{
public:
    CrunchMsg_0x183(QString);
    void processPayload(string *pStrOut, float fTime, unsigned int *pPayload);

private:
    typedef struct
    {
        uint16_t u16Kv      ;
        uint16_t u16Ma      ;
        uint16_t u16MaS     ;
        uint16_t u16Ms      ;
    } structLog;
};

#endif // CRUNCHMSG_H
