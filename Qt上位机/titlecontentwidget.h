#ifndef TITLECONTENTWIDGET_H
#define TITLECONTENTWIDGET_H

#include "custom_window.h"

namespace Ui {
class TitleContentWidget;
}

class TitleContentWidget : public CustomWindow
{
    Q_OBJECT

public:
    explicit TitleContentWidget(QWidget *parent = 0);
    ~TitleContentWidget();

    int getTitleLabelHeight() const;
    void setTitleLabelHeight(int value);

private:
    Ui::TitleContentWidget *ui;
    int titleLabelHeight;
};

#endif // TITLECONTENTWIDGET_H
