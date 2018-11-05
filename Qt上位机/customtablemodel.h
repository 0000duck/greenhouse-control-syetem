#ifndef CUSTOMTABLEMODEL_H
#define CUSTOMTABLEMODEL_H

#include <QtCore/QAbstractTableModel>
#include <QtCore/QHash>
#include <QtCore/QRect>
#include <QSqlTableModel>
#include <QSqlRecord>

class CustomTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit CustomTableModel(QObject *parent = 0,const QString &tableString="temperature");

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
    Qt::ItemFlags flags(const QModelIndex &index) const;

    void addMapping(QString color, QRect area);
    void clearMapping() { m_mapping.clear(); }
    void setDatas();

private:
    QList<QVector<qreal> * > m_data;
    QHash<QString, QRect> m_mapping;
    QSqlTableModel *model;
    int m_columnCount;
    int m_rowCount;
    QString tableName;
public slots:
    //void updateData();
};

#endif // CUSTOMTABLEMODEL_H
