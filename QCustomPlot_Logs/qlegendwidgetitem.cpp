#include "qlegendwidgetitem.h"

QLegendWidgetItem::QLegendWidgetItem(QCPGraph *graph, QString qStrLegend, QListWidget *parent, int type) :
                        QListWidgetItem(qStrLegend, parent, type), graph(nullptr)
{
    this->graph = graph;
}
