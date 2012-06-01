#include "dashboard.h"

Dashboard::Dashboard(QString u, QWidget *parent) :
    QWidget(parent)
{
    mainlayout= new QHBoxLayout;
    re =new record(u);
    mainlayout->addWidget(re);
    this->setLayout(mainlayout);

}
