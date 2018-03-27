#include "CrunchLog.h"
#include <QString>
#include "mainwindow.h"

#include "ui_mainwindow.h"


CrunchLog::CrunchLog()
{

}
#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;



//--------------------------------------------------------
void CrunchLog::unpackBit(string * pstrOut, unsigned int uiVal)
{
	int ii, iBit;

	for (ii=0; ii<19; ii++)
	{
		char u8aNum[4];
		iBit = ( uiVal & (1<<ii) ) !=0;
		itoa(iBit,u8aNum,10);
		pstrOut->append(u8aNum);
		pstrOut->append(" ");
	}
}

//--------------------------------------------------------
string CrunchLog::createTimeString(const char * u8aData) {
    string strTime, temp;

    temp = string(u8aData);
//    strcpy(&temp, u8aData);

    strTime = temp.substr(0,13);

    return strTime;
}

//--------------------------------------------------------
unsigned long CrunchLog::unpackTimeString(const char * u8aData)
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
void CrunchLog::removeCharsUntil(string * strProcessed, string strMatchToFind)
{
	size_t szPos;

	szPos = strProcessed->find(strMatchToFind);
	if (szPos < strProcessed->size() ){
		strProcessed->erase (0, szPos+strMatchToFind.size());
	}
}
//--------------------------------------------------------
void CrunchLog::removeChars(string * strProcessed, string strMatchToFind)
{
	size_t szPos;

	szPos = strProcessed->find(strMatchToFind);

	while (szPos < strProcessed->size() )
	{
		strProcessed->erase (szPos,strMatchToFind.size());
		szPos = strProcessed->find(strMatchToFind);
	}
}

//--------------------------------------------------------
void CrunchLog::unPackDataError_Msg(unsigned int* uiDataArray, unsigned int *uiIndex, int *iData1) {

    *iData1 = uiDataArray[*uiIndex]<<8;
    *iData1 += uiDataArray[*uiIndex + 1];

    *uiIndex += 2;
}

//--------------------------------------------------------
void CrunchLog::unPackDataError_LongMsg(unsigned int* uiDataArray, int *iData1) {

    *iData1 = uiDataArray[2]<<24;
    *iData1 = uiDataArray[3]<<16;
    *iData1 = uiDataArray[4]<<8;
    *iData1 += uiDataArray[5];

}


//--------------------------------------------------------
void CrunchLog::unPackDataError_2Msgs(unsigned int* uiDataArray, int *iData1, int *iData2) {

    *iData1 = uiDataArray[2]<<8;
    *iData1 += uiDataArray[3];
    *iData2 = uiDataArray[4]<<8;
    *iData2 += uiDataArray[5];

}

//--------------------------------------------------------
void CrunchLog::unPackDataError_3Msgs(unsigned int* uiDataArray, int *iData1, int *iData2, int *iData3) {

    *iData1 = uiDataArray[2]<<8;
    *iData1 += uiDataArray[3];
    *iData2 = uiDataArray[4]<<8;
    *iData2 += uiDataArray[5];
    *iData3 = uiDataArray[6]<<8;
    *iData3 += uiDataArray[7];

}

//--------------------------------------------------------
void CrunchLog::setLineError(string* strFile, unsigned int* uiDataArray, unsigned int *uiIndex) {
    int iData;
    char s8aDummy[16]={0,}; // more than max Int number: 9 digits + sign

    unPackDataError_Msg(uiDataArray, uiIndex, &iData);

    itoa(iData, s8aDummy, 10);
    strFile->append("LineOfError: ");
    strFile->append(s8aDummy);
    strFile->append("\n");

}

//--------------------------------------------------------
void CrunchLog::setNoMotionData(string* strFile, unsigned int* uiDataArray, unsigned int *uiIndex, vector <string> label) {
    int iData;
    char s8aDummy[16]={0,}; // more than max Int number: 9 digits + sign

    for(int ii = 0; ii < label.size(); ii++) {
         unPackDataError_Msg(uiDataArray, uiIndex, &iData);
         itoa(iData, s8aDummy, 10);
         strFile->append(label[ii]);
         strFile->append(s8aDummy);
    }

    strFile->append("\n" );

}

