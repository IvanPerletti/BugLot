#include <QFile>
#include <QTextStream>
#include <QDebug>
#include "crunchmsg.h"

CrunchMsg::CrunchMsg(QString filename, enumIdCAN idCAN)
{
    QString id_filename(filename);

    id_filename.replace(".txt", QString().sprintf("_%03X.txt", (int)idCAN));
    outFile = new QFile(id_filename);

    memset((void *)payloadPrev, '\0', sizeof(payloadPrev));
}

CrunchMsg::~CrunchMsg(void)
{
    if (outFile)
    {
        if (outFile->isOpen())
            outFile->close();
        delete outFile;
    }
}

//--------------------------------------------------------
void CrunchMsg::unpackBit8(string * pstrOut, unsigned char u8Val, int iNbit)
{
    int ii, iBit;

    if (iNbit > 8)
        iNbit = 8;
    for (ii=0; ii<iNbit; ii++)
    {
        char u8aNum[4];
        iBit = ( u8Val & (1<<ii) ) !=0;
        itoa(iBit,u8aNum,10);
        pstrOut->append(u8aNum);
        pstrOut->append(" ");
    }
}
//--------------------------------------------------------
void CrunchMsg::unpackBit32(string *pstrOut, unsigned int uiVal, int iNbit)
{
    int ii, iBit;

    if (iNbit > 32)
        iNbit = 32;
    for (ii=0; ii<iNbit; ii++)
    {
        char u8aNum[4];
        iBit = ( uiVal & (1<<ii) ) !=0;
        itoa(iBit,u8aNum,10);
        pstrOut->append(u8aNum);
        pstrOut->append(" ");
    }
}
//--------------------------------------------------------
void CrunchMsg::intToStr(string *pStrOut, unsigned int uiVal, string sfx)
{
    char s8aChar[16]={0,};

    sprintf(s8aChar, "%d", uiVal);
    pStrOut->append(s8aChar);
    pStrOut->append(sfx);
}
//--------------------------------------------------------
void CrunchMsg::floatToStr(string *pStrOut, float fVal, string sfx)
{
    char s8aChar[16]={0,};

    sprintf(s8aChar, "%.1f", fVal);
    pStrOut->append(s8aChar);
    pStrOut->append(sfx);
}
//--------------------------------------------------------
unsigned long CrunchMsg::unpackTimeString(const char * u8aData)
{
    unsigned long  ulTime;
    unsigned int l_hour=0, l_min=0, l_sec=0, l_ms=0;
    sscanf( u8aData ,
            "%02d:%02d:%02d:%03d",
            &l_hour	,
            &l_min	,
            &l_sec	,
            &l_ms	);
    ulTime = l_ms + (l_sec + l_min*60 + l_hour * 3600)*1000; // max Num: 90060999ms
    if (ulTime >= 47018074)
        ulTime++;
    return(ulTime);
}
//--------------------------------------------------------
bool CrunchMsg::decodeTimeString(const char * u8aData, unsigned long &ulTime)
{
    unsigned int l_hour=0, l_min=0, l_sec=0, l_ms=0;
    int32_t iNumFound = sscanf( u8aData , "%02d:%02d:%02d.%03d",
            &l_hour	,
            &l_min	,
            &l_sec	,
            &l_ms	);

    if (iNumFound == 4)
        ulTime = l_ms + (l_sec + l_min*60 + l_hour * 3600)*1000;
    return(iNumFound == 4);
}

