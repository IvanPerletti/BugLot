#ifndef CKALOSDECORATOR_H
#define CKALOSDECORATOR_H

#include <QDebug>
#include <QDesktopWidget>
#include <QScreen>
#include <QMessageBox>
#include <QMetaEnum>
#include <QApplication>
#include <QFileDialog>
#include "../../qcustomplot.h"
#include "cparentdecorator.h"

class CKalosDecorator: public CParentDecorator
{
public:
    CKalosDecorator(QCustomPlot *customPlot, QFile *file);
    void buildGraph(QCustomPlot *customPlot, QFile *file);
};

#endif // CKALOSDECORATOR_H
