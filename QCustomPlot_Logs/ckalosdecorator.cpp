#include "ckalosdecorator.h"

CKalosDecorator::CKalosDecorator(QCustomPlot *customPlot, QFile *file, CVariablesToPlot *plotVarsList)
{
    VecPlotList = plotVarsList;
    buildGraph(customPlot, file);
}

void CKalosDecorator::buildGraph(QCustomPlot *customPlot, QFile *file)
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
            int iVal = numStr.toInt(&bCheck);
            if( !bCheck ){
                continue;
            }
            else {
                tempVector.push_back(iVal);
            }
        }
        qvMyVect.push_back(tempVector);
        //  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .
    }

    QVector<QString> LegendList = VecPlotList->VarList;
    LegendList.insert(LegendList.begin(),1, "Time: ");      // Add time to variable labels

    const int iSzVet = qvMyVect.size(); // array Size
    const int iNumElem = qvMyVect[0].size(); // num of plots
    QVector<double> qvTime; // time array
    QVector<double> qvDataArranged; // data array
    QVector<double> qvMinData;
    QVector<double> qvMaxData;

    qvDataArranged.resize(iSzVet); // resize optimze time with memory alloc
    qvTime.resize(iSzVet); // resize optimze time with memory alloc
    qvMinData.resize(iNumElem);
    qvMaxData.resize(iNumElem);

    for (int jj=0; jj<iSzVet; jj++){
        qvTime[jj] = qvMyVect[jj][0]/1000.0 ;
    }

    for (int iDataIdx=1; iDataIdx<iNumElem; iDataIdx++)
    {	// OBS:  index move from 1: data(0,:) are time values
        for ( int jj=0; jj<iSzVet; jj++ ){
            qvDataArranged[jj] = qvMyVect[jj][iDataIdx];
        }
        qvMinData.push_back(*std::min_element(qvDataArranged.constBegin(), qvDataArranged.constEnd()));
        qvMaxData.push_back(*std::max_element(qvDataArranged.constBegin(), qvDataArranged.constEnd()));
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
    dMinXAxis = *std::min_element(qvDataArranged.constBegin(), qvDataArranged.constEnd());
    dMaxXAxis = *std::max_element(qvDataArranged.constBegin(), qvDataArranged.constEnd());
    customPlot->yAxis->setRange(dMinXAxis,dMaxXAxis); // Y axis range

    customPlot->setInteractions(QCP::iSelectLegend);


}
