
#include "CDecorator.h"
//#include <QDebug>
CDecorator cDecorator;
CDecorator::CDecorator()
{

}
//------------------------------------------------------------------------------
// color table " colorcube "
uint8_t u8aColR[64]={ 85, 85, 85, 170, 170, 170, 255, 255, 255, 0, 0, 0, 85, 85, 85, 85, 170, 170, 170, 170, 255, 255, 255, 255, 0, 0, 0, 85, 85, 85, 85, 170, 170, 170, 170, 255, 255, 255, 42, 85, 127, 170, 212, 255, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 36, 72, 109, 145, 182, 218, 255, };
uint8_t u8aColG[64]={ 85, 170, 255, 85, 170, 255, 85, 170, 255, 85, 170, 255, 0, 85, 170, 255, 0, 85, 170, 255, 0, 85, 170, 255, 85, 170, 255, 0, 85, 170, 255, 0, 85, 170, 255, 0, 85, 170, 0, 0, 0, 0, 0, 0, 42, 85, 127, 170, 212, 255, 0, 0, 0, 0, 0, 0, 0, 36, 72, 109, 145, 182, 218, 255, };
uint8_t u8aColB[64]={ 0, 0, 0, 0, 0, 0, 0, 0, 0, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 42, 85, 127, 170, 212, 255, 0, 36, 72, 109, 145, 182, 218, 255, };
//-----------------------------------------------------------------------------
/**
 * @brief CDecorator::addSignalToPlot draw single IO plot
 * @param qvTime	array of time
 * @param qvDataArranged
 * @param LegendList	Legend List to be procesed
 * @param qvMyVect	array of y -output
 * @param iSzVet
 * @param iDataIdx
 * @param customPlot
 */
void CDecorator::addIOSignalToPlot(QVector<double> qvTime,
								   QVector<double> qvDataArranged,
								   QString qStrLegend,
								   QVector <QVector <int> > qvMyVect,
								   int iDataIdx,
								   QCustomPlot *customPlot)
{
	const int iSzVet = qvMyVect.size();
	QPen pen;
	const int iColPos = (3*iDataIdx) % 63; // position Color choice
	pen.setColor(QColor(u8aColR[iColPos], u8aColG[iColPos], u8aColB[iColPos]));
	pen.setWidth(2);

	for ( int jj=0; jj<iSzVet; jj++ ){
		qvDataArranged[jj] = qvMyVect[jj][iDataIdx]*0.5 + (MC_STATUS-iDataIdx) ;
	}
	addGraph(pen, qvDataArranged, qvTime, qStrLegend, customPlot);
}
//-----------------------------------------------------------------------------
/**
 * @brief CDecorator::addSignalToPlot draw single IO plot
 * @param qvTime	array of time
 * @param qvDataArranged
 * @param LegendList	Legend List to be procesed
 * @param qvMyVect
 * @param iSzVet
 * @param iDataIdx
 * @param customPlot
 */
void CDecorator::addGraph(QPen pen, QVector<double> qvDataArranged, QVector<double> qvTime, QString qStrLegend, QCustomPlot *customPlot)
{
	customPlot->addGraph();// create graph
	customPlot->graph()->setPen(pen);
	customPlot->graph()->setName(qStrLegend);
	int iGraphCount = customPlot->graphCount();
	customPlot->graph(iGraphCount-1)->setData(qvTime, qvDataArranged);
}

void CDecorator::addIntSignalToPlot(QVector<double> qvTime,
									QVector<double> qvDataArranged,
									QString qStrLegend,
									QVector <QVector <int> > qvMyVect,
									int iDataIdx,
									QCustomPlot *customPlot)
{
	const int iSzVet = qvMyVect.size();
	QPen pen;
	const int iColPos = (3*iDataIdx) % 63; // position Color choice
	pen.setColor(QColor(u8aColR[iColPos], u8aColG[iColPos], u8aColB[iColPos]));
	pen.setWidth(2);

	for ( int jj=0; jj<iSzVet; jj++ ){
		qvDataArranged[jj] = qvMyVect[jj][iDataIdx] ;
	}
	addGraph(pen, qvDataArranged, qvTime, qStrLegend, customPlot);
}
//-----------------------------------------------------------------------------
/**
 * @brief CDecorator::buildLegend buil legend array
 * @return Full Filled Legend
 */
