#include "options.h"
#include "useroption.h"
Options::Options(QString u, QWidget *parent) :
    QWidget(parent)
{
    layout=new QGridLayout;
    tab =new QTabWidget;
    tab->addTab(new UserOption,QString::fromUtf8("تنظیمات کاربری"));
//    tab->addTab(new aboutSelfEvaluationTab,QString::fromUtf8("تغییراعمال"));

    layout->addWidget(tab);
    this->setLayout(layout);
}
