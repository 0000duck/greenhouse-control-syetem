#ifndef DAPENGINTRO_H
#define DAPENGINTRO_H

#include <QWidget>
#include <QLabel>
#include <QImage>

class DapengIntro : public QWidget
{
    Q_OBJECT
public:
    explicit DapengIntro(QWidget *parent = nullptr);
    virtual ~DapengIntro();
signals:

public slots:
private:
    QLabel *myLabel;
};

#endif // DAPENGINTRO_H
