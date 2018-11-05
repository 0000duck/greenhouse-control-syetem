#include "diagremove.h"
#include "ui_diagremove.h"

DiagRemove::DiagRemove(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DiagRemove)
{
    ui->setupUi(this);

    connect(ui->btnOk,SIGNAL(clicked()),this,SLOT(slotOk()));
    connect(ui->btnCancle,SIGNAL(clicked()),this,SLOT(slotCancle()));

}

void DiagRemove::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    //QStyleOption opt;
    //opt.init(this);
    //QPainter p(this);
    //style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void DiagRemove::slotOk()
{
    emit sigBtn(true);
    this->close();
}

void DiagRemove::slotCancle()
{
    emit sigBtn(false);
    this->close();
}

DiagRemove::~DiagRemove()
{
    delete ui;
}
