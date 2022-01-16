
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDesktopWidget>
#include <QScreen>
#include <QMessageBox>
#include <QMetaEnum>
#include <QApplication>
#include <QFileDialog>
#include <QShortcut>
#include "CrunchLog.h"
#include "CDecorator.h"
#include <iostream>
#include "ISettings.h"
#include "ITimePerform.h"
#include "figurewidget.h"
//-----------------------------------------------------------------------------

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
	ulTimeStart = 0;
	ulTimeStop = ( 23*3600 + 59*60 )* 1000;
	qDebug()<<"Setup";
	ui->pushButtonProcess->setEnabled(true);
    setShortCutKeys();

//    QMetaEnum e = QMetaEnum::fromType<CrunchLogC_Arm::enumIdCAN>();
//    qDebug() << "test" << e.valueToKey(CrunchLogC_Arm::ID_CAN_CONTR);
//    for (int k = 0; k < e.keyCount(); k++)
//    {
//      CrunchLogC_Arm::enumIdCAN id = (CrunchLogC_Arm::enumIdCAN) e.value(k);
//      QListWidgetItem *listWidgetItem = new QListWidgetItem(ui->lswIDs);
//      listWidgetItem->setText(QString().sprintf("0x%X", (int)id));
//      ui->lswIDs->addItem (listWidgetItem);
//    }
    QListWidgetItem *listWidgetItem = new QListWidgetItem(ui->lswIDs);
    listWidgetItem->setText(QString().sprintf("0x%X", (int)CrunchMsg::ID_CAN_ARCO_CONTR));
    listWidgetItem->setCheckState(Qt::Unchecked);
    ui->lswIDs->addItem (listWidgetItem);
    QListWidgetItem *listWidgetItem1 = new QListWidgetItem(ui->lswIDs);
    listWidgetItem1->setText(QString().sprintf("0x%X", (int)CrunchMsg::ID_CAN_ARCO_INV_A));
    listWidgetItem1->setCheckState(Qt::Unchecked);
    ui->lswIDs->addItem (listWidgetItem1);
    QListWidgetItem *listWidgetItem2 = new QListWidgetItem(ui->lswIDs);
    listWidgetItem2->setText(QString().sprintf("0x%X", (int)CrunchMsg::ID_CAN_ARCO_INV_B));
    listWidgetItem2->setCheckState(Qt::Unchecked);
    ui->lswIDs->addItem (listWidgetItem2);
}


//-----------------------------------------------------------------------------

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
    //ui->customPlot->graph()->setData(x, y);

	itemDemoPhaseTracer->setGraphKey((8*M_PI+fmod(M_PI*1.5-phase, 6*M_PI))/k);

    //ui->customPlot->replot();

	// calculate frames per second:
	double key = secs;
	static double lastFpsKey;
	static int frameCount;
	++frameCount;
	if (key-lastFpsKey > 2) // average fps over 2 seconds
	{
		lastFpsKey = key;
		frameCount = 0;
	}
}
//-----------------------------------------------------------------------------

void MainWindow::setupPlayground(QCustomPlot *customPlot)
{
	Q_UNUSED(customPlot)
}
//-----------------------------------------------------------------------------

MainWindow::~MainWindow()
{
	delete ui;
}

//------------------------------------------------------------------------------
/**
 * @brief set the Gui up to process and display result
 */
void MainWindow::setShortCutKeys()
{
	QShortcut *shortcut = new QShortcut(QKeySequence("Ctrl+S"),this);
	connect(shortcut,
			SIGNAL(activated()),
			this,
			SLOT(on_pbScreenShot_clicked()));
	QShortcut *shortcut2 = new QShortcut(QKeySequence(Qt::Key_Right),this);
	connect(shortcut2,
			SIGNAL(activated()),
			this,
			SLOT(on_pushButtonZoomRight_clicked()));
	QShortcut *shortcut3 = new QShortcut(QKeySequence(Qt::Key_Left),this);
	connect(shortcut3,
			SIGNAL(activated()),
			this,
			SLOT(on_pushButtonZoomLeft_clicked()));
	QShortcut *shortcut4 = new QShortcut(QKeySequence(Qt::Key_Up),this);
	connect(shortcut4,
			SIGNAL(activated()),
			this,
			SLOT(on_pushButtonZoomPiu_clicked()));
	QShortcut *shortcut5 = new QShortcut(QKeySequence(Qt::Key_Down),this);
	connect(shortcut5,
			SIGNAL(activated()),
			this,
			SLOT(on_pushButtonZoomMeno_clicked()));
}

