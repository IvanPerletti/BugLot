#include "cprocesskaloslogs.h"
#include <QString>
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

//static bool bAngle = FALSE;
bool bAngle = FALSE;

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
void CProcessKalosLogs::setCanLogEsBkData(string *strFile, unionDataInfo *infoStruct){

    sprintf(strData,
            "EnableSwitch: %d Horns: %d Move: %d Homing: %d "
            "RemoteEnablewitch: %d SUPER_ENABLE_SWITCH: %d BrakeStatus: %d Brake_active: %d",
            infoStruct->msg2.i8Data1, infoStruct->msg2.i8Data2, infoStruct->msg2.i8Data3, infoStruct->msg2.i8Data4,
            infoStruct->msg2.i8Data5, infoStruct->msg2.i8Data6, infoStruct->msg2.i8Data7, infoStruct->msg2.i8Data8);
    strFile->append(strData);

}

//--------------------------------------------------------
void CProcessKalosLogs::setCanLogAutoData1(string *strFile, unionDataInfo *infoStruct){


    sprintf(strData,
            "Stato_movimento_automatico: %d Accessorio: %d Posizione: %d all_movements_started: %d all_movements_finished %d",
            infoStruct->msg4.iData1, infoStruct->msg4.i8Data2, (uint8_t) infoStruct->msg4.i8Data3, infoStruct->msg4.iData4, infoStruct->msg4.iData5);

    strFile->append(strData);

}

//--------------------------------------------------------
void CProcessKalosLogs::setCanLogVertData1(string *strFile, unionDataInfo *infoStruct){

    sprintf(strData,
            "Stato_motore_pensile_vert: %d CmdMask[M_PENSILE_VERT]: %d ExclMask[M_PENSILE_VERT]: %d CollMask[M_PENSILE_VERT]: %d",
            infoStruct->msg1.iData1, infoStruct->msg1.iData2, infoStruct->msg1.iData3, infoStruct->msg1.iData4);
    strFile->append(strData);

}

//--------------------------------------------------------
void CProcessKalosLogs::setCanLogVertData2(string *strFile, unionDataInfo *infoStruct){


    sprintf(strData,
            "WSpeed_pensile: %ld WDir_pensile_vert: %d AKD_drv_status: %d Op_mode_AKD: %d",
            infoStruct->msg5.lData1, infoStruct->msg5.iData2, infoStruct->msg5.i8Data3, infoStruct->msg5.i8Data4);
    strFile->append(strData);

}

//--------------------------------------------------------
void CProcessKalosLogs::setCanLogVertData3(string *strFile, unionDataInfo *infoStruct){


    sprintf(strData,
            "H_AKD_encoder_mm: %d Rampa_tube_vert_mm: %d Tube_Target_Verticale_mm: %d "
            "U_Sound_brake: %d HW_maintenance: %d",
            infoStruct->msg6.iData1, infoStruct->msg6.iData2, infoStruct->msg6.iData3,
            infoStruct->msg6.i8Data4, infoStruct->msg6.i8Data5);
    strFile->append(strData);

}

//--------------------------------------------------------
void CProcessKalosLogs::setCanLogVertData4(string *strFile, unionDataInfo *infoStruct){


    sprintf(strData,
            "EndMMove[M_PENSILE_VERT]: %d BrkMask[M_PENSILE_VERT]: %d FcMask[M_PENSILE_VERT]: %d ",
            infoStruct->msg1.iData1, infoStruct->msg1.iData2, infoStruct->msg1.iData3);
    strFile->append(strData);

}

//--------------------------------------------------------
void CProcessKalosLogs::setCanLogLatData1(string *strFile, unionDataInfo *infoStruct){


    sprintf(strData,
            "Stato_motore_pensile_lat: %d CmdMask[M_PENSILE_LAT]: %d ExclMask[M_PENSILE_LAT]: %d CollMask[M_PENSILE_LAT]: %d",
            infoStruct->msg1.iData1, infoStruct->msg1.iData2, infoStruct->msg1.iData3, infoStruct->msg1.iData4);
    strFile->append(strData);

}

