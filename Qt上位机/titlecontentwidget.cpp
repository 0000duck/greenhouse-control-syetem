#include "titlecontentwidget.h"
#include "ui_titlecontentwidget.h"
#include <QVBoxLayout>

TitleContentWidget::TitleContentWidget(QWidget *parent) :
    CustomWindow(parent),
    ui(new Ui::TitleContentWidget)
{
    ui->setupUi(this);
    //ui->titleLabel->setText(titleString);
    //ui->contentLabel->setText(contentString);
    QVBoxLayout *vboxLayout=new QVBoxLayout();
   /* this->setFixedHeight(85*4);
    this->ui->titleLabel->setFixedHeight(85);
    this->ui->contentLabel->setFixedHeight(85*3);*/
    this->setFixedHeight(90*4);
    this->ui->titleLabel->setFixedHeight(90);
    this->ui->contentLabel->setFixedHeight(90*3);
    vboxLayout->addWidget(ui->titleLabel);
    vboxLayout->addWidget(ui->contentLabel);
    vboxLayout->setSpacing(0);
    vboxLayout->setMargin(0);
    ui->titleLabel->setFont(QFont("Times",18,QFont::Bold));
    ui->contentLabel->setFont(QFont("Times",22,QFont::Bold));


    ui->titleLabel->setTextFormat(Qt::RichText);//文本格式
    ui->titleLabel->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);//对齐方式
    ui->titleLabel->setAutoFillBackground(true);

    ui->contentLabel->setWordWrap(true);//自动换行
    ui->contentLabel->setTextFormat(Qt::RichText);//文本格式
    ui->contentLabel->setAlignment(Qt::AlignCenter);//对齐方式
    ui->contentLabel->setAutoFillBackground(true);

    ui->titleLabel->setStyleSheet(
                // "border-style:none;"
                 "background-color: #FAEBD7;");

    ui->contentLabel->setStyleSheet(// "border-style:none;"
                                  "background-color: #BEBEBE;"
                                    );//设置样式表

}

TitleContentWidget::~TitleContentWidget()
{
    delete ui;
}

int TitleContentWidget::getTitleLabelHeight() const
{
    return titleLabelHeight;
}

void TitleContentWidget::setTitleLabelHeight(int value)
{
    titleLabelHeight = value;
    this->setFixedHeight(titleLabelHeight*4);
    this->ui->titleLabel->setFixedHeight(titleLabelHeight);
    this->ui->contentLabel->setFixedHeight(titleLabelHeight*3);
    this->show();
}
