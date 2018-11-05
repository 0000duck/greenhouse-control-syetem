#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDateTime>
#include <QGraphicsDropShadowEffect>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
   // ui->TitletoolButton->setEnabled(false);
    ui->toolBar->setWindowFlags(Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint);
    ui->toolBar->setStyleSheet("border-style:none;");
    this->menuBar()->setStyleSheet("border-style:none;");
   // ui->groupBox->setStyleSheet("border-style:none;");
    setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    ui->horizontalLayout->setContentsMargins(SHADOW_WIDTH, SHADOW_WIDTH, SHADOW_WIDTH, SHADOW_WIDTH);

    QGraphicsDropShadowEffect *wndShadow = new QGraphicsDropShadowEffect;
    wndShadow->setBlurRadius(5.0);
    wndShadow->setOffset(0);
    wndShadow->setColor(QColor("#017acc"));
    this->setGraphicsEffect(wndShadow);
    this->setStyleSheet("background-color:#FFE4B5;"
                       );

    loginDialog=new LoginDialog();
    connect(this,SIGNAL(toLoginDialog()),loginDialog,SLOT(comeMainWindow()));
    rightStackedWidget=new QStackedWidget();
    devicesManage=new DevicesManage();
    firstPageWidget=new FirstPageWidget();
    historyDataDisplay=new HistoryDataDisplay();
    realDataDisplay=new RealDataDisplay();
    userManage=new UserManage();
    warningHandle=new WarningHandle();
    dapengIntro=new DapengIntro();
    companyIntro=new CompanyIntro();
    sysIntro=new SysIntro();   
    uploadDialog = new Dialog();

    //leftVBoxlayout=new QVBoxLayout();
    rightStackedWidget=ui->stackedWidget;
    rightStackedWidget->addWidget(firstPageWidget);
    rightStackedWidget->addWidget(realDataDisplay);
    rightStackedWidget->addWidget(historyDataDisplay);
    rightStackedWidget->addWidget(devicesManage);
    rightStackedWidget->addWidget(warningHandle);
    rightStackedWidget->addWidget(userManage);

    rightStackedWidget->addWidget(dapengIntro);
    rightStackedWidget->addWidget(companyIntro);
    rightStackedWidget->addWidget(sysIntro);

/*
    leftVBoxlayout->addWidget(ui->TitletoolButton);
    leftVBoxlayout->addWidget(ui->DapengIntroducePushButton);
    leftVBoxlayout->addWidget(ui->CompanyIntroducePushButton);
    leftVBoxlayout->addWidget(ui->DetectSysIntroducePushButton);
*/
//    ui->TitletoolButton->setContentsMargins(40,20,40,20);
//    ui->groupBox->setLayout(leftVBoxlayout);

/*    ui->groupBox->setStyleSheet("background-color:#FF6A6A;"
                                //"border-style:none;"
                                //solid
                                "border-style:solid;"
                                 //"border-style: outset;"
                                "border-width: 2px;"
                                "border-radius: 10px;"
                                "border-color: #FFA07A;"
                                );
*/
//    ui->horizontalLayout->addWidget(ui->groupBox);
    ui->horizontalLayout->addWidget(rightStackedWidget);

    ui->horizontalLayout->setMargin(10);
    ui->horizontalLayout->setSpacing(10);
//    ui->horizontalLayout->setStretch(0,0);
//    ui->horizontalLayout->setStretch(1,1);

//    this->setLayout(ui->horizontalLayout);

    connect(userManage,SIGNAL(EmitToFirstPage()),this,SLOT(on_actionDetectFirstPage_triggered()));
    tcpServer=new TcpServer();
    tcpServer->CreateServer();
    qDebug()<<tr("创建服务器成功！")<<endl;

    this->showFullScreen();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::comeLoginDialog(QString name, QString num)
{
    WorkerName=name;
    WorkerNum=num;
    connect(this,SIGNAL(comefromLOginDialog(QString,QString)),userManage,SLOT(comeLOginDialog(QString,QString)));
    emit comefromLOginDialog(WorkerNum,WorkerName);
    QDateTime time = QDateTime::currentDateTime();//获取系统现在的时间
    QString str = time.toString("yyyy-MM-dd hh:mm:ss ddd"); //设置显示格式
    QString statusTip="("+WorkerName+" "+str+" "+"登录"+")";
    QString disStr=ui->TipLabel->text()+statusTip;
    ui->TipLabel->setText(disStr);
}

void MainWindow::on_actionExit_triggered()
{
    this->close();
    this->firstPageWidget->videoCapClose();
    emit toLoginDialog();
}

void MainWindow::on_actionuse_help_U_triggered()
{

}

void MainWindow::on_actionUpdate_triggered()
{

}

void MainWindow::on_actionSkinSet_triggered()
{
    firstPageWidget->savefile();
}

void MainWindow::on_actionabout_A_triggered()
{

}

void MainWindow::on_actionDetectFirstPage_triggered()
{
    rightStackedWidget->setCurrentIndex(0);
}

void MainWindow::on_actionRealData_triggered()
{
     rightStackedWidget->setCurrentIndex(1);
}

void MainWindow::on_actionHistoryDta_triggered()
{
     rightStackedWidget->setCurrentIndex(2);
}

void MainWindow::on_actionDeviceManage_triggered()
{
     rightStackedWidget->setCurrentIndex(3);
}

void MainWindow::on_actionWarnManage_triggered()
{
     rightStackedWidget->setCurrentIndex(4);
}

void MainWindow::on_actionUserManage_triggered()
{
     rightStackedWidget->setCurrentIndex(5);
}


void MainWindow::on_actionThemeColor_triggered()
{
     uploadDialog->exec();
}

void MainWindow::on_actionDapengIntroduce_triggered()
{
    rightStackedWidget->setCurrentIndex(8);
}

void MainWindow::on_actionCompanyIntroduce_triggered()
{
    rightStackedWidget->setCurrentIndex(7);
}

void MainWindow::on_actionDetectIntro_triggered()
{
    rightStackedWidget->setCurrentIndex(8);
}