//--------------------------------------------------------
void CProcessKalosLogs::setCanLogLatData2(string *strFile, unionDataInfo *infoStruct){


    sprintf(strData,
            "WDir_pensile_lat: %d Pos_pensile_lat_mm: %d",
            infoStruct->msg1.iData1, infoStruct->msg1.iData2);
    strFile->append(strData);

}

//--------------------------------------------------------
void CProcessKalosLogs::setCanLogLongData1(string *strFile, unionDataInfo *infoStruct){


    sprintf(strData,
            "Stato_motore_pensile_long: %d CmdMask[M_PENSILE_LONG]: %d ExclMask[M_PENSILE_LONG]: %d CollMask[M_PENSILE_LONG]: %d",
            infoStruct->msg1.iData1, infoStruct->msg1.iData2, infoStruct->msg1.iData3, infoStruct->msg1.iData4);
    strFile->append(strData);

}

//--------------------------------------------------------
void CProcessKalosLogs::setCanLogLongData2(string *strFile, unionDataInfo *infoStruct){


    sprintf(strData,
            "WDir_pensile_long: %d Pos_pensile_long_mm: %d",
            infoStruct->msg1.iData1, infoStruct->msg1.iData2);
    strFile->append(strData);
}

//--------------------------------------------------------
void CProcessKalosLogs::setCanLogRotData1(string *strFile, unionDataInfo *infoStruct){


    sprintf(strData,
            "Stato_motore_pensile_rot: %d CmdMask[M_PENSILE_ROT]: %d ExclMask[M_PENSILE_ROT]: %d CollMask[M_PENSILE_ROT]: %d",
            infoStruct->msg1.iData1, infoStruct->msg1.iData2, infoStruct->msg1.iData3, infoStruct->msg1.iData4);
    strFile->append(strData);

}

//--------------------------------------------------------
void CProcessKalosLogs::setCanLogRotData2(string *strFile, unionDataInfo *infoStruct){


    sprintf(strData,
            "WDir_pensile_rot: %d Angolo_Rot_decdegree: %d",
            infoStruct->msg1.iData1, infoStruct->msg1.iData2);
    strFile->append(strData);
}

//--------------------------------------------------------
void CProcessKalosLogs::setCanLogIncData1(string *strFile, unionDataInfo *infoStruct){


    sprintf(strData,
            "Stato_motore_pensile_inc: %d CmdMask[M_PENSILE_INC]: %d ExclMask[M_PENSILE_INC]: %d CollMask[M_PENSILE_INC]: %d",
            infoStruct->msg1.iData1, (unsigned int) infoStruct->msg1.iData2, (unsigned int) infoStruct->msg1.iData3, (unsigned int) infoStruct->msg1.iData4);
    strFile->append(strData);

}

//--------------------------------------------------------
void CProcessKalosLogs::setCanLogIncData2(string *strFile, unionDataInfo *infoStruct){


    sprintf(strData,
            "WDir_pensile_inc: %d Angolo_Inc_decdegree: %d pensile_target_inc: %ld",
            infoStruct->msg7.iData1, infoStruct->msg7.iData2, infoStruct->msg7.lData3);
    strFile->append(strData);

}

//--------------------------------------------------------
void CProcessKalosLogs::setCanLogDetLatData1(string *strFile, unionDataInfo *infoStruct){


    sprintf(strData,
            "Stato_motore_detettore_lat: %d CmdMask[M_DETETTORE_LAT]: %d ExclMask[M_DETETTORE_LAT]: %d CollMask[M_DETETTORE_LAT]: %d",
            infoStruct->msg1.iData1, infoStruct->msg1.iData2, infoStruct->msg1.iData3, infoStruct->msg1.iData4);
    strFile->append(strData);

}

//--------------------------------------------------------
void CProcessKalosLogs::setCanLogDetLatData2(string *strFile, unionDataInfo *infoStruct){


    sprintf(strData,
            "WDir_detettore_lat: %d Pos_detettore_lat_mm: %d detettore_target_lat: %ld",
            infoStruct->msg7.iData1, infoStruct->msg7.iData2, infoStruct->msg7.lData3);
    strFile->append(strData);

}

