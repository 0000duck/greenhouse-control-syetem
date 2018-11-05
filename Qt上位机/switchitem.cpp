#include "switchitem.h"
#include "server.h"
#include <QMouseEvent>
#include <QDebug>


SwitchItem::SwitchItem( )
{
    this->setFont(QFont("Microsoft Yahei", 15));
    gridLayout=new QGridLayout();

    controlOnOff1=new mySwitchButton( );
    controlOnOff2=new mySwitchButton( );
    controlOnOff3=new mySwitchButton( );
    controlOnOff4=new mySwitchButton( );
    controlOnOff5=new mySwitchButton( );
    controlOnOff6=new mySwitchButton( );

    controlOnOff1->SetCheck(false);
    controlOnOff2->SetCheck(false);
    controlOnOff3->SetCheck(false);
    controlOnOff4->SetCheck(false);
    controlOnOff5->SetCheck(false);;
    controlOnOff6->SetCheck(false);
    /*
    controlOnOff1Label=new QLabel(tr("1号控制回路风扇"));
    controlOnOff2Label=new QLabel(tr("2号控制回路空调"));
    controlOnOff3Label=new QLabel(tr("3号控制回路电灯"));
    controlOnOff4Label=new QLabel(tr("4号控制回路台式机"));
    controlOnOff5Label=new QLabel(tr("5号控制回路增氧泵"));
    controlOnOff6Label=new QLabel(tr("6号控制回路电视机"));
    */
    controlOnOff1Label=new QLabel(tr("1号控制回路路灯"));
    controlOnOff2Label=new QLabel(tr("2号控制回路路灯"));
    controlOnOff3Label=new QLabel(tr("3号控制回路路灯"));
    controlOnOff4Label=new QLabel(tr("4号控制回路路灯"));
    controlOnOff5Label=new QLabel(tr("5号控制回路风扇"));
    controlOnOff6Label=new QLabel(tr("6号控制回路空调"));
    setLabelStyleSheet();
    controlOnOff1Label->setFixedSize(170,30);
    controlOnOff2Label->setFixedSize(170,30);
    controlOnOff3Label->setFixedSize(170,30);
    controlOnOff4Label->setFixedSize(170,30);
    controlOnOff5Label->setFixedSize(170,30);
    controlOnOff6Label->setFixedSize(170,30);

    controlOnOff1Label->setAlignment(Qt::AlignCenter);
    controlOnOff2Label->setAlignment(Qt::AlignCenter);
    controlOnOff3Label->setAlignment(Qt::AlignCenter);
    controlOnOff4Label->setAlignment(Qt::AlignCenter);
    controlOnOff5Label->setAlignment(Qt::AlignCenter);
    controlOnOff6Label->setAlignment(Qt::AlignCenter);

    controlOnOff1Label->setFont(QFont("Microsoft Yahei", 15));
    controlOnOff2Label->setFont(QFont("Microsoft Yahei", 15));
    controlOnOff3Label->setFont(QFont("Microsoft Yahei", 15));
    controlOnOff4Label->setFont(QFont("Microsoft Yahei", 15));
    controlOnOff5Label->setFont(QFont("Microsoft Yahei", 15));
    controlOnOff6Label->setFont(QFont("Microsoft Yahei", 15));


    gridLayout->addWidget(controlOnOff1Label,0,0,Qt::AlignRight);
    gridLayout->addWidget(controlOnOff2Label,1,0,Qt::AlignRight);
    gridLayout->addWidget(controlOnOff3Label,2,0,Qt::AlignRight);
    gridLayout->addWidget(controlOnOff4Label,3,0,Qt::AlignRight);
    gridLayout->addWidget(controlOnOff5Label,4,0,Qt::AlignRight);
    gridLayout->addWidget(controlOnOff6Label,5,0,Qt::AlignRight);

    gridLayout->addWidget(controlOnOff1,0,1,Qt::AlignLeft);
    gridLayout->addWidget(controlOnOff2,1,1,Qt::AlignLeft);
    gridLayout->addWidget(controlOnOff3,2,1,Qt::AlignLeft);
    gridLayout->addWidget(controlOnOff4,3,1,Qt::AlignLeft);
    gridLayout->addWidget(controlOnOff5,4,1,Qt::AlignLeft);
    gridLayout->addWidget(controlOnOff6,5,1,Qt::AlignLeft);


    gridLayout->setSpacing(15);
    gridLayout->setMargin(20);

    this->setTitle(tr("继电器控制区"));

    this->setLayout(gridLayout);
    this->setStyleSheet("background-color:#f8ff70;"
                            "border-style:none;"
                            //"border-style: outset;"
                            "border-width: 2px;"
                            "border-radius: 10px;"
                            "border-color: beige;");

    controlOnOff1->installEventFilter(this);
    controlOnOff2->installEventFilter(this);
    controlOnOff3->installEventFilter(this);
    controlOnOff4->installEventFilter(this);
    controlOnOff5->installEventFilter(this);
    controlOnOff6->installEventFilter(this);
}

SwitchItem::~SwitchItem()
{
    delete controlOnOff1;
    delete controlOnOff2;
    delete controlOnOff3;
    delete controlOnOff4;
    delete controlOnOff5;
    delete controlOnOff6;
    delete controlOnOff1Label;
    delete controlOnOff2Label;
    delete controlOnOff3Label;
    delete controlOnOff4Label;
    delete controlOnOff5Label;
    delete controlOnOff6Label;
}

