#include "tablewidget.h"
#include <QtWidgets/QGridLayout>
#include <QTimer>
#include <QDebug>

QT_CHARTS_USE_NAMESPACE

TableWidget::TableWidget(const QString &color,const QString &text,const QString &theTableString):seriesColorHex(color),
        curveText(text)
{
    tableString=theTableString;
    // create simple model for storing data
    // user's table data model
    model = new CustomTableModel(nullptr,tableString);
    //connect(this,SIGNAL(updateData()),model,SLOT(updateData()));
    // create table view and add model to it
    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(timerUpDate()));
    timer->start(2000);
/*
 ui->operatorInfoTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
ui->operatorInfoTableView->setSelectionMode ( QAbstractItemView::SingleSelection);
ui->operatorInfoTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

*/
    //设置QTableView只能选中单行，不可编辑
    tableView = new QTableView;
    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    //tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    tableView->setModel(model);
    tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tableView->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
/*
    chart = new QChart;
    chart->setAnimationOptions(QChart::AllAnimations);

    series = new QLineSeries;
    series->setUseOpenGL(true);
    //tr("温度曲线(T/℃)")
    series->setName(text);
    series->setColor(QColor(seriesColorHex));
    mapper = new QVXYModelMapper(this);
    mapper->setXColumn(0);
    mapper->setYColumn(1);
    mapper->setSeries(series);
    mapper->setModel(model);

    chart->addSeries(series);

    model->addMapping(seriesColorHex, QRect(0, 0, 2, model->rowCount()));

    chart->createDefaultAxes();
    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setMinimumSize(450, 300);
*/
    // create main layout
    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(tableView, 1, 0);
  //  mainLayout->addWidget(chartView, 1, 1);
  //  mainLayout->setColumnStretch(1, 1);
    mainLayout->setColumnStretch(0, 0);
    setLayout(mainLayout);

    this->setStyleSheet("background-color: rgb(0, 170, 0);"
                                     // "border-style: outset;"
                                      "border-width: 2px;"
                                      "border-radius: 10px;"
                        "border-color: beige;");
}

void TableWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    tableView->setModel(model);

   // series->setName(curveText);
   // series->setColor(QColor(seriesColorHex));
    //mapper->setXColumn(0);
    //mapper->setYColumn(1);
    //mapper->setSeries(series);
    //mapper->setModel(model);
    //chart->addSeries(series);
    //model->addMapping(seriesColorHex, QRect(0, 0, 2, model->rowCount()));
    //chart->createDefaultAxes();

    tableView->show();
    //chartView->show();
    qDebug()<<tr("TableWidget:%1更新数据").arg(tableString)<<endl;
}

void TableWidget::timerUpDate()
{
    model->setDatas();
    this->update();
}

