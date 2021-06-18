#ifndef CRUNCHLOGC_ARM_H
#define CRUNCHLOGC_ARM_H
#include <string>
#include "CrunchLog.h"
using namespace std;
class CrunchLogC_Arm: public CrunchLog
{
protected:
    bool mbPerformance;
    long mlRowCounter;
public:
    CrunchLogC_Arm();
    void setPerformance(bool bFlad){mbPerformance = bFlad;}
    bool isPerformanceOn(){return mbPerformance ;}
    void processFile(const char *ucaNameFileIn,
                     const char *ucaNameFileOut,
                     const unsigned long ulTimeStart = 0,
                     const unsigned long ulTimeStop = 24*60*60);

private:
    void processController(string &STRING,
                           string &strOut,
                           ofstream &outFile,
                           uint32_t &ulTime,
                           const uint32_t &ulTimeStart,
                           CrunchLog::structLog *pstrLog);
};

#endif // CRUNCHLOGC_ARM_H
