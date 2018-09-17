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

void CrunchLog::finalizeString( string *pStrOut,
								unsigned long ulTime,
								long lBitMask,
								long lMcStatus,
								unsigned char u8TableBit,
								unsigned char u8GenStat)
{
	char s8aDummy[16]={0,}; // more than max Int number: 9 digits + sign
	char s8aChar[1];

	pStrOut->clear();
	itoa(ulTime, s8aDummy, 10);
	pStrOut->append(s8aDummy);
	pStrOut->append(" " );
	unpackBit32(pStrOut, lBitMask);
	itoa( lMcStatus,s8aDummy, 10);
	pStrOut->append(s8aDummy);
	pStrOut->append(" " );
	unpackBit8(pStrOut, u8TableBit);
	pStrOut->append(" " );
	itoa(u8GenStat, s8aChar, 10);
	pStrOut->append(s8aChar);
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
			lMcStatus=0,
			ulaData[8]={0,};
	unsigned char
			u8TableBit = 0,
			u8GenStat = 0;

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
						finalizeString(&strOut, ulTime, lBitMask, lMcStatus, u8TableBit, u8GenStat);
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
								   u8TableBit, u8GenStat);
					outFile << strOut;
					finalizeString(&strOut, ulTime, lBitMask, 0, u8TableBit, u8GenStat);
					outFile << strOut;
					finalizeString(&strOut, ulTime+1, lBitMask, lMcStatus,
								   u8TableBit, u8GenStat);
					outFile << strOut;
				}
				else
				{
					std::size_t pos = STRING.find("<Id = CAN_ID_CLISIS_DBG_125 (0125)");
					if (pos < STRING.size() )
					{
						removeCharsUntil(&STRING,"; ");
						ulTime = unpackTimeString( STRING.data() );
						removeCharsUntil(&STRING,"Data = ");
						finalizeString(&strOut, ulTime-1, lBitMask, lMcStatus,
									   u8TableBit, u8GenStat);
						outFile << strOut;
						sscanf( STRING.data() , "%x", &u8TableBit );
						finalizeString(&strOut, ulTime, lBitMask, lMcStatus,
									   u8TableBit, u8GenStat);
						outFile << strOut;
					}
					else
					{
						std::size_t pos = STRING.find("CURRENTSTATE=");
						if (pos < STRING.size() )
						{
							removeCharsUntil(&STRING,"; ");
							ulTime = unpackTimeString( STRING.data() );
							removeCharsUntil(&STRING,"CURRENTSTATE=");
							finalizeString(&strOut, ulTime-1,
										   lBitMask, lMcStatus, u8TableBit, u8GenStat);
							char u8aArray[16]={0,};
							STRING.at(1)=' ';
							sscanf( STRING.data() , "%d %s", &u8GenStat, &u8aArray);
							finalizeString(&strOut, ulTime,
										   lBitMask, lMcStatus, u8TableBit, u8GenStat);
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

