#include "RegisterDialog.h"
#include "ui_RegisterDialog.h"
#include "control.h"

RegisterDialog::RegisterDialog(QWidget *parent) :
    TitleContentWidget(parent),
    ui(new Ui::RegisterDialog)
{

    this->setFont(QFont("Microsoft Yahei", 12));
    setWindowFlags(Qt::FramelessWindowHint);
    ui->setupUi(this);

    Util *util=new Util();
    //设置对话框的大小
    setLayout(ui->verticalLayout);
    this->setMaximumSize(350,320);
    this->setMinimumSize(350,320);

    //创建model,进行数据库操作
    model=new QSqlTableModel(this);
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    //设置注册对话框的背景
   /* QPalette p;
    p.setBrush(QPalette::Background,QBrush(QPixmap(":/images/loginbk1.jpg").scaled(this->size())));
    this->setPalette(p);*/
    //设置注册对话框的标题颜色
    QPalette p1;
    p1.setColor(QPalette::WindowText,Qt::black);
    ui->titlelabel->setPalette(p1);
    //设置注册对话框标题
    this->setWindowTitle("注册用户");
    //设置两个按钮的图案
    //ui->registerbtn->setIcon(QIcon(":/images/Enter.png"));
   // ui->returnbtn->setIcon(QIcon(":/images/exit.png"));

    util->setBtnQss(ui->registerbtn, "#34495E", "#FFFFFF", "#4E6D8C", "#F0F0F0", "#2D3E50", "#B8C6D1");
    util->setBtnQss(ui->returnbtn, "#34495E", "#FFFFFF", "#4E6D8C", "#F0F0F0", "#2D3E50", "#B8C6D1");
    //设置两行密码lineedit的显示
    ui->passwordline->setEchoMode(QLineEdit::PasswordEchoOnEdit);
    ui->passwordline1->setEchoMode(QLineEdit::PasswordEchoOnEdit);
    //设置lineedit提示语句
    ui->userline->setPlaceholderText("请输入用户名");
    ui->workernumline->setPlaceholderText("请输入工作号");
    ui->passwordline->setPlaceholderText("请输入密码");
    ui->passwordline1->setPlaceholderText("请重新输入密码");
    ui->yanzhengline->setPlaceholderText("请输入验证码");

    util->setTxtQss(ui->userline, "#DCE4EC", "#34495E");
    util->setTxtQss(ui->workernumline, "#DCE4EC", "#1ABC9C");
    util->setTxtQss(ui->passwordline, "#DCE4EC", "#34495E");
    util->setTxtQss(ui->yanzhengline, "#DCE4EC", "#1ABC9C");
    util->setTxtQss(ui->passwordline1, "#DCE4EC", "#34495E");

    //设置注册按钮不可用
    ui->registerbtn->setEnabled(false);
    //两个按钮的信号与槽的连接
    connect(ui->registerbtn,SIGNAL(clicked()),this,SLOT(registerbtnSlot()));
    connect(ui->returnbtn,SIGNAL(clicked()),this,SLOT(returnbtnSlot()));
    //设置验证码
    QTime t;
    t= QTime::currentTime();
    qsrand(t.msec()+t.second()*1000);
    this->setyanzheng();

    //lineedit与槽连接
    connect(ui->userline,SIGNAL(textChanged(QString)),this,SLOT(registerbtnSetSlot(QString)));
    connect(ui->passwordline,SIGNAL(textChanged(QString)),this,SLOT(registerbtnSetSlot(QString)));
    connect(ui->workernumline,SIGNAL(textChanged(QString)),this,SLOT(registerbtnSetSlot(QString)));
}

