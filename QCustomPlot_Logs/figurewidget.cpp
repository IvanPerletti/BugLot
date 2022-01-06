#include "figurewidget.h"
#include "ui_figurewidget.h"

FigureWidget::FigureWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FigureWidget)
{
    ui->setupUi(this);
}

FigureWidget::~FigureWidget()
{
    delete ui;
}

QCustomPlot *FigureWidget::customPlot(void)
{
    return ui->customPlot;
}

QListWidget *FigureWidget::lswLegend(void)
{
    return ui->lswLegend;
}
