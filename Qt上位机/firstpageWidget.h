#ifndef FIRSTPAGEWIDGET_H
#define FIRSTPAGEWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QImage>
#include <QVBoxLayout>
#include <QTimer>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "control_slider.h"
#include <QGroupBox>
#include <QMouseEvent>
#include "switchitem.h"

using namespace cv;

class FirstPageWidget : public QWidget
{
    Q_OBJECT
public:
    explicit FirstPageWidget(QWidget *parent = nullptr);
    virtual ~FirstPageWidget();
    void paintEvent(QPaintEvent *event);
    virtual void mousePressEvent(QMouseEvent *event);
    void videoCapClose();
    void savefile();
signals:

public slots:
    void updateImage();
    void setValue();
private:
    QTimer *theTimer;
    Mat srcImage;
    QImage image2;
    VideoCapture videoCap;
    QLabel *myLabel;
    QLabel *textLabel;
    QVBoxLayout *vBoxLayout;

    int labelWidth;
    int labelHight;

    QHBoxLayout *hboxLayout;

    QGroupBox *bottonGroupBox;
    QVBoxLayout *controlValueVBoxLayout;
    QVBoxLayout *rightControlVBoxlayout;
    QGroupBox *leftVideoGroupBox;

    ControlSlider *temperatureSlider;
    ControlSlider *humiditySlider;
    ControlSlider *illuminationSlider;
    ControlSlider *carbonSlider;

    SwitchItem *groupBox;

};

#endif // FIRSTPAGEWIDGET_H
