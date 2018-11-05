#include "bigsystem.h"

BigSystem::BigSystem()
{
    sName="济南温室大棚检测中心";
    sNumber="0000";
}

BigSystem::~BigSystem()
{

}

QString BigSystem::toString()
{
    QString s;

    s +=sNumber+"\n";
    s += sName+"\n";

    for(int i=0; i<subSystems.size(); i++)
    {
        s+= subSystems[i].toString()+"\n";
    }
    return s;
}

bool BigSystem::isExisted(const SubSystem &ref)
{
    for(int i=0; i<subSystems.size();i++)
    {
        if((subSystems[i].sysName==ref.sysName)&&
           (subSystems[i].deviceNode==ref.deviceNode)
            &&(subSystems[i].deviceID == ref.deviceID))
            return true;
    }
    return false;
}

bool BigSystem::addSubSystem(const SubSystem &ref)
{
    if(ref.deviceID== "" || ref.sysName == "" || ref.deviceNode== "")
        return false;
    if(isExisted(ref))
        return false;
    SubSystem record = ref;
    subSystems.push_back(SubSystem(record));
    sortByName(BigSystem::_DECREASE);
    return true;
}

bool BigSystem::removeSubsystem(QString theSysName, QString theDeviceNode, QString theDeviceID){
    for(int i=0; i<subSystems.size();i++){
        if((subSystems[i].sysName == theSysName)&&
           (subSystems[i].deviceNode == theDeviceNode)&&
           (subSystems[i].deviceID == theDeviceID)){
            subSystems.removeAt(i);
            return true;
        }
    }
    return false;
}

bool BigSystem::updateSubsystem(const SubSystem &ref)
{
    if(ref.deviceID == "" || ref.sysName == "" || ref.deviceNode== "")
        return false;

    for(int i=0; i<subSystems.size();i++)
    {
        if((ref.deviceID == subSystems[i].deviceID )&&
           (ref.deviceNode== subSystems[i].deviceNode)&&
           (ref.sysName== subSystems[i].sysName))
            subSystems[i] = ref;
    }
    return true;
}

void BigSystem::sortByName(int sortMode){
    if(subSystems.isEmpty())   // 如果链表为空，返回
        return ;
    bool isIncrease;
    switch(sortMode){
        case 0:
            isIncrease = true; break;
        case 1:
            isIncrease = false; break;
        default:
            isIncrease = true;
    }

    // 首先按照系统名排序
    for(int i=0; i< subSystems.size(); i++){
        for(int k=i+1; k<subSystems.size(); k++){
            if(isIncrease && subSystems[i].sysName <= subSystems[k].sysName){
                SubSystem temp = subSystems[i];
                subSystems[i] = subSystems[k];
                subSystems[k] = temp;
            }
            if(!isIncrease && subSystems[i].sysName >= subSystems[k].sysName){
                SubSystem temp = subSystems[i];
                subSystems[i] = subSystems[k];
                subSystems[k] = temp;
            }
        }
    }

    for(int i=0; i<subSystems.size();i++){
        QString sysName = subSystems[i].sysName;
        for(int k=i+1; k<subSystems.size();k++){
            if(subSystems[k].sysName != sysName)
                break;
            if(isIncrease && subSystems[i].deviceNode <= subSystems[k].deviceNode){
                SubSystem temp = subSystems[i];
                subSystems[i] = subSystems[k];
                subSystems[k] = temp;
            }
            if(!isIncrease && subSystems[i].deviceNode >= subSystems[k].deviceNode){
                SubSystem temp = subSystems[i];
                subSystems[i] = subSystems[k];
                subSystems[k] = temp;
            }
        }
    }
}

void BigSystem::clearAllSubsystem()
{
  subSystems.clear();
}

QVector<SubSystem> BigSystem::searchByDevcieID(QString theDeviceID){
    QVector<SubSystem> buf;

    for(int i=0; i<subSystems.size();i++){
        if(subSystems[i].deviceID == theDeviceID){
            buf.push_back(subSystems[i]);
        }
    }
    return buf;
}


QVector<SubSystem> BigSystem::searchBySysName(QString sysName){
    QVector<SubSystem> buf;

    for(int i=0; i<subSystems.size();i++){
        if(subSystems[i].sysName == sysName){
            buf.push_back(subSystems[i]);
        }
    }
    return buf;
}

QVector<SubSystem> BigSystem::searchByDeviceNode(QString deviceNode){
    QVector<SubSystem> buf;

    for(int i=0; i<subSystems.size();i++){
        if(subSystems[i].deviceID == deviceNode){
            buf.push_back(subSystems[i]);
        }
    }
    return buf;
}

QVector<SubSystem> BigSystem::fileterByName(QString sysName, QString deviceNode)
{
    QVector<SubSystem> buf;
    if(sysName =="全部")  // 全选
        buf = subSystems;
    else
        buf = searchBySysName(sysName);
    if(deviceNode =="全部")
        return buf;
    for(int i=0; i<buf.size();){
        if(buf[i].deviceNode != deviceNode){
            buf.removeAt(i);
        }
        else{
            i++;
        }
    }
    return buf;
}

void BigSystem::getAvgData()
{
   QVector<SubSystem> temp;
   NodeStrcut *theNode;
   averageStruct *ave;
   this->getTotaldeviceNodes();
    for(int i=0;i<sysNames.size();i++)
        for(int j=0;j<deviceNodes.size();j++)
        {
             temp=fileterByName(sysNames.at(i),deviceNodes.at(j));
             if(!temp.isEmpty()){
                theNode->sysName=sysNames.at(i);
                theNode->deviceNodeName=deviceNodes.at(j);
                ave=theNode->averageData;
                this->average(temp,ave);
                nodesAveData.push_back(theNode);
             }
        }

}

void BigSystem::getTotaldeviceNodes()
{
    for(int i=0;i<subSystems.size();i++){
        for(int j=0;j<sysNames.size();j++){
            if(subSystems[i].sysName==sysNames.at(j))
              continue;
            else{
                sysNames.push_back(subSystems.at(i).sysName);
            }
        }
        for(int j=0;j<deviceNodes.size();j++){
            if(subSystems[i].deviceNode==deviceNodes.at(j))
              continue;
            else{
                deviceNodes.push_back(subSystems.at(i).deviceNode);
            }
        }
    }
}

void BigSystem::average(QVector<SubSystem> &ref, averageStruct *average){
    averageStruct *sum=average;
    for(int i=0; i<ref.size();i++){
        sum->AverageTemperature+=ref.at(i).temperature;
        sum->AverageHumidity+=ref.at(i).humidity;
        sum->AverageIllumination+=ref.at(i).illumination;
        sum->AverageCarbon+=ref.at(i).carbon;
    }
    average->AverageTemperature=sum->AverageTemperature/ref.size();
    average->AverageHumidity=sum->AverageHumidity/ref.size();
    average->AverageIllumination=sum->AverageIllumination/ref.size();
    average->AverageCarbon=sum->AverageCarbon/ref.size();

}
