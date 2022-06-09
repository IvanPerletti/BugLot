#include <QString>
#include <QFileInfo>
#include <QMap>
#include <QMetaEnum>
#include <QDebug>
#include <fstream>

#include "CrunchLog.h"

#define MAX(A,B)(((A)>=(B))?(A):(B))

CrunchLog::CrunchLog()
{

}

//--------------------------------------------------------
QList<CrunchMsg::enumIdCAN> CrunchLog::processFile (QString strFileNameIn,
                             const unsigned long ulTimeStart,
                             const unsigned long ulTimeStop)
{
    string strLine, strOut;
    int iMaxIterator = 0;
    ifstream infile;
    float fTime = 0;
    int iNumFound;
    uint32_t idCAN;
    unsigned int ulaData[PAYLOAD_SIZE]={0,};
    QList<CrunchMsg::enumIdCAN> iDsFound;
    QMetaEnum e = QMetaEnum::fromType<CrunchMsg::enumIdCAN>();

    if (strFileNameIn.length() == 0 ){
        return iDsFound;
    }

    QFileInfo fi=strFileNameIn;
    QString filename = fi.absoluteFilePath();

    for (int k = 0; k < e.keyCount(); k++) {
        CrunchMsg *msg;

        if ((msg = CrunchMsg::newCrunchMsg((CrunchMsg::enumIdCAN)e.value(k), filename)) != nullptr)
            crunchMsg[(CrunchMsg::enumIdCAN)e.value(k)] = msg;
    }

    infile.open (strFileNameIn.toStdString().c_str());

    while(iMaxIterator < 800*1000) //4E5: Max Matlab To get you all the lines.
    {
        unsigned int l_hour=0, l_min=0, l_sec=0, l_ms=0;

        getline(infile,strLine);
        if ( infile.eof() || infile.bad())
        {
            break;
        }

        iNumFound = sscanf( strLine.data() , "%02d:%02d:%02d.%03d;%X:%X.%X.%X.%X.%X.%X.%X.%X",
                                    &l_hour	,&l_min	,&l_sec	,&l_ms	,
                                    &idCAN ,
                                    &ulaData[0],
                                    &ulaData[1],
                                    &ulaData[2],
                                    &ulaData[3],
                                    &ulaData[4],
                                    &ulaData[5],
                                    &ulaData[6],
                                    &ulaData[7]
                );

        if (iNumFound > 5)
        {
            fTime = (float)(l_ms + (l_sec + l_min*60 + l_hour * 3600)*1000);
            if ( fTime >= ulTimeStart || fTime <= ulTimeStop )
            {
                CrunchMsg *msg;

                CrunchMsg::enumIdCAN id = (CrunchMsg::enumIdCAN)idCAN;
                if (crunchMsg.contains(id)) {
                    msg = crunchMsg[id];
                    msg->processMsg(fTime, ulaData);
                    if (!iDsFound.contains(id))
                        iDsFound << id;
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

    return iDsFound;
}
