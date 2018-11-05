#ifndef SWITCHITEM_H
#define SWITCHITEM_H

#include "myswitchbutton.h"
#include "server.h"
#include <QGridLayout>
#include <QLabel>
#include <QGroupBox>

//extern bool controlOnOff1isOn;
//extern bool controlOnOff2isOn;
//extern bool controlOnOff3isOn;
//extern bool controlOnOff4isOn;
//extern bool controlOnOff5isOn;
//extern bool controlOnOff6isOn;

class SwitchItem : public QGroupBox
{
    Q_OBJECT
public:
    explicit SwitchItem( );
    ~SwitchItem();
    void setLabelStyleSheet();
    void sendMsgToAllclients(const QString &msg);
signals:

public slots:
     bool eventFilter(QObject *,QEvent *);                   //QObject的事件监视函数
private:
    QLabel *controlOnOff1Label;
    QLabel *controlOnOff2Label;
    QLabel *controlOnOff3Label;
    QLabel *controlOnOff4Label;
    QLabel *controlOnOff5Label;
    QLabel *controlOnOff6Label;

    mySwitchButton *controlOnOff1;
    mySwitchButton *controlOnOff2;
    mySwitchButton *controlOnOff3;
    mySwitchButton *controlOnOff4;
    mySwitchButton *controlOnOff5;
    mySwitchButton *controlOnOff6;
    QGridLayout *gridLayout;

};

#endif // SWITCHITEM_H
