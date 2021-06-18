/******************************************************************************
 * @file 		ISettings class implementation
 * @brief		This class is used to configure Application Settings
 * @author		IVAN Perletti - General Medical Merate.spa - Seriate - ITALY
 * @version		1.0
 * @date		July 25th, 2019
 * @post 		Nope
 * @bug			Not all memory is freed when deleting an object of this class.
 * @warning		Improper use can crash your application
 * @copyright 	GMM.spa - All Rights Reserved
 ******************************************************************************/
#include "ISettings.h"
#include <QDir>
#include <QDebug>

ISettings iSettings = ISettings::instance();
//------------------------------------------------------------------------------
const ISettings::structRecordSettings ISettings::recordList[]
{
	{ISettings::SET_CYCLESDONE ,"Cycles", "Grp0", int(0)              },
	{ISettings::SET_HASH_01    ,"Key01" , "Grp0", QString("B0DEB4238")},
	{ISettings::SET_CURR_PATH    ,"Key02" , "Grp0", QString("./")},

};
//------------------------------------------------------------------------------
ISettings::ISettings()
{
	pSetting = nullptr;
	initSettings();
}
//------------------------------------------------------------------------------
/**
 * @brief save settings to file
 * @param key     variable to be saved
 * @param value   value to be saved
 */
void ISettings::save(const enumSettings key,
					 const QVariant &value)
{
	const QString strKey   = recordList[key].strParam;
	const QString strGroup = recordList[key].strGroup;
	saveParam(strKey,strGroup,value);
}
//------------------------------------------------------------------------------
/**
 * @brief load current settings belonging to variable
 * @param key            key value string to be searched into settings file
 * @param defaultValue   default value if variable is not found
 * @return value or default value if varible is not found
 */
QVariant ISettings::load(const enumSettings &key)
{
	QVariant variant = "-1"; // invalid
	if( key < SET_NUMEL )
	{
		const QString strKey   = recordList[key].strParam;
		const QString strGroup = recordList[key].strGroup;
		QVariant valDflt  = recordList[key].strDefault;
		variant = loadParam(strKey,strGroup,valDflt);
	}
	return(variant);
}
//------------------------------------------------------------------------------
void ISettings::initSettings(void)
{
	QString str1 = QDir::currentPath()+"/config.ini";
	qDebug()<<str1;
	pSetting = new QSettings(str1,
							 QSettings::IniFormat);
}

//------------------------------------------------------------------------------
/**
 * @brief save settings to file
 * @param key     variable to be saved
 * @param value   value to be saved
 * @param group   group of the variable
 */
void ISettings::saveParam(const QString &key,
						  const QString &group,
						  const QVariant &value)
{
	if(pSetting!=nullptr)
	{
		pSetting->beginGroup(group);
		pSetting->setValue(key, value);
		pSetting->endGroup();
	}
}
//------------------------------------------------------------------------------
/**
 * @brief load current settings belonging to variable
 * @param key            key value string to be searched into settings file
 * @param group          belonging group of searched variable
 * @param defaultValue   default value if variable is not found
 * @return value or default value if varible is not found
 */
QVariant ISettings::loadParam(const QString &key,
							  const QString &group,
							  const QVariant &defaultValue)
{
	QVariant value ;
	if(pSetting!=nullptr)
	{
		pSetting->beginGroup(group);
		QString str1 =  pSetting->fileName();
		if(str1!=" ")
		{
			value = pSetting->value(key, defaultValue);
			pSetting->endGroup();
		}
	}
	return value;
}
//------------------------------------------------------------------------------