//--------------------------------------------------------
void CrunchMsg::removeCharsUntil(string * strProcessed, string strMatchToFind)
{
    size_t szPos;

    szPos = strProcessed->find(strMatchToFind);
    if (szPos < strProcessed->size() ){
        strProcessed->erase (0, szPos+strMatchToFind.size());
    }
}
//--------------------------------------------------------
void CrunchMsg::removeChars(string * strProcessed, string strMatchToFind)
{
    size_t szPos;

    szPos = strProcessed->find(strMatchToFind);

    while (szPos < strProcessed->size() )
    {
        strProcessed->erase (szPos,strMatchToFind.size());
        szPos = strProcessed->find(strMatchToFind);
    }
}
//--------------------------------------------------------
void CrunchMsg::strReplaceOccurrence(string *pStrOut,
                                     const string csSubStrLook,
                                     const string csSubStrSubst )
{
    int index = 0;
    while (1)
    {
        int length = csSubStrLook.size();
        index = pStrOut->find(csSubStrLook, index);
        if (index < 0) {
            break;
        }
        pStrOut->replace(index, length, csSubStrSubst);/* Make the replacement. */
        index += 1;				/* Advance index */
    }
}

void CrunchMsg::processMsg(float fTime, unsigned int *pPayload)
{
    QTextStream stream(outFile);

    if (!outFile->isOpen()) {
        outFile->open(QIODevice::WriteOnly);
        if (legendList.empty() == false) {
            stream << HEADER_PREFIX << " " << LEGENDS_TAG;
            foreach( QString legend, legendList)
                stream << " " << legend;
            stream << endl;
        }
        if (typeList.empty() == false) {
            stream << HEADER_PREFIX << " " << TYPES_TAG;
            foreach( QString type, typeList)
                stream << " " << type;
            stream << endl;
        }
    }

    if (memcmp((void *)payloadPrev, (void *)pPayload, sizeof(payloadPrev))) {
        string strOut;

        processPayload(&strOut, (fTime - 0.1), payloadPrev);
        stream << strOut.c_str();
        processPayload(&strOut, fTime, pPayload);
        stream << strOut.c_str();
        memcpy((void *)payloadPrev, (void *)pPayload, sizeof(payloadPrev));
    }
}

CrunchMsg_0x6A0::CrunchMsg_0x6A0(QString filename) : CrunchMsg(filename, ID_CAN_CONTR)
{
    idCAN = ID_CAN_CONTR;

    typeList << TYPE_BIT << TYPE_BIT << TYPE_BIT << TYPE_BIT << TYPE_BIT;
    legendList << "I_PID_SDCAL" << "I_PID_APPOPEN" << "I_PID_READY" <<"I_PID_PULSE_MODE" << "O_PID_HCF_MODE";
    typeList << TYPE_BIT << TYPE_BIT << TYPE_BIT << TYPE_BIT << TYPE_BIT;
    legendList << "I_GEN_REQ_FL_HCF" << "I_GEN_PREP_RAD" << "I_GEN_COM_REQ" << "I_GEN_READY" << "I_GEN_REQ_RAD";
    typeList << TYPE_BIT << TYPE_BIT << TYPE_BIT << TYPE_BIT << TYPE_BIT;
    legendList << "O_PID_CFL" << "O_PREP_PID" << "O_CRAD_PID" << "I_PID_EXP_RX" << "O_PID_DOSE_ADJ";
    typeList << TYPE_BIT << TYPE_BIT << TYPE_BIT << TYPE_BIT;
    legendList << "O_GEN_READY_ACQ_FL" << "O_READY_ACQ_RAD_FL" << "I_GEN_EXON" << "O_PID_EXON";
}

void CrunchMsg_0x6A0::processPayload(string *pStrOut, float fTime, unsigned int *pPayload)
{
    structLog strLog;
    unsigned long ulBitMaskNew;

    memset((void *)&strLog, '\0', sizeof(structLog));
    ulBitMaskNew = pPayload[2];
    ulBitMaskNew += (pPayload[3]<<8);
    ulBitMaskNew += (pPayload[4]<<16);
    ulBitMaskNew += (pPayload[5]<<24);
    strLog.ulBitMask = ulBitMaskNew;
    strLog.lMcStatus = 0;

    pStrOut->clear();

    floatToStr(pStrOut, fTime);

    unpackBit32(pStrOut, strLog.ulBitMask, 19);
    pStrOut->append("\n");
}

