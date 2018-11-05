#ifndef HISTORYDATADISPLAY_H
#define HISTORYDATADISPLAY_H

#include <QWidget>
#include "RealTimeCurveQChartWidget.h"

class HistoryDataDisplay : public QWidget
{
    Q_OBJECT
public:
    explicit HistoryDataDisplay(QWidget *parent = nullptr);
    virtual ~HistoryDataDisplay();
    //void paintEvent(QPaintEvent *event);
    //void getData(int id,double value);
signals:
   //void updateMyData();
public slots:
   //void updateData();
    void timerUpDate();
private:
    RealTimeCurveQChartWidget *temperatureTableWidget;
    RealTimeCurveQChartWidget *illumilationTableWidget;
    RealTimeCurveQChartWidget *carbonTableWidget;
    RealTimeCurveQChartWidget *humidityTableWidget;
    int tableWidth;
    int tableHight;

};

#endif // HISTORYDATADISPLAY_H
