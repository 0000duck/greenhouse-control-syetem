#ifndef MYSWITCHITEM_H
#define MYSWITCHITEM_H

#include <QObject>

class MySwitchItem : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool isOn READ isOn WRITE setisOn NOTIFY isOnchanged)
    Q_PROPERTY(QString deviceName READ deviceName WRITE setDeviceName NOTIFY deviceNameChanged)
public:
    MySwitchItem(QObject *parent = nullptr);
    void setisOn(bool theIsOn);
    bool isOn();
    QString deviceName();
    void setDeviceName(const QString &theDeviceName);
signals:
    void deviceNameChanged(const QString &myDeviceName);
    void isOnchanged(bool isOn);
public slots:
    QString getDeviceName();
    void getisOn();
private:
    bool m_isOn;
    QString m_deviceName;
};

#endif // MYSWITCHITEM_H
