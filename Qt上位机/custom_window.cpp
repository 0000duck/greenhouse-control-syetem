#include "custom_window.h"


CustomWindow::CustomWindow(QWidget *parent)
{
    Q_UNUSED(parent);
    this->setWindowFlags(Qt::FramelessWindowHint|this->windowFlags());
    this->setStyleSheet(
                  "border-style:none;"
                  "border-width: 2px;"
                  "border-radius: 10px;"
                  "border-color: #FFA07A;"
                  "background-color:#FFE4B5;"
                );
     this->setFixedSize(350,200);
}
