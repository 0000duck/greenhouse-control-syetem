#ifndef WARNINGHANDLE_H
#define WARNINGHANDLE_H

#include <QWidget>
#include <QLabel>
#include "qledindicator.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "realdataDisplay.h"
#include <QTimer>

class WarningHandle : public QWidget
{
    Q_OBJECT
public:
    explicit WarningHandle(QWidget *parent = nullptr);
    virtual ~WarningHandle();
    float getTemperatureMaxValue() const;
    void setTemperatureMaxValue(float value);

    float getTemperatureMinValue() const;
    void setTemperatureMinValue(float value);

    int getHumidityMaxValue() const;
    void setHumidityMaxValue(int value);

    int getHumidityMinValue() const;
    void setHumidityMinValue(int value);

    int getIlluminationMaxValue() const;
    void setIlluminationMaxValue(int value);

    int getIlluminationMinValue() const;
    void setIlluminationMinValue(int value);

    int getCarbonMaxValue() const;
    void setCarbonMaxValue(int value);

    int getCarbonMinValue() const;
    void setCarbonMinValue(int value);

signals:

public slots:
    void checkState();
    void cShow();
    void iShow();
    void tShow();
    void hShow();
private:
    QLabel *carbonLabel;
    QLabel *illuminationLabel;
    QLabel *temperatureLabel;
    QLabel *humidityLabel;
    QLedIndicator *carbonLedIndicator;
    QLedIndicator *illuminationLedIndicator;
    QLedIndicator *temperatureIndicator;
    QLedIndicator *humidityLedIndicator;
    QVBoxLayout *carbonVBoxLayout;
    QVBoxLayout *illuminationVBoxLayout;
    QVBoxLayout *temperatureVBoxLayout;
    QVBoxLayout *humidityVBoxLayout;
    QHBoxLayout *mainLayout;

    float temperatureMaxValue=60;
    float temperatureMinValue=4;
    int humidityMaxValue=95;
    int humidityMinValue=10;
    int illuminationMaxValue=7000;
    int illuminationMinValue=200;
    int carbonMaxValue=2000;
    int carbonMinValue=100;

    RealDataDisplay *realDataDisplay;

    bool temperatureAbnormalFlag=0;
    bool humidityAbnormalFlag=0;
    bool illuminationAbnormalFlag=0;
    bool carbonAbnormalFlag=0;

    QTimer *temperatureTimer ;
    QTimer *humidityTimer ;
    QTimer *illuminationTimer ;
    QTimer *carbonTimer ;
};

#endif // WARNINGHANDLE_H
