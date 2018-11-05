#ifndef TABLEWIDGET_H
#define TABLEWIDGET_H

#include <QtWidgets/QWidget>
#include <QtWidgets/QTableView>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QVXYModelMapper>
#include <QtWidgets/QHeaderView>
#include "customtablemodel.h"

QT_CHARTS_USE_NAMESPACE
class TableWidget : public QWidget
{
    Q_OBJECT

public:
    TableWidget(const QString &color,const QString &text,const QString &theTableString);
    void paintEvent(QPaintEvent *event);
signals:
    //void updateData();
public slots:
    //void updateMydata();
    void timerUpDate();
private:
    QString seriesColorHex;
    QString curveText;
    CustomTableModel *model;
    QString tableString;
    QTableView *tableView;
  /*  QChartView *chartView;
    QVXYModelMapper *mapper;
    QChart *chart;
    QLineSeries *series;
    */
};

#endif // TABLEWIDGET_H
