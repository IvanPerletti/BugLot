#ifndef ZOOMPLOT_H
#define ZOOMPLOT_H

#include <QDialog>
#include "mainwindow.h"
namespace Ui {
class ZoomPlot;
}

class ZoomPlot : public QDialog
{
    Q_OBJECT

public:
    explicit ZoomPlot(QWidget *parent = 0);
    ~ZoomPlot();

private:
    Ui::ZoomPlot *ui;
};

#endif // ZOOMPLOT_H