void MainWindow::setupPlotLogs(FigureWidget *figure)
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
		return;
	}
	/// Alcohol may be man's worst enemy, but the bible says love your enemy.

    cDecorator.buildGraph(figure->customPlot(), figure->lswLegend(), &file);

    double dMinXAxis = figure->customPlot()->xAxis->range().lower;
    double dMaxXAxis = figure->customPlot()->xAxis->range().upper;
    dLastTimeVal = dMaxXAxis; // used for "OnAir option"

    ui->lineEditMin->setText(QString::number(dMinXAxis));
    ui->lineEditInterval->setText(QString::number(dMaxXAxis-dMinXAxis));
//	disconnect(ui->customPlot,
//			   SIGNAL(legendClick(QCPLegend*, QCPAbstractLegendItem*, QMouseEvent*)));

	// connect some interaction slots:
//	connect(ui->customPlot,
//			SIGNAL(legendClick(QCPLegend*, QCPAbstractLegendItem*, QMouseEvent*)),
//			this,
//			SLOT(plotterLegendClick(QCPLegend*,QCPAbstractLegendItem*,QMouseEvent*)));

    connect(figure->customPlot(),
            SIGNAL(legendDoubleClick(QCPLegend*,QCPAbstractLegendItem*,QMouseEvent*)),
            this,
            SLOT(legendDoubleClick(QCPLegend*,QCPAbstractLegendItem*)));
    // tooltip on mouse hover
    connect(figure->customPlot(),
            SIGNAL(mouseMove(QMouseEvent*)),
            this,
            SLOT(showPointToolTip(QMouseEvent*)));
    //	new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_S), this, SLOT(screenShot()));
    connect(figure->customPlot(),
            SIGNAL(mouseDoubleClick(QMouseEvent*)),
            this,
            SLOT(onMouseDuobleClick(QMouseEvent*)));
}
//-----------------------------------------------------------------------------
/**
 * @brief plotterLegendClick - Slot signal Once I clicked on Legend
 * @param l  	ptr to legend
 * @param ai	Legend Item ptr
 * @param me	Mouse event to capture
 */
void MainWindow::plotterLegendClick(QCPLegend *l, QCPAbstractLegendItem *ai, QMouseEvent *me)
{
	Q_UNUSED(me);

	if(NULL != l && NULL != ai)
	{
//		for (int i=0; i<ui->customPlot->graphCount(); ++i)
//		{
//			QCPGraph *graph = ui->customPlot->graph(i);
//			if( graph->visible() )
//			{
//				QCPPlottableLegendItem *item = ui->customPlot->legend->itemWithPlottable(graph);
//				QPen qpGraphPen = l->parentPlot()->graph(i)->pen ();

//				if (item->selected() || graph->selected()){
//					qpGraphPen.setStyle(Qt::DotLine);
//					qpGraphPen.setWidth(4);
//				}
//				else
//				{
//					qpGraphPen.setStyle(Qt::SolidLine);
//					qpGraphPen.setWidth(2);
//				}
//				l->parentPlot()->graph(i)->setPen(qpGraphPen);
//			}
//		}
	}
}
//------------------------------------------------------------------------------
void MainWindow::onMouseDuobleClick(QMouseEvent *event)
{
	if(event->button() == Qt::LeftButton)
	{
//		if(ui->customPlot->axisRect()->rect().contains(event->pos()))
//		{
//			dTimeA = ui->customPlot->xAxis->pixelToCoord(event->x());
//			QString msgA = QString ("%1").arg (dTimeA);
//			ui->lneTimeA->setText(msgA);
//		}
	}
	else if(event->button() == Qt::RightButton)
	{
//		if(ui->customPlot->axisRect()->rect().contains(event->pos()))
//		{
//			dTimeB = ui->customPlot->xAxis->pixelToCoord(event->x());
//			QString msgB = QString ("%1").arg (dTimeB);
//			ui->lneTimeB->setText(msgB);
//		}
	}
	double dDeltaTime = dTimeB - dTimeA;
	QString msg = QString ("d: %1 s").arg (dDeltaTime);
	ui->lneDeltaTime->setText(msg);
}
//------------------------------------------------------------------------------
/**
 * @brief show Point Tool Tip on mouse hover
 * @param event mouse event connected
 */
