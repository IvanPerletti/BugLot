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
	CrunchLog();
	void processFile(const char *ucaNameFileIn,
					 const char *ucaNameFileOut,
					 const unsigned long ulTimeStart = 0,
					 const unsigned long ulTimeStop = 24*60*60);
	void extractLog (const char * ucaNameFileIn,
					 const char * ucaNameFileOut,
					 const char * ucaStrToSearch,
					 const unsigned long ulNumLineNext);
	private:
	void unpackBit8(string * pstrOut, unsigned char u8Val);
	void unpackBit32(string * pstrOut, unsigned int uiVal);
	unsigned long unpackTimeString(const char * u8aData);
	void removeCharsUntil(string * strProcessed, string strMatchToFind);
	void removeChars( string * strProcessed, string strMatchToFind);
	void finalizeString(string *pStrOut, unsigned long ulTime,
						long lBitMask,
						long lMcStatus,
						unsigned char u8TableBit,
						int u8GenStat, int iDllStat);

	void strReplaceOccurrence(string *pStrOut,
							  const string csSubStrLook,
							  const string csSubStrSubst );


};

#endif // CRUNCHLOG_H
