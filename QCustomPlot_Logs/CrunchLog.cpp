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
void CrunchLog::unpackBit8(string * pstrOut, unsigned char u8Val, int iNbit)
{
	int ii, iBit;

    if (iNbit > 8)
        iNbit = 8;
    for (ii=0; ii<iNbit; ii++)
	{
		char u8aNum[4];
		iBit = ( u8Val & (1<<ii) ) !=0;
		itoa(iBit,u8aNum,10);
		pstrOut->append(u8aNum);
		pstrOut->append(" ");
	}
}
//--------------------------------------------------------
void CrunchLog::unpackBit32(string *pstrOut, unsigned int uiVal, int iNbit)
{
	int ii, iBit;

    if (iNbit > 32)
        iNbit = 32;
    for (ii=0; ii<iNbit; ii++)
	{
		char u8aNum[4];
		iBit = ( uiVal & (1<<ii) ) !=0;
		itoa(iBit,u8aNum,10);
		pstrOut->append(u8aNum);
		pstrOut->append(" ");
	}
}
//--------------------------------------------------------
void CrunchLog::intToStr(string *pStrOut, unsigned int uiVal, string sfx)
{
    char s8aChar[16]={0,};

    sprintf(s8aChar, "%.1lf", (double)uiVal);
    pStrOut->append(s8aChar);
    pStrOut->append(sfx);
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
bool CrunchLog::decodeTimeString(const char * u8aData, unsigned long &ulTime)
{
    unsigned int l_hour=0, l_min=0, l_sec=0, l_ms=0;
    int32_t iNumFound = sscanf( u8aData , "%02d:%02d:%02d.%03d",
            &l_hour	,
            &l_min	,
            &l_sec	,
            &l_ms	);

    if (iNumFound == 4)
        ulTime = l_ms + (l_sec + l_min*60 + l_hour * 3600)*1000;
    return(iNumFound == 4);
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
