#include "options.h"
#include "useroption.h"
Options::Options(QWidget *parent) :
    QWidget(parent)
{
    layout=new QGridLayout;
    tab =new QTabWidget;
    tab->addTab(new UserOption,QString::fromUtf8("تنظیمات کاربری"));
//    tab->addTab(new aboutSelfEvaluationTab,QString::fromUtf8("درباره محاسبه نفس"));
//    tab->addTab(new Helptab,QString::fromUtf8("آموزش نرم افزار"));

    layout->addWidget(tab);
    this->setLayout(layout);
}
