#include "cprocesskaloslogs.h"
#include <QString>
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

CProcessKalosLogs::CProcessKalosLogs(const char * ucaNameFileIn, const char * ucaNameFileOut)
{
    processFile(ucaNameFileIn, ucaNameFileOut);
}

//--------------------------------------------------------
/**
 * @brief CProcessKalosLogs::createTimeString copy time string as in Log File
 * @param u8aData
 * @return
 */
string CProcessKalosLogs::createTimeString(const char * u8aData) {
    string strTime, temp;

    temp = string(u8aData);

    strTime = temp.substr(0,13);

    return strTime;
}

//--------------------------------------------------------
unsigned long CProcessKalosLogs::unpackTimeString(const char * u8aData)
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
void CProcessKalosLogs::removeCharsUntil(string * strProcessed, string strMatchToFind)
{
    size_t szPos;

    szPos = strProcessed->find(strMatchToFind);
    if (szPos < strProcessed->size() ){
        strProcessed->erase (0, szPos+strMatchToFind.size());
    }
}
//--------------------------------------------------------
void CProcessKalosLogs::removeChars(string * strProcessed, string strMatchToFind)
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
/**
 * @brief CProcessKalosLogs::unPackDataError_OneSlotMsg unpack single byte message
 * @param uiDataArray   data array from log file
 * @param uiIndex       index of data message from log file
 * @param iData1        data message coming from correct split of log data
 */
void CProcessKalosLogs::unPackDataError_OneSlotMsg(unsigned int* uiDataArray, unsigned int *uiIndex, int *iData1) {

    *iData1 = uiDataArray[*uiIndex];

    *uiIndex += 1;
}

//--------------------------------------------------------
/**
 * @brief CProcessKalosLogs::unPackDataError_TwoSlotsMsg unpack two bytes message
 * @param uiDataArray   data array from log file
 * @param uiIndex       index of data message from log file
 * @param iData1        data message coming from correct split of log data
 */
void CProcessKalosLogs::unPackDataError_TwoSlotsMsg(unsigned int* uiDataArray, unsigned int *uiIndex, int *iData1) {

    *iData1 = uiDataArray[*uiIndex]<<8;
    *iData1 += uiDataArray[*uiIndex + 1];

    *uiIndex += 2;
}

//--------------------------------------------------------
/**
 * @brief CProcessKalosLogs::unPackDataError_FourSlotsMsg unpack four bytes message
 * @param uiDataArray   data array from log file
 * @param uiIndex       index of data message from log file
 * @param iData1        data message coming from correct split of log data
 */
void CProcessKalosLogs::unPackDataError_FourSlotsMsg(unsigned int* uiDataArray, unsigned int *uiIndex, int *iData1) {

    *iData1 = uiDataArray[*uiIndex]<<24;
    *iData1 = uiDataArray[*uiIndex + 1]<<16;
    *iData1 = uiDataArray[*uiIndex + 2]<<8;
    *iData1 += uiDataArray[*uiIndex + 3];

    *uiIndex += 4;

}

//--------------------------------------------------------
void CProcessKalosLogs::setCanLogEsBkData(InfoDataStruct *infoStruct){
    const int iNumData = 8;
    string strEsBklabel[iNumData] = {"EnableSwitch: ", " Horns: ", " Move: ", " Homing: ",
                                     " RemoteEnablewitch: ", " SUPER_ENABLE_SWITCH: ", " BrakeStatus: ", " HW_maintenance: "};
    for(int ii = 0; ii < iNumData; ii++) {
        infoStruct->uiSize.push_back(1);
        infoStruct->strLabel.push_back(strEsBklabel[ii]);
    }

}

//--------------------------------------------------------
void CProcessKalosLogs::setCanLogAutoData1(InfoDataStruct *infoStruct){

    infoStruct->uiSize.push_back(2);
    infoStruct->uiSize.push_back(1);
    infoStruct->uiSize.push_back(1);
    infoStruct->uiSize.push_back(2);
    infoStruct->uiSize.push_back(2);

    infoStruct->strLabel.push_back("Stato_movimento_automatico: ");
    infoStruct->strLabel.push_back(" Accessorio: ");
    infoStruct->strLabel.push_back(" Posizione: ");
    infoStruct->strLabel.push_back(" all_movements_started: ");
    infoStruct->strLabel.push_back(" all_movements_finished: ");

}

