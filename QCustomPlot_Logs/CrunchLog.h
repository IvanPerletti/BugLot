/*
#ifndef CRUNCHLOG_H
#define CRUNCHLOG_H

#include <QDialog>

namespace Ui {
class CrunchLog;
}

class CrunchLog : public QDialog
{
	Q_OBJECT

public:
	explicit CrunchLog(QWidget *parent = 0);
	~CrunchLog();

private:
	Ui::CrunchLog *ui;
};
 */
#ifndef CRUNCHLOG_H
#define CRUNCHLOG_H
#include <string>
#include <QString>
#include "mainwindow.h"
using namespace std;

class CrunchLog
{
	public:
	typedef struct
	{
		unsigned long  ulBitMask    ;
		long           lMcStatus    ;
		unsigned long  ulTableBit   ;
		int            ulGenStat    ;
		int            iDllStat     ;
		unsigned long  ulTableBitExt;
		unsigned char  u8LogicalMode;
	} structLog;
	private:
	bool mbPerformance;
	long mlRowCounter;
	public:
	CrunchLog();
	void processApr(const char *ucaNameFileIn, const char *ucaNameFileOut);
	void processDose(const char *ucaNameFileIn,
					 const char *ucaNameFileOut);
	void processFile(const char *ucaNameFileIn,
					 const char *ucaNameFileOut,
					 const unsigned long ulTimeStart = 0,
					 const unsigned long ulTimeStop = 24*60*60);
	void extractLog (const char * ucaNameFileIn,
					 const char * ucaNameFileOut,
					 const char * ucaStrToSearch,
					 const unsigned long ulNumLineNext);
	void setPerformance(bool bFlad){mbPerformance = bFlad;}
	bool isPerformanceOn(){return mbPerformance ;}
	private:
	void unpackBit8(string * pstrOut, unsigned char u8Val);
	void unpackBit32(string * pstrOut, unsigned int uiVal);
	unsigned long unpackTimeString(const char * u8aData);
	void removeCharsUntil(string * strProcessed, string strMatchToFind);
	void removeChars( string * strProcessed, string strMatchToFind);
	void finalizeString(string *pStrOut,
						unsigned long ulTime,
						unsigned long lBitMask,
						long lMcStatus,
						unsigned long ulTableBit,
						int u8GenStat,
						int iDllStat,
						unsigned long ulTableBitExt,
						unsigned char u8LogicalMode);
	void finalizeString(string *pStrOut,
						unsigned long ulTime,
						structLog *pstrLog);
	void strReplaceOccurrence(string *pStrOut,
							  const string csSubStrLook,
							  const string csSubStrSubst );

	void processId652(string & STRING,
					  string & strOut,
					  ofstream &outFile,
					  uint32_t & ulTime,
					  const uint32_t &ulTimeStart,
					  CrunchLog::structLog * pstrLog);
};

#endif // CRUNCHLOG_H
