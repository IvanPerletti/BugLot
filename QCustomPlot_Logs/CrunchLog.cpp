#include "CrunchLog.h"
#include <QString>
#include "mainwindow.h"
//#include <QDebug>
#include "ui_mainwindow.h"
#define MAX(A,B)(((A)>=(B))?(A):(B))

CrunchLog::CrunchLog()
{
	mbPerformance = true;
	mlRowCounter = 0;
}


#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;


//--------------------------------------------------------
void CrunchLog::unpackBit8(string * pstrOut, unsigned char u8Val)
{
	int ii, iBit;

	for (ii=0; ii<8; ii++)
	{
		char u8aNum[4];
		iBit = ( u8Val & (1<<ii) ) !=0;
		itoa(iBit,u8aNum,10);
		pstrOut->append(u8aNum);
		pstrOut->append(" ");
	}
}
//--------------------------------------------------------
void CrunchLog::unpackBit32(string * pstrOut, unsigned int uiVal)
{
	int ii, iBit;

	for (ii=0; ii<19; ii++)
	{
		char u8aNum[4];
		iBit = ( uiVal & (1<<ii) ) !=0;
		itoa(iBit,u8aNum,10);
		pstrOut->append(u8aNum);
		pstrOut->append(" ");
	}
}
//--------------------------------------------------------
unsigned long CrunchLog::unpackTimeString(const char * u8aData)
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
void CrunchLog::removeCharsUntil(string * strProcessed, string strMatchToFind)
{
	size_t szPos;

	szPos = strProcessed->find(strMatchToFind);
	if (szPos < strProcessed->size() ){
		strProcessed->erase (0, szPos+strMatchToFind.size());
	}
}
//--------------------------------------------------------
void CrunchLog::removeChars(string * strProcessed, string strMatchToFind)
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

void CrunchLog::finalizeString(string *pStrOut,
							   unsigned long ulTime,
							   unsigned long lBitMask,
							   long lMcStatus,
							   unsigned long ulTableBit,
							   int u8GenStat,
							   int iDllStat,
							   unsigned long ulTableBitExt,
							   unsigned char u8LogicalMode)
{
	char s8aDummy[16]={0,}; // more than max Int number: 9 digits + sign
	char s8aChar[10]={0,};

	pStrOut->clear();
	itoa(ulTime, s8aDummy, 10);
	pStrOut->append(s8aDummy);
	pStrOut->append(" " );
	unpackBit32(pStrOut, lBitMask);
	itoa( lMcStatus,s8aDummy, 10);
	pStrOut->append(s8aDummy);
	pStrOut->append(" " );
	unpackBit8(pStrOut, static_cast<unsigned char>( ulTableBit ));
	//	pStrOut->append(" " );already in unpack8Bit
	itoa(u8GenStat, s8aChar, 10);
	pStrOut->append(s8aChar);
	pStrOut->append(" " );
	memset(s8aChar,0,sizeof(s8aChar));
	itoa(iDllStat, s8aChar, 10);
	pStrOut->append(s8aChar);
	pStrOut->append(" " );
	unpackBit8(pStrOut, static_cast<unsigned char>(ulTableBitExt) );
	itoa( u8LogicalMode, s8aDummy, 10);
	pStrOut->append(s8aDummy) ;
	pStrOut->append("\n");
}
//--------------------------------------------------------
void CrunchLog::finalizeString(string *pStrOut,
							   unsigned long ulTime,
							   CrunchLog::structLog * pstrLog)
{
	if ( pstrLog != nullptr && pStrOut != nullptr )
	{
		finalizeString( pStrOut                ,
						ulTime                 ,
						pstrLog->ulBitMask      ,
						pstrLog->lMcStatus     ,
						pstrLog->ulTableBit    ,
						pstrLog->ulGenStat     ,
						pstrLog->iDllStat      ,
						pstrLog->ulTableBitExt ,
						pstrLog->u8LogicalMode );
		mlRowCounter++;
	}
}
//--------------------------------------------------------
void CrunchLog::processId652(string & STRING,
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
void CrunchLog::processFile (const char * ucaNameFileIn,
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
							outFile << strOut;
							long lMcStat = strLog.lMcStatus;
							strLog.lMcStatus = 0;
							finalizeString(&strOut, ++ulTime, &strLog);
							outFile << strOut;
							strLog.lMcStatus = lMcStat;
							finalizeString(&strOut, ++ulTime, &strLog);
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
										outFile << strOut;
										long lMcStat = strLog.lMcStatus;
										strLog.lMcStatus = -5;
										finalizeString(&strOut, ++ulTime, &strLog);
										outFile << strOut;
										strLog.lMcStatus = lMcStat;
										finalizeString(&strOut, ++ulTime, &strLog);
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
											outFile << strOut;
											removeCharsUntil(&STRING,"(43) 00 00 00 ");
											sscanf( STRING.data() , "%cx",
													&strLog.u8LogicalMode );
											finalizeString(&strOut, ++ulTime, &strLog);
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
 * @brief CrunchLog::process File looking at Apr
 * @param ucaNameFileIn  name of file to be processed
 * @param ucaNameFileOut name of file to be saved
 */
void CrunchLog::processApr(const char *ucaNameFileIn,
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
void CrunchLog::processDose(const char *ucaNameFileIn,
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
//--------------------------------------------------------
void CrunchLog::strReplaceOccurrence(string *pStrOut,
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


//--------------------------------------------------------
void CrunchLog::extractLog (const char * ucaNameFileIn,
							const char * ucaNameFileOut,
							const char * ucaStrToSearch,
							const unsigned long ulNumLineNext)
{
	string STRING;
	string previousLine="";
	ifstream infile;
	ofstream outFile;
	unsigned long iRowCounter=0;

	if (ucaNameFileIn == NULL || ucaNameFileOut == NULL ){
		return;
	}

	infile.open (ucaNameFileIn);
	outFile.open (ucaNameFileOut, std::ofstream::out | std::ofstream::trunc);

	qDebug()<<"processing Extract Log";
	while(iRowCounter<10000000) // To get you all the lines.
	{
		getline(infile,STRING); // Saves the line in STRING.
		if (infile.eof() || infile.bad() ){
			break;
		}
		if (STRING != previousLine)// true in the end of file or file corrupted
		{
			previousLine = STRING;
			std::size_t pos = STRING.find(ucaStrToSearch);// if "find" fails then pos  = 4000000
			if (pos < STRING.size() )
			{ // found <Id = 0652
				for (unsigned int jj=0; jj< ulNumLineNext; jj++)
				{
					getline(infile,STRING); // Saves the line in STRING.
					if (infile.eof() || infile.bad() ){
						break;
					}
					outFile << STRING <<"\n";
				}
			}
		}
	}
	outFile.close();
	infile.close();
}
