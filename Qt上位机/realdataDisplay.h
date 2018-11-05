#ifndef REALDATADISPLAY_H
#define REALDATADISPLAY_H

#include <QWidget>
#include "text_label.h"
#include <QImage>
#include <QSqlTableModel>
#include <QSqlRecord>
#include <QDebug>

class RealDataDisplay : public QWidget
{
    Q_OBJECT
public:
    explicit RealDataDisplay(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event);
    int getCarbon() const;
    void setCarbon(int value);

    int getHumidity() const;
    void setHumidity(int value);

    int getIllumination() const;
    void setIllumination(int value);

    float getTemperature() const;
    void setTemperature(float value);

signals:
private:
    TextLabel *carbonLabel;
    TextLabel *illuminationLabel;
    TextLabel *temperatureLabel;
    TextLabel *humidityLabel;
private:
    int carbon;
    int humidity;
    int illumination;
    float temperature;
    int labelHight;
    int lableWidth;
    QSqlTableModel *model;
    int m_rowCount;

public slots:
    void timerUpDate();
};

#endif // REALDATADISPLAY_H
