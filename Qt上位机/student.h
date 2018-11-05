#ifndef STUDENT_H
#define STUDENT_H
#include <QVector>
#include "course.h"

class Student
{
public:
    Student();

    static int noSequence;

    QString sName;                // 学生名
    int sNo;                      // 学号
    QVector<Course> courses;      //该学生的所有课程

    enum{           // 标记排序的升降序
        _INCREASE,
        _DECREASE
    };

    QString toString();

    // 查
    bool isExisted(const Course& ref);       // 根据ref.cName检查是否已经存在

    // 增、删
    bool addCourse(const Course& ref);      // 添加课程ref到courses中
    bool removeCourse(QString cName);       // 删除制定课程名的course

    // 查
    bool updateCourse(const Course& ref);   // 更新课程ref的数据

    // 按照"学年、学期"排序
    void sortByTime(int sortMode);

    // 清空courses
    void clearAllCourse();

    /// 搜索
    QVector<Course> searchByCName(QString name);
    QVector<Course> searchByYear(int year);
    QVector<Course> searchByTerm(int term);

    QVector<Course> fileterByTime(int year,int term);  // 过滤器：先学年后学期

    /// 计算数据
    float getSumCredit(QVector<Course> cv);
    float getAvgGrade(QVector<Course> cv);
    float getGPA5(QVector<Course> cv);

};

#endif // STUDENT_H
