#include "status.h"

Status::Status(QWidget *parent) :
    QWidget(parent)
{
    layout=new QGridLayout;
    this->setLayout(layout);
}
