#ifndef SYSINTRO_H
#define SYSINTRO_H

#include <QWidget>
#include <QLabel>
#include <QImage>

class SysIntro : public QWidget
{
    Q_OBJECT
public:
    explicit SysIntro(QWidget *parent = nullptr);
    virtual ~SysIntro();
signals:

public slots:
private:
    QLabel *myLabel;
};

#endif // SYSINTRO_H
