#include "userManage.h"
#include "ui_usermanage.h"
#include "messagedialog.h"
#include <control.h>

UserManage::UserManage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserManage)
{
    ui->setupUi(this);
    Util *util=new Util();
    this->setStyleSheet( util->getQssContent());
    this->setFont(QFont("Microsoft Yahei", 15));
    mainLayout=new QHBoxLayout();

    model=new QSqlTableModel(this);
    model->setTable("worker");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);

    model2=new QSqlTableModel(this);
    model2->setTable("worker");
    model2->setEditStrategy(QSqlTableModel::OnManualSubmit);

    ui->horizontalLayout->setStretch(0,0);
    ui->horizontalLayout->setStretch(1,1);
    ui->leftGroupBox->setFont( QFont("Microsoft Yahei", 14));
    ui->rightGroupBox->setFont( QFont("Microsoft Yahei", 14));
    mainLayout->addWidget(this->ui->leftGroupBox,1);
    mainLayout->addWidget(this->ui->rightGroupBox,1);
    mainLayout->setMargin(10);
    mainLayout->setSpacing(10);

    ui->leftGroupBox->setStyleSheet("background-color:#FAEBD7;"
                                    "border-style:none;"
                                    "border-width: 2px;"
                                    "border-radius:5px;"
                                    "border-color: #FFA07A;"
                                    );
    ui->rightGroupBox->setStyleSheet("background-color:#FAEBD7;"
                                    "border-style:none;"
                                    "border-width: 2px;"
                                    "border-radius: 5px;"
                                    "border-color: #FFA07A;"
                                    );

   util->setBtnQss(ui->confirmbtn, "#34495E", "#FFFFFF", "#4E6D8C", "#F0F0F0", "#2D3E50", "#B8C6D1");
   util->setBtnQss(ui->canclebtn, "#34495E", "#FFFFFF", "#4E6D8C", "#F0F0F0", "#2D3E50", "#B8C6D1");

   util->setBtnQss(ui->searchbtn, "#34495E", "#FFFFFF", "#4E6D8C", "#F0F0F0", "#2D3E50", "#B8C6D1");
   util->setBtnQss(ui->returnbtn, "#34495E", "#FFFFFF", "#4E6D8C", "#F0F0F0", "#2D3E50", "#B8C6D1");

   ui->nameLineEdit->setPlaceholderText(tr("请输入姓名"));
   ui->numLineEdit->setPlaceholderText(tr("请输入工作号"));
   ui->passwordLineEdit->setPlaceholderText(tr("请输入密码"));
   ui->telephoneLineEdit->setPlaceholderText(tr("请输入电话号码"));
   ui->qqLineEdit->setPlaceholderText(tr("请输入qq号"));
   ui->emailLineEdit->setPlaceholderText(tr("请输入e-mail"));
   ui->adressLineEdit->setPlaceholderText(tr("请输入家庭地址"));

   util->setTxtQss(ui->nameLineEdit, "#DCE4EC", "#34495E");
   util->setTxtQss(ui->numLineEdit, "#DCE4EC", "#34495E");
   util->setTxtQss(ui->passwordLineEdit, "#DCE4EC", "#34495E");
   util->setTxtQss(ui->telephoneLineEdit, "#DCE4EC", "#34495E");
   util->setTxtQss(ui->qqLineEdit, "#DCE4EC", "#34495E");
   util->setTxtQss(ui->emailLineEdit, "#DCE4EC", "#34495E");
   util->setTxtQss(ui->adressLineEdit, "#DCE4EC", "#34495E");
   util->setTxtQss(ui->inputline, "#DCE4EC", "#34495E");


   connect(ui->emailLineEdit,SIGNAL(textChanged(QString)),this,SLOT(emainlineSlot(QString)));

   ui->userInfoSearchView->setEditTriggers(QAbstractItemView::NoEditTriggers);
   ui->userInfoSearchView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

   ui->returnbtn->setFlat(true);
   //设置inputedit提示显示
   ui->inputline->setPlaceholderText("请输入用户工号或者用户姓名");

   model2->setHeaderData(0,Qt::Horizontal,"工号");
   model2->setHeaderData(1,Qt::Horizontal,"用户姓名");
   model2->setHeaderData(2,Qt::Horizontal,"用户密码");
   model2->setHeaderData(3,Qt::Horizontal,"电话号码");
   model2->setHeaderData(4,Qt::Horizontal,"QQ号");
   model2->setHeaderData(5,Qt::Horizontal,"email");
   model2->setHeaderData(6,Qt::Horizontal,"地址");
   //model2->removeColumns(5,5);

   //创建buttongroup
   buttongroup=new QButtonGroup(this);
   buttongroup->addButton(ui->numradio,0);
   buttongroup->addButton(ui->nameradio,1);
   //连接inputedit信号和槽
   connect(ui->inputline,SIGNAL(textChanged(QString)),this,SLOT(inputeditSlot(QString)));
   connect(buttongroup,SIGNAL(buttonClicked(int)),this,SLOT(buttongroupSlot(int)));

}

UserManage::~UserManage()
{
    delete ui;
}