//--------------------------------------------------------
void CProcessKalosLogs::setCanLogVertData1(InfoDataStruct *infoStruct){
    const int iNumData = 4;
    string strVert1abel[iNumData] = {"Stato_motore_pensile_vert: ", " CmdMask[M_PENSILE_VERT]: ", " ExclMask[M_PENSILE_VERT]: ", " CollMask[M_PENSILE_VERT]: "};

    for(int ii = 0; ii < iNumData; ii++) {
        infoStruct->uiSize.push_back(2);
        infoStruct->strLabel.push_back(strVert1abel[ii]);
    }

}

//--------------------------------------------------------
void CProcessKalosLogs::setCanLogVertData2(InfoDataStruct *infoStruct){

    infoStruct->uiSize.push_back(4);
    infoStruct->uiSize.push_back(2);
    infoStruct->uiSize.push_back(1);
    infoStruct->uiSize.push_back(1);

    infoStruct->strLabel.push_back("WSpeed_pensile: ");
    infoStruct->strLabel.push_back(" WDir_pensile_vert: ");
    infoStruct->strLabel.push_back(" AKD_drv_status: ");
    infoStruct->strLabel.push_back(" Op_mode_AKD: ");

}

//--------------------------------------------------------
void CProcessKalosLogs::setCanLogVertData3(InfoDataStruct *infoStruct){

    infoStruct->uiSize.push_back(2);
    infoStruct->uiSize.push_back(2);
    infoStruct->uiSize.push_back(2);
    infoStruct->uiSize.push_back(1);

    infoStruct->strLabel.push_back("H_AKD_encoder_mm: ");
    infoStruct->strLabel.push_back(" Rampa_tube_vert_mm: ");
    infoStruct->strLabel.push_back(" Tube_Target_Verticale_mm: ");
    infoStruct->strLabel.push_back(" U_Sound_brake: ");

}

//--------------------------------------------------------
void CProcessKalosLogs::setCanLogVertData4(InfoDataStruct *infoStruct){
    const int iNumData = 3;
    string strVert4label[iNumData] = {"EndMMove[M_PENSILE_VERT]: ", " BrkMask[M_PENSILE_VERT]: ", " FcMask[M_PENSILE_VERT]: "};

    for(int ii = 0; ii < iNumData; ii++) {
        infoStruct->uiSize.push_back(2);
        infoStruct->strLabel.push_back(strVert4label[ii]);
    }

}

//--------------------------------------------------------
void CProcessKalosLogs::setCanLogLatData1(InfoDataStruct *infoStruct){
    const int iNumData = 4;
    string strLat1label[iNumData] = {"Stato_motore_pensile_lat: ", " CmdMask[M_PENSILE_LAT]: ", " ExclMask[M_PENSILE_LAT]: ", " CollMask[M_PENSILE_LAT]: "};

    for(int ii = 0; ii < iNumData; ii++) {
        infoStruct->uiSize.push_back(2);
        infoStruct->strLabel.push_back(strLat1label[ii]);
    }

}

//--------------------------------------------------------
void CProcessKalosLogs::setCanLogLatData2(InfoDataStruct *infoStruct){
    const int iNumData = 2;
    string strLat2label[iNumData] = {"WDir_pensile_lat: ", " Pos_pensile_lat_mm: "};

    for(int ii = 0; ii < iNumData; ii++) {
        infoStruct->uiSize.push_back(2);
        infoStruct->strLabel.push_back(strLat2label[ii]);
    }
}

//--------------------------------------------------------
void CProcessKalosLogs::setCanLogLongData1(InfoDataStruct *infoStruct){
    const int iNumData = 4;
    string strLong1label[iNumData] = {"Stato_motore_pensile_long: ", " CmdMask[M_PENSILE_LONG]: ", " ExclMask[M_PENSILE_LONG]: ", " CollMask[M_PENSILE_LONG]: "};

    for(int ii = 0; ii < iNumData; ii++) {
        infoStruct->uiSize.push_back(2);
        infoStruct->strLabel.push_back(strLong1label[ii]);
    }

}

