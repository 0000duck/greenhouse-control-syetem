#ifndef CONTROL_SLIDER_H
#define CONTROL_SLIDER_H

#include <QWidget>
#include "sliderruler.h"
#include <QLabel>
#include <QHBoxLayout>

class ControlSlider : public QWidget
{
    Q_OBJECT
public:
    ControlSlider(const QString &theLabelString,const double &theValue,const double &theMaxValue,
                  const double &theMinValue,const int &thePrecision,const int &theLongstep,
                  const int &theShortStep,const int &theSpace );
    ~ControlSlider();
    //double getCurrentValue() const;
   // void setCurrentValue(double value);
    QString getLabelString() const;
    void setLabelString(const QString &value);

    double getValue() const;
    void setValue(double value);

    double getMaxValue() const;
    void setMaxValue(double value);

    double getMinValue() const;
    void setMinValue(double value);

    int getPrecision() const;
    void setPrecision(int value);

    int getLongStep() const;
    void setLongStep(int value);

    int getShortStep() const;
    void setShortStep(int value);

    int getSpace() const;
    void setSpace(int value);

signals:

public slots:
    void setSliderValue(double theValue);
private:
    QString labelString;
    double value;               //目标值
    double maxValue;            //最小值
    double minValue;            //最大值
    int precision;              //精确度,小数点后几位
    int longStep;               //长线条等分步长
    int shortStep;              //短线条等分步长
    int space;                  //间距

    QLabel *leftLabel;
    SliderRuler *rightSliderRuler;
    QHBoxLayout *hboxlayout;
};

#endif // CONTROL_SLIDER_H
