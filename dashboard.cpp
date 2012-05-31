#include "dashboard.h"
#include <QDebug>
Dashboard::Dashboard(QString u, QWidget *parent) :
    QWidget(parent)
{
    mainlayout= new QGridLayout;
    re =new record();
    mainlayout->addWidget(re);
    this->setLayout(mainlayout);

}

