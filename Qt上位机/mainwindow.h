#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include "devicesManage.h"
#include "firstpageWidget.h"
#include "historydatadisplay.h"
#include "realdataDisplay.h"
#include "userManage.h"
#include "warningHandle.h"
#include "dapengIntro.h"
#include "companyIntro.h"
#include "sysIntro.h"
#include "tcpserver.h"
#include "Logindialog.h"
#include "dialog.h"

#define SHADOW_WIDTH  5

class LoginDialog;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    virtual ~MainWindow();
signals:
  void toLoginDialog();
  void comefromLOginDialog(QString theWorkerNum,QString theWorkerName);
private slots:
    void comeLoginDialog(QString,QString);          //登录成功接收登录信息
    void on_actionExit_triggered();                 //离开退出
    void on_actionuse_help_U_triggered();           //帮助显示
    void on_actionUpdate_triggered();               //更新大棚信息
    void on_actionSkinSet_triggered();              //设置皮肤
    void on_actionabout_A_triggered();              //关于说明
    void on_actionDetectFirstPage_triggered();      //监控首页
    void on_actionRealData_triggered();             //实时数据显示
    void on_actionHistoryDta_triggered();           //历史数据显示
    void on_actionDeviceManage_triggered();         //设备管理
    void on_actionWarnManage_triggered();           //报警处理
    void on_actionUserManage_triggered();           //用户管理
    void on_actionThemeColor_triggered();           //主题颜色设置
    void on_actionDapengIntroduce_triggered();      //大棚介绍
    void on_actionCompanyIntroduce_triggered();     //公司介绍
    void on_actionDetectIntro_triggered();          //检测系统简介

private:
    Ui::MainWindow *ui;
    QString WorkerName;
    QString WorkerNum;
    QStackedWidget * rightStackedWidget;
    DevicesManage *devicesManage;
    FirstPageWidget *firstPageWidget;
    HistoryDataDisplay *historyDataDisplay;
    RealDataDisplay *realDataDisplay;
    UserManage *userManage;
    WarningHandle *warningHandle;
    DapengIntro *dapengIntro;
    CompanyIntro *companyIntro;
    SysIntro *sysIntro;

    TcpServer *tcpServer;
    LoginDialog *loginDialog;
    Dialog *uploadDialog;
   // QVBoxLayout *leftVBoxlayout;

};

#endif // MAINWINDOW_H