void CrunchLog::setAutoTargetData(string* strFile, unsigned int* uiDataArray) {

}

//--------------------------------------------------------
void CrunchLog::setDirectionData(string* strFile, unsigned int* uiDataArray) {
    int iData1, iData2, iData3;
    char s8aDummy[16]={0,}; // more than max Int number: 9 digits + sign

    unPackDataError_3Msgs(uiDataArray, &iData1, &iData2, &iData3);

    itoa(iData1, s8aDummy, 10);
    strFile->append("iActual: ");
    strFile->append(s8aDummy);
    strFile->append(" iPrevPos:" );
    itoa(iData2, s8aDummy, 10);
    strFile->append(s8aDummy);
    strFile->append(" iCheckPos:" );
    itoa(iData3, s8aDummy, 10);
    strFile->append(s8aDummy);
    strFile->append("\n" );
}

//--------------------------------------------------------
void CrunchLog::setElevixTargetPosData(string* strFile, unsigned int* uiDataArray) {
    int iData1, iData2, iData3;
    char s8aDummy[16]={0,}; // more than max Int number: 9 digits + sign

    unPackDataError_3Msgs(uiDataArray, &iData1, &iData2, &iData3);

    itoa(iData1, s8aDummy, 10);
    strFile->append("Elevix Actual: ");
    strFile->append(s8aDummy);
    strFile->append(" Min EEprom:" );
    itoa(iData2, s8aDummy, 10);
    strFile->append(s8aDummy);
    strFile->append(" Max EEprom:" );
    itoa(iData3, s8aDummy, 10);
    strFile->append(s8aDummy);
    strFile->append("\n" );
}

//--------------------------------------------------------
void CrunchLog::setSynchroTargetData(string* strFile, unsigned int* uiDataArray) {
    int iData1, iData2;

    char s8aDummy[16]={0,}; // more than max Int number: 9 digits + sign

    unPackDataError_2Msgs(uiDataArray, &iData1, &iData2);

    itoa(iData1, s8aDummy, 10);
    strFile->append("iTarget: ");
    strFile->append(s8aDummy);
    strFile->append(" iActual:" );
    itoa(iData2, s8aDummy, 10);
    strFile->append(s8aDummy);
    strFile->append("\n" );
}

//--------------------------------------------------------
void CrunchLog::setDataToErrorType(string* strFile, unsigned int* uiDataArray, unsigned int error) {
    unsigned int uiIndexData = 2;       // First valid byte of data
    vector <string> vLabel;         // Max number of variables that can be saved

    vLabel.clear();

    switch(error){
    case 851:
    case 852:
        setLineError(strFile, uiDataArray, &uiIndexData);
        break;
    case 825:
    case 826:
    case 827:
    case 828:
    case 829:
    case 830:
    case 831:
    case 832:
    case 833:
    case 834:
    case 835:
    case 836:
    case 837:
    case 838:
    case 839:
    case 840:
    case 841:
    case 842:
    case 846:
    case 847:
        vLabel.push_back("iActual: ");
        vLabel.push_back(" iTarget: ");
        vLabel.push_back(" iThr: ");

        setNoMotionData(strFile, uiDataArray, &uiIndexData, vLabel);
        break;
    case 781:
    case 783:
    case 785:
    case 787:
    case 789:
    case 797:
    case 799:
    case 805:
    case 807:
    case 848:
        setAutoTargetData(strFile, uiDataArray);
        break;
    case 782:
    case 784:
    case 786:
    case 788:
    case 790:
    case 792:
    case 798:
    case 800:
    case 802:
    case 804:
    case 806:
    case 808:
    case 810:
    case 811:
    case 812:
    case 813:
    case 814:
    case 815:
    case 816:
    case 817:
    case 818:
    case 819:
    case 820:
    case 849:
    case 850:
        setDirectionData(strFile, uiDataArray);
        break;
    case 843:
        setElevixTargetPosData(strFile, uiDataArray);
        break;
    case 768:
    case 769:
    case 794:
    case 796:
        strFile->append("\n" );
        break;
    case 791:
    case 801:
    case 803:
        setSynchroTargetData(strFile, uiDataArray);
        break;

    }
}

