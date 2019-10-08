#include "CrunchLog.h"
#include <QString>
#include "mainwindow.h"
//#include <QDebug>
#include "ui_mainwindow.h"


CrunchLog::CrunchLog()
{

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
								unsigned long ulTableBitExt)
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
	pStrOut->append("\n");

}
//--------------------------------------------------------
void CrunchLog::processFile (const char * ucaNameFileIn,
							 const char * ucaNameFileOut,
							 const unsigned long ulTimeStart,
							 const unsigned long ulTimeStop)
{
	string STRING, strOut;
	string previousLine="";
	ifstream infile;
	ofstream outFile;
	int iRowCounter=0;
	unsigned int
			lBitMask=0,
			ulTime=0,
			ulaData[8]={0,};
	long lMcStatus=0;
	unsigned long
			u8TableBit = 0,
			u8TableExtBit = 0;
	int iGenStat = 0, iDllStat = 0;

	if (ucaNameFileIn == NULL || ucaNameFileOut == NULL ){
		return;
	}

	infile.open (ucaNameFileIn);
	outFile.open (ucaNameFileOut, std::ofstream::out | std::ofstream::trunc);

	qDebug()<<"processing files";
	while(iRowCounter<1000000) // To get you all the lines.
	{
		getline(infile,STRING); // Saves the line in STRING.
		if (infile.eof() || infile.bad() ){
			break;
		}
		if (STRING != previousLine)// true in the end of file or file corrupted
		{
			previousLine = STRING;
			std::size_t pos = STRING.find("<Id = 0652");// if "find" fails then pos  = 4000000
			if (pos < STRING.size() )
			{ // found <Id = 0652
				removeCharsUntil(&STRING,"; ");
				ulTime = unpackTimeString( STRING.data() );
				if (ulTime > ulTimeStop){
					break; // end of time interval
				}else if (ulTime > ulTimeStart)
				{
					removeCharsUntil(&STRING,"DEBUG data = ");
					removeChars(&STRING,"0X");// replace 0X with blank spaces
					sscanf( STRING.data() , "%x %x %x %x %x %x",
							&ulaData[0] ,
							&ulaData[1] ,
							&ulaData[2] ,
							&ulaData[3] ,
							&ulaData[4] ,
							&ulaData[5] );// extract numbers
					lBitMask = ulaData[1];
					lBitMask+= (ulaData[2]<<8);
					lBitMask+= (ulaData[3]<<16);
					lBitMask+= (ulaData[4]<<24);
					lMcStatus = ulaData[5] ;
					switch(ulaData[0])
					{
					case 6:
						finalizeString(&strOut, ulTime, lBitMask, lMcStatus,
									   u8TableBit, iGenStat, iDllStat, u8TableExtBit);
						cout<< strOut.c_str(); // Prints out STRING
						outFile << strOut;
						break;
					}
				}
			}
			else
			{
				std::size_t pos = STRING.find("OPERATOR TIMING BOOKMARK");
				if (pos < STRING.size() )
				{
					removeCharsUntil(&STRING,"; ");
					ulTime = unpackTimeString( STRING.data() );
					finalizeString(&strOut, ulTime-1, lBitMask, lMcStatus,
								   u8TableBit, iGenStat, iDllStat, u8TableExtBit);
					outFile << strOut;
					finalizeString(&strOut, ulTime, lBitMask, 0, u8TableBit,
								   iGenStat, iDllStat, u8TableExtBit);
					outFile << strOut;
					finalizeString(&strOut, ulTime+1, lBitMask, lMcStatus,
								   u8TableBit, iGenStat, iDllStat, u8TableExtBit);
					outFile << strOut;
				}
				else
				{
					std::size_t pos = STRING.find("0125");
					if (pos < STRING.size() )
					{
						removeCharsUntil(&STRING,"; ");
						ulTime = unpackTimeString( STRING.data() );
						removeCharsUntil(&STRING,"Data = ");
						finalizeString(&strOut, ulTime-1, lBitMask, lMcStatus,
									   u8TableBit, iGenStat, iDllStat, u8TableExtBit);
						outFile << strOut;

						sscanf( STRING.data() , "%x %x ",
								&u8TableBit,
								&u8TableExtBit );
						finalizeString(&strOut, ulTime, lBitMask, lMcStatus,
									   u8TableBit, iGenStat, iDllStat, u8TableExtBit);
						outFile << strOut;
					}
					else
					{
						std::size_t pos = STRING.find("CURRENTSTATE=");
						std::size_t posB = STRING.find("IQ to DLL");

						if ( pos < STRING.size() )
						{
							removeCharsUntil(&STRING,"; ");
							ulTime = unpackTimeString( STRING.data() );
							finalizeString(&strOut, ulTime-1,
										   lBitMask, lMcStatus,
										   u8TableBit, iGenStat, iDllStat, u8TableExtBit);

							if (  posB < STRING.size() ){// IQ to DLL
								removeCharsUntil(&STRING,"CURRENTSTATE=");
								STRING.at(1)= ' ';
								iGenStat = strtol ( STRING.data(), NULL, 10);
							}else { // DLL to IQ
								removeCharsUntil(&STRING,"NEXTSTATE=");
								STRING.at(1)= ' ';
								iDllStat = strtol ( STRING.data(), NULL, 10);
								iDllStat = (iDllStat<<1)/2;
							}

							finalizeString(&strOut, ulTime,
										   lBitMask, lMcStatus,
										   u8TableBit, iGenStat, iDllStat, u8TableExtBit);
							outFile << strOut;
						}
					}
				}
			}
		}
		iRowCounter++;
	}// while..

	outFile.close();
	infile.close();
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
