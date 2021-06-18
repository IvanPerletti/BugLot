#ifndef ACCESS_H
#define ACCESS_H

#include <QDialog>
#include "mainwindow.h"

namespace Ui {
class access;
}

class access : public QDialog
{
	Q_OBJECT

public:
	explicit access(QWidget *parent = 0);
	~access();

private slots:
	void on_pushButton_login_clicked();

private:
	Ui::access *ui;
	MainWindow *mainWindow;
	uint32_t hash(uint32_t u32Seed);
	uint32_t u32Licence;
};

#endif // ACCESS_H
