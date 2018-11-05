#include "control.h"
#include <QApplication>
#include <QFile>

Util::Util()
{
     QDesktopWidget* desktopWidget = QApplication::desktop();
     //获取可用桌面大小
     //QRect deskRect = desktopWidget->availableGeometry();
     //获取设备屏幕大小
     QRect screenRect = desktopWidget->screenGeometry();

     width = screenRect.width();
     height = screenRect.height();
}

int Util::getWidth() const
{
    return width;
}

void Util::setWidth(int value)
{
    width = value;
}

int Util::getHeight() const
{
    return height;
}

void Util::setHeight(int value)
{
    height = value;
}

void Util::setBtnQss(QPushButton *btn, QString normalColor, QString normalTextColor, QString hoverColor, QString hoverTextColor, QString pressedColor, QString pressedTextColor)
{
    QStringList qss;
    qss.append(QString("QPushButton{border-style:none;padding:5px;border-radius:2px;color:%1;background:%2;}").arg(normalTextColor).arg(normalColor));
    qss.append(QString("QPushButton:hover{color:%1;background:%2;}").arg(hoverTextColor).arg(hoverColor));
    qss.append(QString("QPushButton:pressed{color:%1;background:%2;}").arg(pressedTextColor).arg(pressedColor));
    btn->setStyleSheet(qss.join(""));
}

void Util::setTxtQss(QLineEdit *txt, QString normalColor, QString focusColor)
{
    QStringList qss;
    qss.append(QString("QLineEdit{border-style:none;padding:2px;border-radius:1px;border:1px solid %1;}").arg(normalColor));
    qss.append(QString("QLineEdit:focus{border:1px solid %1;}").arg(focusColor));
    txt->setStyleSheet(qss.join(""));
}

QString Util::getQssContent()
{
    QFile styleSheet(":/ss/style.ss");
    if (!styleSheet.open(QIODevice::ReadOnly))
    {
        qWarning("Can't open the style sheet file.");
        return "";
    }
    return styleSheet.readAll();
}
