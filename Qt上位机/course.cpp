#include "course.h"
#include <QDebug>

Course::Course()
{
    year = -1;
    term = -1;

    cName = "";     // key

    regularGrade = -1;
    finalExamGrade = -1;
    sumGrade = -1;     // key;

    credit = -1;       // key;

    teacherName = "";
}

Course::Course(QString s)
{
    QStringList slist = s.split(QRegExp("\\s+"));

    qDebug()<<slist;
    year = slist[0].toInt();
    term = slist[1].toInt();

    cName = slist[2];

    regularGrade = slist[3].toFloat();
    finalExamGrade = slist[4].toFloat();
    sumGrade = slist[5].toFloat();

    credit = slist[6].toFloat();

    teacherName = slist[7];
}

QString Course::toString()
{
    return  QString::number(year)+" "+QString::number(term)+" "+
            cName +" "+
            QString::number(regularGrade)+" "+QString::number(finalExamGrade)+" "+
            QString::number(sumGrade) +" "+QString::number(credit)+" "+
            teacherName;
}
