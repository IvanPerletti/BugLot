#include "legenditem.h"
#include "ui_legenditem.h"

LegendItem::LegendItem(QCPGraph *graph,
                       const QString &strName,
                       const QString &strFactor,
                       QColor color,
                       QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LegendItem)
{
    ui->setupUi(this);
    ui->lblName->setText(strName);
    ui->lblFactor->setText(strFactor);
    ui->hlnPlot->setStyleSheet(QString::asprintf("background-color: rgb(%d,%d,%d)", color.red(), color.green(), color.blue()));

    this->graph = graph;
}

void LegendItem::setAsCurrent(bool current)
{
    if (current)
        ui->hlnPlot->setLineWidth(10);
    else
        ui->hlnPlot->setLineWidth(6);
}

LegendItem::~LegendItem()
{
    delete ui;
}
