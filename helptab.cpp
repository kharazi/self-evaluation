#include "helptab.h"

Helptab::Helptab(QWidget *parent) :
    QWidget(parent)
{
    about =new QLabel("<b>help tab</b>");
    mainlayout =new QGridLayout;
    scroll=new QScrollArea;
    scroll->setWidget(about);
    mainlayout->addWidget(scroll);
    this->setLayout(mainlayout);
}

Helptab::~Helptab()
{
  delete about;
  delete scroll;
  delete mainlayout;
}