//--------------------------------------------------------
void CProcessKalosLogs::setCanLogLongData2(InfoDataStruct *infoStruct){
    const int iNumData = 2;
    string strLong2label[iNumData] = {"WDir_pensile_long: ", " Pos_pensile_long_mm: "};

    for(int ii = 0; ii < iNumData; ii++) {
        infoStruct->uiSize.push_back(2);
        infoStruct->strLabel.push_back(strLong2label[ii]);
    }
}

//--------------------------------------------------------
void CProcessKalosLogs::setCanLogRotData1(InfoDataStruct *infoStruct){
    const int iNumData = 4;
    string strRot1label[iNumData] = {"Stato_motore_pensile_rot: ", " CmdMask[M_PENSILE_ROT]: ", " ExclMask[M_PENSILE_ROT]: ", " CollMask[M_PENSILE_ROT]: "};

    for(int ii = 0; ii < iNumData; ii++) {
        infoStruct->uiSize.push_back(2);
        infoStruct->strLabel.push_back(strRot1label[ii]);
    }

}

//--------------------------------------------------------
void CProcessKalosLogs::setCanLogRotData2(InfoDataStruct *infoStruct){
    const int iNumData = 2;
    string strRot2label[iNumData] = {"WDir_pensile_rot: ", " Angolo_Rot_decdegree: "};

    for(int ii = 0; ii < iNumData; ii++) {
        infoStruct->uiSize.push_back(2);
        infoStruct->strLabel.push_back(strRot2label[ii]);
    }
}

//--------------------------------------------------------
void CProcessKalosLogs::setCanLogIncData1(InfoDataStruct *infoStruct){
    const int iNumData = 4;
    string strInc1label[iNumData] = {"Stato_motore_pensile_inc: ", " CmdMask[M_PENSILE_INC]: ", " ExclMask[M_PENSILE_INC]: ", " CollMask[M_PENSILE_INC]: "};

    for(int ii = 0; ii < iNumData; ii++) {
        infoStruct->uiSize.push_back(2);
        infoStruct->strLabel.push_back(strInc1label[ii]);
    }

}

//--------------------------------------------------------
void CProcessKalosLogs::setCanLogIncData2(InfoDataStruct *infoStruct){
    const int iNumData = 2;
    string strInc2label[iNumData] = {"WDir_pensile_inc: ", " Angolo_Inc_decdegree: "};

    for(int ii = 0; ii < iNumData; ii++) {
        infoStruct->uiSize.push_back(2);
        infoStruct->strLabel.push_back(strInc2label[ii]);
    }

    infoStruct->uiSize.push_back(4);
    infoStruct->strLabel.push_back(" pensile_target_inc: ");
}

//--------------------------------------------------------
void CProcessKalosLogs::setCanLogDetLatData1(InfoDataStruct *infoStruct) {
    const int iNumData = 4;
    string strDetLat1label[iNumData] = {"Stato_motore_detettore_lat: ", " CmdMask[M_DETETTORE_LAT]: ", " ExclMask[M_DETETTORE_LAT]: ", " CollMask[M_DETETTORE_LAT]: "};

    for(int ii = 0; ii < iNumData; ii++) {
        infoStruct->uiSize.push_back(2);
        infoStruct->strLabel.push_back(strDetLat1label[ii]);
    }

}

//--------------------------------------------------------
void CProcessKalosLogs::setCanLogDetLatData2(InfoDataStruct *infoStruct){
    const int iNumData = 2;
    string strDetLat2label[iNumData] = {"WDir_detettore_lat: ", " Pos_detettore_lat_mm: "};

    for(int ii = 0; ii < iNumData; ii++) {
        infoStruct->uiSize.push_back(2);
        infoStruct->strLabel.push_back(strDetLat2label[ii]);
    }

    infoStruct->uiSize.push_back(4);
    infoStruct->strLabel.push_back(" detettore_target_lat: ");
}

//--------------------------------------------------------
void CProcessKalosLogs::setCanLogDetLongData1(InfoDataStruct *infoStruct) {
    const int iNumData = 4;
    string strDetLong1label[iNumData] = {"Stato_motore_detettore_long: ", " CmdMask[M_DETETTORE_LONG]: ", " ExclMask[M_DETETTORE_LONG]: ", " CollMask[M_DETETTORE_LONG]: "};

    for(int ii = 0; ii < iNumData; ii++) {
        infoStruct->uiSize.push_back(2);
        infoStruct->strLabel.push_back(strDetLong1label[ii]);
    }

}

