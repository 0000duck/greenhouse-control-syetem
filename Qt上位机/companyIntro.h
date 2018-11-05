#ifndef COMPANYINTRO_H
#define COMPANYINTRO_H

#include <QWidget>
#include <QLabel>
#include <QImage>

class CompanyIntro : public QWidget
{
    Q_OBJECT
public:
    explicit CompanyIntro(QWidget *parent = nullptr);
    virtual ~CompanyIntro();
signals:

public slots:
private:
    QLabel *myLabel;
};

#endif // COMPANYINTRO_H
