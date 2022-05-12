#include "figurewidget.h"
#include "ui_figurewidget.h"
#include "legenditem.h"

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

void FigureWidget::on_pbnHide_clicked()
{
    QListWidgetItem *item;

    foreach(item, ui->lswLegend->selectedItems()) {
        QCPGraph *graph = ((LegendItem *)ui->lswLegend->itemWidget(item))->plottable();

        graph->setVisible(false);
    }
    ui->customPlot->replot();
}

void FigureWidget::on_pbnShow_clicked()
{
    QListWidgetItem *item;

    foreach(item, ui->lswLegend->selectedItems()) {
        QCPGraph *graph = ((LegendItem *)ui->lswLegend->itemWidget(item))->plottable();

        graph->setVisible(true);
    }
    ui->customPlot->replot();
}

void FigureWidget::on_pbnReset_clicked()
{
    for (int i = 0; i<ui->lswLegend->count(); i++) {
        QListWidgetItem *item = ui->lswLegend->item(i);
        QCPGraph *graph = ((LegendItem *)ui->lswLegend->itemWidget(item))->plottable();

        graph->setVisible(true);
    }
    ui->customPlot->replot();
}

