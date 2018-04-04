#ifndef CVARIABLESTOPLOT_H
#define CVARIABLESTOPLOT_H

#include <QTableWidget>
#include <QDesktopWidget>
#include <QMessageBox>
#include <QMetaEnum>
#include <QApplication>
#include <QFileDialog>
#include <string>
#include <QString>
#include "mainwindow.h"

using namespace std;
class CVariablesToPlot
{
public:
    CVariablesToPlot(QTableWidget *table, QString strFileName);
    void processVarsToPlot(QTableWidget *table, QString strFileName);

private:
    unsigned long unpackTimeString(const char * u8aData);
    void removeCharsUntil(string * strProcessed, string strMatchToFind);
    void finalizeString( string *pStrOut, unsigned long ulTime, vector<int> vecVals);
};

#endif // CVARIABLESTOPLOT_H
