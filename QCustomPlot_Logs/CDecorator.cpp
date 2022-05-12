#include <QMath.h>
#include <QDebug>

#include "CDecorator.h"
#include "CrunchLog.h"

#define ARRAY_DIM       (250*1000) /// max number of lines to auto-stop proessing

#define BITFIELD_DELTA_Y        10
#define ROUND_MAX_Y_AXIS        10

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
void CDecorator::addGraph(QPen pen, QVector<double> qvDataArranged, QVector<double> qvTime, QString qStrLegend, QString qStrFactor, QCustomPlot *customPlot)
{
    customPlot->addGraph();
	customPlot->graph()->setPen(pen);
    customPlot->graph()->setData(qvTime, qvDataArranged);

    QListWidgetItem *listWidgetItem = new QListWidgetItem(lswLegend);
    lswLegend->addItem (listWidgetItem);

    LegendItem *legendItem = new LegendItem(customPlot->graph(), qStrLegend, qStrFactor, pen.color());
    qDebug() << "legendItem" << legendItem->sizeHint().width() << " " << legendItem->sizeHint().height();
    QSize sizeHint = legendItem->sizeHint ();
    sizeHint.setHeight(40);
    listWidgetItem->setSizeHint ( sizeHint );
    qDebug() << listWidgetItem->sizeHint().width() << " " << listWidgetItem->sizeHint().height();

    lswLegend->setItemWidget (listWidgetItem, legendItem);
}

void CDecorator::addSignalToPlot(int iSignalIdx, QVector<QVector<double>> qvVect, QVector<double> qvTime, double dMaxYAxis, QCustomPlot *customPlot)
{
    QVector<double> qvDataArranged;
    QString qStrLegend = legendList.at(iSignalIdx);
    QString qStrFactor;

    int iSzVet = qvVect.size();
	QPen pen;
    const int iColPos = (3*iSignalIdx + 1) % 63; // position Color choice

    pen.setColor(QColor(u8aColR[iColPos], u8aColG[iColPos], u8aColB[iColPos]));
	pen.setWidth(2);

    if ( iSzVet > ARRAY_DIM ){
		iSzVet = ARRAY_DIM;
	}

    qvDataArranged.resize(iSzVet); // resize optimze time with memory alloc
    for ( int jj=0; jj<iSzVet; jj++ ) {
        qvDataArranged[jj] = qvVect[jj][iSignalIdx + 1];
    }

    if (typeList.at(iSignalIdx) == TYPE_BIT) {
        int iDeltaY = ((int)(dMaxYAxis / typeList.count(TYPE_BIT)) / 10) * 10;
        int iOfsY = iDeltaY * (typeList.count(TYPE_BIT) - (typeList.mid(0, iSignalIdx).count(TYPE_BIT)));
        for ( int jj=0; jj<iSzVet; jj++ ) {
            qvDataArranged[jj] = iOfsY + (qvDataArranged[jj] * (iDeltaY / 2));
        }
        qStrFactor = QString("^%1").arg(iOfsY);
    } else if (typeList.at(iSignalIdx) == TYPE_INT) {
        int iFactor = 1;
        double dMax = *std::max_element(qvDataArranged.constBegin(), qvDataArranged.constEnd());
        if (dMax != 0.0) {
            while ((dMax * iFactor * 10) < dMaxYAxis) {
                iFactor *= 10;
            }
        }
        for ( int jj=0; jj<iSzVet; jj++ ) {
            qvDataArranged[jj] *= iFactor;
        }
        if (iFactor > 1)
            qStrFactor = QString("x%1").arg(iFactor);
    }
    addGraph(pen, qvDataArranged, qvTime, qStrLegend, qStrFactor, customPlot);
}

//-----------------------------------------------------------------------------
void CDecorator::cleanGraph(FigureWidget *figure)
{
    for( int ii=0; ii<figure->customPlot()->graphCount(); ii++ )
	{
        figure->customPlot()->graph(ii)->data().data()->clear();
	}
    figure->customPlot()->replot();
}

//-----------------------------------------------------------------------------
/**
 * @brief CDecorator::buildGraph build the graph accordin to own method implementation
 */
