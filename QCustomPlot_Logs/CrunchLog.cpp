#include <QString>
#include <QFileInfo>
#include <QMap>
#include <QDebug>
#include <fstream>

#include "CrunchLog.h"

#define MAX(A,B)(((A)>=(B))?(A):(B))

CrunchLog::CrunchLog()
{

}

CrunchMsg *CrunchLog::newCrunchMsg(CrunchMsg::enumIdCAN id, QString filename)
{
    CrunchMsg *crunchMsg = nullptr;

    switch (id) {
    case CrunchMsg::ID_CAN_CONTR:
        crunchMsg = new CrunchMsg_0x6A0(filename);
        break;
    case CrunchMsg::ID_CAN_INV_A:
        crunchMsg = new CrunchMsg_0x5A0(filename);
        break;
    case CrunchMsg::ID_CAN_INV_B:
        crunchMsg = new CrunchMsg_0x5A1(filename);
        break;
    }

    return crunchMsg;
}

//--------------------------------------------------------
void CrunchLog::processFile (QString strFileNameIn,
                                  QList<CrunchMsg::enumIdCAN> iDs,
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
    QString filename = fi.absoluteFilePath();

    QListIterator<CrunchMsg::enumIdCAN> idIterator(iDs);
    while (idIterator.hasNext()) {
        CrunchMsg *msg;

        CrunchMsg::enumIdCAN id = idIterator.next();
        if ((msg = newCrunchMsg(id, filename)) != nullptr)
            crunchMsg[id] = msg;
    }

    infile.open (strFileNameIn.toStdString().c_str());
//    outFile.open (ucaNameFileOut, std::ofstream::out | std::ofstream::trunc);

    while(iMaxIterator < 800*1000) //4E5: Max Matlab To get you all the lines.
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
                CrunchMsg *msg;

                CrunchMsg::enumIdCAN id = (CrunchMsg::enumIdCAN)idCAN;
                if (crunchMsg.contains(id)) {
                    msg = crunchMsg[id];
                    msg->processMsg(fTime, ulaData);
                }
            }
            iMaxIterator++;
        }
    }

    {
        QMapIterator<CrunchMsg::enumIdCAN, CrunchMsg *> outIterator(crunchMsg);
        while (outIterator.hasNext()) {
            outIterator.next();
            if (outIterator.value())
                delete outIterator.value();
        }
    }

    infile.close();
}
