#include "warningHandle.h"

WarningHandle::WarningHandle(QWidget *parent) : QWidget(parent)
{
        this->setFont(QFont("Microsoft Yahei",15));
        this->setStyleSheet("background-color:#f8ff70;"
                  "color: rgb(0, 170, 0);"
                  "border-style:none;"
                  "border-width: 2px;"
                  "border-radius: 10px;"
                 "border-color: beige;"
                        );

        realDataDisplay=new RealDataDisplay();

        carbonVBoxLayout=new QVBoxLayout();
        carbonLedIndicator=new QLedIndicator(this );
        /*  onColor1 =  QColor(0,255,0);
        onColor2 =  QColor(0,192,0);
        offColor1 = QColor(0,28,0);
        offColor2 = QColor(0,128,0);*/
        carbonLedIndicator->setOnColor1(QColor(255,0,0));
        carbonLedIndicator->setOnColor2(QColor(255,125,0));
        carbonLedIndicator->setOffColor1(QColor(0,255,0));
        carbonLedIndicator->setOnColor2(QColor(0,100,0));
        carbonLedIndicator->resize(200,200);

        carbonLabel=new QLabel(this);
        carbonLabel->setText("CO2浓度报警指示");
        carbonLabel->setTextFormat(Qt::RichText);//文本格式
        carbonLabel->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);//对齐方式
        carbonLabel->setAutoFillBackground(true);
        carbonLabel->setWordWrap(true);//自动换行
        carbonLabel->setTextFormat(Qt::RichText);//文本格式
        carbonLabel->setAlignment(Qt::AlignCenter);//对齐方式
        carbonLabel->setAutoFillBackground(true);
        carbonLabel->setStyleSheet(
                  "border-style:none;"
                  //"background-color: #708090;");
                    "background-color: #E0EEEE;");
        carbonLabel->setFont(QFont( "Courier New", 30, 75));
        carbonVBoxLayout->addWidget(carbonLabel);
        carbonVBoxLayout->addWidget(carbonLedIndicator);


        illuminationVBoxLayout=new QVBoxLayout();
        illuminationLedIndicator=new QLedIndicator(this );
        illuminationLedIndicator->setOnColor1(QColor(255,0,0));
        illuminationLedIndicator->setOnColor2(QColor(255,125,0));
        illuminationLedIndicator->setOffColor1(QColor(0,255,0));
        illuminationLedIndicator->setOnColor2(QColor(0,100,0));
        illuminationLedIndicator->resize(200,200);
        illuminationLabel=new QLabel(this);
        illuminationLabel->setText("光照强度报警指示");
        illuminationLabel->setTextFormat(Qt::RichText);//文本格式
        illuminationLabel->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);//对齐方式
        illuminationLabel->setAutoFillBackground(true);
        illuminationLabel->setWordWrap(true);//自动换行
        illuminationLabel->setTextFormat(Qt::RichText);//文本格式
        illuminationLabel->setAlignment(Qt::AlignCenter);//对齐方式
        illuminationLabel->setAutoFillBackground(true);
        illuminationLabel->setStyleSheet(
               "border-style:none;"
               "background-color: #CDB5CD;");
        illuminationLabel->setFont(QFont( "Courier New", 30, 75));
        illuminationVBoxLayout->addWidget(illuminationLabel);
        illuminationVBoxLayout->addWidget(illuminationLedIndicator);


        temperatureVBoxLayout=new QVBoxLayout();
        temperatureIndicator=new QLedIndicator(this );
        temperatureIndicator->setOnColor1(QColor(255,0,0));
        temperatureIndicator->setOnColor2(QColor(255,125,0));
        temperatureIndicator->setOffColor1(QColor(0,255,0));
        temperatureIndicator->setOnColor2(QColor(0,100,0));
        temperatureIndicator->resize(200,200);
        temperatureLabel=new QLabel(this);
        temperatureLabel->setText("温度报警指示");
        temperatureLabel->setTextFormat(Qt::RichText);//文本格式
        temperatureLabel->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);//对齐方式
        temperatureLabel->setAutoFillBackground(true);
        temperatureLabel->setWordWrap(true);//自动换行
        temperatureLabel->setTextFormat(Qt::RichText);//文本格式
        temperatureLabel->setAlignment(Qt::AlignCenter);//对齐方式
        temperatureLabel->setAutoFillBackground(true);
        temperatureLabel->setStyleSheet(
               "border-style:none;"
               "background-color: #FFA07A;");
        temperatureLabel->setFont(QFont( "Courier New", 30, 75));
        temperatureVBoxLayout->addWidget(temperatureLabel);
        temperatureVBoxLayout->addWidget(temperatureIndicator);


        humidityVBoxLayout=new QVBoxLayout();
        humidityLedIndicator=new QLedIndicator(this );
        humidityLedIndicator->setOnColor1(QColor(255,0,0));
        humidityLedIndicator->setOnColor2(QColor(255,125,0));
        humidityLedIndicator->setOffColor1(QColor(0,255,0));
        humidityLedIndicator->setOnColor2(QColor(0,100,0));
        humidityLedIndicator->resize(200,200);
        humidityLabel=new QLabel(this);
        humidityLabel->setText("湿度报警指示");
        humidityLabel->setTextFormat(Qt::RichText);//文本格式
        humidityLabel->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);//对齐方式
        humidityLabel->setAutoFillBackground(true);
        humidityLabel->setWordWrap(true);//自动换行
        humidityLabel->setTextFormat(Qt::RichText);//文本格式
        humidityLabel->setAlignment(Qt::AlignCenter);//对齐方式
        humidityLabel->setAutoFillBackground(true);
        humidityLabel->setStyleSheet(
               "border-style:none;"
               "background-color: #BDB76B;");
        humidityLabel->setFont(QFont( "Courier New", 30, 75));
        humidityVBoxLayout->addWidget(humidityLabel);
        humidityVBoxLayout->addWidget(humidityLedIndicator);

        mainLayout=new QHBoxLayout();
        mainLayout->addLayout(carbonVBoxLayout);
        mainLayout->addLayout(illuminationVBoxLayout);
        mainLayout->addLayout(temperatureVBoxLayout);
        mainLayout->addLayout(humidityVBoxLayout);
        mainLayout->setSpacing(50);
        mainLayout->setMargin(50);

        setLayout(mainLayout);

        QTimer *timer = new QTimer(this);
        temperatureTimer = new QTimer(this);
        humidityTimer = new QTimer(this);
        illuminationTimer = new QTimer(this);
        carbonTimer = new QTimer(this);

        connect(timer,SIGNAL(timeout()),this,SLOT(checkState()));
        timer->start(10000);

        connect(carbonTimer,SIGNAL(timeout()),this,SLOT(cShow()));
        connect(temperatureTimer,SIGNAL(timeout()),this,SLOT(tShow()));
        connect(humidityTimer,SIGNAL(timeout()),this,SLOT(hShow()));
        connect(illuminationTimer,SIGNAL(timeout()),this,SLOT(iShow()));


}

