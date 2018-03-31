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

class CDecorator
{
	public:
	CDecorator();
	void buildGraph(QCustomPlot *customPlot, QFile *file);
	private:
	QRect qrAxisDim;
};
extern CDecorator cDecorator;
#endif // CDECORATOR_H
