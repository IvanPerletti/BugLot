#include "CrunchLog.h"
#include <QString>
#include "mainwindow.h"
//#include <QDebug>
#include "ui_mainwindow.h"
#define MAX(A,B)(((A)>=(B))?(A):(B))

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

void CrunchLog::finalizeString2(string *pStrOut,
                               float ulTime,
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
    itoa(ulTime, s8aDummy, 16);
    snprintf(s8aDummy, 16, "%.1f", ulTime);
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
                               float ulTime,
                               CrunchLog::structLog * pstrLog)
{
	if ( pstrLog != nullptr && pStrOut != nullptr )
	{
        finalizeString2( pStrOut                ,
						ulTime                 ,
						pstrLog->ulBitMask      ,
						pstrLog->lMcStatus     ,
						pstrLog->ulTableBit    ,
						pstrLog->ulGenStat     ,
						pstrLog->iDllStat      ,
						pstrLog->ulTableBitExt ,
						pstrLog->u8LogicalMode );
	}
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