QVector<QString> CDecorator::buildLegend()
{
	QVector<QString> LegendList;
	LegendList<< "TIME                "
			  << "I PID SDCAL STP     "
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
			  << "I_CNS_PREP          "	// stato del segnale di preparazione dato dai 2 segnali in arrivo
			  << "I_CNS_FL            "	// stato del segnale di fluoro dato dai 2 segnali in arrivo
			  << "I_CNS_RAD           "	// stato del segnale di esposizione dato dai 2 segnali in arrivo
			  << "O_TAB_?             "	// fluoroscopia (pedale fluoro)
			  << "O_TAB_FL            "	// preparazione (tasto di preparazione su consolle)
			  << "O_TAB_PREP          "	// esposizione rx (consenso finale rx)
			  << "O_TAB_RAD           "	// grafia (second step)
			  << "O_TAB_EN            "
			  << "GEN STAT            "
			  << "DLL STAT            "
			  << "GEN_REQ_BIT        "
			  << "GEN_XRAY_ON_BIT    "
			  << "PREPARATION_BIT_EXT"
			  << "FLUORO_BIT_EXT     "
			  << "EXPOSURE_BIT_EXT   "
			  << "CONS1_PREP_HW      "
			  << "CONS1_RAD_HW       "
			  << "CONS1_FL_HW        "
			  << "   "
				 ;
	qDebug()<<"Legend";
	return LegendList;
}
//-----------------------------------------------------------------------------
/**
 * @brief CDecorator::buildGraph build the graph accordin to own method implementation
 */
