#include "legenditem.h"
#include "ui_legenditem.h"

LegendItem::LegendItem(QCPGraph *graph,
                       const QString &strName,
                       const QString &strFactor,
                       QColor color,
                       QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LegendItem),
    m_Color(color)
{
    ui->setupUi(this);
    ui->lblName->setText(strName);
    ui->lblFactor->setText(strFactor);
    ui->hlnPlot->setStyleSheet(QString::asprintf("background-color: rgb(%d,%d,%d); border: 5px solid;", m_Color.red(), m_Color.green(), m_Color.blue()));
    ui->lblFactor->setMinimumWidth(ui->lblFactor->sizeHint().width());
    ui->lblName->setMinimumWidth(ui->lblName->sizeHint().width());
    setAsCurrent(false);
    this->graph = graph;
}

void LegendItem::setAsCurrent(bool current)
{
    char u8aStrBg[] = "border: %dpx solid rgba(255,255,255, 255);border-bottom: %dpx solid rgba(255,255,255,255 );";
    QString strBgColor = QString::asprintf("background-color: rgb(%d,%d,%d);", m_Color.red(), m_Color.green(), m_Color.blue());
    if (current)
    {
        ui->hlnPlot->setStyleSheet(QString::asprintf( u8aStrBg, 0, 0) + strBgColor);
    }
    else
    {
        ui->hlnPlot->setStyleSheet(QString::asprintf( u8aStrBg, 3, 3) + strBgColor);
    }
}

LegendItem::~LegendItem()
{
    delete ui;
}
