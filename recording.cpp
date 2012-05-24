#include "recording.h"

Recording::Recording(QWidget *parent) :
    QWidget(parent)
{
    layout=new QGridLayout;
    lable=new QLabel("start the page");
    layout->addWidget(lable);
    record= new QPushButton(QString::fromUtf8("ثبت"));
    record->setStyleSheet("background-image: url(:/images/hizom.png)");//:D
    record->setFixedSize(120,120);
    layout->addWidget(record,1,0,1,1,Qt::AlignLeft);
    this->setLayout(layout);
}
