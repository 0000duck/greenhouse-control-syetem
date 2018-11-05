#ifndef USERMANAGE_H
#define USERMANAGE_H

#include <QWidget>
#include <QSqlTableModel>
#include <QSqlRecord>
#include <QMessageBox>
#include <QDebug>
#include <QStringList>
#include <QCompleter>
#include <QStringListModel>
#include <QHBoxLayout>
#include <QButtonGroup>

namespace Ui {
class UserManage;
}

class UserManage : public QWidget
{
    Q_OBJECT

public:
    explicit UserManage(QWidget *parent=0);
    ~UserManage();
    bool judgeEmpty();
    void clearAll();
signals:
    void EmitToFirstPage();
private slots:
    void on_confirmbtn_clicked();
    void on_canclebtn_clicked();
    void on_searchbtn_clicked();
    void on_returnbtn_clicked();
    void emainlineSlot(QString);
    void comeLOginDialog(QString theWorkerNum,QString theName);

    void inputeditSlot(QString);
    void buttongroupSlot(int);
private:
   Ui::UserManage *ui;
   QString workerNum;
   QString workerName;
   QSqlTableModel *model;
   QStringListModel *listModel;
   QCompleter *completer;
   QHBoxLayout *mainLayout;
   QSqlTableModel *model1;
   QSqlTableModel *model2;
   QButtonGroup  *buttongroup;
};

#endif // USERMANAGE_H
