#ifndef CDECORATOR_H
#define CDECORATOR_H

#include <QDebug>
#include <QDesktopWidget>
#include <QScreen>
#include <QMessageBox>
#include <QMetaEnum>
#include <QApplication>
#include <QFileDialog>
#include "../../qcustomplot.h"
#include "cparentdecorator.h"

class CDecorator: public CParentDecorator
{
	public:
    CDecorator(QCustomPlot *customPlot, QFile *file);
    void buildGraph(QCustomPlot *customPlot, QFile *file);
	private:
	QRect qrAxisDim;
};

#endif // CDECORATOR_H
