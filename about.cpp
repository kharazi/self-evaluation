#include "about.h"

About::About(QString u, QWidget *parent) :
    QWidget(parent)
{

    layout=new QGridLayout;
    tab =new QTabWidget;

    tab->addTab(new aboutSelfEvaluationTab,QString::fromUtf8("درباره محاسبه نفس"));
    tab->addTab(new Helptab,QString::fromUtf8("درباره نرم افزار"));
    tab->addTab(new aboutTab,QString::fromUtf8("درباره"));

    layout->addWidget(tab);
    this->setLayout(layout);

}

About::~About()
{
  delete tab;
  delete layout;
}
