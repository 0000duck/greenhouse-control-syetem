#include "myswitchitem.h"
#include<QDebug>

MySwitchItem::MySwitchItem(QObject *parent): QObject(parent)
{

}

void MySwitchItem::setisOn(bool theIsOn)
{
    if(m_isOn==theIsOn)
        return;
    m_isOn=theIsOn;
}

bool MySwitchItem::isOn()
{
    return m_isOn;
}

QString MySwitchItem::deviceName()
{
    return m_deviceName;
}

void MySwitchItem::setDeviceName(const QString &theDeviceName)
{
    if(m_deviceName==theDeviceName)
        return;
    m_deviceName=theDeviceName;
    emit deviceNameChanged(m_deviceName);
}

QString MySwitchItem::getDeviceName( )
{
    return m_deviceName;
}

void MySwitchItem::getisOn()
{

    QString string=(m_isOn==true)?"true":"false";
    qDebug()<<"m_isOn是"<<string<<endl;
}




