#include <QDebug>
#include "CrunchLogDiscovery.h"
#include <iostream>
#include <fstream>
#include <iomanip>

#define MAX(A,B)(((A)>=(B))?(A):(B))

CrunchLogDiscovery::CrunchLogDiscovery()
{
    mbPerformance = true;
    mlRowCounter = 0;
}

//--------------------------------------------------------
void CrunchLogDiscovery::processId652(string & STRING,
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
//--------------------------------------------------------
void CrunchLogDiscovery::processFile (const char * ucaNameFileIn,
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
                else
                {
                    std::size_t pos = STRING.find("OPERATOR TIMING BOOKMARK");
                    if (pos < STRING.size() )
                    {
                        removeCharsUntil(&STRING,"; ");
                        unsigned long ulTimeN = unpackTimeString( STRING.data() );
                        if (ulTimeN > ulTimeStart)
                        {
                            ulTime = MAX(ulTime+1, ulTimeN);
                            finalizeString(&strOut, ++ulTime, &strLog);
                            mlRowCounter++;

                            outFile << strOut;
                            long lMcStat = strLog.lMcStatus;
                            strLog.lMcStatus = 0;
                            finalizeString(&strOut, ++ulTime, &strLog);
                            mlRowCounter++;

                            outFile << strOut;
                            strLog.lMcStatus = lMcStat;
                            finalizeString(&strOut, ++ulTime, &strLog);
                            mlRowCounter++;

                            outFile << strOut;
                        }
                    }
                    else
                    {
                        std::size_t pos = STRING.find("0125");
                        if (pos < STRING.size() )
                        {
                            removeCharsUntil(&STRING,"; ");
                            unsigned long ulTimeN = unpackTimeString( STRING.data() );
                            bool bNeedToSave = true;

                            if (ulTimeN > ulTimeStart)
                            {
                                ulTime = MAX(ulTime+1, ulTimeN);
                                removeCharsUntil(&STRING,"Data = ");
                                finalizeString(&strOut, ++ulTime, &strLog);
                                mlRowCounter++;

                                if ( isPerformanceOn() )
                                {
                                    bNeedToSave = ( strLog.ulTableBit & 0x77FF ) != 0;
                                }
                                if (bNeedToSave)
                                {
                                    outFile << strOut;
                                }
                                sscanf( STRING.data() , "%lx %lx ",
                                        &strLog.ulTableBit,
                                        &strLog.ulTableBitExt );
                                finalizeString(&strOut, ++ulTime, &strLog);
                                mlRowCounter++;

                                if ( isPerformanceOn() )
                                {
                                    bNeedToSave = ( strLog.ulTableBit & 0x77FF ) != 0;
                                }
                                if (bNeedToSave)
                                {
                                    outFile << strOut;
                                }
                            }
                        }
                        else
                        {
                            std::size_t pos = STRING.find("CURRENTSTATE=");
                            std::size_t posB = STRING.find("IQ to DLL");

                            if ( pos < STRING.size() )
                            {
                                removeCharsUntil(&STRING,"; ");
                                unsigned long ulTimeN = unpackTimeString( STRING.data() );
                                if (ulTimeN > ulTimeStart)
                                {
                                    ulTime = MAX(ulTime+1, ulTimeN);
                                    finalizeString(&strOut, ++ulTime, &strLog);
                                    mlRowCounter++;


                                    if (  posB < STRING.size() ){// IQ to DLL
                                        removeCharsUntil(&STRING,"CURRENTSTATE=");
                                        STRING.at(1)= ' ';
                                        strLog.ulGenStat = strtol ( STRING.data(), nullptr, 10);
                                    }else { // DLL to IQ
                                        removeCharsUntil(&STRING,"NEXTSTATE=");
                                        STRING.at(1)= ' ';
                                        strLog.iDllStat = strtol ( STRING.data(), nullptr, 10);
                                    }

                                    finalizeString(&strOut, ++ulTime, &strLog);
                                    mlRowCounter++;

                                    outFile << strOut;
                                }
                            }else
                            {
                                std::size_t pos = STRING.find("<ERROR:");
                                if (pos < STRING.size() )
                                {
                                    removeCharsUntil(&STRING,"; ");
                                    unsigned long ulTimeN = unpackTimeString( STRING.data() );
                                    if (ulTimeN > ulTimeStart)
                                    {
                                        ulTime = MAX(ulTime+1, ulTimeN);
                                        finalizeString(&strOut, ++ulTime, &strLog);
                                        mlRowCounter++;

                                        outFile << strOut;
                                        long lMcStat = strLog.lMcStatus;
                                        strLog.lMcStatus = -5;
                                        finalizeString(&strOut, ++ulTime, &strLog);
                                        mlRowCounter++;

                                        outFile << strOut;
                                        strLog.lMcStatus = lMcStat;
                                        finalizeString(&strOut, ++ulTime, &strLog);
                                        mlRowCounter++;

                                        outFile << strOut;
                                    }
                                }
                                else
                                {
                                    std::size_t pos = STRING.find("enDLL_LogicalMode(43)");
                                    if (pos < STRING.size() )
                                    {
                                        removeCharsUntil(&STRING,"; ");
                                        unsigned long ulTimeN = unpackTimeString( STRING.data() );
                                        if (ulTimeN > ulTimeStart)
                                        {
                                            ulTime = MAX(ulTime+1, ulTimeN);
                                            finalizeString(&strOut, ++ulTime, &strLog);
                                            mlRowCounter++;

                                            outFile << strOut;
                                            removeCharsUntil(&STRING,"(43) 00 00 00 ");
                                            sscanf( STRING.data() , "%cx",
                                                    &strLog.u8LogicalMode );
                                            finalizeString(&strOut, ++ulTime, &strLog);
                                            mlRowCounter++;

                                            outFile << strOut;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }

        }
        iMaxIterator++;
    }// while..

    outFile.close();
    infile.close();
}
//-----------------------------------------------------------------------------
/**
 * @brief CrunchLogDiscovery::process File looking at Apr
 * @param ucaNameFileIn  name of file to be processed
 * @param ucaNameFileOut name of file to be saved
 */
void CrunchLogDiscovery::processApr(const char *ucaNameFileIn,
                                    const char *ucaNameFileOut)
{
    string STRING, strOut, strApr;
    string previousLine="";
    ifstream infile;
    ofstream outFile , outFileDose;
    int iRowCounter=0;
    int iDoseZero = 0;
    int iDoseDigits = 0;
    int iTotRad = 0, iTotFluo = 0;

    if (ucaNameFileIn == nullptr || ucaNameFileOut == nullptr ){
        return;
    }
    outFileDose.open("apr.txt", std::ofstream::out | std::ofstream::trunc);
    infile.open (ucaNameFileIn);
    outFile.open (ucaNameFileOut, std::ofstream::out | std::ofstream::trunc);

    qDebug()<<"processing files";
    while(iRowCounter<3000000) // To get you all the lines.
    {
        getline(infile,STRING); // Saves the line in STRING.
        if (infile.eof() || infile.bad() ){
            break;
        }
        if (STRING != previousLine)// true in the end of file or file corrupted
        {
            previousLine = STRING;
            std::size_t pos = STRING.find("KD_MSG_RAD_POST_DATA_x10 - Dose=");// if "find" fails then pos  = 4000000
            if (pos < STRING.size() )
            { // found <Id = 0652
                iTotRad++;
                strOut.assign(STRING);
                removeCharsUntil(&strOut,"; ");
                uint32_t ulTime = unpackTimeString( strOut.data() );
                removeCharsUntil(&strOut, "Dose=");
                int num1 = std::stoi(strOut);
                outFileDose <<
                               std::to_string(ulTime) << ";" <<
                               std::to_string(num1)   << std::endl;

                if(num1 == 0){
                    outFile << "ZERO ";
                    iDoseZero++;
                }
                else if((num1 %100) == 0){
                    outFile << "DIGITS ";
                    iDoseDigits++;
                }
                outFile << STRING << std::endl;
                getline(infile,STRING); // Saves the line in STRING.
                std::size_t pos2 = STRING.find("KD_MSG_COLLIMATOR_DATA");// if "find" fails then pos  = 4000000
                if (pos2 < STRING.size() )
                {
                    outFile << STRING << std::endl;
                }
            }else
            {
                std::size_t pos = STRING.find("KD_MSG_FLUO_POST_DATA_x10 - Dose=");// if "find" fails then pos  = 4000000
                if (pos < STRING.size() )
                { // found <Id = 0652
                    iTotFluo++;
                    strOut.assign(STRING);
                    removeCharsUntil(&strOut,"; ");
                    uint32_t ulTime = unpackTimeString( strOut.data() );
                    removeCharsUntil(&strOut, "Dose=");
                    int num1 = std::stoi(strOut);
                    outFileDose <<
                                   std::to_string(ulTime) << ";" <<
                                   std::to_string(num1)   << std::endl;
                    if(num1 == 0){
                        outFile << "ZERO ";
                        iDoseZero++;
                    }
                    else if((num1 %100) == 0){
                        outFile << "DIGITS ";
                        iDoseDigits++;
                    }
                    outFile << STRING << std::endl;
                    getline(infile,STRING); // Saves the line in STRING.
                    std::size_t pos2 = STRING.find("KD_MSG_COLLIMATOR_DATA");// if "find" fails then pos  = 4000000
                    if (pos2 < STRING.size() )
                    {
                        outFile << STRING << std::endl;
                    }
                }
                else
                {
                    std::size_t pos = STRING.find("<KD_MSG_SET_ANATOMIC - AnatomicName=");
                    if (pos < STRING.size() )
                    {
                        strApr.assign(STRING);
                        removeCharsUntil(&strApr,"; ");
                        removeChars(&strApr,"<KD_MSG_SET_ANATOMIC - AnatomicName=");
                        removeChars(&strApr,">");
                    }
                    else
                    {
                        std::size_t pos = STRING.find("<KD_MSG_SET_PROJECTION - ProjectionName=");
                        if (pos < STRING.size() )
                        {
                            strOut.assign(STRING);
                            removeCharsUntil(&strOut,"<KD_MSG_SET_PROJECTION - ProjectionName=");
                            removeChars(&strOut,">");
                            strApr.append(" - ");
                            strApr.append(strOut);
                            outFile << strApr << std::endl;
                        }
                    }
                }
            }
        }
        iRowCounter++;
    }// while..
    outFile << "\r\n Statistics:";
    outFile << ", ZERO dose =" << std::to_string(iDoseZero)   ;
    outFile << ", ZEROED Digits =" << std::to_string(iDoseDigits);
    outFile << ", Tot Rad =" << std::to_string(iTotRad);
    outFile << ", Tot Fluo =" << std::to_string(iTotFluo) << std::endl;
    outFile.close();
    infile.close();
    outFileDose.close();
}
//-----------------------------------------------------------------------------
void CrunchLogDiscovery::processDose(const char *ucaNameFileIn,
                                     const char *ucaNameFileOut)
{
    string STRING, strOut;
    string previousLine="";
    ifstream infile;
    ofstream outFile , outFileDose;
    int iRowCounter=0;
    int iDoseZero = 0;
    int iDoseDigits = 0;
    int iTotRad = 0, iTotFluo = 0;

    if (ucaNameFileIn == nullptr || ucaNameFileOut == nullptr ){
        return;
    }
    outFileDose.open("dose.txt", std::ofstream::out | std::ofstream::trunc);
    infile.open (ucaNameFileIn);
    outFile.open (ucaNameFileOut, std::ofstream::out | std::ofstream::trunc);

    qDebug()<<"processing files";
    while(iRowCounter<3000000) // To get you all the lines.
    {
        getline(infile,STRING); // Saves the line in STRING.
        if (infile.eof() || infile.bad() ){
            break;
        }
        if (STRING != previousLine)// true in the end of file or file corrupted
        {
            previousLine = STRING;
            std::size_t pos = STRING.find("KD_MSG_RAD_POST_DATA_x10 - Dose=");// if "find" fails then pos  = 4000000
            if (pos < STRING.size() )
            { // found <Id = 0652
                iTotRad++;
                strOut.assign(STRING);
                removeCharsUntil(&strOut,"; ");
                uint32_t ulTime = unpackTimeString( strOut.data() );
                removeCharsUntil(&strOut, "Dose=");
                int num1 = std::stoi(strOut);
                outFileDose <<
                               std::to_string(ulTime) << ";" <<
                               std::to_string(num1)   << std::endl;

                if(num1 == 0){
                    outFile << "ZERO ";
                    iDoseZero++;
                }
                else if((num1 %100) == 0){
                    outFile << "DIGITS ";
                    iDoseDigits++;
                }
                outFile << STRING << std::endl;
                getline(infile,STRING); // Saves the line in STRING.
                std::size_t pos2 = STRING.find("KD_MSG_COLLIMATOR_DATA");// if "find" fails then pos  = 4000000
                if (pos2 < STRING.size() )
                {
                    outFile << STRING << std::endl;
                }
            }else
            {
                std::size_t pos = STRING.find("KD_MSG_FLUO_POST_DATA_x10 - Dose=");// if "find" fails then pos  = 4000000
                if (pos < STRING.size() )
                { // found <Id = 0652
                    iTotFluo++;
                    strOut.assign(STRING);
                    removeCharsUntil(&strOut,"; ");
                    uint32_t ulTime = unpackTimeString( strOut.data() );
                    removeCharsUntil(&strOut, "Dose=");
                    int num1 = std::stoi(strOut);
                    outFileDose <<
                                   std::to_string(ulTime) << ";" <<
                                   std::to_string(num1)   << std::endl;
                    if(num1 == 0){
                        outFile << "ZERO ";
                        iDoseZero++;
                    }
                    else if((num1 %100) == 0){
                        outFile << "DIGITS ";
                        iDoseDigits++;
                    }
                    outFile << STRING << std::endl;
                    getline(infile,STRING); // Saves the line in STRING.
                    std::size_t pos2 = STRING.find("KD_MSG_COLLIMATOR_DATA");// if "find" fails then pos  = 4000000
                    if (pos2 < STRING.size() )
                    {
                        outFile << STRING << std::endl;
                    }
                }
                else
                {
                    std::size_t pos = STRING.find("DAPDose");
                    if (pos < STRING.size() )
                    {
                        outFile << STRING << std::endl;
                    }
                    else
                    {
                        std::size_t pos = STRING.find("SUBJECT Main Controller DEVICE System");
                        if (pos < STRING.size() )
                        {
                            outFile << STRING << std::endl;
                        }
                    }
                }
            }
        }
        iRowCounter++;
    }// while..
    outFile << "\r\n Statistics:";
    outFile << ", ZERO dose =" << std::to_string(iDoseZero)   ;
    outFile << ", ZEROED Digits =" << std::to_string(iDoseDigits);
    outFile << ", Tot Rad =" << std::to_string(iTotRad);
    outFile << ", Tot Fluo =" << std::to_string(iTotFluo) << std::endl;
    outFile.close();
    infile.close();
    outFileDose.close();
}
