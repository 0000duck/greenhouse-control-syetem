#include "dapengIntro.h"

DapengIntro::DapengIntro(QWidget *parent) : QWidget(parent)
{
    myLabel=new QLabel(this);
    //myLabel->setText(tr("first Page!"));
    //myLabel->show();
    // QImage *newImg=pictureProcess->greyScale(&img);
//       QImage *newImg=greyScale(&img);
//       ui->img_Label->setPixmap(QPixmap::fromImage(*newImg));
//       ui->img_Label->resize(ui->img_Label->pixmap()->size());
     QImage myImage=QImage(":/images/test/1.png");
     myLabel->setPixmap(QPixmap::fromImage(myImage));
     myLabel->resize(myLabel->pixmap()->size());
}

DapengIntro::~DapengIntro()
{
    delete myLabel;
}
