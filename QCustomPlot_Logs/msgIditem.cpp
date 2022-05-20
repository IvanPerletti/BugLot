#include "msgIditem.h"
#include "ui_msgIditem.h"

MsgIdItem::MsgIdItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MsgIdItem)
{
    ui->setupUi(this);
}

MsgIdItem::~MsgIdItem()
{
    delete ui;
}

QPushButton *MsgIdItem::pushButton(void)
{
    return ui->pushButton;
}
