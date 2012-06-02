#include "status.h"

Status::Status(QString u, QWidget *parent) :
    QWidget(parent)
{
    layout=new QGridLayout;
    this->setLayout(layout);
    QSqlQuery query;
    query.exec("");
}
