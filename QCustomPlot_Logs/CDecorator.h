#ifndef CDECORATOR_H
#define CDECORATOR_H
#include <QDesktopWidget>
#include <QScreen>
#include <QMessageBox>
#include <QMetaEnum>
#include <QApplication>
#include <QFileDialog>
#include <QElapsedTimer>
#include "../../qcustomplot.h"
#include "qlegendwidgetitem.h"
#include "CrunchLog.h"

class CDecorator : public QObject
{
    Q_OBJECT

public:
	CDecorator();
	void cleanGraph(QCustomPlot *customPlot);
    bool buildGraph(QCustomPlot *customPlot, QListWidget *lswLegend, QFile *file);
    void showHideElements(void);

private:
    QVector<double> qvTime;
    QVector <QVector <double> > qvVect;
    QStringList legendList;
    QStringList typeList;
    QMap<QString, bool> markedItemMap;
    QCustomPlot *customPlot;
    QListWidget *lswLegend;

    QList <QListWidgetItem *> actSelectedItems;

    void addSignalToPlot(int iSignalIdx, double dMaxYAxis, QCustomPlot *customPlot);
    void addGraph(QPen pen, QVector<double> qvDataArranged, QVector<double> qvTime, QString qStrLegend, QCustomPlot *customPlot);

private slots:
    void currentItemChanged(QListWidgetItem *, QListWidgetItem *);
    void itemSelectionChanged();

};
extern CDecorator cDecorator;
#endif // CDECORATOR_H
