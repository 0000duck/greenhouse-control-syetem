#include "LoginDialog.h"
#include "ui_LoginDialog.h"
#include <QVBoxLayout>
#include <QDebug>
#include "messagedialog.h"
#include "control.h"

LoginDialog::LoginDialog(QWidget *parent) :
    TitleContentWidget(parent),
    ui(new Ui::LoginDialog)
{
    //ifLOginSuccess=false;
    //setWindowFlags(Qt::FramelessWindowHint);
    ui->setupUi(this);

    Util *util=new Util();
    this->ui->titlelabel->setAlignment(Qt::AlignCenter);
    this->ui->verticalSpacer->changeSize(10,20);
    this->ui->verticalSpacer_2->changeSize(10,30);
    this->ui->verticalSpacer_3->changeSize(10,5);
    this->setFont(QFont("Microsoft Yahei", 12));
    setLayout(ui->verticalLayout);
    //创建QSqlTableModel
    model=new QSqlTableModel(this);
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    //设置登录对话框的标题
    this->setWindowTitle("登录");
    //设置登录对话框的图标
    this->setWindowIcon(QIcon(":/images/Icon/SmartHome.ico"));
    //设置登录对话框大小固定为399*252
    this->setMaximumSize(387,252);
    this->setMinimumSize(387,252);
    //设置调色板,用于设置titlelabel的颜色
    QPalette p;
    p.setColor(QPalette::WindowText,Qt::black);
    ui->titlelabel->setPalette(p);

    //设置三个按钮的图标
   // ui->exitbtn->setIcon(QIcon(":/images/exit.png"));
   // ui->registerbtn->setIcon(QIcon(":/images/login/log.png"));
    //ui->loginbtn->setIcon(QIcon(":/images/Enter.png"));

    //设置登录按钮不可用
    ui->loginbtn->setEnabled(false);

    util->setBtnQss(ui->exitbtn, "#34495E", "#FFFFFF", "#4E6D8C", "#F0F0F0", "#2D3E50", "#B8C6D1");
    util->setBtnQss(ui->registerbtn, "#1ABC9C", "#E6F8F5", "#2EE1C1", "#FFFFFF", "#16A086", "#A7EEE6");
    util->setBtnQss(ui->loginbtn, "#3498DB", "#FFFFFF", "#5DACE4", "#E5FEFF", "#2483C7", "#A0DAFB");
    //setBtnQss(ui->btn4, "#E74C3C", "#FFFFFF", "#EC7064", "#FFF5E7", "#DC2D1A", "#F5A996");

    //设置lineedit提示语句
    ui->userline->setPlaceholderText("请输入用户名");
    ui->passwordline->setPlaceholderText("请输入密码");
    //设置passlineedit显示为密码模式
    ui->passwordline->setEchoMode(QLineEdit::Password);

    util->setTxtQss(ui->userline, "#DCE4EC", "#34495E");
    util->setTxtQss(ui->passwordline, "#DCE4EC", "#1ABC9C");
    //setTxtQss(ui->txt3, "#DCE4EC", "#3498DB");
    //setTxtQss(ui->txt4, "#DCE4EC", "#E74C3C");
    //连接信号与槽
    connect(ui->loginbtn,SIGNAL(clicked()),this,SLOT(loginbtnSlot()));
    connect(ui->registerbtn,SIGNAL(clicked()),this,SLOT(registerbtnSlot()));
    connect(ui->exitbtn,SIGNAL(clicked()),this,SLOT(exitbtnSlot()));
    //设置登录按钮可用
    connect(ui->userline,SIGNAL(textChanged(QString)),this,SLOT(loginbtnSetSlot(QString)));
    connect(ui->passwordline,SIGNAL(textChanged(QString)),this,SLOT(loginbtnSetSlot(QString)));

}
LoginDialog::~LoginDialog()
{
    delete ui;
}


void LoginDialog::loginbtnSlot()
{
    if(!this->judgeEmpty())
    {
        ui->passwordline->clear();
        return;
    }
    //用户登录判断用户名，密码是否正确
    model->setTable("worker");
    model->select();
    int i;
    for(i=0;i<model->rowCount();i++)
    {
        QSqlRecord record=model->record(i);

        if(record.value(0)==ui->userline->text()&&
                record.value(2)==ui->passwordline->text())
        {
            QString str1="登录成功";
            ifLOginSuccess=true;
            QString str2=record.value(1).toString();
            QString str3="用户";
            QString str=str3+str2+str1;
            str=str.toUtf8();
            MessageDialog box(tr("提示"),str);
            box.exec();
            this->clearAll();
            //创建主界面窗口
            mainwindow=new MainWindow();
            //连接工作人员信息管理窗口和登录对话框信号与槽
            connect(mainwindow,SIGNAL(toLoginDialog()),this,SLOT(show()));
            connect(this,SIGNAL(toUserManage(QString,QString)),mainwindow,SLOT(comeLoginDialog(QString,QString)));
            this->close();
            emit toUserManage(str2,record.value(0).toString());
            //mainwindow->show();
            return;
        }
        else if(record.value(0)==ui->userline->text()&&
                record.value(5)!=ui->passwordline->text())
       {
            MessageDialog box(tr("提示"),tr("密码输入有误"));
            box.exec();
            this->clearAll();
            return;
        }
    }

    MessageDialog box(tr("提示"),tr("用户不存在,请注册"));
    box.exec();
    this->clearAll();
    return;

}
void LoginDialog::registerbtnSlot()
{
    RegisterDialog d;
    this->close();
    d.show();
    qDebug()<<"进入注册界面"<<endl;
    if(d.exec()==QDialog::Accepted)
    {
        d.close();
        this->show();
    }
    this->clearAll();
}
void LoginDialog::exitbtnSlot()
{
    qDebug()<<"退出登录界面，退出主程序"<<endl;
    this->close();
}
void LoginDialog::loginbtnSetSlot(QString)
{
    ui->loginbtn->setEnabled(true);
}

void LoginDialog::comeMainWindow()
{

}
/*
void LoginDialog::setBtnQss(QPushButton *btn, QString normalColor, QString normalTextColor, QString hoverColor, QString hoverTextColor, QString pressedColor, QString pressedTextColor)
{
    QStringList qss;
    qss.append(QString("QPushButton{border-style:none;padding:5px;border-radius:2px;color:%1;background:%2;}").arg(normalTextColor).arg(normalColor));
    qss.append(QString("QPushButton:hover{color:%1;background:%2;}").arg(hoverTextColor).arg(hoverColor));
    qss.append(QString("QPushButton:pressed{color:%1;background:%2;}").arg(pressedTextColor).arg(pressedColor));
    btn->setStyleSheet(qss.join(""));

}

void LoginDialog::setTxtQss(QLineEdit *txt, QString normalColor, QString focusColor)
{
    QStringList qss;
    qss.append(QString("QLineEdit{border-style:none;padding:2px;border-radius:1px;border:1px solid %1;}").arg(normalColor));
    qss.append(QString("QLineEdit:focus{border:1px solid %1;}").arg(focusColor));
    txt->setStyleSheet(qss.join(""));

}
*/
void LoginDialog::clearAll()
{
    ui->userline->clear();
    ui->passwordline->clear();
}
bool LoginDialog::judgeEmpty()
{
    if(ui->userline->text().isEmpty())
    {
        MessageDialog box(tr("警告"),tr("用户名不能为空"));
        box.exec();
        return false;
    }
    if(ui->passwordline->text().isEmpty())
    {
        MessageDialog box(tr("警告"),tr("密码不能为空"));
        box.exec();
        return false;
    }
    else
        return true;
}