//--------------------------------------------------------
void CProcessKalosLogs::setCanLogDetLongData1(string *strFile, unionDataInfo *infoStruct) {


    sprintf(strData,
            "Stato_motore_detettore_long: %d CmdMask[M_DETETTORE_LONG]: %d ExclMask[M_DETETTORE_LONG]: %d CollMask[M_DETETTORE_LONG]: %d",
            infoStruct->msg1.iData1, infoStruct->msg1.iData2, infoStruct->msg1.iData3, infoStruct->msg1.iData4);
    strFile->append(strData);

}

//--------------------------------------------------------
void CProcessKalosLogs::setCanLogDetLongData2(string *strFile, unionDataInfo *infoStruct){


    sprintf(strData,
            "WDir_detettore_long: %d Pos_detettore_long_mm: %d detettore_target_long: %ld",
            infoStruct->msg7.iData1, infoStruct->msg7.iData2, infoStruct->msg7.lData3);
    strFile->append(strData);
}

//--------------------------------------------------------
void CProcessKalosLogs::setCanLogSyncData(string *strFile, unionDataInfo *infoStruct){


    sprintf(strData,
            "Syncro_status: %d ok_to_synchronize: %d is_synchronized: %d exit_from_synchro: %d "
            "Dead_zone_sync: %d Syncro_pensile_error: %d",
            infoStruct->msg9.iData1, infoStruct->msg9.i8Data2, infoStruct->msg9.i8Data3, infoStruct->msg9.i8Data4,
            infoStruct->msg9.i8Data5, infoStruct->msg9.iData6);
    strFile->append(strData);

}

//--------------------------------------------------------
void CProcessKalosLogs::setCanLogTargetData1(string *strFile, unionDataInfo *infoStruct){


    sprintf(strData,
            "pensile_target_vert: %ld pensile_target_lat: %ld ",
            infoStruct->msg3.lData1, infoStruct->msg3.lData2);
    strFile->append(strData);

}

//--------------------------------------------------------
void CProcessKalosLogs::setCanLogTargetData2(string *strFile, unionDataInfo *infoStruct){


    sprintf(strData,
            "pensile_target_long: %ld pensile_target_rot: %ld ",
            infoStruct->msg3.lData1, infoStruct->msg3.lData2);
    strFile->append(strData);

}

//--------------------------------------------------------
void CProcessKalosLogs::setInterlockData(string *strFile, unionDataInfo *infoStruct){

    sprintf(strData,
                "X_rays_interlock_movement: %d X_rays_interlock_exam_changed: %d  X_rays_interlock_cassette_not_ok: %d",
                infoStruct->msg2.i8Data1, infoStruct->msg2.i8Data2, infoStruct->msg2.i8Data3);

    strFile->append(strData);

}

//--------------------------------------------------------
void CProcessKalosLogs::setBrakesBlockData(string *strFile, unionDataInfo *infoStruct){

    if(infoStruct->caAllData[0] == (char) 255) {
        sprintf(strData,
                "LOG BRAKES Libera_freni_automatico()");
    }
    else {
        sprintf(strData,
                "Motore: %d OnOff: %d  ID: %d",
                infoStruct->msg2.i8Data1, infoStruct->msg2.i8Data2, infoStruct->msg2.i8Data3);
    }
    strFile->append(strData);

}

//--------------------------------------------------------
void CProcessKalosLogs::setCanLogDetLatSyncData(string *strFile, unionDataInfo *infoStruct){


    sprintf(strData,
            "FM713_detettore_lat_loop_speed: %d Syncro_detettore_lat_error: %d orobix_dead_zone_sync_lat_before: %d"
            "orobix_dead_zone_sync_lat_after: %d Corsa_detettore_lat: %d",
            infoStruct->msg8.iData1, infoStruct->msg8.i8Data2, infoStruct->msg8.i8Data3, infoStruct->msg8.i8Data4, infoStruct->msg8.i8Data5);
    strFile->append(strData);
}

