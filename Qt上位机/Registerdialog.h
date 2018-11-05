#ifndef REGISTERDIALOG_H
#define REGISTERDIALOG_H

#include <QDialog>
#include <QDebug>
#include <QPalette>
#include <QSqlTableModel>
#include <QSqlRecord>
#include <QTime>
#include <QMessageBox>
#include <QButtonGroup>
#include <QLineEdit>
#include "titlecontentwidget.h"
namespace Ui {
class RegisterDialog;
}

class RegisterDialog : public TitleContentWidget
{
    Q_OBJECT

public:
    explicit RegisterDialog(QWidget *parent = 0);
    virtual ~RegisterDialog();
    void clearAll();
    void setyanzheng();
    bool judgeEmpty();
private:
    Ui::RegisterDialog *ui;
    QSqlTableModel *model;
    int yanzheng;
private slots:
    void registerbtnSlot();
    void returnbtnSlot();
    void registerbtnSetSlot(QString);
    /*void setBtnQss(QPushButton *btn,
                   QString normalColor, QString normalTextColor,
                   QString hoverColor, QString hoverTextColor,
                   QString pressedColor, QString pressedTextColor);
    void setTxtQss(QLineEdit *txt, QString normalColor, QString focusColor);*/
};

#endif // REGISTERDIALOG_H
