#include "abouttab.h"

aboutTab::aboutTab(QWidget *parent) :
    QWidget(parent)
{
    about =new QLabel("<b>about tab</b>");
    mainlayout =new QGridLayout;
//    scroll=new QScrollArea;
//    scroll->setWidget(about);
//    mainlayout->addWidget(scroll);
    mainlayout->addWidget(about);
    this->setLayout(mainlayout);
}
