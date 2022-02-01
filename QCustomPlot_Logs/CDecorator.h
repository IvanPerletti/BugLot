#ifndef CDECORATOR_H
#define CDECORATOR_H
#include <QDesktopWidget>
#include <QScreen>
#include <QMessageBox>
#include <QMetaEnum>
#include <QApplication>
#include <QFileDialog>
#include <QElapsedTimer>
#include "qcustomplot.h"
#include "legenditem.h"
#include "figurewidget.h"

class CDecorator : public QObject
{
    Q_OBJECT

public:
	CDecorator();
    void cleanGraph(FigureWidget *figure);
    bool buildGraph(FigureWidget *figure, QStringList files);

private:

    QStringList legendList;
    QStringList typeList;
    QListWidget *lswLegend;

    void addSignalToPlot(int iSignalIdx, QVector<QVector<double>> qvVect, QVector<double> qvTime, double dMaxYAxis, QCustomPlot *customPlot);
    void addGraph(QPen pen, QVector<double> qvDataArranged, QVector<double> qvTime, QString qStrLegend, QString qStrFactor, QCustomPlot *customPlot);

private slots:
    void currentItemChanged(QListWidgetItem *, QListWidgetItem *);
    void itemSelectionChanged();

};
extern CDecorator cDecorator;
#endif // CDECORATOR_H
