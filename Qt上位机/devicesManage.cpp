#include "devicesManage.h"
#include "ui_devicemanage.h"
#include "control.h"
#include <QDebug>

DevicesManage::DevicesManage(QWidget *parent) : QWidget(parent),ui(new Ui::DeviceManage)
{
    ui->setupUi(this);
    Util *util=new Util();
    this->setStyleSheet( util->getQssContent());
    this->setLayout(ui->horizontalLayout_3);

    ui->tableView->initTableView();
    ui->tableView->verticalHeader()->hide();
    loadFile("E:/stuInfo.txt");
    isFilter = false;

    connect(ui->btnAdd,SIGNAL(clicked()),this,SLOT(slotAddNewRow()));
    connect(ui->btnSave,SIGNAL(clicked()),this,SLOT(slotSave()));
    connect(ui->cbxYear,SIGNAL(currentIndexChanged(int)),this,SLOT(slotCbx()));
    connect(ui->cbxTerm,SIGNAL(currentIndexChanged(int)),this,SLOT(slotCbx()));
    connect(ui->btnRemove,SIGNAL(clicked()),this,SLOT(slotRemoveBtn()));
}

DevicesManage::~DevicesManage()
{

}

void DevicesManage::loadFile(QString fileName)
{
    QFile file(fileName);
    filePath = fileName;
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug()<<"Error: 没有找到数据文件"<<fileName;
        exit(1);
    }

    QTextStream in(&file);

    curStu.sNumber = in.readLine();
    curStu.sName = in.readLine();
    ui->bigSyslabel->setText(curStu.sName+"\n"+curStu.sNumber+"号");
    QString line = in.readLine();

    while (!line.isNull())
    {
        qDebug()<<line<<endl;
        qDebug()<<"---------------------------"<<endl;
        SubSystem temp(line);
        curStu.addSubSystem(temp);
       line = in.readLine();
    }

    curCour = curStu.subSystems;
    ui->tableView->updateTableView(curCour);
    initCbxSysName();
    updateInfo();

    file.close();

}

void DevicesManage::initCbxSysName()
{
    ui->cbxYear->clear();
    ui->cbxTerm->clear();
    ui->cbxYear->addItem("全部");
    ui->cbxTerm->addItem("全部");
    QStringList list;
    QStringList list1;
    for(int i=0; i<curStu.subSystems.size();i++)
    {
        bool f = false;
        QString newItem =  curStu.subSystems[i].sysName;
        for(int k=0; k<list.size(); k++)
        {
            if(list[k] == newItem)
            {
                f = true;
                break;
            }
        }

        if(f == false)
        {
            ui->cbxYear->addItem(newItem);
            list.push_back(newItem);
        }
    }

    for(int i=0; i<curStu.subSystems.size();i++)
    {
        bool f = false;
        QString newItem = curStu.subSystems[i].deviceNode;
        for(int k=0; k<list1.size(); k++)
        {
            if(list1[k] == newItem)
            {
                f = true;
                break;
            }
        }

        if(f == false)
        {
            ui->cbxTerm->addItem(newItem);
            list1.push_back(newItem);
        }
    }
}

void DevicesManage::updateInfo()
{
    QString sysName ="";
    int totalNodeNum = 0;
    QString currentNode ="";

    sysName = ui->cbxYear->currentText();
    currentNode = ui->cbxTerm->currentText();
    totalNodeNum = ui->cbxTerm->count()-1;

    ui->SysNameLabel->setText(sysName);
    ui->currentNodeLabel->setText(currentNode);
    ui->TotalNodeNumLabel->setText(QString::number(totalNodeNum));
}

void DevicesManage::slotAddNewRow()
{
    isAddNewRows=true;
    ui->tableView->appendNewRow();
}

void DevicesManage::slotSave()
{
    bool noError = true;
    if(!isFilter)
    {
        curStu.clearAllSubsystem();
        for(int i=0; i<ui->tableView->model->rowCount(); i++)
        {
            noError = curStu.addSubSystem(ui->tableView->getSubsystemAt(i));
        }
    }
    else
    {
        for(int i=0; i<ui->tableView->model->rowCount();i++)
        {
            SubSystem temp = ui->tableView->getSubsystemAt(i);
            if(curStu.isExisted(temp))
            {
                noError = curStu.updateSubsystem(temp);
            }
            else
            {
                noError = curStu.addSubSystem(temp);
            }
        }
    }

    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream out(&file);
    out<<curStu.toString();

    //curCour = curStu.subSystems;
    QString sysName = ui->cbxYear->currentText();
    QString deviceNode = ui->cbxTerm->currentText();
    curCour = curStu.fileterByName(sysName,deviceNode);
    ui->tableView->updateTableView(curCour);
    //initCbxSysName();
    updateInfo();
    file.close();

    if(!noError)
    {
        //Dialog * diag = new Dialog();
        //diag->exec();
    }
}

void DevicesManage::slotCbx()
{
    QString sysName;
    QString deviceNode;
  /*  if(ui->cbxYear->currentIndex() == 0)
        sysName ="全部";
    else

    QString deviceNode;
    if(ui->cbxYear->currentIndex() == 0)
        deviceNode ="全部";
    else
        deviceNode = ui->cbxTerm->currentText();
*/
    sysName = ui->cbxYear->currentText();
    deviceNode = ui->cbxTerm->currentText();
    curCour = curStu.fileterByName(sysName,deviceNode);
    ui->tableView->updateTableView(curCour);

    if((sysName =="全部") && (deviceNode =="全部"))
        isFilter = false;
    else
        isFilter = true;
    updateInfo();
}

void DevicesManage::slotRemoveBtn()
{
    if(!ui->tableView->isSelected())
        return;

    DiagRemove* diag = new DiagRemove(this);
    QPropertyAnimation* anim = new QPropertyAnimation(diag,"pos");
    anim->setStartValue(QPoint(width()-319,height()));
    anim->setEndValue(QPoint(width()-319,height()-115));
    anim->setDuration(250);
    anim->start();
    diag->setVisible(true);

    connect(diag,SIGNAL(sigBtn(bool)),this,SLOT(slotRemoveSelected(bool)));
    ui->tableView->makeRowAllItemSelected();

}

void DevicesManage::slotRemoveSelected(bool b)
{
    if(b == false)
        return;
    QString sysName = ui->cbxYear->currentText();
    QString deviceNode = ui->cbxTerm->currentText();
    savedCour=curStu.fileterByName(sysName,deviceNode);
    ui->tableView->removeSelected(curStu);
    isRemoveRows=true;
    QFile file("E:/out.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    QTextStream out(&file);
    out<<curStu.toString();

    //curCour = curStu.subSystems;
    curCour = curStu.fileterByName(sysName,deviceNode);
    ui->tableView->updateTableView(curCour);
    //initCbxSysName();
    //updateInfo();
    file.close();

}


void DevicesManage::on_btnRedo_clicked()
{
    if(isAddNewRows)
    {
        QString sysName = ui->cbxYear->currentText();
        QString deviceNode = ui->cbxTerm->currentText();
        curCour=curStu.fileterByName(sysName,deviceNode);
         ui->tableView->updateTableView(curCour);
    }
    if(isRemoveRows)
        ui->tableView->updateTableView(savedCour);
}