void SwitchItem::setLabelStyleSheet()
{
    QString string;
    string.append("border-style:none;");
    string.append("background-color:#B0C4DE;");
    string.append( "border-width: 2px;");
    string.append("border-radius: 10px;");
    string.append(  "border-color: #006400;");

    controlOnOff1Label->setStyleSheet(string);
    controlOnOff1Label->setStyleSheet(string);
    controlOnOff2Label->setStyleSheet(string);
    controlOnOff3Label->setStyleSheet(string);
    controlOnOff4Label->setStyleSheet(string);
    controlOnOff5Label->setStyleSheet(string);
    controlOnOff6Label->setStyleSheet(string);
}

bool SwitchItem::eventFilter(QObject *watched, QEvent *event)
{
    if(watched==controlOnOff1){
        /*判断事件发生的的类型*/
        if(event->type()==QEvent::MouseButtonPress){
            /*将事件转化为鼠标事件*/
            QMouseEvent *mouseEvent=(QMouseEvent *)event;
            /*根据鼠标的按键类型分别显示*/
            if(mouseEvent->buttons()&Qt::LeftButton){
                if(!controlOnOff1->GetCheck())
                    sendMsgToAllclients(tr("turnonled1"));
                else
                    sendMsgToAllclients(tr("turnoffled1"));
                 qDebug()<<tr("controlOnOff1鼠标按下")<<endl;
                 qDebug()<<((controlOnOff1->GetCheck() ==true)?"checked":"notchecked")<<endl;
            }
         }
    }
    else if(watched==controlOnOff2){
        /*判断事件发生的的类型*/
        if(event->type()==QEvent::MouseButtonPress){
            /*将事件转化为鼠标事件*/
            QMouseEvent *mouseEvent=(QMouseEvent *)event;
            /*根据鼠标的按键类型分别显示*/
            if(mouseEvent->buttons()&Qt::LeftButton){
                if(!controlOnOff2->GetCheck())
                    sendMsgToAllclients(tr("turnonled2"));
                else
                    sendMsgToAllclients(tr("turnoffled2"));
                 qDebug()<<tr("controlOnOff2鼠标按下")<<endl;
                 //theClicked_OntrolOnOff_Id=controlOnOff2->getId();
            }
         }
    }
    else if(watched==controlOnOff3){
        /*判断事件发生的的类型*/
        if(event->type()==QEvent::MouseButtonPress){
            /*将事件转化为鼠标事件*/
            QMouseEvent *mouseEvent=(QMouseEvent *)event;
            /*根据鼠标的按键类型分别显示*/
            if(mouseEvent->buttons()&Qt::LeftButton){
                if(!controlOnOff3->GetCheck())
                     sendMsgToAllclients(tr("turnonled3"));
                else
                     sendMsgToAllclients(tr("turnoffled3"));
                 qDebug()<<tr("controlOnOff3鼠标按下")<<endl;
                 //theClicked_OntrolOnOff_Id=controlOnOff3->getId();
            }
         }
    }
    else if(watched==controlOnOff4){
        /*判断事件发生的的类型*/
        if(event->type()==QEvent::MouseButtonPress){
            /*将事件转化为鼠标事件*/
            QMouseEvent *mouseEvent=(QMouseEvent *)event;
            /*根据鼠标的按键类型分别显示*/
            if(mouseEvent->buttons()&Qt::LeftButton){
                if(!controlOnOff4->GetCheck())
                     sendMsgToAllclients(tr("turnonled4"));
                else
                     sendMsgToAllclients(tr("turnoffled4"));
                 qDebug()<<tr("controlOnOff4鼠标按下")<<endl;
                 //theClicked_OntrolOnOff_Id=controlOnOff4->getId();
            }
         }
    }
    else if(watched==controlOnOff5){
        /*判断事件发生的的类型*/
        if(event->type()==QEvent::MouseButtonPress){
            /*将事件转化为鼠标事件*/
            QMouseEvent *mouseEvent=(QMouseEvent *)event;
            /*根据鼠标的按键类型分别显示*/
            if(mouseEvent->buttons()&Qt::LeftButton){
                if(!controlOnOff5->GetCheck())
                    sendMsgToAllclients(tr("turnonled5"));
                else
                    sendMsgToAllclients(tr("turnoffled5"));
                qDebug()<<tr("controlOnOff5鼠标按下")<<endl;
            }
         }
    }
    else if(watched==controlOnOff6){
        /*判断事件发生的的类型*/
        if(event->type()==QEvent::MouseButtonPress){
            /*将事件转化为鼠标事件*/
            QMouseEvent *mouseEvent=(QMouseEvent *)event;
            /*根据鼠标的按键类型分别显示*/
            if(mouseEvent->buttons()&Qt::LeftButton){
                if(!controlOnOff6->GetCheck())
                    sendMsgToAllclients(tr("turnonled6"));
                else
                    sendMsgToAllclients(tr("turnoffled6"));
                 qDebug()<<tr("controlOnOff6鼠标按下")<<endl;
                // theClicked_OntrolOnOff_Id=controlOnOff6->getId();
            }
         }
    }

    return QWidget::eventFilter(watched,event);
}

void SwitchItem::sendMsgToAllclients(const QString &msg)
{
    int length=msg.length();
    for(int i=0;i<tcpClientSocketList.count();i++){
        QTcpSocket *item=tcpClientSocketList.at(i);
        if(item->write(msg.toLatin1(),length)!=length){
            continue;
        }
    }
}
