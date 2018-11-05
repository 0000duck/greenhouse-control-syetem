#include "control_slider.h"
#include <QDebug>
#include <QTimer>

ControlSlider::ControlSlider(const QString &theLabelString,
                             const double &theValue,
                             const double &theMaxValue,
                             const double &theMinValue,
                             const int &thePrecision,
                             const int &theLongstep,
                             const int &theShortStep,
                             const int &theSpace):
    labelString(theLabelString),value(theValue),maxValue(theMaxValue),minValue(theMinValue),
    precision(thePrecision),longStep(theLongstep),shortStep(theShortStep),space(theSpace)
{
    leftLabel=new QLabel(this);
    leftLabel->setFont(QFont("Microsoft Yahei", 10));
    leftLabel->setText(labelString);

    leftLabel->setTextFormat(Qt::RichText);//文本格式
    leftLabel->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);//对齐方式
    leftLabel->setAutoFillBackground(true);
    leftLabel->setFixedWidth(50);

    rightSliderRuler=new SliderRuler(value,maxValue,minValue,
                                     precision,longStep,shortStep,space);
    rightSliderRuler->setSliderColor(QColor(1, 139, 0), QColor(101, 205, 107));

    hboxlayout=new QHBoxLayout();
    hboxlayout->setMargin(10);
    hboxlayout->setSpacing(10);
    hboxlayout->addWidget(leftLabel);
    hboxlayout->addWidget(rightSliderRuler);
    hboxlayout->setStretch(0,0);
    hboxlayout->setStretch(1,1);

    this->setLayout(hboxlayout);

}

ControlSlider::~ControlSlider()
{
    delete leftLabel;
    delete rightSliderRuler;
}

QString ControlSlider::getLabelString() const
{
    return labelString;
}

void ControlSlider::setLabelString(const QString &value)
{
    labelString = value;
}

double ControlSlider::getValue() const
{
    return value;
}

void ControlSlider::setValue(double value)
{
    value = value;
}

double ControlSlider::getMaxValue() const
{
    return maxValue;
}

void ControlSlider::setMaxValue(double value)
{
    maxValue = value;
}

double ControlSlider::getMinValue() const
{
    return minValue;
}

void ControlSlider::setMinValue(double value)
{
    minValue = value;
}

int ControlSlider::getPrecision() const
{
    return precision;
}

void ControlSlider::setPrecision(int value)
{
    precision = value;
}

int ControlSlider::getLongStep() const
{
    return longStep;
}

void ControlSlider::setLongStep(int value)
{
    longStep = value;
}

int ControlSlider::getShortStep() const
{
    return shortStep;
}

void ControlSlider::setShortStep(int value)
{
    shortStep = value;
}

int ControlSlider::getSpace() const
{
    return space;
}

void ControlSlider::setSpace(int value)
{
    space = value;
}

void ControlSlider::setSliderValue(double theValue)
{
    rightSliderRuler->setValue(theValue);
    value=theValue;
    qDebug()<<"当前值为："<<theValue<<endl;
}



