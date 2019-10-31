/***************************************************************************
**                                                                        **
**  QCustomPlot, an easy to use, modern plotting widget for Qt            **
**  Copyright (C) 2011-2017 Emanuel Eichhammer                            **
**                                                                        **
**  This program is free software: you can redistribute it and/or modify  **
**  it under the terms of the GNU General Public License as published by  **
**  the Free Software Foundation, either version 3 of the License, or     **
**  (at your option) any later version.                                   **
**                                                                        **
**  This program is distributed in the hope that it will be useful,       **
**  but WITHOUT ANY WARRANTY; without even the implied warranty of        **
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         **
**  GNU General Public License for more details.                          **
**                                                                        **
**  You should have received a copy of the GNU General Public License     **
**  along with this program.  If not, see http://www.gnu.org/licenses/.   **
**                                                                        **
****************************************************************************
**           Author: Emanuel Eichhammer                                   **
**  Website/Contact: http://www.qcustomplot.com/                          **
**             Date: 04.09.17                                             **
**          Version: 2.0.0                                                **
****************************************************************************/

/************************************************************************************************************
**                                                                                                         **
**  This is the example code for QCustomPlot.                                                              **
**                                                                                                         **
**  It demonstrates basic and some advanced capabilities of the widget. The interesting code is inside     **
**  the "setup(...)Demo" functions of MainWindow.                                                          **
**                                                                                                         **
**  In order to see a demo in action, call the respective "setup(...)Demo" function inside the             **
**  MainWindow constructor. Alternatively you may call setupDemo(i) where i is the index of the demo       **
**  you want (for those, see MainWindow constructor comments). All other functions here are merely a       **
**  way to easily create screenshots of all demos for the website. I.e. a timer is set to successively     **
**  setup all the demos and make a screenshot of the window area and save it in the ./screenshots          **
**  directory.                                                                                             **
**                                                                                                         **
*************************************************************************************************************/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "../../qcustomplot.h" // the header file of QCustomPlot. Don't forget to add it to your project, if you use an IDE, so it gets compiled.
#include "zoomplot.h"

namespace Ui {
	class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

	public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

	void setupDemo(int demoIndex);

	void setupPlotLogs(void);
	void setupPlayground(QCustomPlot *customPlot);

	void realtimeDataSlot();
	void bracketDataSlot();
	void screenShot();
	void allScreenShots();
	private:
	QTimer *timer;
	void updateUiTimeEdit(long l_ms);
	void checkUserDirs(void);


	private slots:
	void plotterLegendClick(QCPLegend *l, QCPAbstractLegendItem *ai, QMouseEvent *me);
	void onMouseDuobleClick(QMouseEvent *event);
	void showPointToolTip(QMouseEvent *event);

	void legendDoubleClick(QCPLegend *legend, QCPAbstractLegendItem *item);

	void MyTimerSlot();

	void on_pushButtonZoomRange_clicked();

	void on_dial_valueChanged(int Msec);

	void on_pushButtonZoomPiu_clicked();

	void on_pushButtonZoomMeno_clicked();

	void on_LoadFile_clicked();

	void on_SaveButton_clicked();

	void on_PulisciButton_clicked();

	void on_pushButtonProcess_clicked();

	void on_save();

	void on_LoadFile();

	void on_UpgradePlot();

	void on_pushButtonZoomLeft_clicked();

	void on_pushButtonZoomRight_clicked();

	void on_pushButtonDiretta_clicked();

	void on_timeEdit_timeChanged(const QTime &time);

	void on_pbScreenShot_clicked();

	void on_timeEdit_editingFinished();

	void on_timeEdit_2_timeChanged(const QTime &time);

	void on_timeEdit_3_timeChanged(const QTime &time);

	void on_pbnDoseAnalysis_clicked();

	private:
	Ui::MainWindow *ui;
	QString demoName;
	QTimer dataTimer;
	QCPItemTracer *itemDemoPhaseTracer;
	int currentDemoIndex;
	double *y1;
	QString strFileNameOut;
	QString strFileNameIn;
	QString strFileNameExtractLog;
	bool TimerFlag = false;
	bool customPlotVariable = true;
	double dLastTimeVal; // last value of Time
	unsigned long ulTimeStart; // starting time [ms]
	unsigned long ulTimeStop; // ending time [ms]
	double dTimeA;
	double dTimeB;
};

#endif // MAINWINDOW_H