WarningHandle::~WarningHandle()
{

}

void WarningHandle::checkState()
{
  float temperature=realDataDisplay->getTemperature();
  int humidity=realDataDisplay->getHumidity();
  int illumination=realDataDisplay->getIllumination();
  int carbon=realDataDisplay->getCarbon();

  QString text;

  if(temperature>temperatureMaxValue||
     temperature<temperatureMinValue )
  {
    temperatureAbnormalFlag=1;
    //QString text=temperatureLabel->text();
    if(temperature>temperatureMaxValue)
    {
       text.clear();
       text=QString(tr("当前温度为%1℃,超过警戒高值").arg(temperature));
       temperatureLabel->setText(text);
       temperatureLabel->show();
    }
    else
    {
       text.clear();
       text=text.append(tr("当前温度为%1℃,低于警戒低值").arg(temperature));
       temperatureLabel->setText(text);
       temperatureLabel->show();
    }
    //temperatureTimer->start(500);
    if(!temperatureTimer->isActive())
        temperatureTimer->start(200);
    //temperatureIndicator->setChecked(true);
  }
  else
  {
      if(temperatureTimer->isActive())
          temperatureTimer->stop();
      temperatureIndicator->setChecked(false);
      temperatureLabel->setText("温度报警指示");
  }

  if(humidity>humidityMaxValue||
     humidity<humidityMinValue )
  {
    humidityAbnormalFlag=1;
    //QString text=humidityLabel->text();
    if(humidity>humidityMaxValue)
    {
       text.clear();
       text=text.append(tr("当前湿度为%1 %RH,超过警戒高值").arg(humidity));
       humidityLabel->setText(text);
       humidityLabel->show();
    }
    else
    {
       text.clear();
       text=text.append(tr("当前温度为%1 %RH,低于警戒低值").arg(humidity));
       humidityLabel->setText(text);
       humidityLabel->show();
    }
    //humidityTimer->start(500);
    //humidityLedIndicator->setChecked(true);
    if(!humidityTimer->isActive())
        humidityTimer->start(200);
  }
  else {
      if(humidityTimer->isActive())
          humidityTimer->stop();
      humidityLedIndicator->setChecked(false);
      humidityLabel->setText("湿度报警指示");
  }
  if(illumination>illuminationMaxValue||
     illumination<illuminationMinValue )
  {
    illuminationAbnormalFlag=1;
    //QString text=illuminationLabel->text();
    if(illumination>illuminationMaxValue)
    {
       text.clear();
       text=text.append(tr("当前光照强度为%1 LX,超过警戒高值").arg(illumination));
       illuminationLabel->setText(text);
       illuminationLabel->show();
    }
    else
    {
       text.clear();
       text=text.append(tr("当前光照强度为%1 LX,低于警戒低值").arg(illumination));
       illuminationLabel->setText(text);
       illuminationLabel->show();
    }
    //illuminationTimer->start(500);
    //illuminationLedIndicator->setChecked(true);
    if(!illuminationTimer->isActive())
        illuminationTimer->start(200);
  }
  else
  {
      if(illuminationTimer->isActive())
          illuminationTimer->stop();
      illuminationLedIndicator->setChecked(false);
      illuminationLabel->setText("光照强度报警指示");
  }
  if((carbon>carbonMaxValue)||
     (carbon<carbonMinValue) )
  {
    carbonAbnormalFlag=1;
    //QString text=carbonLabel->text();
    if(carbon>carbonMaxValue)
    {
       text.clear();
       text=text.append(tr("当前CO2浓度为%1 PPM,超过警戒高值").arg(carbon));
       carbonLabel->setText(text);
       carbonLabel->show();
    }
    else
    {
       text.clear();
       text=text.append(tr("当前CO2浓度为%1 PPM，低于警戒低值").arg(carbon));
       carbonLabel->setText(text);
       carbonLabel->show();
    }
    //carbonTimer->start(500);
    //carbonLedIndicator->setChecked(true);
    if(!carbonTimer->isActive())
        carbonTimer->start(200);
  }
  else
  {
      if(carbonTimer->isActive())
          carbonTimer->stop();
      carbonLedIndicator->setChecked(false);
      carbonLabel->setText("CO2浓度报警指示");
  }
}

