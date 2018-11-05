#include "subsystem.h"
#include <QDebug>


SubSystem::SubSystem()
{
    sysName="济南温室大棚系统";
    deviceNode="节点1";
    deviceID="0000";
    temperature=25.0;
    humidity=80.0;
    illumination=5000;
    carbon=1200;
    isOn=notRun;
    runState=normal;
}

SubSystem::SubSystem(QString s)
{
    qDebug()<<"start"<<endl;
    QStringList slist = s.split(QRegExp("\\s+"));

    qDebug()<<slist;
    sysName = slist[0];
    qDebug()<<sysName<<endl;
    deviceNode = slist[1];
    qDebug()<<deviceNode<<endl;
    deviceID = slist[2];
    qDebug()<<deviceID<<endl;
    temperature = slist[3].toFloat();
    humidity = slist[4].toFloat();
    illumination = slist[5].toInt();
    carbon = slist[6].toInt();
    isOn =(slist[7].at(0)=='Y')?run:notRun;
    runState=(slist[8].at(0)=='Y')?normal:notNormal;
}

QString SubSystem::toString()
{
    return  sysName+" "+
            deviceNode+" "+
            deviceID +" "+
            QString::number(temperature)+" "+
            QString::number(humidity)+" "+
            QString::number(illumination) +" "+
            QString::number(carbon )+" "+
            ((isOn==run)?QString("Y"):QString("N"))+" "+
            ((runState==normal)?QString("Y"):QString("N"));
}
