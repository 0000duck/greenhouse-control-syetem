#ifndef SUBSYSTEM_H
#define SUBSYSTEM_H

#include <QObject>
#include <QString>
#include <QStringList>
#include <QRegExp>

enum Run{
    run,
    notRun
} ;
enum Normal{
    normal,
    notNormal
} ;

class SubSystem
{

public:
    SubSystem( );
    SubSystem(QString s);

    QString sysName;
    QString deviceNode;
    QString deviceID;
    float temperature;
    float humidity;
    int illumination;
    int carbon;
    Run isOn;
    Normal runState;
    QString toString();
};

#endif // DEVICES_H
