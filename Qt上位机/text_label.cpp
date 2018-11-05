#include "text_label.h"
#include <QPainter>
TextLabel::TextLabel(const QString &path): text(""),unit("ppm"),prefix(tr("当前CO2浓度为："))
{
    this->path=path;
    QImage myImage=QImage(this->path);
    myImage=myImage.scaled(this->width()/3,this->height(),Qt::KeepAspectRatio,Qt::SmoothTransformation);
    this->setPixmap(QPixmap::fromImage(myImage));
    //this->setAlignment(Qt::AlignLeft);
    //this->setScaledContents(true);
/*
background-color: rgb(220, 226, 241);
color: rgb(0, 170, 0);

*/
/*    setStyleSheet("background-color:green;"
                     "border-style: outset;"
                     "border-width: 2px;"
                     "border-radius: 10px;"
                     "border-color: beige;");  // 设置QLabel背景的颜色
                     */
    setStyleSheet(   "background-color: rgb(220, 226, 241);"
                     "color: rgb(0, 170, 0);"
                     "border-style: outset;"
                     "border-width: 2px;"
                     "border-radius: 10px;"
                     "border-color: beige;");  // 设置QLabel背景的颜色
    update();
}

void TextLabel::paintEvent(QPaintEvent *event)
{

    QLabel::paintEvent(event);
    QPainter painter(this);
    //QFont font( "Microsoft YaHei", 30, 75); //第一个属性是字体（微软雅黑），第二个是大小，第三个是加粗（权重是75）
    QFont font( "Courier New", 30, 75);
    painter.setFont(font);

    const QRect rectangle = QRect(this->width()/2,this->height()/4,this->width()/2,this->height()/2);
    QRect boundingRect;
    painter.drawText(rectangle,Qt::TextWordWrap, text, &boundingRect);


}
