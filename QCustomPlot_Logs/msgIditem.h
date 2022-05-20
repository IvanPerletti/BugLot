#ifndef MSGIDITEM_H
#define MSGIDITEM_H

#include <QWidget>
#include <QPushButton>

namespace Ui {
class MsgIdItem;
}

class MsgIdItem : public QWidget
{
    Q_OBJECT

public:
    explicit MsgIdItem(QWidget *parent = nullptr);
    ~MsgIdItem();

    QPushButton *pushButton(void);
    void setText(QString text);
    void setEnabled(bool en);

private:
    Ui::MsgIdItem *ui;
};

#endif // MSGIDITEM_H
