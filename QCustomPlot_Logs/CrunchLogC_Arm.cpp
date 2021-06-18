#include <QDebug>
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
        unsigned long ulTimeN = 0;
        removeCharsUntil( &strTime , ";" );
        ulTimeN = unpackTimeString( strTime.data() );

        if ( infile.eof() || infile.bad() || ulTimeN > ulTimeStop )
        {
            break;
        }
        else if ( ulTimeN >= ulTimeStart )
        {
            if (STRING != previousLine)// true in the end of file or file corrupted
            {
                previousLine = STRING;
                std::size_t pos = STRING.find("<Id = 0652");// if "find" fails then pos  = 4000000
                if (pos < STRING.size() )
                { // found <Id = 0652
                    processId652(STRING,
                                 strOut,
                                 outFile,
                                 ulTime,
                                 ulTimeStart,
                                 &strLog);
                }
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
    removeCharsUntil(&STRING,"; ");
    unsigned long ulTimeN = unpackTimeString( STRING.data() );
    ulTime = MAX(ulTime+1, ulTimeN);
    if (ulTimeN > ulTimeStart)
    {
        long unsigned int ulaData[6]={0,};
        removeCharsUntil(&STRING,"DEBUG data = ");
        removeChars(&STRING,"0X");// replace 0X with blank spaces
        sscanf( STRING.data() , "%lx %lx %lx %lx %lx %lx",
                &ulaData[0] ,
                &ulaData[1] ,
                &ulaData[2] ,
                &ulaData[3] ,
                &ulaData[4] ,
                &ulaData[5] ); // extract numbers
        // ACHTUNG: warning is necessary for proper conversion
        unsigned long ulBitMaskNew = ulaData[1];
        ulBitMaskNew += (ulaData[2]<<8);
        ulBitMaskNew += (ulaData[3]<<16);
        ulBitMaskNew += (ulaData[4]<<24);
        long lMcStatus = ulaData[5];
        bool bNeedToSave = true;
        if ( isPerformanceOn() )
        {
            bNeedToSave = ( lMcStatus > 3 );
        }
        switch(ulaData[0])
        {
        case 6:
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
            pstrLog->lMcStatus = ulaData[5] ;
            if (bNeedToSave)
            {
                finalizeString(&strOut, ulTime, pstrLog);
                cout<< strOut.c_str(); // Prints out STRING
                outFile << strOut;
            }
            break;
        }
    }
}
