#ifndef SWITCHCONTROLBOX_H
#define SWITCHCONTROLBOX_H

#include <QGroupBox>
#include <QGridLayout>
#include "controlonoff.h"

class switchControlBox : public QGroupBox
{
    Q_OBJECT
public:
    switchControlBox();
    ~switchControlBox();
public slots:
    bool eventFilter(QObject *,QEvent *);                   //QObject的事件监视函数
private:
    ControlOnOff *controlOnOff1;
    ControlOnOff *controlOnOff2;
    ControlOnOff *controlOnOff3;
    ControlOnOff *controlOnOff4;
    ControlOnOff *controlOnOff5;
    ControlOnOff *controlOnOff6;

    QGridLayout *gridLayout;
};

#endif // SWITCHCONTROLBOX_H