//--------------------------------------------------------
void CProcessKalosLogs::setCanLogDetLongData2(InfoDataStruct *infoStruct){
    const int iNumData = 2;
    string strDetLong2label[iNumData] = {"WDir_detettore_long: ", " Pos_detettore_long_mm: "};

    for(int ii = 0; ii < iNumData; ii++) {
        infoStruct->uiSize.push_back(2);
        infoStruct->strLabel.push_back(strDetLong2label[ii]);
    }

    infoStruct->uiSize.push_back(4);
    infoStruct->strLabel.push_back(" detettore_target_long: ");
}

//--------------------------------------------------------
void CProcessKalosLogs::setCanLogSyncData(InfoDataStruct *infoStruct){

    infoStruct->uiSize.push_back(2);
    infoStruct->uiSize.push_back(1);
    infoStruct->uiSize.push_back(1);
    infoStruct->uiSize.push_back(1);
    infoStruct->uiSize.push_back(1);
    infoStruct->uiSize.push_back(1);
    infoStruct->uiSize.push_back(1);

    infoStruct->strLabel.push_back("Syncro_status: ");
    infoStruct->strLabel.push_back(" ok_to_synchronize: ");
    infoStruct->strLabel.push_back(" is_synchronized: ");
    infoStruct->strLabel.push_back(" exit_from_synchro: ");
    infoStruct->strLabel.push_back(" sync_error_position: ");
    infoStruct->strLabel.push_back(" Dead_zone_sync: ");
    infoStruct->strLabel.push_back(" Syncro_pensile_error: ");

}

//--------------------------------------------------------
void CProcessKalosLogs::setCanLogTargetData1(InfoDataStruct *infoStruct){
    const int iNumData = 2;
    string strTarget1label[iNumData] = {"pensile_target_vert: ", " pensile_target_lat: "};

    for(int ii = 0; ii < iNumData; ii++) {
        infoStruct->uiSize.push_back(4);
        infoStruct->strLabel.push_back(strTarget1label[ii]);
    }
}

//--------------------------------------------------------
void CProcessKalosLogs::setCanLogTargetData2(InfoDataStruct *infoStruct){
    const int iNumData = 2;
    string strTarget2label[iNumData] = {"pensile_target_long: ", " pensile_target_rot: "};

    for(int ii = 0; ii < iNumData; ii++) {
        infoStruct->uiSize.push_back(4);
        infoStruct->strLabel.push_back(strTarget2label[ii]);
    }

}

//--------------------------------------------------------
void CProcessKalosLogs::setCanLogDetLatSyncData(InfoDataStruct *infoStruct){

    infoStruct->uiSize.push_back(2);
    infoStruct->uiSize.push_back(1);
    infoStruct->uiSize.push_back(1);
    infoStruct->uiSize.push_back(1);
    infoStruct->uiSize.push_back(1);

    infoStruct->strLabel.push_back("FM713_detettore_lat_loop_speed: ");
    infoStruct->strLabel.push_back(" Syncro_detettore_lat_error: ");
    infoStruct->strLabel.push_back(" orobix_dead_zone_sync_lat_before: ");
    infoStruct->strLabel.push_back(" orobix_dead_zone_sync_lat_after: ");
    infoStruct->strLabel.push_back(" Corsa_detettore_lat: ");
}

//--------------------------------------------------------
void CProcessKalosLogs::setCanLogDetLongSyncData(InfoDataStruct *infoStruct){

    infoStruct->uiSize.push_back(2);
    infoStruct->uiSize.push_back(1);
    infoStruct->uiSize.push_back(1);
    infoStruct->uiSize.push_back(1);
    infoStruct->uiSize.push_back(1);

    infoStruct->strLabel.push_back("FM713_detettore_long_loop_speed: ");
    infoStruct->strLabel.push_back(" Syncro_detettore_long_error: ");
    infoStruct->strLabel.push_back(" orobix_dead_zone_sync_long_before: ");
    infoStruct->strLabel.push_back(" orobix_dead_zone_sync_long_after: ");
    infoStruct->strLabel.push_back(" Corsa_detettore_long: ");
}

