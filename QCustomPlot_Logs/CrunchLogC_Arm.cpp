#include <QDebug>
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
}


//--------------------------------------------------------
void CrunchLogC_Arm::processFile (const char * ucaNameFileIn,
                                  const char * ucaNameFileOut,
                                  const unsigned long ulTimeStart,
                                  const unsigned long ulTimeStop)
{
    string STRING, strOut;
    string previousLine="";
    int iMaxIterator = 0;
    ifstream infile;
    ofstream outFile;
    uint32_t ulTime=0;
    structLog strLog;
    strLog.ulBitMask      = 0;
    strLog.lMcStatus     = 0;
    strLog.ulTableBit    = 0;
    strLog.ulGenStat     = 0;
    strLog.iDllStat      = 0;
    strLog.ulTableBitExt = 0;
    strLog.u8LogicalMode = 0;

    if (ucaNameFileIn == NULL || ucaNameFileOut == NULL ){
        return;
    }

    infile.open (ucaNameFileIn);
    outFile.open (ucaNameFileOut, std::ofstream::out | std::ofstream::trunc);
    outFile.clear();
    qDebug() << "processing files";
    while( mlRowCounter < 400*1000 && iMaxIterator < 800*1000) //4E5: Max Matlab To get you all the lines.
    {
        getline(infile,STRING); // Saves the line in STRING.
        string strTime = STRING;
        unsigned long ulTimeN = 4567890;

        if ( infile.eof() || infile.bad() || ulTimeN > ulTimeStop )
        {
            break;
        }
        else if ( 1 )
        {
            if (STRING != previousLine)// true in the end of file or file corrupted
            {
                previousLine = STRING;
                processController(STRING,
                                  strOut,
                                  outFile,
                                  ulTime,
                                  ulTimeStart,
                                  &strLog);

            }

        }
        iMaxIterator++;
    }// while..

    outFile.close();
    infile.close();
}


//--------------------------------------------------------
void CrunchLogC_Arm::processController(string & STRING,
                                       string & strOut,
                                       ofstream &outFile,
                                       uint32_t & ulTime,
                                       const uint32_t & ulTimeStart,
                                       CrunchLog::structLog * pstrLog
                                       )
{
    //    1907715.2 107942 10
    //    1907821.2 239014 10
    //    1907822.2 501158 11
    //    1907834.2 501190 11
    //    1907835.2 501158 11
    uint32_t
            ulTimeN,
            ulBitMaskNew;
    int lMcStatus;
    float fTime;
    int32_t iNumFound = sscanf( STRING.data() , "%f %lu %d" , &fTime , &ulBitMaskNew, &lMcStatus );
    if ( iNumFound >= 2 )
    {
        ulTimeN = fTime;
        ulTime = MAX(ulTime+1, ulTimeN);

        if ( ulTimeN > ulTimeStart )
        {
            bool bNeedToSave = true;

            if ( isPerformanceOn() )
            {
                bNeedToSave = ( lMcStatus > 3 );
            }

            if (bNeedToSave)
            {
                if ( pstrLog->ulBitMask != ulBitMaskNew || pstrLog->lMcStatus != lMcStatus )
                {
                    ulTime++;
                    finalizeString(&strOut, ulTime, pstrLog);
                    outFile << strOut;
                }
            }
            ulTime++;
            pstrLog->ulBitMask = ulBitMaskNew;
            pstrLog->lMcStatus = lMcStatus ;
            if (bNeedToSave)
            {
                finalizeString(&strOut, ulTime, pstrLog);
                cout<< strOut.c_str(); // Prints out STRING
                outFile << strOut;
            }
        }
    }
}
