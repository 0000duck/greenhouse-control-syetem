#ifndef MESSAGEDIALOG_H
#define MESSAGEDIALOG_H

#include "custom_window.h"
#include <QPushButton>
namespace Ui {
    class MessageDialog;
}

class MessageDialog : public CustomWindow
{
    Q_OBJECT
public:
    explicit MessageDialog(const QString &theTitleString,
                           const QString &theContentString);

    ~MessageDialog();
    void setBtnQss(QPushButton *btn,
                   QString normalColor, QString normalTextColor,
                   QString hoverColor, QString hoverTextColor,
                   QString pressedColor, QString pressedTextColor);
protected:
    void paintEvent(QPaintEvent *event);
signals:
    void sigBtn(bool a);
public slots:
    void slotOk();
private:
    Ui::MessageDialog *ui;
    QString titleString;
    QString contentString;
};

#endif // MESSAGEDIALOG_H
