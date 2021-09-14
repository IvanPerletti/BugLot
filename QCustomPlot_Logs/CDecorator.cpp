
#include "CDecorator.h"

//#include <QDebug>
#define ARRAY_DIM       (250*1000) /// max number of lines to auto-stop proessing

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
 * @param qvVect
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

void CDecorator::addSignalToPlot(QVector<double> qvTime,
									QString qStrLegend,
                                    QString qStrType,
                                    QVector <QVector <double> > qvVect,
                                    QVector<double> &qvDataArranged,
                                    int iDataIdx, int uiNumBitField,
									QCustomPlot *customPlot)
{
    int iSzVet = qvVect.size();
	QPen pen;
	const int iColPos = (3*iDataIdx) % 63; // position Color choice
	pen.setColor(QColor(u8aColR[iColPos], u8aColG[iColPos], u8aColB[iColPos]));
	pen.setWidth(2);
	if ( iSzVet > ARRAY_DIM ){
		iSzVet = ARRAY_DIM;
	}
    qvDataArranged.resize(iSzVet); // resize optimze time with memory alloc
    for ( int jj=0; jj<iSzVet; jj++ ){
        if (qStrType == TYPE_BIT)
            qvDataArranged[jj] = qvVect[jj][iDataIdx] * 0.5 + ((uiNumBitField / 2) - iDataIdx) ;
        else
            qvDataArranged[jj] = qvVect[jj][iDataIdx];

	}
	addGraph(pen, qvDataArranged, qvTime, qStrLegend, customPlot);
}

//-----------------------------------------------------------------------------
void CDecorator::cleanGraph(QCustomPlot *customPlot)
{
    for( int ii=0; ii<customPlot->graphCount(); ii++ )
	{
        customPlot->graph(ii)->data().data()->clear();
	}
    customPlot->replot();
}

//-----------------------------------------------------------------------------
/**
 * @brief CDecorator::buildGraph build the graph accordin to own method implementation
 */
bool CDecorator::buildGraph(QCustomPlot *customPlot, QFile *file)
{
    unsigned int uiNumBitField = 0;
    QTextStream in(file);
    QString line;
    int pos;

    do {
        line = in.readLine(); //read one line at a time
        if (line.isEmpty()) {
            return false; // if here means "reached end of file"
        }
        if (line.startsWith(HEADER_PREFIX) == false)
            break;
        if ((pos = line.indexOf(LEGENDS_TAG)) >= 0) {
            legendList = line.mid(pos + QString(LEGENDS_TAG).length()).split(" ", QString::SkipEmptyParts);
        } else if ((pos = line.indexOf(TYPES_TAG)) >= 0) {
            typeList = line.mid(pos + QString(TYPES_TAG).length()).split(" ", QString::SkipEmptyParts);
        }
    } while (true);

	customPlot->legend->setVisible(true);
	customPlot->legend->setFont(QFont("Helvetica", 8));
	customPlot->legend->setSelectableParts(QCPLegend::spItems); // legend box shall not be selectable, only legend items

	// now we move the legend from the inset layout of the axis rect into the main grid layout.
	// We create a sub layout so we can generate a small gap between the plot layout cell border
	// and the legend border:
	QCPLayoutGrid *subLayout = new QCPLayoutGrid;
	customPlot->plotLayout()->addElement(0, 1, subLayout);
	subLayout->setMargins(QMargins(5, 0, 5, 5));
	subLayout->addElement(0, 0, customPlot->legend);

	customPlot->plotLayout()->setColumnStretchFactor (1, 0.001);

    QVector <QVector <double> > qvVect;

	unsigned long ulMaxLi; // MAX legnth of "photograms" to draw
    for (ulMaxLi=1; ulMaxLi<ARRAY_DIM; ulMaxLi++) // reached certain num of lines break!
	{
        QVector <double> tempVector;

		foreach( QString numStr, line.split(" ", QString::SkipEmptyParts) )
		{	// unroll each line into current Time array and into current
			bool bCheck = false; // flag to signalize double value found
			double dVal = numStr.toDouble(&bCheck);
			if( !bCheck ){
				continue;
            } else {
				tempVector.push_back(dVal);
			}
		}
        qvVect.push_back(tempVector);

        line = in.readLine(); //read one line at a time
        if (line.isEmpty()) {
            break; // if here means "reached end of file"
        }
    }
	if (ulMaxLi > 0)
	{
        const int iSzVet = qvVect.size(); // array Size
        const int iNumElem = qvVect[0].size(); // num of plots
		QVector<double> qvTime; // time array
		QVector<double> qvDataArranged; // data array

		if (iSzVet> 0 )
		{
            double dMinYAxis = 0.0;
            double dMaxYAxis = 0.0;

            if (legendList.length() < iNumElem) {
                for (int iLegendIdx = legendList.length() + 1; iLegendIdx <= iNumElem; iLegendIdx++) {
                    legendList << QString("Item ") + QString("%1").arg(iLegendIdx);
                }
            }

            if (typeList.length() < iNumElem) {
                for (int iTypeIdx = typeList.length() + 1; iTypeIdx <= iNumElem; iTypeIdx++) {
                    typeList << TYPE_INT;
                }
            }
            foreach (QString type, typeList) {
                if (type == QString(TYPE_BIT))
                    ++uiNumBitField;
            }

            qvTime.resize(iSzVet); // resize optimze time with memory alloc
            for (int jj=0; jj<iSzVet; jj++) {
                qvTime[jj] = qvVect[jj][0]/1000.0 ;
			}

            for (int iDataIdx=1; iDataIdx < iNumElem; iDataIdx++) {
                addSignalToPlot(qvTime,
                                legendList.at(iDataIdx - 1), typeList.at(iDataIdx - 1),
                                qvVect, qvDataArranged,
                                iDataIdx, uiNumBitField, customPlot);
                dMinYAxis = fmin(dMinYAxis, *std::min_element(qvDataArranged.constBegin(), qvDataArranged.constEnd()));
                dMaxYAxis = fmax(dMaxYAxis, *std::max_element(qvDataArranged.constBegin(), qvDataArranged.constEnd()));
            }

			// give the axes some labels:
			customPlot->xAxis->setLabel("t [s]");
			QSharedPointer<QCPAxisTickerDateTime> dateTicker(new QCPAxisTickerDateTime);
			dateTicker->setDateTimeFormat("hh\rmm:ss\nzzz");
			dateTicker->setDateTimeSpec(Qt::UTC);
			customPlot->xAxis->setTicker(dateTicker);
			customPlot->yAxis->setLabel("y");

			// set axes ranges, so we see all data:
			double dMinXAxis = *std::min_element(qvTime.constBegin(), qvTime.constEnd());
			double dMaxXAxis = *std::max_element(qvTime.constBegin(), qvTime.constEnd());

			customPlot->xAxis->setRange(dMinXAxis-1,dMaxXAxis+1);
            customPlot->yAxis->setRange(dMinYAxis, dMaxYAxis); // Y axis range
			customPlot->setInteractions(QCP::iSelectLegend);
		}
	}
    return (ulMaxLi > 0);
}
