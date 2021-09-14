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

#include <QFile>
#include <string>

using namespace std;

#define HEADER_PREFIX   "%"
#define LEGENDS_TAG     "Legends:"
#define TYPES_TAG       "Types:"
#define TYPE_INT        "I"
#define TYPE_BIT        "B"

class CrunchLog
{
public:
    CrunchLog();
    void extractLog (const char * ucaNameFileIn,
                     const char * ucaNameFileOut,
                     const char * ucaStrToSearch,
                     const unsigned long ulNumLineNext);


protected:
    static void unpackBit8(string * pstrOut, unsigned char u8Val, int iNbit = 8);
    static void unpackBit32(string * pstrOut, unsigned int uiVal, int iNbit = 32);
    static void intToStr(string *pStrOut, unsigned int uiVal, string sfx = " ");
    static unsigned long unpackTimeString(const char * u8aData);
    static bool decodeTimeString(const char * u8aData, unsigned long &ulTime);
    static void removeCharsUntil(string * strProcessed, string strMatchToFind);
    static void removeChars( string * strProcessed, string strMatchToFind);
    static void strReplaceOccurrence(string *pStrOut,
                              const string csSubStrLook,
                              const string csSubStrSubst );


};

#endif // CRUNCHLOG_H
