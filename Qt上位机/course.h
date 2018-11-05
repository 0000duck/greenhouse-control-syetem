#ifndef COURSE_H
#define COURSE_H
#include <QString>
#include <QStringList>
#include <QRegExp>

class Course
{
public:
    Course();
    Course(QString s);

    QString cName;         // 课程名   唯一标识
    int year;              // 学期
    int term;              // 学年
    float regularGrade;    // 平时成绩
    float finalExamGrade;  // 期末
    float sumGrade;        // 总评
    float credit;          //学分
    QString teacherName;

    QString toString();
};

#endif // COURSE_H
