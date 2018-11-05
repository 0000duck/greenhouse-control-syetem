#ifndef CONTROLONOFF_H
#define CONTROLONOFF_H

#include <QWidget>
//#include "myswitchitem.h"

namespace Ui {
class ControlOnOff;
}

class ControlOnOff : public QWidget
{
    Q_OBJECT

public:
    explicit ControlOnOff(const QString &theDeviceName,
                          const int &theOnoffWidth,
                          const int &myId);
    ~ControlOnOff();
    int getId() const;
    void setId(int value);
    //virtual void installEventFilter(QObject *filterObj);

private:
    Ui::ControlOnOff *ui;
    QString deviceName;
    int OnoffWidth;
    int id;
};

#endif // CONTROLONOFF_H
