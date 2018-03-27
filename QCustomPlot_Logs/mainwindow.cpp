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

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QDesktopWidget>
#include <QScreen>
#include <QMessageBox>
#include <QMetaEnum>
#include <QApplication>
#include "crunchlog.h"




MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	setGeometry(400, 250, 542, 390);
	timer = new QTimer(this);
	// setup signal and slot
	connect(timer, SIGNAL(timeout()), this, SLOT(MyTimerSlot()));
	timer->start(1000);    // msec
}



void MainWindow::setupDemo(int demoIndex)
{
	switch (demoIndex)
	{
	case 20: setupLineStyleFabioDemo(ui->customPlot); break;
	}
	setWindowTitle("QCustomPlot: "+demoName);
	statusBar()->clearMessage();
	currentDemoIndex = demoIndex;

	ui->customPlot->replot();
}



void MainWindow::realtimeDataSlot()
{
	static QTime time(QTime::currentTime());
	// calculate two new data points:
	double key = time.elapsed()/1000.0; // time elapsed since start of demo, in seconds
	static double lastPointKey = 0;
	if (key-lastPointKey > 0.002) // at most add point every 2 ms
	{
		// add data to lines:
		ui->customPlot->graph(0)->addData(key, qSin(key)+qrand()/(double)RAND_MAX*1*qSin(key/0.3843));
		ui->customPlot->graph(1)->addData(key, qCos(key)+qrand()/(double)RAND_MAX*0.5*qSin(key/0.4364));
		// rescale value (vertical) axis to fit the current data:
		//ui->customPlot->graph(0)->rescaleValueAxis();
		//ui->customPlot->graph(1)->rescaleValueAxis(true);
		lastPointKey = key;
	}
	// make key axis range scroll with the data (at a constant range size of 8):
	ui->customPlot->xAxis->setRange(key, 8, Qt::AlignRight);
	ui->customPlot->replot();

	// calculate frames per second:
	static double lastFpsKey;
	static int frameCount;
	++frameCount;
	if (key-lastFpsKey > 2) // average fps over 2 seconds
	{
		ui->statusBar->showMessage(
					QString("%1 FPS, Total Data points: %2")
					.arg(frameCount/(key-lastFpsKey), 0, 'f', 0)
					.arg(ui->customPlot->graph(0)->data()->size()+ui->customPlot->graph(1)->data()->size())
					, 0);
		lastFpsKey = key;
		frameCount = 0;
	}
}

void MainWindow::bracketDataSlot()
{
	double secs = QCPAxisTickerDateTime::dateTimeToKey(QDateTime::currentDateTime());

	// update data to make phase move:
	int n = 500;
	double phase = secs*5;
	double k = 3;
	QVector<double> x(n), y(n);
	for (int i=0; i<n; ++i)
	{
		x[i] = i/(double)(n-1)*34 - 17;
		y[i] = qExp(-x[i]*x[i]/20.0)*qSin(k*x[i]+phase);
	}
	ui->customPlot->graph()->setData(x, y);

	itemDemoPhaseTracer->setGraphKey((8*M_PI+fmod(M_PI*1.5-phase, 6*M_PI))/k);

	ui->customPlot->replot();

	// calculate frames per second:
	double key = secs;
	static double lastFpsKey;
	static int frameCount;
	++frameCount;
	if (key-lastFpsKey > 2) // average fps over 2 seconds
	{
		ui->statusBar->showMessage(
					QString("%1 FPS, Total Data points: %2")
					.arg(frameCount/(key-lastFpsKey), 0, 'f', 0)
					.arg(ui->customPlot->graph(0)->data()->size())
					, 0);
		lastFpsKey = key;
		frameCount = 0;
	}
}

