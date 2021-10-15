#include <QDebug>
#include <QFileDialog>
#include <QList>
#include <QMap>

#include <inttypes.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include "CrunchLogC_Arm.h"

#define MAX(A,B)(((A)>=(B))?(A):(B))

CrunchLogC_Arm::CrunchLogC_Arm()
{
    mbPerformance = true;
    mlRowCounter = 0;

    outFile[ID_CAN_CONTR].processPayload = processPayloadContr;
    outFile[ID_CAN_CONTR].typeList << TYPE_BIT << TYPE_BIT << TYPE_BIT << TYPE_BIT << TYPE_BIT << TYPE_BIT << TYPE_BIT << TYPE_BIT << TYPE_BIT << TYPE_BIT;
    outFile[ID_CAN_CONTR].typeList << TYPE_BIT << TYPE_BIT << TYPE_BIT << TYPE_BIT << TYPE_BIT << TYPE_BIT << TYPE_BIT << TYPE_BIT << TYPE_BIT;
    outFile[ID_CAN_CONTR].legendList << "I_PID_SDCAL" << "I_PID_APPOPEN" << "I_PID_READY" <<"I_PID_PULSE_MODE" << "O_PID_HCF_MODE";
    outFile[ID_CAN_CONTR].legendList << "I_GEN_REQ_FL_HCF" << "I_GEN_PREP_RAD" << "I_GEN_COM_REQ" << "I_GEN_READY" << "I_GEN_REQ_RAD";
    outFile[ID_CAN_CONTR].legendList << "O_PID_CFL" << "O_PREP_PID" << "O_CRAD_PID" << "I_PID_EXP_RX" << "O_PID_DOSE_ADJ";
    outFile[ID_CAN_CONTR].legendList << "O_GEN_READY_ACQ_FL" << "O_READY_ACQ_RAD_FL" << "I_GEN_EXON" << "O_PID_EXON";

    outFile[ID_CAN_INV_A].processPayload = processPayloadInvA;
    outFile[ID_CAN_INV_A].legendList << "Kv0" << "Kv+" << "Kv-" <<"MaGain" << "Ma0" << "Ma";

    outFile[ID_CAN_INV_B].processPayload = processPayloadInvB;
    outFile[ID_CAN_INV_B].legendList << "FilGain" << "Fil0" << "Fil";
    outFile[ID_CAN_INV_B].typeList << TYPE_INT << TYPE_INT << TYPE_INT;
    outFile[ID_CAN_INV_B].legendList << "B0" << "B1" << "B2" << "B3" << "B4" << "B5" << "B6" << "B7";
    outFile[ID_CAN_INV_B].typeList << TYPE_BIT << TYPE_BIT << TYPE_BIT << TYPE_BIT << TYPE_BIT << TYPE_BIT << TYPE_BIT << TYPE_BIT;
    outFile[ID_CAN_INV_B].legendList << "Focus" << "Fluo" << "Exp" << "Status";
    outFile[ID_CAN_INV_B].typeList << TYPE_INT << TYPE_INT << TYPE_INT << TYPE_INT;
}

//--------------------------------------------------------
void CrunchLogC_Arm::processPayloadContr(string *pStrOut, float fTime, unsigned int *pPayload)
{
    structLogContr strLogContr;
    unsigned long ulBitMaskNew;

    memset((void *)&strLogContr, '\0', sizeof(structLogContr));
    ulBitMaskNew = pPayload[2];
    ulBitMaskNew += (pPayload[3]<<8);
    ulBitMaskNew += (pPayload[4]<<16);
    ulBitMaskNew += (pPayload[5]<<24);
    strLogContr.ulBitMask = ulBitMaskNew;
    strLogContr.lMcStatus = 0;

    pStrOut->clear();

    floatToStr(pStrOut, fTime);

    unpackBit32(pStrOut, strLogContr.ulBitMask, 19);
    pStrOut->append("\n");
}

//--------------------------------------------------------
void CrunchLogC_Arm::processPayloadInvA(string *pStrOut, float fTime, unsigned int *pPayload)
{
    structLogInv strLogInv;

    memset((void *)&strLogInv, '\0', sizeof(structLogInv));
    strLogInv.u8Kv0 = (uint8_t)pPayload[0];
    strLogInv.u8KvPlus = (uint8_t)pPayload[1];
    strLogInv.u8KvMinus = (uint8_t)pPayload[2];
    strLogInv.u8MaGain = (uint8_t)pPayload[3];
    strLogInv.u8Ma0 = (uint8_t)pPayload[4];
    strLogInv.u8Ma = (uint8_t)pPayload[5];

    pStrOut->clear();

    floatToStr(pStrOut, fTime);

    intToStr(pStrOut, strLogInv.u8Kv0);
    intToStr(pStrOut, strLogInv.u8KvPlus);
    intToStr(pStrOut, strLogInv.u8KvMinus);
    intToStr(pStrOut, strLogInv.u8MaGain);
    intToStr(pStrOut, strLogInv.u8Ma0);
    intToStr(pStrOut, strLogInv.u8Ma, "\n");
}

