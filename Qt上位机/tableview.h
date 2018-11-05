#ifndef TABLEVIEW_H
#define TABLEVIEW_H

#include <QTableView>
#include <QStandardItemModel>
#include <QWidget>
#include <QHeaderView>
//#include "student.h"
#include "bigsystem.h"

class TableView : public QTableView
{
    Q_OBJECT
public:
    explicit TableView(QWidget *parent = 0);
    QStandardItemModel* model;
    void initTableView();       // 设置表头
    void updateTableView(QVector<SubSystem> ref);
    void appendNewRow();       // 追加新的一行( 不会修改到curStu)
    SubSystem getSubsystemAt(int row);  // 得到当前显示在TableView的课程中，第row行的课程Course
    bool isSelected();        // 获取状态：当前是否选中1行或若干行
    void makeRowAllItemSelected();    // 全选当前选中的item所在的一行
    void removeSelected(BigSystem& ref);   // 删除选中的行
    void restoreRemoved();
private:
    void setRowAlignCenter(int row);
    void handleSumGradeFont(int row,int col);
    void setHeaderStyle();
    // 一些数据类型转换函数
    Run StringToTerm(QString s);
    QString TermToString(int term);
    Normal StringTorunState(QString s);
    QString runStateToString(int term);
    int myToInt(QString s);
    float myToFloat(QString s);
    QString NumberToString(float n);
public slots:
    void slotClicked();
};

#endif // TABLEVIEW_H
