#include "tableview.h"
#include <QDebug>

TableView::TableView(QWidget *parent) :
    QTableView(parent)
{
    connect(this,SIGNAL(clicked(QModelIndex)),this,SLOT(slotClicked()));
    setSortingEnabled(true);
    setAlternatingRowColors(true);
    model = new QStandardItemModel();
    setModel(model);
}

void TableView::initTableView()
{
    model->setHorizontalHeaderItem(0, new QStandardItem(tr("系统名")));
    model->setHorizontalHeaderItem(1, new QStandardItem(tr("设备节点")));
    model->setHorizontalHeaderItem(2, new QStandardItem(tr("设备ID")));
    model->setHorizontalHeaderItem(3, new QStandardItem(tr("温度(℃)")));
    model->setHorizontalHeaderItem(4, new QStandardItem(tr("湿度(%RH)")));
    model->setHorizontalHeaderItem(5, new QStandardItem(tr("光照强度(LX)")));
    model->setHorizontalHeaderItem(6, new QStandardItem(tr("CO2浓度(PPM)")));
    model->setHorizontalHeaderItem(7, new QStandardItem(tr("是否运行(Y/N)")));
    model->setHorizontalHeaderItem(8, new QStandardItem(tr("是否正常(Y/N)")));

    setColumnWidth(0,200);
    setColumnWidth(1,80);
    setColumnWidth(2,80);
    setColumnWidth(3,100);
    setColumnWidth(4,100);
    setColumnWidth(5,100);
    setColumnWidth(6,100);
    setColumnWidth(7,100);
    setColumnWidth(8,100);
}

void TableView::appendNewRow()
{
    model->appendRow(new QStandardItem(""));
    this->setCurrentIndex(QModelIndex(model->item(model->rowCount()-1)->index()));
}

SubSystem TableView::getSubsystemAt(int row)
{
    QStringList list;
    for(int i=0; i<model->columnCount(); i++)
    {
        list<<model->index(row,i).data().toString();
    }

    SubSystem temp;
    temp.sysName = list[0];
    temp.deviceNode = list[1];
    temp.deviceID = list[2];
    temp.temperature = myToFloat(list[3]);
    temp.humidity = myToFloat(list[4]);
    temp.illumination = myToInt(list[5]);
    temp.carbon = myToInt(list[6]);
    temp.isOn =StringToTerm(list[7]);
    temp.runState =StringTorunState(list[8]);
    return temp;
}

void TableView::updateTableView(QVector<SubSystem> ref)
{
    model->clear();
    initTableView();

    for(int i=0; i<ref.size(); i++)
    {
        model->setVerticalHeaderItem(i,new QStandardItem(QString::number(i+1)));
        model->setItem(i,0,new QStandardItem(ref[i].sysName));
        model->setItem(i,1,new QStandardItem(ref[i].deviceNode));
        model->setItem(i,2,new QStandardItem(ref[i].deviceID));
        model->setItem(i,3,new QStandardItem(NumberToString(ref[i].temperature)));
        model->setItem(i,4,new QStandardItem(NumberToString(ref[i].humidity)));
        model->setItem(i,5,new QStandardItem(NumberToString(ref[i].illumination)));
        model->setItem(i,6,new QStandardItem(NumberToString(ref[i].carbon)));
        model->setItem(i,7,new QStandardItem(TermToString(ref[i].isOn)));
        model->setItem(i,8,new QStandardItem(TermToString(ref[i].runState)));
        handleSumGradeFont(i,7);
        setRowAlignCenter(i);
    }

    setHeaderStyle();
}

Run TableView::StringToTerm(QString s)
{
    if(s == "Y")
        return run;
    else
        return notRun;

}

QString TableView::TermToString(int term)
{
    switch (term) {
    case 0:
        return "Y";
    case 1:
        return "N";
    default:
        return "";
    }

}

Normal TableView::StringTorunState(QString s)
{
    if(s == "Y")
        return normal;
    else
        return notNormal;
}

QString TableView::runStateToString(int term)
{
    switch (term) {
    case 0:
        return "Y";
    case 1:
        return "N";
    default:
        return "";
    }

}

int TableView::myToInt(QString s)
{
    if(s == "0")
        return 0;

    int val = s.toInt();
    if(val == 0)
        return -1;

    return val;
}

float TableView::myToFloat(QString s)
{
    if(s == "0" || s == "0.0")
        return 0;

    float val = s.toFloat();
    if(val == 0)
        return -1;

    return val;
}

QString TableView::NumberToString(float n)
{
    if(n== -1)
        return "";

    return QString::number(n);
}

void TableView::slotClicked()
{

}

void TableView::setRowAlignCenter(int row)
{
    for(int i=0; i<model->columnCount();i++)
    {
        model->item(row,i)->setTextAlignment(Qt::AlignCenter);
    }
}

void TableView::handleSumGradeFont(int row, int col)
{
    // 字体加粗
    QFont font = model->item(row,col)->font();

    font.setBold(true);
    model->item(row,col)->setFont(font);
    Run val = StringToTerm(model->item(row,col)->text());
    Normal val1 = StringTorunState(model->item(row,col+1)->text());
    if( val==run)
        model->item(row,col)->setForeground(QBrush(QColor(255, 0, 0)));

    else
        model->item(row,col)->setForeground(QBrush(QColor(0, 0, 0)));
    if( val1==normal)
        model->item(row,col+1)->setForeground(QBrush(QColor(255, 0, 0)));

    else
        model->item(row,col+1)->setForeground(QBrush(QColor(0, 0, 0)));
}

void TableView::setHeaderStyle()
{
    QString qss = "QHeaderView::section, QTableCornerButton::section {"
            "padding: 1px;"
            "border: none;"
            "border-bottom: 1px solid rgb(160, 160, 160);"
            "border-right: 1px solid rgb(160, 160, 160);"
            "border-bottom: 1px solid gray;"
            "background-color: #DCDCDC;}";

    this->horizontalHeader()->setStyleSheet(qss);
    this->verticalHeader()->setStyleSheet(qss);
}

bool TableView::isSelected()
{
    if(this->selectedIndexes().isEmpty())
        return false;
    return true;
}

void TableView::makeRowAllItemSelected()
{
    QModelIndexList list =selectedIndexes();

    setSelectionMode(QAbstractItemView::MultiSelection);  // 允许多行选择
    for(int i=0; i<list.size();i++)
    {
        int row = list[i].row();
        selectRow(row);
    }
    setSelectionMode(QAbstractItemView::ExtendedSelection);  // 允许多行选择
}

void TableView::removeSelected(BigSystem& ref)
{
    QModelIndexList list =selectedIndexes();
    QVector<QString> vec(3);
    QList< QVector<QString> >  vecList;

    for(int i=0; i<list.size();i++)
    {
        int row = list[i].row();

        QString sysName = model->item(row,0)->text();
        QString deviceNode = model->item(row,1)->text();
        QString deviceID = model->item(row,2)->text();
        vec.clear();
        vec.push_back(sysName);
        vec.push_back(deviceNode);
        vec.push_back(deviceID);
        if(vecList.indexOf(vec) == -1)
        {
             vecList.push_back(vec);
        }
    }

    for(int i=0; i<vecList.size();i++)
    {
        ref.removeSubsystem(vecList[i].at(0),vecList[i].at(1),vecList[i].at(2));
        qDebug()<<"移除"<<endl;
        qDebug()<<vecList[i].at(0)<<" "<<vecList[i].at(1)<<" "<<vecList[i].at(2)<<endl;
    }
}