void MainWindow::setupPlayground(QCustomPlot *customPlot)
{
	Q_UNUSED(customPlot)
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::screenShot()
{
#if QT_VERSION < QT_VERSION_CHECK(5, 0, 0)
	QPixmap pm = QPixmap::grabWindow(qApp->desktop()->winId(), this->x()+2, this->y()+2, this->frameGeometry().width()-4, this->frameGeometry().height()-4);
#elif QT_VERSION < QT_VERSION_CHECK(5, 5, 0)
	QPixmap pm = qApp->primaryScreen()->grabWindow(qApp->desktop()->winId(), this->x()+2, this->y()+2, this->frameGeometry().width()-4, this->frameGeometry().height()-4);
#else
	QPixmap pm = qApp->primaryScreen()->grabWindow(qApp->desktop()->winId(), this->x()-7, this->y()-7, this->frameGeometry().width()+14, this->frameGeometry().height()+14);
#endif
	QString fileName = demoName.toLower()+".png";
	fileName.replace(" ", "");
	pm.save("./screenshots/"+fileName);
	qApp->quit();
}

void MainWindow::allScreenShots()
{
#if QT_VERSION < QT_VERSION_CHECK(5, 0, 0)
	QPixmap pm = QPixmap::grabWindow(qApp->desktop()->winId(), this->x()+2, this->y()+2, this->frameGeometry().width()-4, this->frameGeometry().height()-4);
#elif QT_VERSION < QT_VERSION_CHECK(5, 5, 0)
	QPixmap pm = qApp->primaryScreen()->grabWindow(qApp->desktop()->winId(), this->x()+2, this->y()+2, this->frameGeometry().width()-4, this->frameGeometry().height()-4);
#else
	QPixmap pm = qApp->primaryScreen()->grabWindow(qApp->desktop()->winId(), this->x()-7, this->y()-7, this->frameGeometry().width()+14, this->frameGeometry().height()+14);
#endif
	QString fileName = demoName.toLower()+".png";
	fileName.replace(" ", "");
	pm.save("./screenshots/"+fileName);

	if (currentDemoIndex < 19)
	{
		if (dataTimer.isActive())
			dataTimer.stop();
		dataTimer.disconnect();
		delete ui->customPlot;
		ui->customPlot = new QCustomPlot(ui->centralWidget);

		setupDemo(currentDemoIndex+1);
		// setup delay for demos that need time to develop proper look:
		int delay = 250;
		if (currentDemoIndex == 10) // Next is Realtime data demo
			delay = 12000;
		else if (currentDemoIndex == 15) // Next is Item demo
			delay = 5000;
		QTimer::singleShot(delay, this, SLOT(allScreenShots()));
	} else
	{
		qApp->quit();
	}
}


//------------------------------------------------------------------------------------------------
// color table " colorcube "
uint8_t u8aColR[64]={ 85, 85, 85, 170, 170, 170, 255, 255, 255, 0, 0, 0, 85, 85, 85, 85, 170, 170, 170, 170, 255, 255, 255, 255, 0, 0, 0, 85, 85, 85, 85, 170, 170, 170, 170, 255, 255, 255, 42, 85, 127, 170, 212, 255, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 36, 72, 109, 145, 182, 218, 255, };
uint8_t u8aColG[64]={ 85, 170, 255, 85, 170, 255, 85, 170, 255, 85, 170, 255, 0, 85, 170, 255, 0, 85, 170, 255, 0, 85, 170, 255, 85, 170, 255, 0, 85, 170, 255, 0, 85, 170, 255, 0, 85, 170, 0, 0, 0, 0, 0, 0, 42, 85, 127, 170, 212, 255, 0, 0, 0, 0, 0, 0, 0, 36, 72, 109, 145, 182, 218, 255, };
uint8_t u8aColB[64]={ 0, 0, 0, 0, 0, 0, 0, 0, 0, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 42, 85, 127, 170, 212, 255, 0, 36, 72, 109, 145, 182, 218, 255, };


void MainWindow::setupLineStyleFabioDemo(QCustomPlot *customPlot)
{


	/* QString selFilter="Text files(*.txt)";
	QString LoadFile;
	LoadFile = QFileDialog::getOpenFileName(this,"Open Full Log",
											QDir::currentPath(),
											"Text files(*.txt)",
											&selFilter);
	*/
	QFile file(strFileNameOut);
	if (!file.open(QFile::ReadOnly | QFile::Text)) {
		QMessageBox::warning(this,"op","file not open");
		//return

	}

	//  .  .  .  .  .  .  .  .  .  .  .  .

	customPlot->legend->setVisible(true);
	customPlot->legend->setFont(QFont("Helvetica", 9));
	customPlot->plotLayout()->setColumnStretchFactor (1, 1.1);
	//customPlot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::RightButton);
	//  .  .  .  .  .  .  .  .  .  .  .  .

#define ARRAY_DIM 100000
	QTextStream in(&file);
	QVector<double>
			qvTime(ARRAY_DIM), // time array
			qvIoRaw(ARRAY_DIM*21); // I/O data
	QVector <QVector <int> > qvMyVect;


	unsigned long ulDataLen; // legnth of "photograms" to draw
	for (ulDataLen=0; ulDataLen<ARRAY_DIM; ulDataLen++)
	{
		QString line = in.readLine(); //read one line at a time
		if (line.isEmpty()) {
			break; // if here means "reached end of file"
		}
		QTextStream myteststream(&line); // cast line into textStream (easier to process)
		// int *y1;
		// unroll each line into current Time array and into current
		myteststream >>
				qvTime[ulDataLen] >>
				qvIoRaw[ulDataLen+ARRAY_DIM*	1	]  >>
				qvIoRaw[ulDataLen+ARRAY_DIM*	2	]  >>
				qvIoRaw[ulDataLen+ARRAY_DIM*	3	]  >>
				qvIoRaw[ulDataLen+ARRAY_DIM*	4	]  >>
				qvIoRaw[ulDataLen+ARRAY_DIM*	5	]  >>
				qvIoRaw[ulDataLen+ARRAY_DIM*	6	]  >>
				qvIoRaw[ulDataLen+ARRAY_DIM*	7	]  >>
				qvIoRaw[ulDataLen+ARRAY_DIM*	8	]  >>
				qvIoRaw[ulDataLen+ARRAY_DIM*	9	]  >>
				qvIoRaw[ulDataLen+ARRAY_DIM*	10	]  >>
				qvIoRaw[ulDataLen+ARRAY_DIM*	11	]  >>
				qvIoRaw[ulDataLen+ARRAY_DIM*	12	]  >>
				qvIoRaw[ulDataLen+ARRAY_DIM*	13	]  >>
				qvIoRaw[ulDataLen+ARRAY_DIM*	14	]  >>
				qvIoRaw[ulDataLen+ARRAY_DIM*	15	]  >>
				qvIoRaw[ulDataLen+ARRAY_DIM*	16	]  >>
				qvIoRaw[ulDataLen+ARRAY_DIM*	17	]  >>
				qvIoRaw[ulDataLen+ARRAY_DIM*	18	]  >>
				qvIoRaw[ulDataLen+ARRAY_DIM*	19	]  >>
				qvIoRaw[ulDataLen+ARRAY_DIM*	20	]  ;
		UltimoValore = qvTime[ulDataLen];
		//  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .
		QVector<int> tempVector;
		foreach( QString numStr, line.split(" ", QString::SkipEmptyParts) )
		{
			bool bCheck = false; // flag to signalize double value found
			double dVal = numStr.toDouble(&bCheck);
			if( !bCheck ){
				continue;
			}
			else {
				tempVector.push_back(dVal);
			}
		}
		qvMyVect.push_back(tempVector);
		//  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .

	}
	double dX0 =  0 ;
	y1 = &dX0;

	for (uint32_t jj=0; jj<ulDataLen; jj++)
	{
		qvTime[jj] = qvTime[jj] - dX0;
	}

	QVector<double> qvDataArranged(ARRAY_DIM); // data vertically shifted

	//  buildLegend() { =========================================
	QVector<QString> LegendList;
	LegendList<< "I PID SDCAL STP     "
			  << "I PID APPOPEN       "
			  << "I PID READY         "
			  << "I PID PULSE MODE    "
			  << "O PID HCF MODE      "
			  << "I GEN REQ FL HCF    "
			  << "I GEN PREP RAD      "
			  << "I GEN COM REQ       "
			  << "I GEN READY         "
			  << "I GEN REQ RAD       "
			  << "O PID CFL           "
			  << "O PREP PID          "
			  << "O CRAD PID          "
			  << "I PID EXP RX        "
			  << "O PID DOSE ADJ      "
			  << "O GEN READY ACQ FL  "
			  << "O READY ACQ RAD HCF "
			  << "I GEN EXON          "
			  << "O PID EXON          "
			  << "STATUS              "
			  << "ADC CM10            "
			  << "DAC ABS             ";
	//  } .=========================================
	for (int iGIndex=0; iGIndex<20; iGIndex++)
	{
		//  } .=========================================

		for (int jj=0; jj<ARRAY_DIM; jj++)
		{
			qvDataArranged[jj] = qvIoRaw[jj + ARRAY_DIM*iGIndex]*0.5 + (20-iGIndex) ;
		}
		// create graph and assign data to it:

		customPlot->addGraph();
		QPen pen;
		pen.setColor(QColor(u8aColR[iGIndex], u8aColG[iGIndex], u8aColB[iGIndex]));
		customPlot->graph()->setPen(pen);

		//customPlot->graph()->setName(QString::number(iGIndex + 1) + " grafico");
		QString qStr1 = LegendList.at(iGIndex);
		customPlot->graph()->setName(qStr1);
		customPlot->graph(iGIndex)->setData(qvTime, qvDataArranged);
		//  } .=========================================
	}
	// give the axes some labels:
	customPlot->xAxis->setLabel("x");
	customPlot->yAxis->setLabel("y");
	// set axes ranges, so we see all data:
	double min = *std::min_element(qvTime.constBegin(), qvTime.constEnd());
	double max = *std::max_element(qvTime.constBegin(), qvTime.constEnd());

	ui->lineEditMin->setText(QString::number(qvTime[0]));
	ui->lineEditInterval->setText(QString::number(max-min));
	customPlot->xAxis->setRange(min-1,max+1);
	max = *std::max_element(qvDataArranged.constBegin(), qvDataArranged.constEnd());
	customPlot->yAxis->setRange(-1, 21-max);


	// connect some interaction slots:
	customPlot->setInteractions(QCP::iSelectLegend);
	connect(ui->customPlot,
			SIGNAL(legendClick(QCPLegend*,
							   QCPAbstractLegendItem*,
							   QMouseEvent*)),
			this,
			SLOT(plotterLegendClick(QCPLegend*,QCPAbstractLegendItem*,QMouseEvent*)));



}

void MainWindow::plotterLegendClick(QCPLegend *l, QCPAbstractLegendItem *ai, QMouseEvent *me)
{
	Q_UNUSED(me);

	if(NULL != l && NULL != ai)
	{
		// Check for selection
		for(int i=0; i<l->parentPlot()->graphCount(); i++)
		{
			QPen qpGraphPen = l->parentPlot()->graph(i)->pen ();
			if("QCPPlottableLegendItem" == QString(ai->metaObject()->className()))
			{
				ui->statusBar->showMessage("Selected Graph: \"" + l->parentPlot()->graph(i)->name() + "\"");
				qpGraphPen.setStyle(Qt::SolidLine);
			}
			else
			{
				qpGraphPen.setStyle(Qt::DotLine);
			}
			l->parentPlot()->graph(i)->setPen(qpGraphPen);
		}
	}
}

//  on_pushButtonProcedi_clicked(ui->customPlot);

// FUNZIONE PROVA
/* void MainWindow::on_pushButton_2_clicked(QCustomPlot *customPlot, int xMin, int xMax)
	{

		int minFinale = ui->lineEditMin->text().toInt();
		int maxFinale = ui->lineEditMax->text().toInt();
		if(minFinale==NULL && maxFinale ==NULL){
			QMessageBox::warning(this,"","non hai inserito nulla!!");

		}
		if(minFinale==NULL && maxFinale!=NULL){
			QMessageBox::warning(this,"","inserire il range inferiore!");

		}
		if(minFinale!=NULL && maxFinale==NULL){
			QMessageBox::warning(this,"alt","inserire il range superiore!");

		}
		if (minFinale < xMin-1 || maxFinale > xMax+1) {
			QMessageBox::warning(this,"attenzione","range non corretti");

		}
		else {
			&customPlot->xAxis->setRange(minFinale, maxFinale );
	}
   }

*/



//}

//    //on_pushButtonProcedi_clicked(ui->customPlot, max-1, min-1, QFile &file(LoadFile));
//    /*
//    demoName = "Line Style Demo";
//    ///    QFile load fabioRules.txt
//    /// copia da altri prog e leggi una riga alla volta
//    /// usando scanf() trasforma il testo della riga in numeri
//    /// il primo numero che trovi è il tempo ed è uguale per tutti i grafi
//    /// il secondo numero della riga è uno 0 o 1: va messo nelle ordinate
//    /// dichiara t e y della dimensione delle righe del testo
//    QString selFilter="Text files(*.txt)";
//    QString LoadFile;
//    LoadFile = QFileDialog::getOpenFileName(this,"Open Full Log",
//                                            QDir::currentPath(),
//                                            "Text files(*.txt)",
//                                            &selFilter);

//    QFile file(LoadFile);
//    if (!file.open(QFile::ReadOnly | QFile::Text)) {
//        QMessageBox::warning(this,"op","file not open");
//        return;
//    }

//    QTextStream in(&file);
//    QVector<double> vetT(40), vetY0(40), vetY1(40);
//    //while (!in.atEnd())
//    for (int ii=0; ii<40; ii++)
//    {
//        QString line = in.readLine(); //read one line at a time
//        QTextStream myteststream(&line);
//        //int t = 0, y0 = 0;
//        myteststream >>
//                vetT[ii] >>
//                vetY0[ii] >>
//                vetY1[ii];

//    }
//    file.close();



//    customPlot->legend->setVisible(true);
//    customPlot->legend->setFont(QFont("Helvetica", 9));
//    customPlot->addGraph();
//    //customPlot->graph()->setData(vetT, vetY1);


//    customPlot->xAxis->setRange(52684367, 53155512);
//    customPlot->yAxis->setRange(-2, 5);
//    customPlot->graph(0)->setData(vetT, vetY1);
//    //QPen pen;

//    QStringList lineNames;
//    lineNames << "lsLine";
//    // << "lsLine" << "lsStepLeft" << "lsStepRight" << "lsStepCenter" << "lsImpulse";
//    // add graphs with different line styles:
//    for (int i=1; i<2; i++)
//    {
//        customPlot->addGraph();
//        pen.setColor(QColor(0,0,0));
//        customPlot->graph()->setPen(pen);
//       // customPlot->graph()->setName(lineNames.at(QCPGraph::lsLine));

//      // customPlot->graph()->setLineStyle((QCPGraph::lsLine));
//       // customPlot->graph()->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 5));
//        // generate data:
////        QVector<double> x(15), y(15);
////        for (int j=0; j<15; ++j)
////        {
////            x[j] = j/15.0 * 5*3.14 + 0.01;
////            y[j] = 7*qSin(x[j])/x[j] - (i-QCPGraph::lsNone)*5 + (QCPGraph::lsImpulse)*5 + 2;
////        }

//        customPlot->graph()->setData(vetT, vetY1);
//     //   customPlot->graph()->rescaleAxes(true);
//    }
//    // zoom out a bit:
//    customPlot->yAxis->scaleRange(1.1, customPlot->yAxis->range().center());
//    //customPlot->xAxis->scaleRange(1.1000000000, customPlot->xAxis->range().center());
//    customPlot->xAxis->setRangeLower(52684367);
//    customPlot->xAxis->setRangeUpper(53155512);
//    // set blank axis lines:
//    customPlot->xAxis->setTicks(true);
//    customPlot->yAxis->setTicks(true);
//    customPlot->xAxis->setTickLabels(true);
//    customPlot->yAxis->setTickLabels(true);
//    // make top right axes clones of bottom left axes:
//   // customPlot->axisRect()->setupFullAxesBox();
//   */



//------------------------------------------------------------------------------------------------
void MainWindow::MyTimerSlot()
{
	//    Qui entriamo ogni 500ms
	if(TimerFlag == true)
	{
		QTime time = QTime::currentTime();
		QString time_text = time.toString("hh : mm : ss");
		if ((time.second() % 2) == 0) {
			time_text[3]== ' ';
			time_text[8]== ' ';
		}

		ui->label_time->setText(time_text);
		on_LoadFile();
		on_save();
		//double minFinale = ui->lineEditMin->text().toDouble() ;
		//double interval = ui->lineEditInterval->text().toDouble();
		customPlotVariable = false;
		on_pushButtonProcess_clicked();
		ui->lineEditMin->setText(QString::number(UltimoValore-2000));
		ui->lineEditInterval->setText(QString::number(2000));

		on_UpgradePlot();

	}

}



void MainWindow::on_UpgradePlot()
{
	if(   //  ui->lineEditMin->text().isEmpty()    ||
		  ui->lineEditInterval->text().isEmpty()   ){
		QMessageBox::warning(this,"","insert interval!!!");
	}
	else
	{

		double minFinale = ui->lineEditMin->text().toDouble() ;
		double interval = ui->lineEditInterval->text().toDouble();
		// ui->lineEditMin->setMaxLength(minFinale);

		if(minFinale<=0){
			QMessageBox::warning(this,"alt","insert superior extreme");

		}
		if (interval<=0) {
			QMessageBox::warning(this,"alt","insert correct interval");

		}
		//        if (minFinale < min1-1 || maxFinale > max1+1) {
		//            QMessageBox::warning(this,"attenzione","range non corretti");
		//        }

		ui->customPlot->xAxis->setRange(minFinale, minFinale+interval);


		ui->customPlot->replot();
	}
	//ui->hsInfInterval->setValue(0);
	//ui->hsSupInterval->setValue(100);





}
//------------------------------------------------------------------------------------------------

void MainWindow::on_pushButtonZoomRange_clicked()
{
	on_UpgradePlot();

}

//------------------------------------------------------------------------------------------------


void MainWindow::on_dial_valueChanged(int Msec)
{
	ui->lcdNumber->display(Msec);

	double dRangeX0 = ui->lineEditMin->text().toDouble();
	double dInterval = ui->lineEditInterval->text().toDouble();
	double dRangeX1 = dRangeX0 + dInterval;

	double dDelta = Msec*(dInterval)/200;
	dRangeX0 += dDelta;
	dRangeX1 += dDelta;
	ui->customPlot->xAxis->setRange(dRangeX0,dRangeX1);
	ui->customPlot->replot();
	//    ui->lineEditInterval->setText(QString::number(rangeX1-rangeX0));
	//    ui->lineEditMin->setText(QString::number(rangeX0)); Ba
}

//------------------------------------------------------------------------------------------------

void MainWindow::on_pushButtonZoom_clicked()
{
	ui->dial->setValue(0);
	if (ui->lineEditMin->text().toDouble() <= 0 || ui->lineEditInterval->text().toDouble()<= 0)
	{
		QMessageBox::warning(this, "attenzione", "inserisci il limite inferiore e l'intervallo!!");
		ui->hsInfInterval->setValue(0);
		ui->hsSupInterval->setValue(100);

	}else
	{
		int numInf = ui->hsInfInterval->value();
		int numSup = ui->hsSupInterval->value();
		if (numInf>=numSup){
			QMessageBox::warning(this,"attenazione","Imposta bene i range!");
			return;
		}
		if (numInf!=0 || numSup!=100)
		{
			double rangeX0 = ui->lineEditMin->text().toDouble();
			double interval=ui->lineEditInterval->text().toDouble();
			//int rangeX1 = rangeX0 + interval;
			//int rangeX1 = rangeX0 + interval;

			double rangeX0final = rangeX0 + ((interval*numInf)*0.01);
			double rangeX1final = rangeX0 + ((interval*numSup)*0.01);
			double newInterval = rangeX1final - rangeX0final;
			ui->lineEditInterval->setText(QString::number(newInterval));
			ui->lineEditMin->setText(QString::number(rangeX0final));

			//ui->customPlot->xAxis->setRange(rangeX0final, (rangeX0final+newInterval));
			// ui->customPlot->replot();
			on_UpgradePlot();
			ui->hsInfInterval->setValue(0);
			ui->hsSupInterval->setValue(100);

		}
	}

}
//------------------------------------------------------------------------------------------------
int MainWindow::on_hsInfInterval_valueChanged()
{
	int numInf = ui->hsInfInterval->value();
	return numInf;
}
//------------------------------------------------------------------------------------------------
int MainWindow::on_hsSupInterval_valueChanged()
{
	int numSup = ui->hsSupInterval->value();
	return numSup;
}
//------------------------------------------------------------------------------------------------
void MainWindow::on_pushButtonZoomPiu_clicked()

{
	double rangeX0 = ui->lineEditMin->text().toDouble();
	double interval = ui->lineEditInterval->text().toDouble();
	double newInterval = interval*0.2;
	double newRangeX0 = rangeX0 + newInterval;
	ui->lineEditMin->setText(QString::number(newRangeX0, 'd', 3));

	double finalInterval = interval - 2*newInterval;
	ui->lineEditInterval->setText(QString::number(finalInterval, 'd', 3));

	// double newRangeX1 = newRangeX0 + finalInterval;



	// ui->customPlot->xAxis->setRange(newRangeX0, newRangeX1 );
	// ui->customPlot->replot();
	on_UpgradePlot();
	ui->dial->setValue(0);
}
//------------------------------------------------------------------------------------------------
void MainWindow::on_pushButtonZoomMeno_clicked()
{
	double rangeX0 = ui->lineEditMin->text().toDouble();
	double interval = ui->lineEditInterval->text().toDouble();
	double newInterval = interval*0.2;
	double newRangeX0 = rangeX0 - newInterval;
	ui->lineEditMin->setText(QString::number(newRangeX0, 'd', 3));

	double finalInterval = interval + 2*newInterval;
	ui->lineEditInterval->setText(QString::number(finalInterval, 'd', 3));

	//double newRangeX1 = newRangeX0 + finalInterval;

	// ui->customPlot->xAxis->setRange(newRangeX0, newRangeX1 );
	// ui->customPlot->replot();
	on_UpgradePlot();
	ui->dial->setValue(0);
}

//------------------------------------------------------------------------------------------------
void MainWindow::on_LoadFile_clicked()
{
	QString selFilter="Text files (*.txt)";
	strFileNameIn.clear();
	strFileNameIn = QFileDialog::getOpenFileName(this,
												 "Open Full Log",
												 QDir::currentPath(),
												 "Text files (*.txt);;All files (*.*)",
												 &selFilter);
	on_LoadFile();
}
//-------------------------------------------------------------------------------------------------
void MainWindow::on_LoadFile()
{

	QFile file(strFileNameIn);
	if (!file.open(QFile::ReadOnly | QFile::Text)) {
		QMessageBox::warning(this,"op","file not open");
		return;
	}
	QTextStream in(&file);
	QString text = in.read(1000);
	text.append("\r\n [...]");
	ui->textEdit->setText(text);
	//ui->qlFileName->setText("NOME FILE SCELTO:" + strFileNameIn );
	QFileInfo fi=strFileNameIn;
	QString str = fi.fileName();
	QString path= fi.baseName();
	ui->qlFileName->setText("Input File: " + path);

}
//------------------------------------------------------------------------------------------------
/**
 * @brief save the new file in the .txt format
 */

void MainWindow::on_SaveButton_clicked()
{
	QString selFilter="Text files (*.txt)";
	strFileNameOut.clear();
//	strFileNameOut = QFileDialog::getSaveFileName(this,
//												  "Choose Output filename",
//												  QDir::currentPath()+"/out.txt",
//												  "Text files (*.txt);;All files (*.*)",
//												  &selFilter);
	strFileNameOut = QDir::currentPath()+"/out.txt";
	on_save();
}

void MainWindow::on_save()
{
	if (strFileNameOut.size() > 0)
	{
		QFile file(strFileNameOut);

		if (!file.open(QFile::WriteOnly | QFile::Text)) {
			QMessageBox::warning(this,"op","file not open");
			return;
		}

		file.flush();
		file.close();
		ui->pushButtonProcess->setEnabled(true);
		QFileInfo fi=strFileNameOut;
		QString str = fi.fileName();
		QString path= fi.baseName();
		ui->SaveLabel->setText("Processed File: " + path);
	}
	else{
		ui->pushButtonProcess->setEnabled(false);
		// -qmesage box
	}
}

//------------------------------------------------------------------------------------------------------------
/**
 * @brief this button clean all the Text Edit
 */
void MainWindow::on_PulisciButton_clicked()
{
	ui->textEdit->setText("");
	ui->qlTestoFinito->setText("");
	ui->FinishTextEdit->setPlainText("");
}

//------------------------------------------------------------------------------------------------
/**
 * @brief filter the text in input and provide the lines of interest, where at every number of time link a sequence of binary number
 */

void MainWindow::on_pushButtonProcess_clicked()
{

	CrunchLog crunchLog;
	char caDummy[256] = {0,};
	char caOutfile[256] = {0,};
	memcpy(caDummy, strFileNameIn.toStdString().c_str() ,sizeof(caDummy));
	memcpy(caOutfile, strFileNameOut.toStdString().c_str() ,sizeof(caOutfile));
	crunchLog.processFile(caDummy, caOutfile);
	QFile file (strFileNameOut);
	if (!file.open(QFile::ReadOnly | QFile::Text)) {
		QMessageBox::warning(this,"op","Cannot open file");
		return;
	}


	//  QTextStream out(&file);
	//  QString text = ui->textEdit->toPlainText();
	//  out<<text;
	QString contents = file.readAll().constData();
	ui->FinishTextEdit->setPlainText(contents);

	file.close();
	ui->qlTestoFinito->setText("filter text");
	//ui->customPlot->replot();
	setupLineStyleFabioDemo(ui->customPlot);
	if (customPlotVariable==true){
		ui->customPlot->replot();
		ui->hsInfInterval->setValue(0);
		ui->hsSupInterval->setValue(100);
	}


}

void MainWindow::on_pushButtonZoomLeft_clicked()
{
	double rangeX0 = ui->lineEditMin->text().toDouble();
	double interval = ui->lineEditInterval->text().toDouble();

	double delta = (interval)/10;
	rangeX0 -= delta;
	interval -= delta;
	ui->lineEditMin->setText(QString::number(rangeX0));
	ui->lineEditInterval->setText(QString::number(interval));

	ui->customPlot->xAxis->setRange(rangeX0,rangeX0+interval);
	ui->customPlot->replot();

}

//----------------------------------------------------------------------------

void MainWindow::on_pushButtonZoomRight_clicked()
{
	double rangeX0 = ui->lineEditMin->text().toDouble();
	double interval = ui->lineEditInterval->text().toDouble();

	double delta = (interval)/10;
	rangeX0 += delta;
	interval += delta;
	ui->lineEditMin->setText(QString::number(rangeX0));
	ui->lineEditInterval->setText(QString::number(interval));

	ui->customPlot->xAxis->setRange(rangeX0,rangeX0+interval);
	ui->customPlot->replot();
}

//--------------------------------------------------------------------------

void MainWindow::on_pushButtonDiretta_clicked()
{
	if (TimerFlag == true)
	{
		// set button text
		TimerFlag = false;
	}
	else{
		//        set other buuton text
		TimerFlag = true;
	}
}

void MainWindow::on_timeEdit_timeChanged(const QTime &time)
{
	int hour = time.hour();
	int min =  time.minute();
	int sec =  time.second();

	int sommaMsec = (hour*60*60) + (min*60) + (sec) ;

	ui->lineEditMin->setText(QString::number(sommaMsec*1000));
}
