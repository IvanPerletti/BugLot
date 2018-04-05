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

using namespace std;

class CVariablesToPlot
{
    friend class CKalosDecorator;       // To have access to private and protected members of this class from kalos decorator
public:
    CVariablesToPlot(QTableWidget *table, QString *strFileName);
    void processVarsToPlot(QTableWidget *table, QString *strFileName);

private:
    QVector<QString> VarList;

    unsigned long unpackTimeString(const char * u8aData);
    void removeCharsUntil(string * strProcessed, string strMatchToFind);
    void finalizeString( string *pStrOut, unsigned long ulTime, vector<int> vecVals);
    void fillPrevVals(vector<vector<int> > *table, int *iVal, int index, int iRow);
    void controlNullVals(vector<int> *vecVals, vector<int> *lastVals, vector<vector<int> > *table, int row);
    void finalizeTable(vector<int> *vecVals, vector<int> *lastVals, vector<vector<int> > *table, int row);
    void writeTableToFile(ofstream *file, vector<unsigned int> time, vector<vector<int>> table);
};

#endif // CVARIABLESTOPLOT_H
