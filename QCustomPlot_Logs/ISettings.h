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
 *
 ******************************************************************************/
#ifndef ISETTINGS_H
#define ISETTINGS_H

#include <QString>
#include <QVariant>
#include <QSettings>


class ISettings
{

	public:
	typedef enum
	{
		SET_CYCLESDONE   = 0,
		SET_HASH_01         ,
		SET_CURR_PATH       ,
		SET_NUMEL           ,
	}enumSettings           ;

	private:
	typedef struct {
		enumSettings enVal  ; // enumerative associated
		QString strParam    ; // parameter's name
		QString strGroup    ; // parameter's group
		QVariant strDefault ; // default string
	}structRecordSettings   ;

	static const structRecordSettings recordList[SET_NUMEL];
	QSettings * pSetting;

	public:
	static ISettings& instance()
	{
		static ISettings iSettings;
		return iSettings;
	}

	void save(const enumSettings key,
			  const QVariant &value);

	QVariant load(const enumSettings &key);

	private:
	void initSettings(void);
	void saveParam(const QString &key,
				   const QString &group,
				   const QVariant &value);

	QVariant loadParam(const QString &key,
					   const QString &group,
					   const QVariant &defaultValue = QVariant());

	ISettings();
};
extern ISettings iSettings;
#endif // ISETTINGS_H
