#ifndef CEEPROMPROCESS_H
#define CEEPROMPROCESS_H

#include <string>
#include <QString>
#include <iostream>
#include <fstream>
#include <iomanip>
#include "commontypes.h"

using namespace std;

class cEEpromProcess
{
public:
    bool bNeedEEpromFile;
    cEEpromProcess();
    void createEEpromFile(const char * rawFileName, const char * outFileName);
    void writeEEpromDataonFile(unionDataInfo *data);

private:
  QString strEEpromFileName;
  ofstream outFile;

  bool is_eeprom_end(int iAddr);
};

#endif // CEEPROMPROCESS_H
