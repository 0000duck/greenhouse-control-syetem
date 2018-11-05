#ifndef DIAGREMOVE_H
#define DIAGREMOVE_H

#include <QWidget>
#include <QPaintEvent>
#include <QPainter>

namespace Ui {
class DiagRemove;
}

class DiagRemove : public QWidget
{
    Q_OBJECT

public:
    explicit DiagRemove(QWidget *parent = 0);
    ~DiagRemove();
protected:
    void paintEvent(QPaintEvent *event);

signals:
    void sigBtn(bool a);

public slots:
    void slotOk();
    void slotCancle();

private:
    Ui::DiagRemove *ui;
};

#endif // DIAGREMOVE_H
