#ifndef TEXT_LABEL_H
#define TEXT_LABEL_H

#include<QLabel>

class TextLabel : public QLabel
{
public:
    TextLabel(const QString &path);

    void paintEvent(QPaintEvent*);
    void setText(const QString &text)
    {
        this->text=prefix+" "+text+" "+unit;
    }
    void setText(const int &text)
    {
        this->text=prefix+" "+QString::number(text,10)+" "+unit;
    }

    void setText(const float &text)
    {
        this->text=prefix+" "+QString("%1").arg(text)+" "+unit;
    }
    void setUnit(const QString &unit)
    {
        this->unit=unit;
    }
    void setPath(const QString &path)
    {
        this->path=path;
    }
    void setPrefix(const QString &prefix)
    {
        this->prefix=prefix;
    }
private:
    QString text;
    QString unit;
    QString path;
    QString prefix;
};

#endif // TEXT_LABEL_H
