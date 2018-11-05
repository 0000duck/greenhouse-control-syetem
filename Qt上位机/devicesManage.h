#ifndef DEVICESMANAGE_H
#define DEVICESMANAGE_H

#include <QWidget>
#include <QStandardItemModel>
#include <QResizeEvent>
#include <QTime>
#include <QPropertyAnimation>
#include "diagremove.h"
#include "tableview.h"
#include "dialog.h"
#include <QTextStream>
#include <QDebug>

namespace Ui {
class DeviceManage;
}
class DevicesManage: public QWidget
{
    Q_OBJECT
public:
    explicit DevicesManage(QWidget *parent = nullptr);
    virtual ~DevicesManage();

    BigSystem curStu;
    QVector<SubSystem> curCour;   // 经过筛选过后的成绩单，显示在tableView上的成绩单
    QVector<SubSystem> savedCour;
    bool isFilter;               // 是否有筛选，将影响slotSave()的方式
    void loadFile(QString fileName);
    bool isAddNewRows=false;
    bool isRemoveRows=false;
private:
    QString filePath;  // 记录数据库文件的位置
    void initCbxSysName();
    void updateInfo();
public slots:
    void slotAddNewRow();
    void slotSave();
    void slotCbx();
    void slotRemoveBtn();
    void slotRemoveSelected(bool b);
private slots:
    void on_btnRedo_clicked();

private:
    Ui::DeviceManage *ui;
};

#endif // DEVICESMANAGE_H
