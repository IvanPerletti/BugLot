#ifndef CDECORATOR_H
#define CDECORATOR_H
#include <QDesktopWidget>
#include <QScreen>
#include <QMessageBox>
#include <QMetaEnum>
#include <QApplication>
#include <QFileDialog>
#include "../../qcustomplot.h"
#include "CrunchLog.h"

class CDecorator
{
public:
	CDecorator();
	void cleanGraph(QCustomPlot *customPlot);
    bool buildGraph(QCustomPlot *customPlot, QFile *file);

private:
	QRect qrAxisDim;
    QStringList legendList;
    QStringList typeList;
    void addSignalToPlot(QVector<double> qvTime,
							QString qStrLegend,
                            QString qStrType,
                            QVector <QVector <double> > qvMyVect,
                            QVector<double> &qvDataArranged,
                            int iDataIdx, int iNumElem,
							QCustomPlot *customPlot);
    void addGraph(QPen pen, QVector<double> qvDataArranged, QVector<double> qvTime, QString qStrLegend, QCustomPlot *customPlot);
};
extern CDecorator cDecorator;
#endif // CDECORATOR_H