void CDecorator::buildGraph(QCustomPlot *customPlot, QFile *file)
{
	customPlot->legend->setVisible(true);
	customPlot->legend->setFont(QFont("Helvetica", 9));
	customPlot->legend->setSelectableParts(QCPLegend::spItems); // legend box shall not be selectable, only legend items

	// now we move the legend from the inset layout of the axis rect into the main grid layout.
	// We create a sub layout so we can generate a small gap between the plot layout cell border
	// and the legend border:
	QCPLayoutGrid *subLayout = new QCPLayoutGrid;
	customPlot->plotLayout()->addElement(0, 1, subLayout);
	subLayout->setMargins(QMargins(5, 0, 5, 5));
	subLayout->addElement(0, 0, customPlot->legend);
	// change the fill order of the legend, so it's filled left to right in columns:
	//	customPlot->legend->setFillOrder(QCPLegend::foColumnsFirst);
	// set legend's row stretch factor very small so it ends up with minimum height:
	//	customPlot->plotLayout()->setRowStretchFactor(1, 0.001);

	customPlot->plotLayout()->setColumnStretchFactor (1, 0.001);
	//customPlot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::RightButton);
	//  .  .  .  .  .  .  .  .  .  .  .  .

#define ARRAY_DIM 100000 /// max number of lines to auto-stop proessing
	QTextStream in(file);
	QVector <QVector <int> > qvMyVect;

	unsigned long ulMaxLi; // MAX legnth of "photograms" to draw
	for (ulMaxLi=0; ulMaxLi<ARRAY_DIM; ulMaxLi++) // reached certain num of lines break!
	{
		QString line = in.readLine(); //read one line at a time
		if (line.isEmpty()) {
			break; // if here means "reached end of file"
		}

		QVector<int> tempVector;
		foreach( QString numStr, line.split(" ", QString::SkipEmptyParts) )
		{	// unroll each line into current Time array and into current
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
	QVector<QString> LegendList = buildLegend();


	const int iSzVet = qvMyVect.size(); // array Size
	const int iNumElem = qvMyVect[0].size(); // num of plots
	QVector<double> qvTime; // time array
	QVector<double> qvDataArranged; // data array

	if (iSzVet> 0 )
	{
		qvDataArranged.resize(iSzVet); // resize optimze time with memory alloc
		qvTime.resize(iSzVet); // resize optimze time with memory alloc
		qDebug()<<"ResizeOk";
		for (int jj=0; jj<iSzVet; jj++){
			qvTime[jj] = qvMyVect[jj][0]/1000.0 ;
		}
		qDebug()<<"ForB";

		for (int iDataIdx=I_PID_SDCAL_STP; iDataIdx <= O_PID_EXON; iDataIdx++)
		{	// OBS:  index move from 1: data(0,:) are time values
			addIOSignalToPlot(qvTime, qvDataArranged,
							  LegendList.at(iDataIdx), qvMyVect,
							  iDataIdx, customPlot);
		}
		qDebug()<<"Plot IO";
		QVector<int> qVTablePlot = {
			I_CNS_PREP, I_CNS_FL  ,
			I_CNS_RAD , O_TAB_x   ,
			O_TAB_FL  , O_TAB_PREP,
			O_TAB_RAD , O_TAB_EN   };
		for (int ii=0; ii < qVTablePlot.size(); ii++)
		{	// OBS:  index move from 1: data(0,:) are time values
			int iDataIdx = qVTablePlot.at(ii);
			addIOSignalToPlot(qvTime, qvDataArranged,
							  LegendList.at(iDataIdx), qvMyVect,
							  iDataIdx, customPlot);
		}
		qDebug()<<"Plot Table";

		QVector<int> qVIntPlot = {MC_STATUS, GEN_STAT, DLL_GE_STAT};
		for (int ii=0; ii <qVIntPlot.size(); ii++)
		{	// OBS:  index move from 1: data(0,:) are time values
			int iDataIdx = qVIntPlot.at(ii);
			addIntSignalToPlot(qvTime, qvDataArranged,
							   LegendList.at(iDataIdx), qvMyVect,
							   iDataIdx, customPlot);
		}
		qDebug()<<"Plot Int ";
		qDebug()<<"Plot IO";
		QVector<int> qVTableExtPlot = {
			GEN_REQ_BIT        ,
			GEN_XRAY_ON_BIT    ,
			PREPARATION_BIT_EXT,
			FLUORO_BIT_EXT     ,
			CONS1_PREP_HW   ,
			CONS1_RAD_HW    ,
			CONS1_FL_HW     ,
		};
		for (int ii=0; ii < qVTableExtPlot.size(); ii++)
		{	// OBS:  index move from 1: data(0,:) are time values
			int iDataIdx = qVTableExtPlot.at(ii);
			addIOSignalToPlot(qvTime, qvDataArranged,
							  LegendList.at(iDataIdx), qvMyVect,
							  iDataIdx, customPlot);
		}
		qDebug()<<"Plot TableExt";
		// give the axes some labels:
		customPlot->xAxis->setLabel("t [s]");
		QSharedPointer<QCPAxisTickerDateTime> dateTicker(new QCPAxisTickerDateTime);
		dateTicker->setDateTimeFormat("hh\rmm:ss\nzzz");
		dateTicker->setDateTimeSpec(Qt::UTC);
		customPlot->xAxis->setTicker(dateTicker);
		customPlot->yAxis->setLabel("y");
		qDebug()<<"Set Axis";
		// set axes ranges, so we see all data:
		double dMinXAxis = *std::min_element(qvTime.constBegin(), qvTime.constEnd());
		double dMaxXAxis = *std::max_element(qvTime.constBegin(), qvTime.constEnd());

		customPlot->xAxis->setRange(dMinXAxis-1,dMaxXAxis+1);
		dMaxXAxis = *std::max_element(qvDataArranged.constBegin(), qvDataArranged.constEnd());
		customPlot->yAxis->setRange(19-iNumElem, 20); // Y axis range

		customPlot->setInteractions(QCP::iSelectLegend);
	}

}