void MainWindow::showPointToolTip(QMouseEvent *event)
{
//	const double dTimeS = ui->customPlot->xAxis->pixelToCoord(event->pos().x());

//	int ss = static_cast<int>(dTimeS);
//	int mm = ( ss / 60    ) % 60;
//	int hh = ( ss / 3660  ) % 24;
//	int ms = static_cast<int>((dTimeS *1000.0)) - ss*1000;
//	ss = ss % 60;

//	setToolTip(QString::asprintf("%02d:%02d:%02d.%03d",hh,mm,ss,ms));

}
//------------------------------------------------------------------------------
/**
 * @brief once clicked onto legend name can change Text of signal name
 * @param legend
 * @param item
 */
void MainWindow::legendDoubleClick(QCPLegend *legend, QCPAbstractLegendItem *item)
{
	// Rename a graph by double clicking on its legend item
	Q_UNUSED(legend)
	if (item) // only react if item was clicked (user could have clicked on border padding of legend where there is no item, then item is 0)
	{
		QCPPlottableLegendItem *plItem = qobject_cast<QCPPlottableLegendItem*>(item);
		bool ok;
		QString newName = QInputDialog::getText(this, "QCustomPlot example", "New graph name:", QLineEdit::Normal, plItem->plottable()->name(), &ok);
		if (ok)
		{
			plItem->plottable()->setName(newName);
            //ui->customPlot->replot();
		}
	}
}
//-----------------------------------------------------------------------------
/**
 * @brief MainWindow::MyTimerSlot  Slot for On Air option - temporized event
 */
void MainWindow::MyTimerSlot()
{
	//    Qui entriamo ogni 500ms
	if(TimerFlag == true)
	{
		on_LoadFile();
		on_save();
		//double minFinale = ui->lineEditMin->text().toDouble() ;
		//double interval = ui->lineEditInterval->text().toDouble();
		customPlotVariable = false;
		on_pushButtonProcess_clicked();
		const int iTimWinDispl = 10000; // time win to be displayed
		ui->lineEditMin->setText(QString::number(dLastTimeVal-iTimWinDispl));
		ui->lineEditInterval->setText(QString::number(iTimWinDispl));
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

        //ui->customPlot->xAxis->setRange(minFinale, minFinale+interval);
        //ui->customPlot->replot();
	}
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
    //ui->customPlot->xAxis->setRange(dRangeX0,dRangeX1);
    //ui->customPlot->replot();
	//    ui->lineEditInterval->setText(QString::number(rangeX1-rangeX0));
	//    ui->lineEditMin->setText(QString::number(rangeX0)); Ba
}
//------------------------------------------------------------------------------------------------
void MainWindow::on_pushButtonZoomPiu_clicked()
{
	double rangeX0 = ui->lineEditMin->text().toDouble();
	double interval = ui->lineEditInterval->text().toDouble();
	double newInterval = interval*0.1;
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
	double dRangeX0 = ui->lineEditMin->text().toDouble();
	double dInterval = ui->lineEditInterval->text().toDouble();
	double dNewInterval = dInterval*0.1;
	double dNewRangeX0 = dRangeX0 - dNewInterval;
	ui->lineEditMin->setText(QString::number(dNewRangeX0, 'd', 3));

	double finalInterval = dInterval + 2*dNewInterval;
	ui->lineEditInterval->setText(QString::number(finalInterval, 'd', 3));

	//double newRangeX1 = newRangeX0 + finalInterval;

	// ui->customPlot->xAxis->setRange(newRangeX0, newRangeX1 );
	// ui->customPlot->replot();
	on_UpgradePlot();
	ui->dial->setValue(0);
}

