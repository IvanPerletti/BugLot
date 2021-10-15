#ifndef QLEGENDWIDGETITEM_H
#define QLEGENDWIDGETITEM_H

#include <QListWidgetItem>
#include "qcustomplot.h"

class QLegendWidgetItem : public QListWidgetItem
{
public:
    QLegendWidgetItem(QCPGraph *, QString qStrLegend, QListWidget *parent = nullptr, int type = QListWidgetItem::UserType);
    ~QLegendWidgetItem() { graph = nullptr; }

    QCPGraph *plottable(void) { return graph; }
private :
    QCPGraph *graph;
};

#endif // QLEGENDWIDGETITEM_H
