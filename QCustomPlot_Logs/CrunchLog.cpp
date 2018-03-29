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
void CrunchLog::unPackDataError_OneSlotMsg(unsigned int* uiDataArray, unsigned int *uiIndex, int *iData1) {

    *iData1 = uiDataArray[*uiIndex];

    *uiIndex += 1;
}

//--------------------------------------------------------
void CrunchLog::unPackDataError_TwoSlotsMsg(unsigned int* uiDataArray, unsigned int *uiIndex, int *iData1) {

    *iData1 = uiDataArray[*uiIndex]<<8;
    *iData1 += uiDataArray[*uiIndex + 1];

    *uiIndex += 2;
}

//--------------------------------------------------------
void CrunchLog::unPackDataError_FourSlotsMsg(unsigned int* uiDataArray, unsigned int *uiIndex, int *iData1) {

    *iData1 = uiDataArray[*uiIndex]<<24;
    *iData1 = uiDataArray[*uiIndex + 1]<<16;
    *iData1 = uiDataArray[*uiIndex + 2]<<8;
    *iData1 += uiDataArray[*uiIndex + 3];

    *uiIndex += 4;

}

//--------------------------------------------------------
void CrunchLog::setLineError(InfoDataStruct *data) {

    data->uiSize.push_back(2);
    data->strLabel.push_back("LineOfError: ");

}

//--------------------------------------------------------
void CrunchLog::setNoMotionData(InfoDataStruct *data) {

    data->uiSize.push_back(2);
    data->uiSize.push_back(2);
    data->uiSize.push_back(2);

    data->strLabel.push_back("iActual: ");
    data->strLabel.push_back(" iTarget: ");
    data->strLabel.push_back(" iThr: ");

}

//--------------------------------------------------------
bool CrunchLog::isFirstMessage(unsigned int *arrVal, int freeSlots) {
    unsigned int iVal;
    long lFlag = 0xFF;

    // type indicates how many slots are free in the message
    switch(freeSlots) {
    case 1:
        iVal = 7;
        break;
    case 2:
        iVal = 6;
        break;
    case 3:
        iVal = 5;
    case 4:
        iVal = 4;
    case 5:
        iVal = 3;
    case 6:
        iVal = 2;
    case 7:
        iVal = 1;
    default:
        iVal = 8;
    }

    for(int ii = iVal; ii < 8; ii++) {
        lFlag &= arrVal[ii];
        if(lFlag != 0xFF) {
            break;
        }
    }

    //lFlag will be 0xFF<=> all the bytes =oxff
    return (lFlag!=0xFF);
}

//--------------------------------------------------------
void CrunchLog::setAutoTargetData(InfoDataStruct *data, unsigned int *arrVal) {

    if(isFirstMessage(arrVal, 2)) {
        data->uiSize.push_back(4);
        data->uiSize.push_back(2);

        data->strLabel.push_back(" iTarget: ");
        data->strLabel.push_back(" iInitial: ");
    }
    else {
        data->uiSize.push_back(1);
        data->uiSize.push_back(1);
        data->uiSize.push_back(2);

        data->strLabel.push_back(" Direction: ");
        data->strLabel.push_back(" ElementType: ");
        data->strLabel.push_back(" iActual: ");
    }

}

//--------------------------------------------------------
void CrunchLog::setDirectionData(InfoDataStruct *data, unsigned int *arrVal) {

    if(isFirstMessage(arrVal, 4)) {
        data->uiSize.push_back(2);
        data->uiSize.push_back(2);
        data->uiSize.push_back(2);

        data->strLabel.push_back(" iActual: ");
        data->strLabel.push_back(" iPrevPos: ");
        data->strLabel.push_back(" iCheckPos: ");
    }
    else {
        data->uiSize.push_back(1);
        data->uiSize.push_back(1);

        data->strLabel.push_back(" Direction: ");
        data->strLabel.push_back(" ElementType: ");
    }

}

