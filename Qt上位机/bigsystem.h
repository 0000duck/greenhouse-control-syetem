#ifndef BIGSYSTEM_H
#define BIGESYSTEM_H

#include <QObject>
#include <QString>
#include <QVector>
#include "subsystem.h"

struct AverageData{
    float AverageTemperature;
    float AverageHumidity;
    int AverageIllumination;
    int AverageCarbon;
};
typedef struct AverageData averageStruct;

struct aNode{
    QString sysName;
    QString deviceNodeName;
    averageStruct *averageData;
};

typedef struct aNode NodeStrcut;

class BigSystem
{

public:
    explicit BigSystem( );
    virtual ~BigSystem();
    QString sName="全国温室大棚检测中心";        //大系统名
    QString sNumber="";                             //大系统编号
    QVector<SubSystem> subSystems;           //该大系统的所有子系统及所有子系统设备
    QVector<QString> sysNames;
    QVector<QString> deviceNodes;
    QVector<NodeStrcut*> nodesAveData;

    enum{           // 标记排序的升降序
        _INCREASE,
        _DECREASE
    };

    QString toString();
    bool isExisted(const SubSystem& ref);               //检查是否已经存在
    bool addSubSystem(const SubSystem& ref);                     //添加
    bool removeSubsystem(QString theSysName,QString theDeviceNode,QString theDeviceID);          //删除
    bool updateSubsystem(const SubSystem& ref);   // 更新课程ref的数据
    void sortByName(int sortMode);
    void clearAllSubsystem();
    QVector<SubSystem> searchByDevcieID(QString theDeviceID);
    QVector<SubSystem> searchBySysName(QString sysName);
    QVector<SubSystem> searchByDeviceNode(QString deviceNode);
    QVector<SubSystem> fileterByName(QString sysName,QString deviceNode);

    void  getAvgData();
    void getTotaldeviceNodes();
    void average(QVector<SubSystem> &ref, averageStruct *average);
};

#endif // WHOLESYSTEM_H
