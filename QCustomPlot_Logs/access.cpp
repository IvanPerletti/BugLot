#include "access.h"
#include "ui_access.h"
#include "QDebug"
#include <QMessageBox>
#include <QPixmap>
#include <windows.h>
#include "ISettings.h"

access::access(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::access),
	u32Licence(0)
{
	ui->setupUi(this);
	DWORD dwVolSerial;
	bool bIsRetrieved = GetVolumeInformationA("C:\\", NULL, NULL, &dwVolSerial, NULL, NULL, NULL, NULL);
	if ( bIsRetrieved )
	{
		u32Licence = dwVolSerial ^ 0xB0DECAFE;
	}else
	{
		u32Licence = 0xB0DECAFE * 31;
	}
	const uint32_t u32ValA = ( u32Licence >> 16 ) & 0xFFff;
	const uint32_t u32ValB = u32Licence & 0xFFff;

	ui->lblVolumeInfo->setText (
				QString("%1 - %2").
				arg(u32ValA, 0, 16 ).
				arg(u32ValB, 0, 16 ));
}

access::~access()
{
	delete ui;
}


uint32_t access::hash(uint32_t u32Seed)
{
	uint32_t u32Hash = (u32Seed ^ 0xACCADE );
	u32Hash = u32Hash * 0xDEA ;
	return(u32Hash);
}


//uint32_t access::hash(QString str2Hash)
//{
//	uint32_t u32HashAddress = 5381;
//	const uint32_t u32SzStr = str2Hash.size();
//	for (uint32_t ii = 0; ii < u32SzStr ; ii++)
//	{
//		uint32_t u32Val = str2Hash.at(ii).toLatin1();
//		u32HashAddress = ((u32HashAddress << 5) + u32HashAddress) + u32Val;
//	}
//	return(u32HashAddress);
//}

void access::on_pushButton_login_clicked()
{
	QString username = ui->lineEdit_username->text();

	if(username==""){
		QMessageBox::warning(this,"","Invalid User");
	}
	else{

		QString stHash = iSettings.load( ISettings::SET_HASH_01 ).toString();
		iSettings.save( ISettings::SET_HASH_01, stHash );
		bool ok;
		uint32_t u32ParsedValue ;
		uint32_t u32HashedValue ;
		u32ParsedValue = stHash.toLatin1().toUInt(&ok, 16);
		u32HashedValue = hash( u32Licence );
		if ( ok )
		{
			ok = (u32HashedValue == u32ParsedValue);
		}
		QString str0 = ui->lblVolumeInfo->text();

		if (username=="ip" && ok)
		{
			access::close();
			mainWindow = new MainWindow;
			mainWindow->show();
		}
		else {
			if( username!="" ){

						QMessageBox msgWarning;
							msgWarning.setText("WARNING!\nCredential not ok");
							msgWarning.setIcon(QMessageBox::Warning);
							msgWarning.setWindowTitle("LOGIN");
							msgWarning.exec();

				QApplication::quit();
			}
		}
	}
}

