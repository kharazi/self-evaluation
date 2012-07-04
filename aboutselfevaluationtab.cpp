#include "aboutselfevaluationtab.h"

aboutSelfEvaluationTab::aboutSelfEvaluationTab(QWidget *parent) :
    QWidget(parent)
{
    about =new QLabel("<b>درباره ی محاسبه ی نفس</b>");
    mainlayout =new QGridLayout;
    scroll=new QScrollArea;
    scroll->setWidget(about);
    mainlayout->addWidget(scroll);
    this->setLayout(mainlayout);
}