//--------------------------------------------------------
void CrunchLogC_Arm::processPayloadInvB(string *pStrOut, float fTime, unsigned int *pPayload)
{
    structLogInv strLogInv;

    memset((void *)&strLogInv, '\0', sizeof(structLogInv));
    strLogInv.u8FilGain = (uint8_t)pPayload[0];
    strLogInv.u8Fil0 = (uint8_t)pPayload[1];
    strLogInv.u8Fil = (uint8_t)pPayload[2];
    strLogInv.u8IOBit = (uint8_t)pPayload[3];
    strLogInv.u8EnumBit = (uint8_t)pPayload[4];
    strLogInv.u8StatusBit = (uint8_t)pPayload[5];

    pStrOut->clear();

    floatToStr(pStrOut, fTime);

    intToStr(pStrOut, strLogInv.u8FilGain);
    intToStr(pStrOut, strLogInv.u8Fil0);
    intToStr(pStrOut, strLogInv.u8Fil);
    unpackBit8(pStrOut, strLogInv.u8IOBit);
    int enumVal = (strLogInv.u8EnumBit >> FOCUS_BIT_SHIFT) & FOCUS_BIT_MASK;
    intToStr(pStrOut, enumVal);
    enumVal = (strLogInv.u8EnumBit >> FLUOMODE_BIT_SHIFT) & FLUOMODE_BIT_MASK;
    intToStr(pStrOut, enumVal);
    enumVal = (strLogInv.u8EnumBit >> EXPTECH_BIT_SHIFT) & EXPTECH_BIT_MASK;
    intToStr(pStrOut, enumVal);
    intToStr(pStrOut, strLogInv.u8StatusBit, "\n");
}

//--------------------------------------------------------
void CrunchLogC_Arm::processFile (QString strFileNameIn,
                                  QList<enumIdCAN> iDs,
                                  const unsigned long ulTimeStart,
                                  const unsigned long ulTimeStop)
{
    string strLine, strOut;
    int iMaxIterator = 0;
    ifstream infile;
    float fTime = 0;
    int iNumFound;
    uint32_t idCAN;
    unsigned int ulaData[6]={0,};

    if (strFileNameIn.length() == 0 ){
        return;
    }

    QFileInfo fi=strFileNameIn;

    QListIterator<enumIdCAN> idIterator(iDs);
    while (idIterator.hasNext()) {
        QString filename = fi.absoluteFilePath();
        enumIdCAN id = idIterator.next();
        if (outFile.contains(id))
        {
            filename.replace(".txt", QString().sprintf("_%03X.txt", (int)id));
            outFile[id].outFile = new QFile(filename);
        }
    }

    infile.open (strFileNameIn.toStdString().c_str());
//    outFile.open (ucaNameFileOut, std::ofstream::out | std::ofstream::trunc);
    qDebug() << "processing files";

    while( mlRowCounter < 400*1000 && iMaxIterator < 800*1000) //4E5: Max Matlab To get you all the lines.
    {
        unsigned int l_hour=0, l_min=0, l_sec=0, l_ms=0;

        getline(infile,strLine);
        if ( infile.eof() || infile.bad())
        {
            break;
        }

        iNumFound = sscanf( strLine.data() , "%02d:%02d:%02d.%03d;%X:%X.%X.%X.%X.%X.%X",
                                    &l_hour	,&l_min	,&l_sec	,&l_ms	,
                                    &idCAN ,
                                    &ulaData[0],
                                    &ulaData[1],
                                    &ulaData[2],
                                    &ulaData[3],
                                    &ulaData[4],
                                    &ulaData[5]);

        if (iNumFound == 11)
        {
            fTime = (float)(l_ms + (l_sec + l_min*60 + l_hour * 3600)*1000);
            if ( fTime >= ulTimeStart || fTime <= ulTimeStop )
            {
                enumIdCAN id = (enumIdCAN)idCAN;
                if (outFile.contains(id))
                {
                    if (outFile[id].outFile)
                    {
                        QTextStream stream( outFile[id].outFile );

                        if (!outFile[id].outFile->isOpen()) {
                            outFile[id].outFile->open(QIODevice::WriteOnly);
                            if (outFile[id].legendList.empty() == false) {
                                stream << HEADER_PREFIX << " " << LEGENDS_TAG;
                                foreach( QString legend, outFile[id].legendList)
                                    stream << " " << legend;
                                stream << endl;
                            }
                            if (outFile[id].typeList.empty() == false) {
                                stream << HEADER_PREFIX << " " << TYPES_TAG;
                                foreach( QString type, outFile[id].typeList)
                                    stream << " " << type;
                                stream << endl;
                            }
                        }
                        if (memcmp((void *)outFile[id].ulaDataPrev, (void *)ulaData, sizeof(ulaData))) {
                            outFile[id].processPayload(&strOut, (fTime - 0.1), outFile[id].ulaDataPrev);
                            stream << strOut.c_str();
                            outFile[id].processPayload(&strOut, fTime, ulaData);
                            stream << strOut.c_str();
                            memcpy((void *)outFile[id].ulaDataPrev, (void *)ulaData, sizeof(ulaData));
                        }
                    }
                }
            }
            iMaxIterator++;
        }
    }// while..

    {
        QMapIterator<enumIdCAN, structOutFile> outIterator(outFile);
        while (outIterator.hasNext()) {
            outIterator.next();
            if (outIterator.value().outFile)
            {
                if (outIterator.value().outFile->isOpen())
                    outIterator.value().outFile->close();
                delete outIterator.value().outFile;
            }
        }
    }

    infile.close();
}
