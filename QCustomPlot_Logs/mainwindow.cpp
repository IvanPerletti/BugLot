
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

    figureList.clear();

    QMetaEnum e = QMetaEnum::fromType<CrunchMsg::enumIdCAN>();
    for (int k = 0; k < e.keyCount(); k++)
    {
        QListWidgetItem *listWidgetItem = new QListWidgetItem(ui->lswIDs);
        listWidgetItem->setText(QString().sprintf("0x%X", e.value(k)));
        auto currentFlags = listWidgetItem->flags();
        listWidgetItem->setFlags(currentFlags & (~Qt::ItemIsEnabled));
        listWidgetItem->setCheckState(Qt::Unchecked);
        ui->lswIDs->addItem (listWidgetItem);
    }
    ui->tabWidget->setCurrentIndex(0);
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

bool MainWindow::setupPlotLogs(FigureWidget *figure, QStringList fileNames)
{
    cDecorator.buildGraph(figure, fileNames);

    double dMinXAxis = figure->customPlot()->xAxis->range().lower;
    double dMaxXAxis = figure->customPlot()->xAxis->range().upper;
    dLastTimeVal = dMaxXAxis; // used for "OnAir option"

    ui->lineEditMin->setText(QString::number(dMinXAxis));
    ui->lineEditInterval->setText(QString::number(dMaxXAxis-dMinXAxis));
//	disconnect(ui->customPlot,
//			   SIGNAL(legendClick(QCPLegend*, QCPAbstractLegendItem*, QMouseEvent*)));

	// connect some interaction slots:
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

    return true;
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
		//double minFinale = ui->lineEditMin->text().toDouble() ;
		//double interval = ui->lineEditInterval->text().toDouble();

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
    foreach (FigureWidget *figure, figureList) {
        figure->customPlot()->xAxis->setRange(dRangeX0,dRangeX1);
        figure->customPlot()->replot();
    }
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

    double newRangeX1 = newRangeX0 + finalInterval;
    foreach (FigureWidget *figure, figureList) {
        figure->customPlot()->xAxis->setRange(newRangeX0, newRangeX1 );
        figure->customPlot()->replot();
    }
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

    double newRangeX1 = dNewRangeX0 + finalInterval;
    foreach (FigureWidget *figure, figureList) {
        figure->customPlot()->xAxis->setRange(dNewRangeX0, newRangeX1 );
        figure->customPlot()->replot();
    }
	on_UpgradePlot();
	ui->dial->setValue(0);
}

//----------------------------------------------------------------------------
void MainWindow::on_pushButtonZoomLeft_clicked()
{
    double rangeX0 = ui->lineEditMin->text().toDouble();
    double interval = ui->lineEditInterval->text().toDouble();

    double delta = (interval)/10;
    rangeX0 -= delta;
    interval -= delta;
    ui->lineEditMin->setText(QString::number(rangeX0));
    ui->lineEditInterval->setText(QString::number(interval));

    foreach (FigureWidget *figure, figureList) {
        figure->customPlot()->xAxis->setRange(rangeX0,rangeX0+interval);
        figure->customPlot()->replot();
    }
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

    foreach (FigureWidget *figure, figureList) {
        figure->customPlot()->xAxis->setRange(rangeX0,rangeX0+interval);
        figure->customPlot()->replot();
    }
}

//------------------------------------------------------------------------------
void MainWindow::on_LoadFile_clicked()
{
	QString selFilter="Text files (*.txt)";
	strFileNameIn.clear();
	QString strPrevPath = iSettings.load(ISettings::SET_CURR_PATH).toString();
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
    file.close();

	text.append("\r\n [...]");
	ui->textEdit->setText(text);
	QFileInfo fi=strFileNameIn;
    ui->qlFileName->setText("Input File: " + fi.baseName());

    CrunchLog crunchLog;

    qDebug() << "calling crunch";
    ulTimeStart = ui->timeEdit_2->time().msecsSinceStartOfDay();
    ulTimeStop = ui->timeEdit_3->time().msecsSinceStartOfDay();
    if ( ulTimeStart > ulTimeStop )
        ulTimeStop = ulTimeStart + 10000;
    qDebug()<< "Start " << ulTimeStart << " Stop " << ulTimeStop;

    QList<CrunchMsg::enumIdCAN> iDsFound = crunchLog.processFile(strFileNameIn, ulTimeStart, ulTimeStop);

    ui->FinishTextEdit->clear();
    QMetaEnum e = QMetaEnum::fromType<CrunchMsg::enumIdCAN>();
    for (int k = 0; k < e.keyCount(); k++)
    {
        ui->lswIDs->item(k)->setCheckState(Qt::Unchecked);
        auto currentFlags = ui->lswIDs->item(k)->flags();
        if (iDsFound.contains((CrunchMsg::enumIdCAN)e.value(k))) {
            ui->lswIDs->item(k)->setFlags(currentFlags | (Qt::ItemIsEnabled));
            strFileNameOut = strFileNameIn;
            strFileNameOut.replace(".txt", QString().sprintf("_%03X.txt", e.value(k)));
            QFile file (strFileNameOut);
            if (!file.open(QFile::ReadOnly | QFile::Text)) {
                QMessageBox::warning(this,"op","Cannot open file");
            } else {
                QString contents = file.readAll().constData();
                ui->FinishTextEdit->appendPlainText(contents);
                file.close();
            }
        } else
            ui->lswIDs->item(k)->setFlags(currentFlags & (~Qt::ItemIsEnabled));
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
    QMetaEnum e = QMetaEnum::fromType<CrunchMsg::enumIdCAN>();
    QStringList fileNames;

    for (int i = 0; i < ui->lswIDs->count(); i++) {
        if (ui->lswIDs->item(i)->checkState() == Qt::Checked) {
            strFileNameOut = strFileNameIn;
            strFileNameOut.replace(".txt", QString().sprintf("_%03X.txt", e.value(i)));
            fileNames.append(strFileNameOut);
        }
    }

    if (!fileNames.isEmpty()) {
        FigureWidget *figure = new FigureWidget(NULL);
        figureList.append(figure);

        ui->vrlFigure->addWidget(figure);

        demoName.append("GmmScope");

        setupPlotLogs(figure, fileNames);
        ui->tabWidget->setCurrentIndex(1);
        if (figureList.count() > 1)
            alignXRange();
    }
}

void MainWindow::alignXRange(void)
{
   QCPRange xRange(figureList.at(0)->customPlot()->xAxis->range().lower, figureList.at(0)->customPlot()->xAxis->range().upper);
   FigureWidget *figure;

   foreach (figure, figureList)
       xRange.expand(figure->customPlot()->xAxis->range());
   foreach (figure, figureList) {
       figure->customPlot()->xAxis->setRange(xRange);
       figure->customPlot()->replot();
   }
}

//--------------------------------------------------------------------------

void MainWindow::on_pushButtonDiretta_clicked()
{
    if (!figureList.isEmpty()) {
        FigureWidget *figure = figureList.takeLast();
        ui->vrlFigure->removeWidget(figure);
        delete figure;
    }

//	if (TimerFlag == true)
//	{
//		// set button text
//		TimerFlag = false;
//	}
//	else{
//		//        set other buuton text
//		TimerFlag = true;
//	}
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
