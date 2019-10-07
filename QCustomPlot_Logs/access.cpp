#include "access.h"
#include "ui_access.h"
#include "QDebug"
#include <QMessageBox>
#include <QPixmap>

access::access(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::access)
{
	ui->setupUi(this);
}

access::~access()
{
	delete ui;
}

void access::on_pushButton_login_clicked()
{
	QString username = ui->lineEdit_username->text();
	QString password = ui->lineEdit_password->text();
	if(username==""&&password!=""){
		QMessageBox::warning(this,"","Invalid User");
	}
	if(password==""&&username!=""){
		QMessageBox::warning(this,"","Invalid password!");
	}
	if(username==""&&password==""){
		QMessageBox::warning(this,"alt","Need to insert valid fields");
	}
	if (password=="a" && username=="a"){

		access::close();
		mainWindow = new MainWindow (this);
		mainWindow->show();

	}
	else {
		if( username!="" && password!="" ){
			// QMessageBox::warning(this,"attenzione","username e password non corretti");
			QMessageBox::StandardButton reply =
					QMessageBox::question(this,"Login Alert",
										  "User Password not correct",
										  QMessageBox::Yes|QMessageBox::No);
			if(reply==QMessageBox::Yes)
			{
				new access (this);
				ui->lineEdit_password->setText("");
				ui->lineEdit_username->setText("");
			}
			else{
				QApplication::quit();
			}
		}
	}
}