void WarningHandle::cShow()
{
    if(carbonLedIndicator->isChecked())
        carbonLedIndicator->setChecked(false);
    else
        carbonLedIndicator->setChecked(true);
}

void WarningHandle::iShow()
{
    if(illuminationLedIndicator->isChecked())
        illuminationLedIndicator->setChecked(false);
    else
        illuminationLedIndicator->setChecked(true);
}

void WarningHandle::tShow()
{
    if(temperatureIndicator->isChecked())
        temperatureIndicator->setChecked(false);
    else
        temperatureIndicator->setChecked(true);
}

void WarningHandle::hShow()
{
    if(humidityLedIndicator->isChecked())
        humidityLedIndicator->setChecked(false);
    else
        humidityLedIndicator->setChecked(true);
}

int WarningHandle::getCarbonMinValue() const
{
    return carbonMinValue;
}

void WarningHandle::setCarbonMinValue(int value)
{
    carbonMinValue = value;
}

int WarningHandle::getCarbonMaxValue() const
{
    return carbonMaxValue;
}

void WarningHandle::setCarbonMaxValue(int value)
{
    carbonMaxValue = value;
}

int WarningHandle::getIlluminationMinValue() const
{
    return illuminationMinValue;
}

void WarningHandle::setIlluminationMinValue(int value)
{
    illuminationMinValue = value;
}

int WarningHandle::getIlluminationMaxValue() const
{
    return illuminationMaxValue;
}

void WarningHandle::setIlluminationMaxValue(int value)
{
    illuminationMaxValue = value;
}

int WarningHandle::getHumidityMinValue() const
{
    return humidityMinValue;
}

void WarningHandle::setHumidityMinValue(int value)
{
    humidityMinValue = value;
}

int WarningHandle::getHumidityMaxValue() const
{
    return humidityMaxValue;
}

void WarningHandle::setHumidityMaxValue(int value)
{
    humidityMaxValue = value;
}

float WarningHandle::getTemperatureMinValue() const
{
    return temperatureMinValue;
}

void WarningHandle::setTemperatureMinValue(float value)
{
    temperatureMinValue = value;
}

float WarningHandle::getTemperatureMaxValue() const
{
    return temperatureMaxValue;
}

void WarningHandle::setTemperatureMaxValue(float value)
{
    temperatureMaxValue = value;
}

