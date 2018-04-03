#ifndef CPROCESSLOGS_H
#define CPROCESSLOGS_H

#include <string>
#include <QString>
#include "mainwindow.h"

class CProcessLogs
{
public:
    CProcessLogs();
    virtual void processFile(const char *ucaNameFileIn, const char *ucaNameFileOut) =0;     // pure virtual function

};

#endif // CPROCESSLOGS_H