void UserManage::on_confirmbtn_clicked()
{
    int i;
    if(!this->judgeEmpty())
    {
        return;
    }
    model->select();

    for(i=0;i<model->rowCount();i++)
    {
        QSqlRecord record=model->record(i);
        if(record.value(0)==workerNum)
        {
            break;
        }
    }
    model->setData(model->index(i,0),ui->numLineEdit->text());
    model->setData(model->index(i,1),ui->nameLineEdit->text());
    model->setData(model->index(i,2),ui->passwordLineEdit->text());
    model->setData(model->index(i,3),ui->telephoneLineEdit->text());
    model->setData(model->index(i,4),ui->qqLineEdit->text());
    model->setData(model->index(i,5),ui->emailLineEdit->text());
    model->setData(model->index(i,6),ui->adressLineEdit->text());

    if(model->submitAll())
    {
        MessageDialog box(tr("提示"),"用户信息修改成功");
        box.exec();
    }
    else
    {
        MessageDialog box(tr("提示"),"用户信息修改失败");
        box.exec();
    }
    this->clearAll();
}

void UserManage::on_canclebtn_clicked()
{

    if( (ui->nameLineEdit->text().isEmpty())&&
        (ui->numLineEdit->text().isEmpty())&&
        (ui->passwordLineEdit->text().isEmpty())&&
        (ui->telephoneLineEdit->text().isEmpty())&&
        (ui->qqLineEdit->text().isEmpty())&&
        (ui->emailLineEdit->text().isEmpty())&&
        (ui->adressLineEdit->text().isEmpty()))
        {
            emit EmitToFirstPage();
            return;
        }

       MessageDialog box(tr("提示"),"尚未提交用户信息");
       box.exec();
       emit EmitToFirstPage();
       this->clearAll();
}

void UserManage::on_searchbtn_clicked()
{
    if(ui->inputline->text().isEmpty())
    {
        MessageDialog box(tr("警告"),"查询输入框不能为空!");
        box.exec();
        return;
    }

    if(buttongroup->checkedId()==0)
    {
        model2->setFilter("workernum="+ui->inputline->text());
        model2->select();
        if(model2->data(model2->index(0,0)).toString().isEmpty())
        {
            MessageDialog box(tr("警告"),"用户不存在!");
            box.exec();
            ui->userInfoSearchView->setModel(model2);
            ui->inputline->clear();
            return;
        }
        ui->userInfoSearchView->setModel(model2);
    }
    else if(buttongroup->checkedId()==1)
    {
        model2->setFilter( "name='"+ui->inputline->text()+"'");
        model2->select();
        if(model2->data(model2->index(0,0)).toString().isEmpty())
        {
            MessageDialog box(tr("警告"),"用户不存在!");
            box.exec();
            ui->userInfoSearchView->setModel(model2);
            ui->inputline->clear();
            return;
        }
        ui->userInfoSearchView->setModel(model2);
    }
    else
    {
        MessageDialog box(tr("警告"),"请选择查询方式!");
        box.exec();
    }
}

void UserManage::on_returnbtn_clicked()
{
    emit EmitToFirstPage();
}

void UserManage::emainlineSlot(QString)
{
    //设置completer
    QStringList list;
    list<<ui->emailLineEdit->text()+"@163.com"<<ui->emailLineEdit->text()+"@qq.com"
    <<ui->emailLineEdit->text()+"@sina.com"<<ui->emailLineEdit->text()+"@gmail.com";
    listModel=new QStringListModel(list,this);
    completer=new QCompleter(this);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    completer->setModel(listModel);
    ui->emailLineEdit->setCompleter(completer);
}

void UserManage::comeLOginDialog(QString theWorkerNum, QString theName)
{
    this->workerNum=theWorkerNum;
    this->workerName=theName;
    this->ui->numLineEdit->setText(workerNum);
    this->ui->nameLineEdit->setText(workerName);
}

void UserManage::inputeditSlot(QString)
{

}

void UserManage::buttongroupSlot(int)
{

}

bool UserManage::judgeEmpty()
{
    if(ui->nameLineEdit->text().isEmpty())
    {
        MessageDialog box(tr("警告"),"用户姓名不能为空!");
        box.exec();
        return false;
    }
    else if(ui->numLineEdit->text().isEmpty())
   {
        MessageDialog box(tr("警告"),"用户工作号不能为空!");
        box.exec();
       return false;
   }
    else if(ui->passwordLineEdit->text().isEmpty())
   {
        MessageDialog box(tr("警告"),"用户密码不能为空!");
        box.exec();
        return false;
   }
    else if(ui->telephoneLineEdit->text().isEmpty())
   {
       MessageDialog box(tr("警告"),"用户电话信息不能为空!");
       box.exec();
       return false;
   }
   else if(ui->qqLineEdit->text().isEmpty())
   {
       MessageDialog box(tr("警告"),"用户qq信息不能为空!");
       box.exec();
       return false;
   }
   else if(ui->emailLineEdit->text().isEmpty())
   {
       MessageDialog box(tr("警告"),"用户email信息不能为空!");
       box.exec();
       return false;
   }
   else if(ui->adressLineEdit->text().isEmpty())
   {
       MessageDialog box(tr("警告"),"用户家庭地址信息不能为空!");
       box.exec();
       return false;
   }
   else
       return true;
}

void UserManage::clearAll()
{
    ui->nameLineEdit->clear();
    ui->numLineEdit->clear();
    ui->passwordLineEdit->clear();
    ui->telephoneLineEdit->clear();
    ui->qqLineEdit->clear();
    ui->emailLineEdit->clear();
    ui->adressLineEdit->clear();
}
