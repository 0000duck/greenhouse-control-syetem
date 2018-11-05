#include "student.h"

int Student::noSequence = 1;

Student::Student()
{
    sName = QString("小黄瓜")+QString::number(noSequence)+"号";

    sNo = -1;
}

bool Student::isExisted(const Course &ref)
{
    for(int i=0; i<courses.size();i++)
    {
        if(courses[i].cName == ref.cName)
            return true;
    }
    return false;
}

bool Student::addCourse(const Course &ref)
{
    if(ref.cName == "" || ref.credit == -1 || ref.sumGrade == -1)
        return false;

    if(isExisted(ref))
        return false;

    Course record = ref;    // 因为要对ref修改，但是ref是constant variable

    if(record.teacherName == "")
        record.teacherName = "isTom?";

    courses.push_back(Course(record));

    sortByTime(Student::_DECREASE);

    return true;
}

bool Student::removeCourse(QString cName)
{
    for(int i=0; i<courses.size();i++)
    {
        if(courses[i].cName == cName)
        {
            courses.removeAt(i);
            return true;
        }
    }
    return false;
}

void Student::sortByTime(int sortMode)
{
    if(courses.isEmpty())   // 如果链表为空，返回
        return ;

    bool isIncrease;

    switch(sortMode)
    {
    case 0:
        isIncrease = true; break;
    case 1:
        isIncrease = false; break;
    default:
        isIncrease = true;
    }

    // 首先按照年份排序
    for(int i=0; i< courses.size(); i++)
    {
        for(int k=i+1; k<courses.size(); k++)
        {
            if(isIncrease && courses[i].year <= courses[k].year)
            {
                Course temp = courses[i];
                courses[i] = courses[k];
                courses[k] = temp;
            }
            if(!isIncrease && courses[i].year >= courses[k].year)
            {
                Course temp = courses[i];
                courses[i] = courses[k];
                courses[k] = temp;
            }
        }
    }

    // 按照学期排序

    for(int i=0; i<courses.size();i++)
    {
        int year = courses[i].year;   // 只比较同一学年

        for(int k=i+1; k<courses.size();k++)
        {
            if(courses[k].year != year)
                break;

            if(isIncrease && courses[i].term <= courses[k].term)
            {
                Course temp = courses[i];
                courses[i] = courses[k];
                courses[k] = temp;
            }
            if(!isIncrease && courses[i].term >= courses[k].term)
            {
                Course temp = courses[i];
                courses[i] = courses[k];
                courses[k] = temp;
            }
        }
    }
}

QString Student::toString()
{
    QString s;

    s += QString::number(sNo)+"\n";
    s += sName+"\n";

    for(int i=0; i<courses.size(); i++)
    {
        s+= courses[i].toString()+"\n";
    }

    return s;
}

void Student::clearAllCourse()
{
    courses.clear();
}

QVector<Course> Student::searchByCName(QString name)
{
    QVector<Course> buf;

    for(int i=0; i<courses.size();i++)
    {
        if(courses[i].cName == name)
        {
            buf.push_back(courses[i]);
        }
    }
    return buf;
}

QVector<Course> Student::searchByYear(int year)
{
    QVector<Course> buf;

    for(int i=0; i<courses.size();i++)
    {
        if(courses[i].year == year)
        {
            buf.push_back(courses[i]);
        }
    }
    return buf;
}

QVector<Course> Student::searchByTerm(int term)
{
    QVector<Course> buf;

    for(int i=0; i<courses.size();i++)
    {
        if(courses[i].term == term)
        {
            buf.push_back(courses[i]);
        }
    }
    return buf;
}

QVector<Course> Student::fileterByTime(int year, int term)
{
    QVector<Course> buf;
    if(year == -999)  // 全选
        buf = courses;
    else
        buf = searchByYear(year);

    if(term == -1)
        return buf;

    for(int i=0; i<buf.size();)
    {
        if(buf[i].term != term)  /// 不符合，不移位，并移除
        {
            buf.removeAt(i);
        }
        else  // 符合时，移位
        {
            i++;
        }
    }
    return buf;
}

bool Student::updateCourse(const Course &ref)
{
    if(ref.cName == "" || ref.credit == -1 || ref.sumGrade == -1)
        return false;

    for(int i=0; i<courses.size();i++)
    {
        if(ref.cName == courses[i].cName)
            courses[i] = ref;
    }
    return true;
}

float Student::getSumCredit(QVector<Course> cv)
{
    float sum = 0;
    for(int i=0; i<cv.size();i++)
    {
        sum+=cv[i].credit;
    }
    return sum;
}

float Student::getAvgGrade(QVector<Course> cv)
{
    float sum = 0;

    for(int i=0; i<cv.size();i++)
    {
        sum+=cv[i].sumGrade*cv[i].credit;
    }
    if(getSumCredit(cv) == 0)
        return -999;
    return sum/getSumCredit(cv);
}

float Student::getGPA5(QVector<Course> cv)
{
    Q_UNUSED(cv);
    return 0;
}