RegisterDialog::~RegisterDialog()
{
    delete ui;
}
void RegisterDialog::registerbtnSlot()
{
    int i;
    //判断lineedit是否为空
    if(!this->judgeEmpty())
    {
        ui->passwordline->clear();
        ui->passwordline1->clear();
        ui->yanzhengline->clear();
        return;
    }
    //判断两次密码输入是否一致
    if(ui->passwordline->text()!=ui->passwordline1->text())
    {
        QMessageBox::warning(this,"警告","两次密码输入不一致",QMessageBox::Yes);
        ui->passwordline->clear();
        ui->passwordline1->clear();
        ui->yanzhengline->clear();
        this->setyanzheng();
        return;
    }
    //判断验证码输入是否正确
    if(ui->yanzhenglabel->text()!=ui->yanzhengline->text())
    {
        QMessageBox::warning(this,"警告","验证码输入错误",QMessageBox::Yes);
        ui->passwordline->clear();
        ui->passwordline1->clear();
        ui->yanzhengline->clear();
        this->setyanzheng();
        return;
    }

    //设置table为student表
    model->setTable("worker");
    model->select();
    for(i=0;i<model->rowCount();i++)
    {
        QSqlRecord record=model->record(i);
        //判断学生信息已经存在
         if((record.value(0)==ui->workernumline->text()&&record.value(2)!=""))
        {
            QMessageBox::warning(this,"警告","用户已存在",QMessageBox::Yes);
            this->clearAll();
            this->setyanzheng();
            return;
        }
    }
    //如果学生信息不存在,添加学生信息进数据库
    if(i==model->rowCount())
    {
        QSqlRecord record1=model->record();
        record1.setValue("workernum",ui->workernumline->text().toUtf8());
        record1.setValue("name",ui->userline->text().toUtf8());
        record1.setValue("password",ui->passwordline->text().toUtf8());
        model->insertRecord(-1,record1);
    }
    //判断学生信息是否上传数据库成功
    if(model->submitAll())
    {
        QMessageBox::information(this,"提示","恭喜你注册成功^*^",QMessageBox::Yes);
        this->accept();
    }
    //上传不成功
    else
        QMessageBox::information(this,"提示","注册失败请重新注册",QMessageBox::Yes);
    this->clearAll();
    this->setyanzheng();

}

void RegisterDialog::returnbtnSlot()
{
    this->accept();
}
void RegisterDialog::registerbtnSetSlot(QString)
{
    ui->registerbtn->setEnabled(true);
}
//清空lineedit的上的文本
void RegisterDialog::clearAll()
{
    ui->userline->clear();
    ui->passwordline->clear();
    ui->passwordline1->clear();
    ui->workernumline->clear();
    ui->yanzhengline->clear();
}
//设置验证码
void RegisterDialog::setyanzheng()
{
    QPalette p1;
    p1.setColor(QPalette::WindowText,Qt::red);
    yanzheng=qrand()%10000;
    while(yanzheng<1000)
        yanzheng=qrand()%10000;
    ui->yanzhenglabel->setText(QString::number(yanzheng));
    ui->yanzhenglabel->setPalette(p1);
}
//判断lineedit是否为空
bool RegisterDialog::judgeEmpty()
{
    if(ui->userline->text().isEmpty())
    {
        QMessageBox::warning(this,"警告","用户名不能为空");
        return false;
    }
    else if(ui->workernumline->text().isEmpty())
    {
        QMessageBox::warning(this,"警告","用户工作号不能为空");
        return false;
    }
    else if(ui->passwordline->text().isEmpty()||
            ui->passwordline1->text().isEmpty())
    {
        QMessageBox::warning(this,"警告","用户密码不能为空");
        return false;
    }
    else if(ui->yanzhengline->text().isEmpty())
    {
        QMessageBox::warning(this,"警告","验证码不能为空");
        return false;
    }
    else
        return true;
}
/*
void RegisterDialog::setBtnQss(QPushButton *btn, QString normalColor, QString normalTextColor, QString hoverColor, QString hoverTextColor, QString pressedColor, QString pressedTextColor)
{
    QStringList qss;
    qss.append(QString("QPushButton{border-style:none;padding:10px;border-radius:5px;color:%1;background:%2;}").arg(normalTextColor).arg(normalColor));
    qss.append(QString("QPushButton:hover{color:%1;background:%2;}").arg(hoverTextColor).arg(hoverColor));
    qss.append(QString("QPushButton:pressed{color:%1;background:%2;}").arg(pressedTextColor).arg(pressedColor));
    btn->setStyleSheet(qss.join(""));

}

void RegisterDialog::setTxtQss(QLineEdit *txt, QString normalColor, QString focusColor)
{
    QStringList qss;
    qss.append(QString("QLineEdit{border-style:none;padding:6px;border-radius:5px;border:2px solid %1;}").arg(normalColor));
    qss.append(QString("QLineEdit:focus{border:2px solid %1;}").arg(focusColor));
    txt->setStyleSheet(qss.join(""));

}
*/
