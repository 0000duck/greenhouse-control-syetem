#include "realdataDisplay.h"
#include <QGridLayout>
#include <QTimer>

RealDataDisplay::RealDataDisplay(QWidget *parent) : QWidget(parent),
    carbon(400),humidity(50),illumination(2000),temperature(25.0)
{
     m_rowCount=0;
     lableWidth=(this->width()-30)/2;
     labelHight=(this->height()-30)/2;

     this->setStyleSheet(
                   //"border-style:none;"
                    //"border-style: outset;"
                    "border-style:solid;"
                   "border-width: 2px;"
                   "border-radius: 10px;"
                  "border-color: #FFA07A;");


     QTimer *timer = new QTimer(this);
     connect(timer,SIGNAL(timeout()),this,SLOT(timerUpDate()));
     timer->start(2000);

     carbonLabel=new TextLabel(":/images/realData/Carbon.jpg");
     carbonLabel->setUnit("ppm");
     carbonLabel->setPrefix(tr("当前CO2浓度为:"));
     carbonLabel->setText(carbon);
     carbonLabel->resize(lableWidth,labelHight);

     illuminationLabel=new TextLabel(":/images/realData/sun.png");
     illuminationLabel->setUnit("lx");
     illuminationLabel->setPrefix(tr("当前光照强度为:"));
     illuminationLabel->setText(illumination);
     illuminationLabel->resize(lableWidth,labelHight);

     temperatureLabel=new TextLabel(":/images/realData/temperature.png");
     temperatureLabel->setUnit("℃");
     temperatureLabel->setPrefix(tr("当前温度为:"));
     temperatureLabel->setText(temperature);
     temperatureLabel->resize(lableWidth,labelHight);

     humidityLabel=new TextLabel(":/images/realData/water.png");
     humidityLabel->setUnit("%RH");
     humidityLabel->setPrefix(tr("当前湿度为:"));
     humidityLabel->setText(humidity);
     humidityLabel->resize(lableWidth,labelHight);

     QGridLayout *mainLayout=new QGridLayout();
     mainLayout->addWidget(temperatureLabel,0,0);
     mainLayout->addWidget(humidityLabel,0,1);
     mainLayout->addWidget(illuminationLabel,1,0);
     mainLayout->addWidget(carbonLabel,1,1);
     mainLayout->setMargin(10);
     mainLayout->setSpacing(10);

     this->setLayout(mainLayout);

}

void RealDataDisplay::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    carbonLabel->setText(carbon);
    carbonLabel->show();
    illuminationLabel->setText(illumination);
    illuminationLabel->show();
    humidityLabel->setText(humidity);
    humidityLabel->show();
    temperatureLabel->setText(temperature);
    temperatureLabel->show();
}

int RealDataDisplay::getCarbon() const
{
    return carbon;
}

void RealDataDisplay::setCarbon(int value)
{
    carbon = value;
}

int RealDataDisplay::getHumidity() const
{
    return humidity;
}

void RealDataDisplay::setHumidity(int value)
{
    humidity = value;
}

int RealDataDisplay::getIllumination() const
{
    return illumination;
}

void RealDataDisplay::setIllumination(int value)
{
    illumination = value;
}

float RealDataDisplay::getTemperature() const
{
    return temperature;
}

void RealDataDisplay::setTemperature(float value)
{
    temperature = value;
}

void RealDataDisplay::timerUpDate()
{
    bool ok;
    //创建model,进行数据库操作
    model=new QSqlTableModel(this);
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);

    //设置table为相应表
    model->setTable(tr("temperature"));
    model->select();
    m_rowCount =model->rowCount()-1;

    if(m_rowCount>=0)
    {
        QSqlRecord record=model->record(m_rowCount);
        temperature=record.value(1).toFloat(&ok);
    }

    //设置table为相应表
    model->setTable(tr("humidity"));
    model->select();
    m_rowCount =model->rowCount()-1;

    if(m_rowCount>=0)
    {
        QSqlRecord record=model->record(m_rowCount);
        humidity=record.value(1).toFloat(&ok);
    }

    //设置table为相应表
    model->setTable(tr("illumination"));
    model->select();
    m_rowCount =model->rowCount()-1;

    if(m_rowCount>=0)
    {
        QSqlRecord record=model->record(m_rowCount);
        illumination=record.value(1).toInt(&ok);
    }

    //设置table为相应表
    model->setTable(tr("carbon"));
    model->select();
    m_rowCount =model->rowCount()-1;

    if(m_rowCount>=0)
    {
        QSqlRecord record=model->record(m_rowCount);
        carbon=record.value(1).toInt(&ok);
    }
/*    qDebug()<<"RealDataDisplay更新数据"<<endl;
    qDebug()<<tr("carbon:%1").arg(carbon)<<"ppm"<<endl;
    qDebug()<<tr("illumination:%1").arg(illumination)<< "LX"<<endl;
    qDebug()<<tr("humidity:%1").arg(humidity)<<"%RH"<<endl;
    qDebug()<<tr("temperature:%1").arg(temperature)<<"℃"<<endl;
*/
    this->update();
}