//--------------------------------------------------------
void CProcessKalosLogs::setCanLogDetLongSyncData(string *strFile, unionDataInfo *infoStruct){


    sprintf(strData,
            "FM713_detettore_long_loop_speed: %d Syncro_detettore_long_error: %d orobix_dead_zone_sync_long_befor:e %d"
            "orobix_dead_zone_sync_long_after: %d Corsa_detettore_long: %d",
            infoStruct->msg8.iData1, infoStruct->msg8.i8Data2, infoStruct->msg8.i8Data3, infoStruct->msg8.i8Data4, infoStruct->msg8.i8Data5);
    strFile->append(strData);

}

//--------------------------------------------------------
/**
 * @brief CProcessKalosLogs::setCanLogMotionMonitoringInfo  set message size (in byte) and label for informative Motion Monitoring CAN logs
 * @param uiType        identify type of info sent
 * @param infoStruct    pointer to struct containing data size and label
 */
void CProcessKalosLogs::setCanLogMotionMonitoringInfo(string *strFile, unionDataInfo *infoStruct){

    signed int iTypeInfo = (int) infoStruct->caAllData[0];

    switch(iTypeInfo) {
    case 1:         // MOTION_TYPE_INFO
        sprintf(strData,
                "Pensile.wType: %d TableBucky.wType: %d WallBucky.wType: %d Elevix.wType: %d "
                "bIsNewPos: %d bExamFinished: %d",
                infoStruct->msg2.i8Data2, infoStruct->msg2.i8Data3, infoStruct->msg2.i8Data4,
                infoStruct->msg2.i8Data5, infoStruct->msg2.i8Data6, infoStruct->msg2.i8Data7);
        break;
    case 2:          // MANUAL_INFO
        sprintf(strData,
                "elType: %d bManualMotion: %d Direction: %d",
                infoStruct->msg2.i8Data2, infoStruct->msg2.i8Data3, infoStruct->msg2.i8Data4);
        break;
    }
    strFile->append(strData);

}

//--------------------------------------------------------
/**
 * @brief CProcessKalosLogs::setLineError set message size (in byte) and label for error message requiring line of error
 * @param data     pointer to struct containing data size and label
 */
void CProcessKalosLogs::setLineError(string *strFile, unionDataInfo *infoStruct) {


    sprintf(strData,
            "LineOfError: %d",
            infoStruct->msgMM_2.i8Data1);
    strFile->append(strData);

}

//--------------------------------------------------------
/**
 * @brief CProcessKalosLogs::setNoMotionData    set message size (in byte) and label for error message related to no motion errors
 * @param data      pointer to struct containing data size and label
 */
