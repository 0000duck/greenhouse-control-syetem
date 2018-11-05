#ifndef REALTIMECURVEQCHARTWIDGET_H
#define REALTIMECURVEQCHARTWIDGET_H

#include <QWidget>
#include <QList>
#include <QSplineSeries>
#include <QScatterSeries>
#include <QChart>
#include <QChartView>
#include <QSqlTableModel>
#include <QSqlRecord>

using namespace QtCharts;
class RealTimeCurveQChartWidget : public QWidget {
    Q_OBJECT
public:
    explicit RealTimeCurveQChartWidget(const QString &color,const QString &text,
                                       const int &theMaxValue,const QString &theTableName);

    ~RealTimeCurveQChartWidget();
    void dataReceived(double value);
protected:
    void timerEvent(QTimerEvent *event) Q_DECL_OVERRIDE;
private:
    /**
     * 接收到数据源发送来的数据，数据源可以下位机，采集卡，传感器等。
     */
    QString seriesColorHex;
    QString curveText;
    int maxValue; // 业务数据的最大值
    QString tableName;
    int timerId;
    int maxSize=32;  // data 最多存储 maxSize 个元素
    QList<double> data; // 存储业务数据的 list
    QChart *chart;
    QChartView *chartView;
    QSplineSeries *splineSeries;
    QScatterSeries *scatterSeries;
    QSqlTableModel *model;

};
#endif // REALTIMECURVEQCHARTWIDGET_H
