#ifndef TOOL_BUTTON_H
#define TOOL_BUTTON_H

//功能按钮 包括：体检、查杀木马等
#include<QToolButton>
#include<QMouseEvent>
#include<QPainter>

class ToolButton:public QToolButton
{
public:
    explicit ToolButton(QString pic_name,QWidget *parent=0);
    virtual ~ToolButton();
    void setMousePress(bool mouse_press);
protected:
    void enterEvent(QEvent *);
    void leaveEvent(QEvent *);
    void mousePressEvent(QMouseEvent *);
    void paintEvent(QPaintEvent *);
    void painterInfo(int top_color, int middle_color, int bottom_color);
public:
    bool mouse_over; //鼠标是否移过
    bool mouse_press; //鼠标是否按下
};
#endif // TOOL_BUTTON_H
