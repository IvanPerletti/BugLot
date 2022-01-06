#ifndef FIGUREWIDGET_H
#define FIGUREWIDGET_H

#include <QWidget>
#include "qcustomplot.h"

namespace Ui {
class FigureWidget;
}

class FigureWidget : public QWidget
{
    Q_OBJECT

public:
    explicit FigureWidget(QWidget *parent = nullptr);
    ~FigureWidget();

    QCustomPlot *customPlot(void);
    QListWidget *lswLegend(void);

private:
    Ui::FigureWidget *ui;
};

#endif // FIGUREWIDGET_H
