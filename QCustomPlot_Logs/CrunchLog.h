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

#include "crunchmsg.h"

using namespace std;

class CrunchLog
{
public:
    CrunchLog();
    QList<CrunchMsg::enumIdCAN> processFile(QString strFileNameIn,
                     const unsigned long ulTimeStart = 0,
                     const unsigned long ulTimeStop = 24*60*60);

private:
    QMap<CrunchMsg::enumIdCAN, CrunchMsg *> crunchMsg;

};

#endif // CRUNCHLOG_H
