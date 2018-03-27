#include "zoomplot.h"
#include "ui_zoomplot.h"

ZoomPlot::ZoomPlot(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ZoomPlot)
{
    ui->setupUi(this);
}

ZoomPlot::~ZoomPlot()
{
    delete ui;
}