//--------------------------------------------------------
void CrunchLog::finalizeString( string *pStrOut, unsigned long ulTime, long lBitMask, long lMcStatus)
{
	char s8aDummy[16]={0,}; // more than max Int number: 9 digits + sign
	pStrOut->clear();
	itoa(ulTime, s8aDummy, 10);
	pStrOut->append(s8aDummy);
	pStrOut->append(" " );
	unpackBit(pStrOut,lBitMask);
	itoa( lMcStatus,s8aDummy, 10);
	pStrOut->append(s8aDummy);
	pStrOut->append("\n");

}

//--------------------------------------------------------
void CrunchLog::processFile (const char * ucaNameFileIn, const char * ucaNameFileOut)
{
    string sIDfile = "<Id = 0657";
    string STRING, strOut, strTime;
	ifstream infile;
	ofstream outFile;


	if (ucaNameFileIn == NULL || ucaNameFileOut == NULL ){
		return;
	}

	infile.open (ucaNameFileIn);
	outFile.open (ucaNameFileOut, std::ofstream::out | std::ofstream::trunc);
	int iRowCounter=0;
	unsigned int
			lBitMask=0,
            lErrorID=0,
			ulTime=0,
			lMcStatus=0,
			ulaData[8]={0,};
    char s8aDummy[16]={0,}; // more than max Int number: 9 digits + sign

	string previousLine="";
	while(iRowCounter<1000000) // To get you all the lines.
	{
		getline(infile,STRING); // Saves the line in STRING.
		if (STRING != previousLine)// true in the end of file or file corrupted
		{
			previousLine = STRING;
            std::size_t pos = STRING.find(sIDfile);// if "find" fails then pos  = 4000000
			if (pos < STRING.size() )
            { // found ID file
				removeCharsUntil(&STRING,"; ");
//				ulTime = unpackTimeString( STRING.data() );
                strTime = createTimeString( STRING.data() );
                removeCharsUntil(&STRING,"Data = ");
                sscanf( STRING.data() , "%x %x %x %x %x %x %x %x",
						&ulaData[0] ,
                        &ulaData[1] ,
                        &ulaData[2] ,
						&ulaData[3] ,
						&ulaData[4] ,
                        &ulaData[5] ,
                        &ulaData[6] ,
                        &ulaData[7] );// extract numbers

                lErrorID = ulaData[0]<<8 ;
                lErrorID += ulaData[1];

                strOut.clear();
                strOut.append(strTime);
                strOut.append(" " );
                itoa(lErrorID, s8aDummy, 10);
                strOut.append("ErrorID: ");
                strOut.append(s8aDummy);
                strOut.append(" " );

                setDataToErrorType(&strOut, ulaData, lErrorID);
                outFile << strOut;
			}
			else
			{
				std::size_t pos = STRING.find("OPERATOR TIMING BOOKMARK");
				if (pos < STRING.size() )
				{
					removeCharsUntil(&STRING,"; ");
					ulTime = unpackTimeString( STRING.data() );
					finalizeString(&strOut, ulTime-1, lBitMask, lMcStatus);
					outFile << strOut;
					finalizeString(&strOut, ulTime, lBitMask, 20);
					outFile << strOut;
					finalizeString(&strOut, ulTime+1, lBitMask, lMcStatus);
					outFile << strOut;

				}
			}
		}
		iRowCounter++;




	}

	outFile.close();
	infile.close();


}

//--------------------------------------------------------
void CrunchLog::strReplaceOccurrence(string *pStrOut,
									 const string csSubStrLook,
									 const string csSubStrSubst )
{
	int index = 0;
	while (1)
	{
		int length = csSubStrLook.size();
		index = pStrOut->find(csSubStrLook, index);
		if (index < 0) {
			break;
		}
		pStrOut->replace(index, length, csSubStrSubst);/* Make the replacement. */
		index += 1;				/* Advance index */
	}
}

