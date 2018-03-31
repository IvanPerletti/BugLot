
#include "CDecorator.h"

CDecorator cDecorator;
CDecorator::CDecorator()
{

}
//------------------------------------------------------------------------------
// color table " colorcube "
uint8_t u8aColR[64]={ 85, 85, 85, 170, 170, 170, 255, 255, 255, 0, 0, 0, 85, 85, 85, 85, 170, 170, 170, 170, 255, 255, 255, 255, 0, 0, 0, 85, 85, 85, 85, 170, 170, 170, 170, 255, 255, 255, 42, 85, 127, 170, 212, 255, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 36, 72, 109, 145, 182, 218, 255, };
uint8_t u8aColG[64]={ 85, 170, 255, 85, 170, 255, 85, 170, 255, 85, 170, 255, 0, 85, 170, 255, 0, 85, 170, 255, 0, 85, 170, 255, 85, 170, 255, 0, 85, 170, 255, 0, 85, 170, 255, 0, 85, 170, 0, 0, 0, 0, 0, 0, 42, 85, 127, 170, 212, 255, 0, 0, 0, 0, 0, 0, 0, 36, 72, 109, 145, 182, 218, 255, };
uint8_t u8aColB[64]={ 0, 0, 0, 0, 0, 0, 0, 0, 0, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 42, 85, 127, 170, 212, 255, 0, 36, 72, 109, 145, 182, 218, 255, };

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

#define ARRAY_DIM 200000 /// max number of lines to auto-stop proessing
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

	//  buildLegend() { =========================================
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
			  << "ADC CM10            "
			  << "DAC ABS             ";

	//  } .=========================================

	const int iSzVet = qvMyVect.size(); // array Size
	const int iNumElem = qvMyVect[0].size(); // num of plots
	QVector<double> qvTime; // time array
	QVector<double> qvDataArranged; // data array
	qvDataArranged.resize(iSzVet); // resize optimze time with memory alloc
	qvTime.resize(iSzVet); // resize optimze time with memory alloc

	for (int jj=0; jj<iSzVet; jj++){
		qvTime[jj] = qvMyVect[jj][0]/1000.0 ;
	}

	for (int iDataIdx=1; iDataIdx<iNumElem; iDataIdx++)
	{	// OBS:  index move from 1: data(0,:) are time values
		for ( int jj=0; jj<iSzVet; jj++ ){
			qvDataArranged[jj] = qvMyVect[jj][iDataIdx]*0.5 + (20-iDataIdx) ;
		}
		customPlot->addGraph();// create graph
		QPen pen;
		const int iColPos = (iDataIdx*2)%63; // position Color choice
		pen.setColor(QColor(u8aColR[iColPos], u8aColG[iColPos], u8aColB[iColPos]));
		pen.setWidth(2);
		customPlot->graph()->setPen(pen);

		QString qStrLegend = LegendList.at(iDataIdx);
		customPlot->graph()->setName(qStrLegend);
		customPlot->graph(iDataIdx-1)->setData(qvTime, qvDataArranged);
	}

	// give the axes some labels:
	customPlot->xAxis->setLabel("t [ms]");
	customPlot->yAxis->setLabel("y");
	// set axes ranges, so we see all data:
	double dMinXAxis = *std::min_element(qvTime.constBegin(), qvTime.constEnd());
	double dMaxXAxis = *std::max_element(qvTime.constBegin(), qvTime.constEnd());

	customPlot->xAxis->setRange(dMinXAxis-1,dMaxXAxis+1);
	dMaxXAxis = *std::max_element(qvDataArranged.constBegin(), qvDataArranged.constEnd());
	customPlot->yAxis->setRange(-1, iNumElem+1); // Y axis range

	customPlot->setInteractions(QCP::iSelectLegend);


}