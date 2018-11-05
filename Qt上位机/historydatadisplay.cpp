#include "historydatadisplay.h"
#include <QGridLayout>
#include <QTimer>
#include <QDebug>

HistoryDataDisplay::HistoryDataDisplay(QWidget *parent) : QWidget(parent)
{

    this->setStyleSheet(
                  "border-style:none;"
                   //"border-style: outset;"
                  "border-width: 2px;"
                  "border-radius: 1px;"
                 "border-color: #0000FF;"
                 //"background-color:#1c5612;"
                                    );
    tableWidth=(this->width()-30)/2;
    tableHight=(this->height()-30)/2;

    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(timerUpDate()));
    timer->start(2000);

    temperatureTableWidget=new RealTimeCurveQChartWidget("#aa55ff",tr("温度曲线(T/℃)"),100,tr("temperature") );
    humidityTableWidget=new RealTimeCurveQChartWidget("#2613ff",tr("湿度曲线(H/%RH)") ,100,tr("humidity"));
    illumilationTableWidget=new RealTimeCurveQChartWidget("#ff5507",tr("光照强度曲线(I/lx)"),3000,tr("illumination"));
    carbonTableWidget=new RealTimeCurveQChartWidget("#00557f",tr("二氧化碳浓度曲线(C/ppm)"),2000,tr("carbon"));

    temperatureTableWidget->resize(tableWidth,tableHight);
    humidityTableWidget->resize(tableWidth,tableHight);
    illumilationTableWidget->resize(tableWidth,tableHight);
    carbonTableWidget->resize(tableWidth,tableHight);

    QGridLayout *mainLayout=new QGridLayout();
    mainLayout->addWidget(temperatureTableWidget,0,0);
    mainLayout->addWidget(humidityTableWidget,0,1);
    mainLayout->addWidget(illumilationTableWidget,1,0);
    mainLayout->addWidget(carbonTableWidget,1,1);
    mainLayout->setMargin(10);
    mainLayout->setSpacing(10);

    this->setLayout(mainLayout);
}

HistoryDataDisplay::~HistoryDataDisplay()
{
    delete  temperatureTableWidget;
    delete  illumilationTableWidget;
    delete  carbonTableWidget;
    delete  humidityTableWidget;
}
/*
void HistoryDataDisplay::getData(int id,double value)
{
    switch (id) {
    case 1:
        temperatureTableWidget->dataReceived(value);
        qDebug()<<"receive data  temperatureTableWidget"<<endl;
        break;
    case 2:
        illumilationTableWidget->dataReceived(value);
        qDebug()<<"receive data  illumilationTableWidget"<<endl;
        break;
    case 3:
        carbonTableWidget->dataReceived(value);
        qDebug()<<"receive data  carbonTableWidget"<<endl;
        break;
    case 4:
        humidityTableWidget->dataReceived(value);
         qDebug()<<"receive data  carbonTableWidget"<<endl;
        break;
    default:
        qDebug()<<"receive data error!"<<endl;
        break;
    }

}*/
/*
void HistoryDataDisplay::paintEvent(QPaintEvent *event)
{
    // temperatureTableWidget->update();
    // illumilationTableWidget->update();
    // carbonTableWidget->update();
    // humidityTableWidget->update();

    // temperatureTableWidget->repaint();
     //illumilationTableWidget->repaint();
     //carbonTableWidget->repaint();
     //humidityTableWidget->repaint();
}
*/

void HistoryDataDisplay::timerUpDate()
{
    this->update();
}
