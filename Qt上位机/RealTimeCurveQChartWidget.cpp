#include "RealTimeCurveQChartWidget.h"
#include <QDateTime>
#include <QHBoxLayout>
RealTimeCurveQChartWidget::RealTimeCurveQChartWidget(const QString &color,const QString &text,
                                                     const int &theMaxValue,const QString &theTableName)
    :seriesColorHex(color),
    curveText(text),
    maxValue(theMaxValue),
    tableName(theTableName)
{
  /*  this->setStyleSheet(
                  "border-style:none;"
                   //"border-style: outset;"
                  "border-width: 2px;"
                  "border-radius: 1px;"
                 "border-color: #CD853F;");
*/

    timerId = startTimer(200);
    qsrand(QDateTime::currentDateTime().toTime_t());
    splineSeries = new QSplineSeries();
    scatterSeries = new QScatterSeries();
    scatterSeries->setMarkerSize(8);

    scatterSeries->setName(text);
    scatterSeries->setColor(QColor(seriesColorHex));

    splineSeries->setName(text);
    splineSeries->setColor(QColor(seriesColorHex));

    // 预先分配坐标，这样在 dataReceived 中直接替换坐标了
    for (int i = 0; i < maxSize; ++i) {
        splineSeries->append(i * 10, -10);
        scatterSeries->append(i * 10, -10);
    }
    chart = new QChart();
    chart->addSeries(splineSeries);
    chart->addSeries(scatterSeries);
    chart->legend()->hide();
    chart->setTitle(text);
    chart->createDefaultAxes();
    chart->axisY()->setRange(0, maxValue);
    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setStyleSheet("border-style:none;"
                             //"border-style: outset;"
                            "border-width: 2px;"
                            "border-radius: 1px;"
                           "border-color: #CD853F;");
    QHBoxLayout *layout = new QHBoxLayout();
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(chartView);
    setLayout(layout);
}
RealTimeCurveQChartWidget::~RealTimeCurveQChartWidget()
{

}

void RealTimeCurveQChartWidget::timerEvent(QTimerEvent *event)
{
    if (event->timerId() == timerId) {
        // 模拟不停的接收到新数据
        //int newData = qrand() % (maxValue + 1);
        bool ok;
        double newData=0.0;
        //创建model,进行数据库操作
        model=new QSqlTableModel(this);
        model->setEditStrategy(QSqlTableModel::OnManualSubmit);

        //设置table为相应表
        model->setTable(tableName);
        model->select();

        if((model->rowCount()-1)>=0)
        {
            QSqlRecord record=model->record(model->rowCount()-1);
            newData=record.value(1).toFloat(&ok);
        }
        dataReceived(newData);
    }
}
void RealTimeCurveQChartWidget::dataReceived(double value)
{
    data << value;
    // 数据个数超过了指定值，则删除最先接收到的数据，实现曲线向前移动
    while (data.size() > maxSize) {
        data.removeFirst();
    }
    if (isVisible()) {
        // 界面被隐藏后就没有必要绘制数据的曲线了
        // 替换曲线中现有数据
        int delta = maxSize - data.size();
        for (int i = 0; i < data.size(); ++i) {
            splineSeries->replace(delta+i, splineSeries->at(delta+i).x(), data.at(i));
            scatterSeries->replace(delta+i, scatterSeries->at(delta+i).x(), data.at(i));
        }
    }
}