bool CDecorator::buildGraph(FigureWidget *figure, QStringList fileNames)
{
    QVector<double> qvTime;
    QVector <QVector <double> > qvVect;
    QString line;
    int pos;
    unsigned long ulMaxLi;
    double dMinYAxis = 0.0, dMaxYAxis = 0.0, dMinXAxis = 0.0, dMaxXAxis = 0.0;

    this->lswLegend = figure->lswLegend();

    figure->customPlot()->clearGraphs();
    figure->customPlot()->legend->setVisible(false);
    figure->customPlot()->plotLayout()->setColumnStretchFactor (1, 0.001);

    for ( const auto& fileName : fileNames  )
    {
        QFile file (fileName);
        if (!file.open(QFile::ReadOnly | QFile::Text))
            continue;

        legendList.clear();
        typeList.clear();

        QTextStream in(&file);
        do {
            line = in.readLine(); //read one line at a time
            if (line.isEmpty()) {
                file.close();
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

        // connect some interaction slots:
        connect(this->lswLegend,
                SIGNAL(currentItemChanged(QListWidgetItem *, QListWidgetItem *)),
                this,
                SLOT(currentItemChanged(QListWidgetItem *, QListWidgetItem *)));
        connect(this->lswLegend,
                SIGNAL(itemSelectionChanged()),
                this,
                SLOT(itemSelectionChanged()));

        qvVect.clear();
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
            dMinYAxis = fmin(dMinYAxis, *std::min_element(tempVector.constBegin() + 1, tempVector.constEnd()));
            dMaxYAxis = fmax(dMaxYAxis, *std::max_element(tempVector.constBegin() + 1, tempVector.constEnd()));

            line = in.readLine(); //read one line at a time
            if (line.isEmpty()) {
                break; // if here means "reached end of file"
            }
        }
        const int iSzVet = qvVect.size(); // array Size
        const int iNumSignal = qvVect[0].size() - 1; // num of plots

        if (iSzVet> 0 )
        {

            if (legendList.length() < iNumSignal) {
                for (int iLegendIdx = legendList.length() + 1; iLegendIdx <= iNumSignal; iLegendIdx++) {
                    legendList << QString("Item ") + QString("%1").arg(iLegendIdx);
                }
            }

            if (typeList.length() < iNumSignal) {
                for (int iTypeIdx = typeList.length() + 1; iTypeIdx <= iNumSignal; iTypeIdx++) {
                    typeList << TYPE_INT;
                }
            }

            qvTime.resize(iSzVet); // resize optimze time with memory alloc
            for (int jj=0; jj<iSzVet; jj++) {
                qvTime[jj] = qvVect[jj][0]/1000.0 ;
            }

//            int iLogMaxYAxis = (int)log10(dMaxYAxis);
//            double dMult = pow(10, (double)iLogMaxYAxis);
//            dMaxYAxis = (((int)((dMaxYAxis - 1) / dMult)) + 1) * dMult;
            dMaxYAxis = fmax((((int)(dMaxYAxis / ROUND_MAX_Y_AXIS)) + 1) * ROUND_MAX_Y_AXIS, (typeList.count(TYPE_BIT) + 1) * BITFIELD_DELTA_Y);

            // add plots
            for (int iSignalIdx=0; iSignalIdx < iNumSignal; iSignalIdx++) {
                addSignalToPlot(iSignalIdx, qvVect, qvTime, dMaxYAxis, figure->customPlot());
            }

            // set axes ranges, so we see all data:
            dMinXAxis = *std::min_element(qvTime.constBegin(), qvTime.constEnd());
            dMaxXAxis = *std::max_element(qvTime.constBegin(), qvTime.constEnd());

        }
    }

    figure->customPlot()->xAxis->setRange(dMinXAxis-1,dMaxXAxis+1);
    figure->customPlot()->yAxis->setRange(dMinYAxis, dMaxYAxis); // Y axis range
    figure->customPlot()->setInteractions(QCP::iSelectLegend | QCP::iRangeDrag | QCP::iRangeZoom);

    // give the axes some labels:
    figure->customPlot()->xAxis->setLabel("t [s]");
    QSharedPointer<QCPAxisTickerDateTime> dateTicker(new QCPAxisTickerDateTime);
    dateTicker->setDateTimeFormat("hh\rmm:ss\nzzz");
    dateTicker->setDateTimeSpec(Qt::UTC);
    figure->customPlot()->xAxis->setTicker(dateTicker);
    figure->customPlot()->yAxis->setLabel("y");

    return (ulMaxLi > 0);
}

void CDecorator::currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    QCPGraph *graph;

    if (previous) {
        graph = ((LegendItem *)previous->listWidget()->itemWidget(previous))->plottable();
        if (graph) {
            QPen qpGraphPen = graph->pen();
            qpGraphPen.setStyle(Qt::SolidLine);
            qpGraphPen.setWidth(2);
            graph->setPen(qpGraphPen);
            ((LegendItem *)previous->listWidget()->itemWidget(previous))->setAsCurrent(false);
        }
    }

    if (current) {
        graph = ((LegendItem *)current->listWidget()->itemWidget(current))->plottable();
        if (graph) {
            QPen qpGraphPen = graph->pen ();
            qpGraphPen.setStyle(Qt::DotLine);
            qpGraphPen.setWidth(4);
            graph->setPen(qpGraphPen);
            graph->parentPlot()->replot();
            ((LegendItem *)current->listWidget()->itemWidget(current))->setAsCurrent(true);
        }
    }
}

void CDecorator::itemSelectionChanged()
{
    QListWidgetItem *item;
    QList<QListWidgetItem *> selItems = lswLegend->selectedItems();
    foreach(item, selItems) {
        ;
    }
}
