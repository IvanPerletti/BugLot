#ifndef CRUNCHLOG_H
#define CRUNCHLOG_H
#include <string>
#include <QString>
#include "cprocesslogs.h"

using namespace std;

class CrunchLog: public CProcessLogs
{
public:
    CrunchLog(const char * ucaNameFileIn, const char * ucaNameFileOut);
    void processFile(const char *ucaNameFileIn, const char *ucaNameFileOut);

private:
    void unpackBit(string * pstrOut, unsigned int uiVal);
    unsigned long unpackTimeString(const char * u8aData);
    void removeCharsUntil(string * strProcessed, string strMatchToFind);
    void removeChars( string * strProcessed, string strMatchToFind);
    void finalizeString( string *pStrOut, unsigned long ulTime, long lBitMask, long lMcStatus);
    void strReplaceOccurrence(string *pStrOut,
                              const string csSubStrLook,
                              const string csSubStrSubst );


};

#endif // CRUNCHLOG_H
