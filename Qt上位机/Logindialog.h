#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include "RegisterDialog.h"
#include "mainwindow.h"
#include <QDebug>
#include <QDialog>
#include <QPalette>
#include <QButtonGroup>
#include <QMessageBox>
#include <QSqlTableModel>
#include <QSqlRecord>
#include <QLineEdit>
//#include "custom_window.h"
#include "titlecontentwidget.h"


class MainWindow;
namespace Ui {
class LoginDialog;
}

class LoginDialog : public TitleContentWidget
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = 0);
    virtual ~LoginDialog();
    void clearAll();
    bool judgeEmpty();

signals:
    void toUserManage(QString,QString);
    //void thisClose();
private slots:
    void exitbtnSlot();
    void registerbtnSlot();
    void loginbtnSlot();
    void loginbtnSetSlot(QString);
    void comeMainWindow();
    /*void setBtnQss(QPushButton *btn,
                   QString normalColor, QString normalTextColor,
                   QString hoverColor, QString hoverTextColor,
                   QString pressedColor, QString pressedTextColor);
                   */
    /*
    void setTxtQss(QLineEdit *txt, QString normalColor, QString focusColor);
    */
private:
    Ui::LoginDialog *ui;
    QSqlTableModel *model;
    MainWindow *mainwindow;
    bool ifLOginSuccess;
};

#endif // LOGINDIALOG_H
