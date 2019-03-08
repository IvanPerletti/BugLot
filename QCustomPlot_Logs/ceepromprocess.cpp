#include "ceepromprocess.h"

cEEpromProcess::cEEpromProcess(){

    // Everytime the Log Processor start, you have to set new EEprom file
    bNeedEEpromFile = true;
}

void cEEpromProcess::createEEpromFile(const char * rawFileName, const char * outFileName) {
    QString strPathFile, strPathData;
    char caOutfile[256] = {0,};

    strPathFile = QString::fromUtf8(outFileName);
    strPathData = QString::fromUtf8(rawFileName);

    int iLastSymb = strPathFile.lastIndexOf("/");
    int iLastSymbData = strPathData.lastIndexOf("/");
    QString temp = strPathData.right(strPathData.size() - iLastSymbData); // Means FileName.txt
    temp = temp.section(".", 0,0);  // Means FileName only (without extension)

    // Set properly EEprom filename: Path/KalosSuspensionLog_data_EEprom.txt
    strEEpromFileName = strPathFile.left(iLastSymb) + temp + "_EEprom.txt";

    // Open file
    memcpy(caOutfile, strEEpromFileName.toStdString().c_str() ,sizeof(caOutfile));
    outFile.open (caOutfile, std::ofstream::out | std::ofstream::trunc);

    // File created just one time, then write it only
    bNeedEEpromFile = false;
}

bool cEEpromProcess::is_eeprom_end(int iAddr) {
    bool bIsEnd = false;

    if(iAddr >= EEE_NUMEL -1) {
        bIsEnd = true;
    }

    return bIsEnd;
}

void cEEpromProcess::writeEEpromDataonFile(unionDataInfo *data){
    char strOut[1024];

    sprintf(strOut,
            "EEE %d: %d", data->msg1.iData1, data->msg1.iData2);
    outFile << strOut << endl;
    sprintf(strOut,
            "EEE %d: %d",data->msg1.iData1 +1, data->msg1.iData3);
    outFile << strOut << endl;
    sprintf(strOut,
            "EEE %d: %d", data->msg1.iData1+2, data->msg1.iData4);
    outFile << strOut << endl;

    if(is_eeprom_end(data->msg1.iData1+2)) {
        outFile.close();
        bNeedEEpromFile = true;
    }
}