//--------------------------------------------------------
/**
 * @brief CProcessKalosLogs::setLineError set message size (in byte) and label for error message requiring line of error
 * @param data     pointer to struct containing data size and label
 */
void CProcessKalosLogs::setLineError(InfoDataStruct *data) {

    data->uiSize.push_back(2);
    data->strLabel.push_back("LineOfError: ");

}

//--------------------------------------------------------
/**
 * @brief CProcessKalosLogs::setNoMotionData    set message size (in byte) and label for error message related to no motion errors
 * @param data      pointer to struct containing data size and label
 */
void CProcessKalosLogs::setNoMotionData(InfoDataStruct *data) {

    data->uiSize.push_back(2);
    data->uiSize.push_back(2);
    data->uiSize.push_back(2);

    data->strLabel.push_back("iActual: ");
    data->strLabel.push_back(" iTarget: ");
    data->strLabel.push_back(" iThr: ");

}

//--------------------------------------------------------
/**
 * @brief CProcessKalosLogs::isFirstMessage control if message is first one for that error type.
 * @param arrVal        data from log file
 * @param freeSlots     number of unsued data slots in the second message
 * @return true if message is the first one
 */
bool CProcessKalosLogs::isFirstMessage(unsigned int *arrVal, int freeSlots) {
    unsigned int iVal;
    long lFlag = 0xFF;

    switch(freeSlots) {
    case 1:
        iVal = 7;
        break;
    case 2:
        iVal = 6;
        break;
    case 3:
        iVal = 5;
        break;
    case 4:
        iVal = 4;
        break;
    case 5:
        iVal = 3;
        break;
    case 6:
        iVal = 2;
        break;
    case 7:
        iVal = 1;
        break;
    default:
        iVal = 8;
    }

    // Control if remaining bytes are not set. In this case the message is a second message and not a first one.
    for(int ii = iVal; ii < 8; ii++) {
        lFlag &= arrVal[ii];
        if(lFlag != 0xFF) {
            break;
        }
    }

    // lFlag will be 0xFF <=> all the bytes = 0xFF
    return (lFlag!=0xFF);
}

//--------------------------------------------------------
/**
 * @brief CProcessKalosLogs::setAutoTargetData  set message size (in byte) and label for auto target element error
 * @param data
 * @param arrVal
 */
