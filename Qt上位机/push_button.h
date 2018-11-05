#ifndef PUSH_BUTTON_H
#define PUSH_BUTTON_H

#include <QPushButton>
#include <QPainter>
#include <QMouseEvent>

class PushButton : public QPushButton
{
    Q_OBJECT
public:
    explicit PushButton(QWidget *parent=0);
    virtual ~PushButton();
    void setPicName(QString pic_name);
protected:
    void enterEvent(QEvent *);
    void leaveEvent(QEvent *event);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void paintEvent(QPaintEvent *);
private:
    //枚举类型的几种状态
    enum ButtonStatus{NORMAL,ENTER,PRESS,NOSTATUS};
    ButtonStatus status;
    QString pic_name;
    //按钮宽高和是否按下鼠标左键标志
    int btn_width;
    int btn_height;
    bool mouse_press;

};
#endif // PUSH_BUTTON_H
