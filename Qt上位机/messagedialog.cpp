#include "messagedialog.h"
#include "ui_messagedialog.h"
#include <QPainter>
#include <QPalette>
MessageDialog::MessageDialog(const QString &theTitleString, const QString &theContentString):
    ui(new Ui::MessageDialog),titleString(theTitleString),contentString(theContentString)
{

    ui->setupUi(this);
    ui->TitleLabel->setText(titleString);
    ui->contentLbel->setText(contentString);
    ui->TitleLabel->setFont(QFont("Times",18,QFont::Bold));
    ui->contentLbel->setFont(QFont("Times",22,QFont::Bold));


    ui->TitleLabel->setTextFormat(Qt::RichText);//文本格式
    ui->TitleLabel->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);//对齐方式
    ui->TitleLabel->setAutoFillBackground(true);

    ui->contentLbel->setWordWrap(true);//自动换行
    ui->contentLbel->setTextFormat(Qt::RichText);//文本格式
    ui->contentLbel->setAlignment(Qt::AlignCenter);//对齐方式
    ui->contentLbel->setAutoFillBackground(true);

    ui->TitleLabel->setStyleSheet(
                // "border-style:none;"
                 "background-color: #006400;");

    ui->contentLbel->setStyleSheet(// "border-style:none;"
                                  "background-color: #8B008B;"
                                    );//设置样式表

    setBtnQss(ui->btnOk, "#E74C3C", "#FFFFFF", "#EC7064", "#FFF5E7", "#DC2D1A", "#F5A996");
    connect(ui->btnOk,SIGNAL(clicked()),this,SLOT(slotOk()));
}

MessageDialog::~MessageDialog()
{

}

void MessageDialog::setBtnQss(QPushButton *btn, QString normalColor, QString normalTextColor, QString hoverColor, QString hoverTextColor, QString pressedColor, QString pressedTextColor)
{
    QStringList qss;
    qss.append(QString("QPushButton{border-style:none;padding:10px;border-radius:5px;color:%1;background:%2;}").arg(normalTextColor).arg(normalColor));
    qss.append(QString("QPushButton:hover{color:%1;background:%2;}").arg(hoverTextColor).arg(hoverColor));
    qss.append(QString("QPushButton:pressed{color:%1;background:%2;}").arg(pressedTextColor).arg(pressedColor));
    btn->setStyleSheet(qss.join(""));
}

void MessageDialog::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
   /* QStyleOption opt;
    opt.init(this);
    QPainter p;
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);*/
}

void MessageDialog::slotOk()
{
    this->close();
}