CrunchMsg_0x5A0::CrunchMsg_0x5A0(QString filename) : CrunchMsg(filename, ID_CAN_INV_A)
{
    idCAN = ID_CAN_INV_A;

    legendList << "Kv0" << "Kv+" << "Kv-" <<"MaGain" << "Ma0" << "Ma";
}

void CrunchMsg_0x5A0::processPayload(string *pStrOut, float fTime, unsigned int *pPayload)
{
    structLog strLog;

    memset((void *)&strLog, '\0', sizeof(structLog));
    strLog.u8Kv0 = (uint8_t)pPayload[0];
    strLog.u8KvPlus = (uint8_t)pPayload[1];
    strLog.u8KvMinus = (uint8_t)pPayload[2];
    strLog.u8MaGain = (uint8_t)pPayload[3];
    strLog.u8Ma0 = (uint8_t)pPayload[4];
    strLog.u8Ma = (uint8_t)pPayload[5];

    pStrOut->clear();

    floatToStr(pStrOut, fTime);

    intToStr(pStrOut, strLog.u8Kv0);
    intToStr(pStrOut, strLog.u8KvPlus);
    intToStr(pStrOut, strLog.u8KvMinus);
    intToStr(pStrOut, strLog.u8MaGain);
    intToStr(pStrOut, strLog.u8Ma0);
    intToStr(pStrOut, strLog.u8Ma, "\n");
}

CrunchMsg_0x5A1::CrunchMsg_0x5A1(QString filename) : CrunchMsg(filename, ID_CAN_INV_B)
{
    idCAN = ID_CAN_INV_B;

    legendList << "FilGain" << "Fil0" << "Fil";
    typeList << TYPE_INT << TYPE_INT << TYPE_INT;
    legendList << "B0" << "B1" << "B2" << "B3" << "B4" << "B5" << "B6" << "B7";
    typeList << TYPE_BIT << TYPE_BIT << TYPE_BIT << TYPE_BIT << TYPE_BIT << TYPE_BIT << TYPE_BIT << TYPE_BIT;
    legendList << "Focus" << "Fluo" << "Exp" << "Status";
    typeList << TYPE_INT << TYPE_INT << TYPE_INT << TYPE_INT;
}

void CrunchMsg_0x5A1::processPayload(string *pStrOut, float fTime, unsigned int *pPayload)
{
    structLog strLog;

    memset((void *)&strLog, '\0', sizeof(structLog));
    strLog.u8FilGain = (uint8_t)pPayload[0];
    strLog.u8Fil0 = (uint8_t)pPayload[1];
    strLog.u8Fil = (uint8_t)pPayload[2];
    strLog.u8IOBit = (uint8_t)pPayload[3];
    strLog.u8EnumBit = (uint8_t)pPayload[4];
    strLog.u8StatusBit = (uint8_t)pPayload[5];

    pStrOut->clear();

    floatToStr(pStrOut, fTime);

    intToStr(pStrOut, strLog.u8FilGain);
    intToStr(pStrOut, strLog.u8Fil0);
    intToStr(pStrOut, strLog.u8Fil);
    unpackBit8(pStrOut, strLog.u8IOBit);
    int enumVal = (strLog.u8EnumBit >> FOCUS_BIT_SHIFT) & FOCUS_BIT_MASK;
    intToStr(pStrOut, enumVal);
    enumVal = (strLog.u8EnumBit >> FLUOMODE_BIT_SHIFT) & FLUOMODE_BIT_MASK;
    intToStr(pStrOut, enumVal);
    enumVal = (strLog.u8EnumBit >> EXPTECH_BIT_SHIFT) & EXPTECH_BIT_MASK;
    intToStr(pStrOut, enumVal);
    intToStr(pStrOut, strLog.u8StatusBit, "\n");
}
