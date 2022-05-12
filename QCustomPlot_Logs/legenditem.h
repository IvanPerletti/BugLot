#ifndef LEGENDITEM_H
#define LEGENDITEM_H

#include <QWidget>
#include "qcustomplot.h"

namespace Ui {
class LegendItem;
}

class LegendItem : public QWidget
{
    Q_OBJECT

public:
    explicit LegendItem(QCPGraph *, const QString &strName, const QString &strFactor, QColor color, QWidget *parent = nullptr);
    ~LegendItem();

    QCPGraph *plottable(void) { return graph; }
    void setAsCurrent(bool current);

private:
    Ui::LegendItem *ui;
    QColor m_Color;
    QCPGraph *graph;
};

#endif // LEGENDITEM_H
