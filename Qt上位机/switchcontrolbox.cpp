#include "switchcontrolbox.h"
#include <QDebug>
#include <QMouseEvent>

int theClicked_OntrolOnOff_Id=0;

switchControlBox::switchControlBox()
{
    gridLayout=new QGridLayout();

    controlOnOff1=new ControlOnOff(tr("1号控制回路风扇"),70,1);
    controlOnOff2=new ControlOnOff(tr("2号控制回路空调"),70,2);
    controlOnOff3=new ControlOnOff(tr("3号控制回路电灯"),70,3);
    controlOnOff4=new ControlOnOff(tr("4号控制回路台式机"),70,4);
    controlOnOff5=new ControlOnOff(tr("5号控制回路增氧泵"),70,5);
    controlOnOff6=new ControlOnOff(tr("6号控制回路电视机"),70,6);

    gridLayout->addWidget(controlOnOff1,0,0);
    gridLayout->addWidget(controlOnOff2,0,1);
    gridLayout->addWidget(controlOnOff3,0,2);
    gridLayout->addWidget(controlOnOff4,0,3);
    gridLayout->addWidget(controlOnOff5,0,4);
    gridLayout->addWidget(controlOnOff6,0,5);


    controlOnOff1->setFocus();
    controlOnOff2->setFocus();
    controlOnOff3->setFocus();
    controlOnOff4->setFocus();
    controlOnOff5->setFocus();
    controlOnOff6->setFocus();

    gridLayout->setSpacing(20);
    gridLayout->setMargin(40);

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

switchControlBox::~switchControlBox()
{
        delete controlOnOff1;
        delete controlOnOff2;
        delete controlOnOff3;
        delete controlOnOff4;
        delete controlOnOff5;
        delete controlOnOff6;
}

bool switchControlBox::eventFilter(QObject *watched, QEvent *event)
{
    if(watched==controlOnOff1){
        /*判断事件发生的的类型*/
        if(event->type()==QEvent::MouseButtonPress){
            /*将事件转化为鼠标事件*/
            QMouseEvent *mouseEvent=(QMouseEvent *)event;
            /*根据鼠标的按键类型分别显示*/
            if(mouseEvent->buttons()&Qt::LeftButton){
                 qDebug()<<tr("controlOnOff1鼠标按下")<<endl;
                 theClicked_OntrolOnOff_Id=controlOnOff1->getId();
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
                 qDebug()<<tr("controlOnOff2鼠标按下")<<endl;
                 theClicked_OntrolOnOff_Id=controlOnOff2->getId();
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
                 qDebug()<<tr("controlOnOff3鼠标按下")<<endl;
                 theClicked_OntrolOnOff_Id=controlOnOff3->getId();
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
                 qDebug()<<tr("controlOnOff4鼠标按下")<<endl;
                 theClicked_OntrolOnOff_Id=controlOnOff4->getId();
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
                 qDebug()<<tr("controlOnOff5鼠标按下")<<endl;
                 theClicked_OntrolOnOff_Id=controlOnOff5->getId();
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
                 qDebug()<<tr("controlOnOff6鼠标按下")<<endl;
                 theClicked_OntrolOnOff_Id=controlOnOff6->getId();
            }
         }
    }

    return QWidget::eventFilter(watched,event);

}
