#include "firstpageWidget.h"
#include <QTimer>
#include <QDebug>

FirstPageWidget::FirstPageWidget(QWidget *parent) : QWidget(parent)
{

    this->setFont(QFont("Microsoft Yahei", 12));
    this->setStyleSheet("background-color:#f8ff70;"
                  "color: rgb(0, 170, 0);"
                  "border-style:none;"
                   //"border-style: outset;"
                  "border-width: 2px;"
                  "border-radius: 10px;"
                 "border-color: beige;"
                        );

    labelWidth=(this->width()-15)/2;
    labelHight=this->height();

    myLabel=new QLabel(this);
    textLabel=new QLabel(this);
    vBoxLayout=new QVBoxLayout();
    theTimer=new QTimer(this);
    hboxLayout=new QHBoxLayout();

    bottonGroupBox=new QGroupBox();
    groupBox=new SwitchItem( );
    controlValueVBoxLayout=new QVBoxLayout();
    rightControlVBoxlayout=new QVBoxLayout();
    leftVideoGroupBox=new QGroupBox();

    temperatureSlider=new ControlSlider("     温度(℃)：",25,40,0,0.1,3,1,30);
    humiditySlider=new ControlSlider("    湿度(%RH)：",60.0,100.0,0.0,0.5,10,1,20);
    illuminationSlider=new ControlSlider("光照强度(k lx)：",5,90,0,1,10,1,20);
    carbonSlider=new ControlSlider("CO2浓度(hppm)：",40,90,0,1,10,1,20);

    controlValueVBoxLayout->addWidget(temperatureSlider);
    controlValueVBoxLayout->addWidget(humiditySlider);
    controlValueVBoxLayout->addWidget(illuminationSlider);
    controlValueVBoxLayout->addWidget(carbonSlider);

    textLabel->setText(tr("视频监控"));
    QFont font("Courier New", 30, 75);
    textLabel->setFont(font);
    textLabel->setAlignment(Qt::AlignHCenter);
    textLabel->setStyleSheet("background-color:#ffcea5;");

    connect(theTimer,SIGNAL(timeout()), this,SLOT(updateImage()));

    //从摄像头获取视频
    if(videoCap.open(0))
    {
       srcImage = Mat::zeros(videoCap.get(CV_CAP_PROP_FRAME_HEIGHT),
                             videoCap.get(CV_CAP_PROP_FRAME_WIDTH), CV_8UC3);
       theTimer->start(33);

    }
    vBoxLayout->addWidget(textLabel,0);
    vBoxLayout->addWidget(myLabel,1);
    leftVideoGroupBox->setLayout(vBoxLayout);
    leftVideoGroupBox->setStyleSheet("background-color:#f8ff70;"
                                     "border-style:none;"
                                     //"border-style: outset;"
                                     "border-width: 2px;"
                                     "border-radius: 10px;"
                                     "border-color: beige;");

    bottonGroupBox->setTitle(tr("控制值设定区"));
    bottonGroupBox->setFont( QFont("Microsoft Yahei", 12));
    bottonGroupBox->setLayout(controlValueVBoxLayout);
    bottonGroupBox->setStyleSheet("background-color:#f8ff70;"
                                  "border-style:none;"
                                  //"border-style: outset;"
                                  "border-width: 2px;"
                                  "border-radius: 10px;"
                                  "border-color: beige;");

    rightControlVBoxlayout->addWidget(groupBox);
    rightControlVBoxlayout->addWidget(bottonGroupBox);

    hboxLayout->addWidget(leftVideoGroupBox,0);
    hboxLayout->addLayout(rightControlVBoxlayout,1);
    this->setLayout(hboxLayout);

    QTimer::singleShot(0, this, SLOT(setValue()));

}

FirstPageWidget::~FirstPageWidget()
{
    delete theTimer;
    delete myLabel;
    delete textLabel;
    delete vBoxLayout;

    delete temperatureSlider;
    delete humiditySlider;
    delete illuminationSlider;
    delete carbonSlider;

}

void FirstPageWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    image2 = QImage((uchar*)(srcImage.data), srcImage.cols, srcImage.rows, QImage::Format_RGB888);
    myLabel->setPixmap(QPixmap::fromImage(image2));
    myLabel->show();
    textLabel->setFixedWidth(myLabel->width());
}

void FirstPageWidget::mousePressEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton)
    {
        qDebug()<<tr("鼠标按下")<<endl;
    }
}

void FirstPageWidget::videoCapClose()
{
    videoCap.release();
}

void FirstPageWidget::savefile()
{
    image2.save("E:/picture/jietu.jpg");
}

void FirstPageWidget::updateImage()
{
    videoCap>>srcImage;
    if(srcImage.data)
    {
        cvtColor(srcImage, srcImage, CV_BGR2RGB);//Qt中支持的是RGB图像, OpenCV中支持的是BGR
        this->update();  //发送刷新消息
    }
}

void FirstPageWidget::setValue()
{
    temperatureSlider->setSliderValue(25.0);
    humiditySlider->setSliderValue(60.0);
    carbonSlider->setSliderValue(40);
    illuminationSlider->setSliderValue(5);
    update();
}
