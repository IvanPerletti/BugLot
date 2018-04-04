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
void CVariablesToPlot::fillPrevVals(vector<vector<int>> *table, int *iVal, int index, int iRow) {

    for(int ii = 0; ii <= iRow; ii++) {
        (*table)[ii][index] = *iVal;
    }

}

//--------------------------------------------------------
void CVariablesToPlot::controlNullVals(vector<int> *vecVals, vector<int> *lastVals, vector<vector<int>> *table, int row) {

    for(int ii = 0; ii < vecVals->size(); ii++) {
        if((*vecVals)[ii] == 0) {      // Set last valid if null
            (*vecVals)[ii] = (*lastVals)[ii];
        }
        else {      // Update to most recent val
            if((*lastVals)[ii] == 0) {
                (*lastVals)[ii] = (*vecVals)[ii];
                fillPrevVals(table, lastVals[ii].data(), ii, row);
                // Need to fill going up til first element of table
            }
            else {
                (*lastVals)[ii] = (*vecVals)[ii];
            }
        }
    }

}

//--------------------------------------------------------
void CVariablesToPlot::finalizeTable(vector<int> *vecVals, vector<int> *lastVals, vector<vector<int>> *table, int row)
{

    table->push_back(*vecVals);
    controlNullVals(vecVals, lastVals, table, row);
    (*table)[row] = *vecVals;       // repeat for update

}

//--------------------------------------------------------
void CVariablesToPlot::writeTableToFile(ofstream *file, vector<unsigned int> time, vector<vector<int>> table) {
    string strOut;

    for(int ii = 0; ii < time.size(); ii++) {
        finalizeString(&strOut, time[ii], table[ii]);
        cout<<strOut;// Prints out STRING.;
        *file << strOut;
    }
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
               goto process;        // Exit from nested loops
           }
        }
    }

    process:
    infile.open (strFileName.toStdString());
    outFile.open (nameFile, std::ofstream::out | std::ofstream::trunc);
    string STRING;
    int iRowCounter=0,
            iRowWritten = 0;
    vector<vector<int>> iTabVals2D;
    vector<int> iVecVals, iLastValidVals;
    vector<unsigned int> uVecTime;
    unsigned int ulTime=0;

    string previousLine="";

    iVecVals.resize(VarList.size());

    iLastValidVals.resize(VarList.size());
    fill(iLastValidVals.begin(), iLastValidVals.end(), 0);  // Only once, before starting filling the table

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
                { // found variable to plot
                    if(all_of(iVecVals.begin(), iVecVals.end(), [](int i) { return i==0; })) {      // Only if no vars has been already set
                        removeCharsUntil(&STRING," - ");
                        ulTime = unpackTimeString( STRING.data() );
                    }
                    removeCharsUntil(&STRING, VarList[IdxList].toStdString());
                    sscanf( STRING.data(), "%d", &iVecVals[IdxList]);
                }
            }
            // if at least one vars have been found
            if(any_of(iVecVals.begin(), iVecVals.end(), [](int i) { return i!=0; })) {
                finalizeTable(&iVecVals, &iLastValidVals, &iTabVals2D, iRowWritten);
                uVecTime.push_back(ulTime);
                iRowWritten++;
            }
        }
        else {
//            strOut.clear();
//            strOut.append("ERROR LINE");
        }
        iRowCounter++;
    }

    // Write to file
    writeTableToFile(&outFile, uVecTime, iTabVals2D);

    outFile.close();
    infile.close();
}