//------------------------------------------------------------------------------
void MainWindow::on_LoadFile_clicked()
{
	QString selFilter="Text files (*.txt)";
	strFileNameIn.clear();
	QString strPrevPath = iSettings.load(ISettings::SET_CURR_PATH).toString();
//    strFileNameIn ="./logC_arm.txt";
        strFileNameIn = QFileDialog::getOpenFileName(this,
                                                     "Open Full Log",
                                                     strPrevPath,
                                                     "Text files (*.txt);;All files (*.*)",
                                                     &selFilter);
	QFileInfo fileInfo(strFileNameIn);
	strPrevPath = fileInfo.absolutePath();
	iSettings.save(ISettings::SET_CURR_PATH, strPrevPath);
	on_LoadFile();
	qDebug()<<"File loaded";
	on_SaveButton_clicked();
}
//------------------------------------------------------------------------------
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
	QString selFilter="Text files (*.i1)";
	ulTimeStart = 0; // reset time intervals
	ulTimeStop = ( 23*3600 + 59*60 )* 1000;
	strFileNameOut.clear();
	//	strFileNameOut = QFileDialog::getSaveFileName(this,
	//												  "Choose Output filename",
	//												  QDir::currentPath()+"/out.txt",
	//												  "Text files (*.txt);;All files (*.*)",
	//												  &selFilter);
	QFileInfo fi=strFileNameIn;
	QString path= fi.absoluteFilePath();
	path.replace(".txt",".i1");
	//	strFileNameOut = QDir::currentPath()+"/out" + path + ".i1";
	strFileNameOut = path;
	strFileNameExtractLog = QDir::currentPath()+"/extractLog.txt";
	on_save();
	qDebug()<<"save";
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
		//		ui->pushButtonProcess->setEnabled(false);
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
	ui->FinishTextEdit->setPlainText("");
}

//------------------------------------------------------------------------------------------------
/**
 * @brief filter the text in input and provide the lines of interest, where at every number of time link a sequence of binary number
 */

void MainWindow::on_pushButtonProcess_clicked()
{
    CrunchLog crunchLog;
    QList<CrunchMsg::enumIdCAN> iDs;

    FigureWidget *figure = new FigureWidget(NULL);
    ui->vrlFigure->addWidget(figure);

	qDebug()<<"calling crunch";
	ulTimeStart = ui->timeEdit_2->time().msecsSinceStartOfDay();
	ulTimeStop = ui->timeEdit_3->time().msecsSinceStartOfDay();
	if ( ulTimeStart > ulTimeStop )
	{
		ulTimeStop = ulTimeStart + 10000;
	}

	qDebug()<<ulTimeStart;
	qDebug()<<ulTimeStop;

    iDs << CrunchMsg::ID_CAN_ARCO_CONTR << CrunchMsg::ID_CAN_ARCO_INV_A << CrunchMsg::ID_CAN_ARCO_INV_B;

    cDecorator.cleanGraph(figure->customPlot());
    crunchLog.processFile(strFileNameIn, iDs, ulTimeStart, ulTimeStop);

    strFileNameOut = strFileNameIn;
    if (ui->lswIDs->item(0)->checkState() == Qt::Checked)
        strFileNameOut.replace(".txt", QString().sprintf("_%03X.txt", (int)CrunchMsg::ID_CAN_ARCO_CONTR));
    else if (ui->lswIDs->item(1)->checkState() == Qt::Checked)
        strFileNameOut.replace(".txt", QString().sprintf("_%03X.txt", (int)CrunchMsg::ID_CAN_ARCO_INV_A));
    else if (ui->lswIDs->item(2)->checkState() == Qt::Checked)
        strFileNameOut.replace(".txt", QString().sprintf("_%03X.txt", (int)CrunchMsg::ID_CAN_ARCO_INV_B));
    else
        return;

	QFile file (strFileNameOut);
	if (!file.open(QFile::ReadOnly | QFile::Text)) {
		QMessageBox::warning(this,"op","Cannot open file");
		return;
	}

	QString contents = file.readAll().constData();
	ui->FinishTextEdit->setPlainText(contents);

	file.close();

	demoName.append("GmmScope");
    setupPlotLogs(figure);
    if (customPlotVariable==true){
        figure->customPlot()->replot();
	}
	ui->tabWidget->setCurrentIndex(1);
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

    //ui->customPlot->xAxis->setRange(rangeX0,rangeX0+interval);
    //ui->customPlot->replot();
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

    //ui->customPlot->xAxis->setRange(rangeX0,rangeX0+interval);
    //ui->customPlot->replot();
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
//--------------------------------------------------------------------------

void MainWindow::on_timeEdit_2_timeChanged(const QTime &time)
{
	int hour = time.hour();
	int min =  time.minute();
	int sec =  time.second();

	ulTimeStart = ((hour*60*60) + (min*60) + (sec))*1000 ;
}
//--------------------------------------------------------------------------
void MainWindow::on_timeEdit_3_timeChanged(const QTime &time)
{
	int hour = time.hour();
	int min =  time.minute();
	int sec =  time.second();
	ulTimeStop = ((hour*60*60) + (min*60) + (sec))*1000 ;
}

void MainWindow::on_tabWidget_currentChanged(int index)
{
}
