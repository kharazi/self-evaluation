#include "options.h"
#include "useroption.h"
#include "hadithoption.h"
Options::Options(QString u, QWidget *parent) :
    QWidget(parent)
{
    layout=new QGridLayout;
    tab =new QTabWidget;
    tab->addTab(new UserOption,QString::fromUtf8("تنظیمات کاربری"));
    tab->addTab(new HadithOption,QString::fromUtf8("افزودن حدیث"));

    layout->addWidget(tab);
    this->setLayout(layout);
}