void CProcessKalosLogs::setNoMotionData(string *strFile, unionDataInfo *infoStruct) {

    sprintf(strData,
            "iActual: %d iTarget: %d iThr: %d",
            infoStruct->msgMM_3.iData1, infoStruct->msgMM_3.iData2, infoStruct->msgMM_3.iData3);
    strFile->append(strData);

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
void CProcessKalosLogs::setAutoTargetData(string *strFile, unionDataInfo *infoStruct) {


    if(isFirstMessage(( unsigned int *) infoStruct->caAllData, 2)) {
        sprintf(strData,
                "iTarget: %ld iInitial: %d",
                infoStruct->msgMM_1.lData1, infoStruct->msg1.iData2);
    }
    else {
        sprintf(strData,
                "Direction: %d ElementType: %d iActual: %d",
                infoStruct->msgMM_2.i8Data1, infoStruct->msgMM_2.i8Data2, infoStruct->msgMM_2.iData3);
    }

    strFile->append(strData);
}

//--------------------------------------------------------
/**
 * @brief CProcessKalosLogs::setDirectionData       set message size (in byte) and label for auto, synchro and manual direction element error
 * @param data
 * @param arrVal
 */
void CProcessKalosLogs::setDirectionData(string *strFile, unionDataInfo *infoStruct) {


    if(isFirstMessage(( unsigned int *) infoStruct->caAllData, 4)) {
        sprintf(strData,
                "iActual: %d iPrevPos: %d iCheckPos: %d",
                infoStruct->msgMM_3.iData1, infoStruct->msgMM_3.iData2, infoStruct->msgMM_3.iData3);
    }
    else {
        sprintf(strData,
                "Direction: %d ElementType: %d",
                infoStruct->msgMM_2.i8Data1, infoStruct->msgMM_2.i8Data2);
    }

    strFile->append(strData);
}

//--------------------------------------------------------
/**
 * @brief CProcessKalosLogs::setElevixTargetPosData     set message size (in byte) and label for elevix target pos error message
 * @param data
 */
void CProcessKalosLogs::setElevixTargetPosData(string *strFile, unionDataInfo *infoStruct) {


    sprintf(strData,
            "iActual: %d EEpromMin: %d EEpromMax: %d",
            infoStruct->msgMM_3.iData1, infoStruct->msgMM_3.iData2, infoStruct->msgMM_3.iData3);

    strFile->append(strData);

}

//--------------------------------------------------------
/**
 * @brief CProcessKalosLogs::setSynchroTargetData       set message size (in byte) and label for Synchro target error message
 * @param data
 */
void CProcessKalosLogs::setSynchroTargetData(string *strFile, unionDataInfo *infoStruct) {


    sprintf(strData,
            "iDelta: %d iTarget: %d iActual: %d",
            infoStruct->msgMM_4.i8Data1, infoStruct->msgMM_4.iData2, infoStruct->msgMM_4.iData3);

    strFile->append(strData);

}

//--------------------------------------------------------
/**
 * @brief CProcessKalosLogs::setAutoTargetPosData       set message size (in byte) and label for relative position elevix-pensile vert message error
 * @param data
 * @param arrVal
 */
void CProcessKalosLogs::setAutoTargetPosData(string *strFile, unionDataInfo *infoStruct) {


    if(isFirstMessage(( unsigned int *) infoStruct->caAllData, 4)) {
        sprintf(strData,
                "ElevixTarget: %ld",
                infoStruct->msgMM_1.lData1);
    }
    else {
        sprintf(strData,
                "PensileVertTarget: %ld",
                infoStruct->msgMM_1.lData1);
    }
    strFile->append(strData);

}

//--------------------------------------------------------
/**
 * @brief CProcessKalosLogs::setSynchroTargetPosData        set message size (in byte) and label for relative synchro position elevix-pensile vert message error
 * @param data
 */
void CProcessKalosLogs::setSynchroTargetPosData(string *strFile, unionDataInfo *infoStruct) {


    sprintf(strData,
            "PensileVertActual: %d ElevixActual: %d",
            infoStruct->msgMM_3.iData1, infoStruct->msgMM_3.iData2);

    strFile->append(strData);
}

//--------------------------------------------------------
/**
 * @brief CProcessKalosLogs::setUntimelySynchroData     set message size (in byte) and label for untimely synchro error message
 * @param data
 */
void CProcessKalosLogs::setUntimelySynchroData(string *strFile, unionDataInfo *infoStruct) {


    sprintf(strData,
            "isNewPos: %d EnableSwitch: %d PensileMotionType: %d bExamFinished: %d all_movements_finished: %d",
            infoStruct->msgMM_5.i8Data1, infoStruct->msgMM_5.i8Data2, infoStruct->msgMM_5.i8Data3, infoStruct->msgMM_5.i8Data4, infoStruct->msgMM_5.iData5);

    strFile->append(strData);

}

//--------------------------------------------------------
void CProcessKalosLogs::setChangeAccessoryData(string *strFile, unionDataInfo *infoStruct) {


    sprintf(strData,
            "Stato_movimento_automatico: %d Accessorio: %d Posizione: %d "
            "Accessorio_Errore: %d Posizione_Errore: %d",
            infoStruct->msgMM_6.iData1, infoStruct->msgMM_6.i8Data2, infoStruct->msgMM_6.i8Data3, infoStruct->msgMM_6.i8Data4, infoStruct->msgMM_6.i8Data5);

    strFile->append(strData);

}

//--------------------------------------------------------
void CProcessKalosLogs::setAxesDriverData(string *strFile, unionDataInfo *infoStruct) {


    sprintf(strData,
            "AxisStat: %d",
            infoStruct->msgMM_5.i8Data1);

    strFile->append(strData);

}

//--------------------------------------------------------
/**
 * @brief CProcessKalosLogs::setDataToErrorType     set message size and label as function of error happened
 * @param uiDataArray       log data
 * @param error         error happened
 * @return  data struct containing correct message sizes and labels
 */
CProcessKalosLogs::InfoDataStruct CProcessKalosLogs::setDataToErrorType(string *strFile, unionDataInfo *infoStruct, unsigned int error) {
    InfoDataStruct dataInfo;

    switch(error){
    case 851:
    case 852:
        setLineError(strFile, infoStruct);
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
        setNoMotionData(strFile, infoStruct);
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
        setAutoTargetData(strFile, infoStruct);
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
        setDirectionData(strFile, infoStruct);
        break;
    case 843:
        setElevixTargetPosData(strFile, infoStruct);
        break;
    case 791:
    case 801:
    case 803:
        setSynchroTargetData(strFile, infoStruct);
        break;
    case 853:
    case 854:
    case 855:
        setAutoTargetPosData(strFile, infoStruct);
        break;
    case 856:
        setSynchroTargetPosData(strFile, infoStruct);
        break;
    case 779:
        setUntimelySynchroData(strFile, infoStruct);
        break;
    case 859:
        setChangeAccessoryData(strFile, infoStruct);
        break;
    case 823:
    case 824:
        setAxesDriverData(strFile, infoStruct);
        break;
    case 768:
    case 769:
    case 794:
    case 796:
        // No data apart from error ID sent from these ones
        break;
    }

    return dataInfo;
}

//--------------------------------------------------------
void CProcessKalosLogs::set_log_char(char *cDataArr, unsigned int* uiDataArray) {

    cDataArr[0] = uiDataArray[0];
    cDataArr[1] = uiDataArray[1];
    cDataArr[2] = uiDataArray[2];
    cDataArr[3] = uiDataArray[3];
    cDataArr[4] = uiDataArray[4];
    cDataArr[5] = uiDataArray[5];
    cDataArr[6] = uiDataArray[6];
    cDataArr[7] = uiDataArray[7];

}

//--------------------------------------------------------
void CProcessKalosLogs::processFile (const char * ucaNameFileIn, const char * ucaNameFileOut)
{
    string STRING, strOut, strTime;
    ifstream infile;
    ofstream outFile;
    InfoDataStruct dataInfo;

    // UNION
    unionDataInfo unionData;

    if (ucaNameFileIn == NULL || ucaNameFileOut == NULL ){
        return;
    }

    infile.open (ucaNameFileIn);
    outFile.open (ucaNameFileOut, std::ofstream::out | std::ofstream::trunc);
    int iRowCounter=0;
    unsigned int uiID = 0;
    char strID[16];
    unsigned int uiErrorID =0;

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
                    &unionData.caAllData[0],
                    &unionData.caAllData[1],
                    &unionData.caAllData[2],
                    &unionData.caAllData[3],
                    &unionData.caAllData[4],
                    &unionData.caAllData[5],
                    &unionData.caAllData[6],
                    &unionData.caAllData[7]);// extract numbers
                strOut.clear();
                strOut.append(strID);
                strOut.append(" - " );
                strOut.append(strTime);
                strOut.append(" " );
                switch(uiID) {
                case 0x0600:    // OX_CANLOG_ID_ES_BK1
                    setCanLogEsBkData(&strOut, &unionData);
                    break;
                case 0x0610:    // OX_CANLOG_ID_AUTO1
                    setCanLogAutoData1(&strOut, &unionData);
                    break;
                case 0x0620:    // OX_CANLOG_ID_VERT1
                    setCanLogVertData1(&strOut, &unionData);
                    break;
                case 0x0621:    // OX_CANLOG_ID_VERT2
                    setCanLogVertData2(&strOut, &unionData);
                    break;
                case 0x0622:    // OX_CANLOG_ID_VERT3
                    setCanLogVertData3(&strOut, &unionData);
                    break;
                case 0x0623:    // OX_CANLOG_ID_VERT4
                    setCanLogVertData4(&strOut, &unionData);
                    break;
                case 0x0630:    // OX_CANLOG_ID_LAT1
                    setCanLogLatData1(&strOut, &unionData);
                    break;
                case 0x0631:    // OX_CANLOG_ID_LAT2
                    setCanLogLatData2(&strOut, &unionData);
                    break;
                case 0x0640:    // OX_CANLOG_ID_LONG1
                    setCanLogLongData1(&strOut, &unionData);
                    break;
                case 0x0641:    // OX_CANLOG_ID_LONG2
                    setCanLogLongData2(&strOut, &unionData);
                    break;
                case 0x0644:    // OX_CANLOG_ID_ROT1
                    setCanLogRotData1(&strOut, &unionData);
                    break;
                case 0x0645:    // OX_CANLOG_ID_ROT2
                    setCanLogRotData2(&strOut, &unionData);
                    break;
                case 0x0647:    // OX_CANLOG_ID_INC1
                    setCanLogIncData1(&strOut, &unionData);
                    break;
                case 0x0648:    // OX_CANLOG_ID_INC2
                    setCanLogIncData2(&strOut, &unionData);
                    break;
                case 0x064A:    // OX_CANLOG_ID_DET_LAT1
                    setCanLogDetLatData1(&strOut, &unionData);
                    break;
                case 0x064B:    // OX_CANLOG_ID_DET_LAT2
                    setCanLogDetLatData2(&strOut, &unionData);
                    break;
                case 0x064D:    // OX_CANLOG_ID_DET_LONG1
                    setCanLogDetLongData1(&strOut, &unionData);
                    break;
                case 0x064E:    // OX_CANLOG_ID_DET_LONG2
                    setCanLogDetLongData2(&strOut, &unionData);
                    break;
                case 0x0650:    // OX_CANLOG_ID_SYNC
                    setCanLogSyncData(&strOut, &unionData);
                    break;
                case 0x0660:    // OX_CANLOG_ID_TARGET1
                    setCanLogTargetData1(&strOut, &unionData);
                    break;
                case 0x0661:    // OX_CANLOG_ID_TARGET2
                    setCanLogTargetData2(&strOut, &unionData);
                    break;
                case 0x652:     // CANLOG_INTERLOCK
                    setInterlockData(&strOut, &unionData);
                    break;
                case 0x653:     // CANLOG_BRAKE_BLOCK
                    setBrakesBlockData(&strOut, &unionData);
                    break;
                case 0x0654:    // OX_CANLOG_ID_DET_LAT_SYNC_DATA
                    setCanLogDetLatSyncData(&strOut, &unionData);
                    break;
                case 0x0656:    // OX_CANLOG_ID_DET_LONG_SYNC_DATA
                    setCanLogDetLongSyncData(&strOut, &unionData);
                    break;
                case 0x0655:    // MM_CANLOG_ID_INFO
                    setCanLogMotionMonitoringInfo(&strOut, &unionData);
                    break;
                case 0x0657:    // MM_CANLOG_ID
                    uiErrorID = (unsigned int) unionData.caAllData[0]<<8 ;
                    uiErrorID += (unsigned int) unionData.caAllData[1];

                    char cArrData[255];
                    sprintf(cArrData,
                            "ErrorID: %d ",
                            uiErrorID);
                    strOut.append(cArrData);

                    dataInfo = setDataToErrorType(&strOut, &unionData, uiErrorID);
                    break;
                default:
                    bLogID = FALSE;
                }

                if(bLogID) {
                    outFile << strOut << endl;
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
