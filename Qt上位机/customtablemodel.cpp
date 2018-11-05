#include "customtablemodel.h"
#include <QtCore/QVector>
#include <QtCore/QTime>
#include <QtCore/QRect>
#include <QtGui/QColor>
#include <QDebug>

CustomTableModel::CustomTableModel(QObject *parent,const QString &tableString) :
    QAbstractTableModel(parent)
{    
    tableName=tableString;
    m_columnCount = 2;


    //创建model,进行数据库操作
    model=new QSqlTableModel(this);
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);

    //设置table为相应表
    model->setTable(tableName);
    model->select();
    m_rowCount =model->rowCount();
    qDebug()<<tr("%1表格有%2行").arg(tableName).arg(m_rowCount)<<endl;

    for(int i=0;i<model->rowCount();i++)
    {
        bool ok;
        QSqlRecord record=model->record(i);
        QVector<qreal>* dataVec = new QVector<qreal>(m_columnCount);
        //判断信息是否为空,非空就把信息插入表格模型中
         if((record.value(0)!="")&&(record.value(1)!=""))
        {
             for (int k = 0; k < dataVec->size(); k++)
             {
                if (k % 2 == 0)
                     dataVec->replace(k,record.value(0).toReal(&ok) );
                 else
                     dataVec->replace(k,record.value(1).toReal(&ok));
             }
             m_data.append(dataVec);
        }
    }

}

int CustomTableModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_data.count();
}

int CustomTableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_columnCount;
}

QVariant CustomTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal) {
        if (section % 2 == 0)
            return "x";
        else
            return "y";
    } else {
        return QString("%1").arg(section + 1);
    }
}

QVariant CustomTableModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole) {
        return m_data[index.row()]->at(index.column());
    } else if (role == Qt::EditRole) {
        return m_data[index.row()]->at(index.column());
    } else if (role == Qt::BackgroundRole) {
        foreach (QRect rect, m_mapping) {
            if (rect.contains(index.column(), index.row()))
                return QColor(m_mapping.key(rect));
        }
        // cell not mapped return white color
        return QColor(Qt::white);
    }
    return QVariant();
}


bool CustomTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.isValid() && role == Qt::EditRole) {
        m_data[index.row()]->replace(index.column(), value.toDouble());
        emit dataChanged(index, index);
        return true;
    }
    return false;
}


Qt::ItemFlags CustomTableModel::flags(const QModelIndex &index) const
{
    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

void CustomTableModel::addMapping(QString color, QRect area)
{
    m_mapping.insertMulti(color, area);
}

void CustomTableModel::setDatas()
{
    //创建model,进行数据库操作
    model=new QSqlTableModel(this);
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);

    //设置table为相应表
    model->setTable(tableName);
    model->select();
    m_rowCount =model->rowCount();

    //m_data.clear();
    for(int i=0;i<model->rowCount();i++)
    {
        bool ok;
        QSqlRecord record=model->record(i);
        QVector<qreal>* dataVec = new QVector<qreal>(m_columnCount);
        //判断信息是否为空,非空就把信息插入表格模型中
         if((record.value(0)!="")&&(record.value(1)!=""))
        {
             for (int k = 0; k < dataVec->size(); k++)
             {
                if (k % 2 == 0)
                     dataVec->replace(k,record.value(0).toReal(&ok) );
                 else
                     dataVec->replace(k,record.value(1).toReal(&ok));
             }
             m_data.replace(i,dataVec);

        }
    }
    emit layoutChanged();
}


