#include "controlonoff.h"
#include "ui_controlonoff.h"
#include <QVBoxLayout>
#include <QQmlContext>
ControlOnOff::ControlOnOff(const QString &theDeviceName,const int &theOnoffWidth,
                           const int &myId) :
    ui(new Ui::ControlOnOff),deviceName(theDeviceName),OnoffWidth(theOnoffWidth),
    id(myId)
{

    ui->setupUi(this);
    QQmlContext *context=ui->quickWidget->rootContext();
    context->setContextProperty("myText",theDeviceName);
    context->setContextProperty("myWidth",OnoffWidth);
    this->setFixedSize(OnoffWidth+20,OnoffWidth*3+40);
    this->setWindowFlags(Qt::FramelessWindowHint);
    QUrl source("qrc:/Switch.qml");
    ui->quickWidget->resize(OnoffWidth,OnoffWidth*3);
    //ui->quickWidget->setResizeMode(QQuickWidget::SizeRootObjectToView);
    ui->quickWidget->setResizeMode(QQuickWidget::SizeViewToRootObject);
    ui->quickWidget->setSource(source);
    this->setLayout(ui->verticalLayout);

}

ControlOnOff::~ControlOnOff()
{
    delete ui;
}

int ControlOnOff::getId() const
{
    return id;
}

void ControlOnOff::setId(int value)
{
    id = value;
}
