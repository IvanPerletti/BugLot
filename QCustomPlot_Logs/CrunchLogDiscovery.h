#ifndef CRUNCHLOGDISCOVERY_H
#define CRUNCHLOGDISCOVERY_H
#include <string>
#include "CrunchLog.h"
using namespace std;
class CrunchLogDiscovery: public CrunchLog
{
protected:
    bool mbPerformance;
    long mlRowCounter;
public:
    CrunchLogDiscovery();
    void setPerformance(bool bFlad){mbPerformance = bFlad;}
    bool isPerformanceOn(){return mbPerformance ;}
    void processFile(const char *ucaNameFileIn,
                     const char *ucaNameFileOut,
                     const unsigned long ulTimeStart = 0,
                     const unsigned long ulTimeStop = 24*60*60);

    static void processApr(const char *ucaNameFileIn, const char *ucaNameFileOut);
    static void processDose(const char *ucaNameFileIn,
                            const char *ucaNameFileOut);
protected:
    void processId652(string & STRING,
                      string & strOut,
                      ofstream &outFile,
                      uint32_t & ulTime,
                      const uint32_t &ulTimeStart,
                      CrunchLog::structLog * pstrLog);

};

#endif // CRUNCHLOGDISCOVERY_H