void CProcessKalosLogs::setAutoTargetData(InfoDataStruct *data, unsigned int *arrVal) {

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
/**
 * @brief CProcessKalosLogs::setDirectionData       set message size (in byte) and label for auto, synchro and manual direction element error
 * @param data
 * @param arrVal
 */
void CProcessKalosLogs::setDirectionData(InfoDataStruct *data, unsigned int *arrVal) {

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
/**
 * @brief CProcessKalosLogs::setElevixTargetPosData     set message size (in byte) and label for elevix target pos error message
 * @param data
 */
void CProcessKalosLogs::setElevixTargetPosData(InfoDataStruct *data) {
    data->uiSize.push_back(2);
    data->uiSize.push_back(2);
    data->uiSize.push_back(2);

    data->strLabel.push_back(" iActual: ");
    data->strLabel.push_back(" EEpromMin: ");
    data->strLabel.push_back(" EEpromMax: ");
}

//--------------------------------------------------------
/**
 * @brief CProcessKalosLogs::setSynchroTargetData       set message size (in byte) and label for Synchro target error message
 * @param data
 */
void CProcessKalosLogs::setSynchroTargetData(InfoDataStruct *data) {
    data->uiSize.push_back(1);
    data->uiSize.push_back(2);
    data->uiSize.push_back(2);

    data->strLabel.push_back(" iDelta: ");
    data->strLabel.push_back(" iTarget: ");
    data->strLabel.push_back(" iActual: ");
}

//--------------------------------------------------------
/**
 * @brief CProcessKalosLogs::setAutoTargetPosData       set message size (in byte) and label for relative position elevix-pensile vert message error
 * @param data
 * @param arrVal
 */
void CProcessKalosLogs::setAutoTargetPosData(InfoDataStruct *data, unsigned int *arrVal) {

    data->uiSize.push_back(4);

    if(isFirstMessage(arrVal, 2)) {
        data->strLabel.push_back(" ElevixTarget ");
    }
    else {
        data->strLabel.push_back(" PensileVertTarget ");
    }

}

//--------------------------------------------------------
/**
 * @brief CProcessKalosLogs::setSynchroTargetPosData        set message size (in byte) and label for relative synchro position elevix-pensile vert message error
 * @param data
 */
void CProcessKalosLogs::setSynchroTargetPosData(InfoDataStruct *data) {

    data->uiSize.push_back(2);
    data->uiSize.push_back(2);

    data->strLabel.push_back(" ElevixActual: ");
    data->strLabel.push_back(" PensileVertActual: ");

}

//--------------------------------------------------------
/**
 * @brief CProcessKalosLogs::setUntimelySynchroData     set message size (in byte) and label for untimely synchro error message
 * @param data
 */
void CProcessKalosLogs::setUntimelySynchroData(InfoDataStruct *data) {

    data->uiSize.push_back(1);
    data->uiSize.push_back(1);
    data->uiSize.push_back(1);

    data->strLabel.push_back(" isNewPos: ");
    data->strLabel.push_back(" EnableSwitch: ");
    data->strLabel.push_back(" PensileMotionType: ");

}

//--------------------------------------------------------
void CProcessKalosLogs::setChangeAccessoryData(InfoDataStruct *data) {

    data->uiSize.push_back(2);

    data->strLabel.push_back("Stato_movimento_automatico: ");

}

//--------------------------------------------------------
/**
 * @brief CProcessKalosLogs::setDataToErrorType     set message size and label as function of error happened
 * @param uiDataArray       log data
 * @param error         error happened
 * @return  data struct containing correct message sizes and labels
 */
CProcessKalosLogs::InfoDataStruct CProcessKalosLogs::setDataToErrorType(unsigned int* uiDataArray, unsigned int error) {
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
    case 857:
    case 858:
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
    case 859:
        setChangeAccessoryData(&dataInfo);
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
/**
 * @brief CProcessKalosLogs::composeLineLog     compose data to write on file using predefined data sizes and labels
 * @param strFile
 * @param infoData
 * @param uiDataArray
 */
void CProcessKalosLogs::composeLineLog(string *strFile, InfoDataStruct *infoData, unsigned int dataID, unsigned int *uiDataArray) {
    unsigned int uiIndexDataArray;
    char s8aDummy[16]={0,};
    int iData;

    // Since for Motion Monitoring Logs we have already written error type, we have already used first two message slots
    if(dataID == 0x0657) {
        uiIndexDataArray = 2;
    }
    else {
        uiIndexDataArray = 0;
    }

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

        if(infoData->strLabel[ii] == " Angolo_Rot_decdegree: " || infoData->strLabel[ii] == " Angolo_Inc_decdegree: " ||
                infoData->strLabel[ii] == " pensile_target_inc: " || infoData->strLabel[ii] == " pensile_target_rot: ") {
            if (iData > 3600){
               iData = (abs(iData-65535) * -0.1);
            }
             else{
               iData = (iData * 0.1);
            }
        }

        itoa(iData, s8aDummy, 10);
        strFile->append(infoData->strLabel[ii]);
        strFile->append(s8aDummy);
    }

    strFile->append("\n" );

}

//--------------------------------------------------------
void CProcessKalosLogs::processFile (const char * ucaNameFileIn, const char * ucaNameFileOut)
{
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
    unsigned int uiID = 0;
    char strID[16];
    unsigned int
            lErrorID=0,
            ulaData[8]={0,};
    char s8aDummy[16]={0,}; // more than max Int number: 9 digits + sign

    string previousLine="";
    while(iRowCounter<1000000) // To get you all the lines.
    {
        bool bLogID = TRUE;
        dataInfo.strLabel.clear();
        dataInfo.uiSize.clear();
        getline(infile,STRING); // Saves the line in STRING.
        if (STRING != previousLine)// true in the end of file or file corrupted
        {
            std::size_t pos;
            previousLine = STRING;
            pos = STRING.find("<Id = 06");// if "find" fails then pos  = 4000000

            if (pos < STRING.size() )
            { // found ID file
                removeCharsUntil(&STRING,"; ");
                strTime = createTimeString( STRING.data() );
                removeCharsUntil(&STRING, "<Id = ");
                sscanf( STRING.data(), "%X", &uiID);
                sscanf( STRING.data(), "%s", strID);
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
                strOut.clear();
                strOut.append(strID);
                strOut.append(" - " );
                strOut.append(strTime);
                strOut.append(" " );
                switch(uiID) {
                case 0x0600:    // OX_CANLOG_ID_ES_BK1
                    setCanLogEsBkData(&dataInfo);
                    break;
                case 0x0610:    // OX_CANLOG_ID_AUTO1
                    setCanLogAutoData1(&dataInfo);
                    break;
                case 0x0620:    // OX_CANLOG_ID_VERT1
                    setCanLogVertData1(&dataInfo);
                    break;
                case 0x0621:    // OX_CANLOG_ID_VERT2
                    setCanLogVertData2(&dataInfo);
                    break;
                case 0x0622:    // OX_CANLOG_ID_VERT3
                    setCanLogVertData3(&dataInfo);
                    break;
                case 0x0623:    // OX_CANLOG_ID_VERT4
                    setCanLogVertData4(&dataInfo);
                    break;
                case 0x0630:    // OX_CANLOG_ID_LAT1
                    setCanLogLatData1(&dataInfo);
                    break;
                case 0x0631:    // OX_CANLOG_ID_LAT2
                    setCanLogLatData2(&dataInfo);
                    break;
                case 0x0640:    // OX_CANLOG_ID_LONG1
                    setCanLogLongData1(&dataInfo);
                    break;
                case 0x0641:    // OX_CANLOG_ID_LONG2
                    setCanLogLongData2(&dataInfo);
                    break;
                case 0x0644:    // OX_CANLOG_ID_ROT1
                    setCanLogRotData1(&dataInfo);
                    break;
                case 0x0645:    // OX_CANLOG_ID_ROT2
                    setCanLogRotData2(&dataInfo);
                    break;
                case 0x0647:    // OX_CANLOG_ID_INC1
                    setCanLogIncData1(&dataInfo);
                    break;
                case 0x0648:    // OX_CANLOG_ID_INC2
                    setCanLogIncData2(&dataInfo);
                    break;
                case 0x064A:    // OX_CANLOG_ID_DET_LAT1
                    setCanLogDetLatData1(&dataInfo);
                    break;
                case 0x064B:    // OX_CANLOG_ID_DET_LAT2
                    setCanLogDetLatData2(&dataInfo);
                    break;
                case 0x064D:    // OX_CANLOG_ID_DET_LONG1
                    setCanLogDetLongData1(&dataInfo);
                    break;
                case 0x064E:    // OX_CANLOG_ID_DET_LONG2
                    setCanLogDetLongData2(&dataInfo);
                    break;
                case 0x0650:    // OX_CANLOG_ID_SYNC
                    setCanLogSyncData(&dataInfo);
                    break;
                case 0x0660:    // OX_CANLOG_ID_TARGET1
                    setCanLogTargetData1(&dataInfo);
                    break;
                case 0x0661:    // OX_CANLOG_ID_TARGET2
                    setCanLogTargetData2(&dataInfo);
                    break;
                case 0x0654:    // OX_CANLOG_ID_DET_LAT_SYNC_DATA
                    setCanLogDetLatSyncData(&dataInfo);
                    break;
                case 0x0656:    // OX_CANLOG_ID_DET_LONG_SYNC_DATA
                    setCanLogDetLongSyncData(&dataInfo);
                    break;
                case 0x0657:    // MM_CANLOG_ID
                    lErrorID = ulaData[0]<<8 ;
                    lErrorID += ulaData[1];
                    itoa(lErrorID, s8aDummy, 10);
                    strOut.append("ErrorID: ");
                    strOut.append(s8aDummy);
                    strOut.append(" " );

                    dataInfo = setDataToErrorType(ulaData, lErrorID);
                    break;
                default:
                    bLogID = FALSE;
                }

                if(bLogID) {
                    composeLineLog(&strOut, &dataInfo, uiID, ulaData);
                    outFile << strOut;
                }
            }
            else
            {
                strOut.clear();
                strOut.append("ERROR LINE");
            }
        }
        iRowCounter++;
    }

    outFile.close();
    infile.close();

}