//--------------------------------------------------------
void CrunchLog::setElevixTargetPosData(InfoDataStruct *data) {
    data->uiSize.push_back(2);
    data->uiSize.push_back(2);
    data->uiSize.push_back(2);

    data->strLabel.push_back(" iActual: ");
    data->strLabel.push_back(" EEpromMin: ");
    data->strLabel.push_back(" EEpromMax: ");
}

//--------------------------------------------------------
void CrunchLog::setSynchroTargetData(InfoDataStruct *data) {
    data->uiSize.push_back(1);
    data->uiSize.push_back(2);
    data->uiSize.push_back(2);

    data->strLabel.push_back(" iDelta: ");
    data->strLabel.push_back(" iTarget: ");
    data->strLabel.push_back(" iActual: ");
}

//--------------------------------------------------------
void CrunchLog::setAutoTargetPosData(InfoDataStruct *data, unsigned int *arrVal) {

    data->uiSize.push_back(4);

    if(isFirstMessage(arrVal, 2)) {
        data->strLabel.push_back(" ElevixTarget ");
    }
    else {
        data->strLabel.push_back(" PensileVertTarget ");
    }

}

//--------------------------------------------------------
void CrunchLog::setSynchroTargetPosData(InfoDataStruct *data) {

    data->uiSize.push_back(2);
    data->uiSize.push_back(2);

    data->strLabel.push_back(" ElevixActual: ");
    data->strLabel.push_back(" PensileVertActual: ");

}

//--------------------------------------------------------
void CrunchLog::setUntimelySynchroData(InfoDataStruct *data) {

    data->uiSize.push_back(1);
    data->uiSize.push_back(1);
    data->uiSize.push_back(1);

    data->strLabel.push_back(" isNewPos: ");
    data->strLabel.push_back(" EnableSwitch: ");
    data->strLabel.push_back(" PensileMotionType: ");

}

//--------------------------------------------------------
CrunchLog::InfoDataStruct CrunchLog::setDataToErrorType(unsigned int* uiDataArray, unsigned int error) {
    InfoDataStruct dataInfo;

    switch(error){
    case 851:
    case 852:
        setLineError(&dataInfo);
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
        setNoMotionData(&dataInfo);
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
        setAutoTargetData(&dataInfo, uiDataArray);
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
        setDirectionData(&dataInfo, uiDataArray);
        break;
    case 843:
        setElevixTargetPosData(&dataInfo);
        break;
    case 791:
    case 801:
    case 803:
        setSynchroTargetData(&dataInfo);
        break;
    case 853:
    case 854:
    case 855:
        setAutoTargetPosData(&dataInfo, uiDataArray);
        break;
    case 856:
        setSynchroTargetPosData(&dataInfo);
        break;
    case 779:
        setUntimelySynchroData(&dataInfo);
        break;
    case 768:
    case 769:
    case 794:
    case 796:
        // No data apart from error ID sent fro these ones
        break;
    }

    return dataInfo;
}

//--------------------------------------------------------
void CrunchLog::composeLineLog(string *strFile, InfoDataStruct *infoData, unsigned int *uiDataArray) {
    unsigned int uiIndexDataArray = 2;
    char s8aDummy[16]={0,};
    int iData;

    for(unsigned int ii = 0; ii < infoData->strLabel.size(); ii++) {
        switch(infoData->uiSize[ii]){
        case 1:
            unPackDataError_OneSlotMsg(uiDataArray, &uiIndexDataArray, &iData);
            break;
        case 2:
            unPackDataError_TwoSlotsMsg(uiDataArray, &uiIndexDataArray, &iData);
            break;
        case 4:
            unPackDataError_FourSlotsMsg(uiDataArray, &uiIndexDataArray, &iData);
            break;
        }

        itoa(iData, s8aDummy, 10);
        strFile->append(infoData->strLabel[ii]);
        strFile->append(s8aDummy);
    }

    strFile->append("\n" );

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
    InfoDataStruct dataInfo;

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

                dataInfo = setDataToErrorType(ulaData, lErrorID);
                composeLineLog(&strOut, &dataInfo, ulaData);

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

