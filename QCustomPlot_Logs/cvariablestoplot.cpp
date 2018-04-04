#include "cvariablestoplot.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>

using namespace std;

CVariablesToPlot::CVariablesToPlot(QTableWidget *table, QString strFileName)
{
    processVarsToPlot(table, strFileName);
}

//--------------------------------------------------------
void CVariablesToPlot::removeCharsUntil(string * strProcessed, string strMatchToFind)
{
    size_t szPos;

    szPos = strProcessed->find(strMatchToFind);
    if (szPos < strProcessed->size() ){
        strProcessed->erase (0, szPos+strMatchToFind.size());
    }
}

//--------------------------------------------------------
unsigned long CVariablesToPlot::unpackTimeString(const char * u8aData)
{
    unsigned long  ulTime;
    unsigned int l_hour, l_min, l_sec, l_ms;
    sscanf( u8aData ,
            "%02d:%02d:%02d:%03d",
            &l_hour	,
            &l_min	,
            &l_sec	,
            &l_ms	);
    ulTime = l_ms + (l_sec + l_min*60 + l_hour * 3600)*1000; // max Num: 90060999ms
    return(ulTime);
}

//--------------------------------------------------------
void CVariablesToPlot::finalizeString( string *pStrOut, unsigned long ulTime, vector<int> vecVals)
{
    char s8aDummy[16]={0,}; // more than max Int number: 9 digits + sign
    pStrOut->clear();
    itoa(ulTime, s8aDummy, 10);
    pStrOut->append(s8aDummy);
    pStrOut->append(" " );
    for(int ii = 0; ii < vecVals.size(); ii++) {
        itoa( vecVals[ii],s8aDummy, 10);
        pStrOut->append(s8aDummy);
        pStrOut->append(" ");
    }

    pStrOut->append("\n");

}

//--------------------------------------------------------
void CVariablesToPlot::processVarsToPlot(QTableWidget *table, QString strFileName) {
    QVector<QString> VarList;
    ifstream infile;
    ofstream outFile;

    string nameFile = QDir::currentPath().toStdString()+"/parsed_out.txt";
    for (int ii = 0; ii < table->rowCount(); ++ii) {
        for (int jj = 0; jj < table->columnCount(); ++jj) {
           QTableWidgetItem *cell = table->item(ii, jj);
           if(cell) {
               VarList << cell->text()+ ": ";
           }
           else {
               goto process;
           }
        }
    }

    process:
    infile.open (strFileName.toStdString());
    outFile.open (nameFile, std::ofstream::out | std::ofstream::trunc);
    string STRING, strOut;
    int iRowCounter=0;
    vector<int> iVecVals;
    unsigned int ulTime=0;

    string previousLine="";

    iVecVals.resize(VarList.size());
    while(iRowCounter<1000000) // To get you all the lines.
    {
        getline(infile,STRING); // Saves the line in STRING.
        if (STRING != previousLine)// true in the end of file or file corrupted
        {
            std::size_t pos;
            previousLine = STRING;
            fill(iVecVals.begin(), iVecVals.end(), 0);
            for(int IdxList = 0; IdxList < VarList.size(); IdxList++) {
                pos = STRING.find(VarList[IdxList].toStdString());// if "find" fails then pos  = 4000000
                if (pos < STRING.size() )
                { // found ID file
                    if(all_of(iVecVals.begin(), iVecVals.end(), [](int i) { return i==0; })) {      // Only if no vars has been already set
                        removeCharsUntil(&STRING," - ");
                        ulTime = unpackTimeString( STRING.data() );
                    }
                    removeCharsUntil(&STRING, VarList[IdxList].toStdString());
                    sscanf( STRING.data(), "%d", &iVecVals[IdxList]);
                }
            }
            if(any_of(iVecVals.begin(), iVecVals.end(), [](int i) { return i!=0; })) {
                finalizeString(&strOut, ulTime, iVecVals);
                cout<<strOut;// Prints out STRING.;
                outFile << strOut;
            }
        }
        else {
            strOut.clear();
            strOut.append("ERROR LINE");
        }
        iRowCounter++;
    }

    outFile.close();
    infile.close();
}
