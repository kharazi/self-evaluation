#include "abouttab.h"

aboutTab::aboutTab(QWidget *parent) :
    QWidget(parent)
{
    about =new QLabel("<b>about tab</b>");
    mainlayout =new QGridLayout;
    mainlayout->addWidget(about);
    this->setLayout(mainlayout);
}

aboutTab::~aboutTab()
{
  delete about;
  delete mainlayout;
}
