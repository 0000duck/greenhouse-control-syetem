#include "sysIntro.h"

SysIntro::SysIntro(QWidget *parent) : QWidget(parent)
{
    myLabel=new QLabel(this);
    //myLabel->setText(tr("first Page!"));
    //myLabel->show();
    // QImage *newImg=pictureProcess->greyScale(&img);
//       QImage *newImg=greyScale(&img);
//       ui->img_Label->setPixmap(QPixmap::fromImage(*newImg));
//       ui->img_Label->resize(ui->img_Label->pixmap()->size());
     QImage myImage=QImage(":/images/test/3.png");
     myLabel->setPixmap(QPixmap::fromImage(myImage));
     myLabel->resize(myLabel->pixmap()->size());
}

SysIntro::~SysIntro()
{
    delete myLabel;
}
