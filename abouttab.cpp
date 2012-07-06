#include "abouttab.h"

aboutTab::aboutTab(QWidget *parent) :
    QWidget(parent)
{
    about =new QLabel;
    about->setWordWrap(true);
    about->resize(about->minimumSize());
    title= new QLabel("dfdsfdskfklsafkj");
    title->setWordWrap(true);
    title->resize(title->minimumSize());
    mainlayout =new QFormLayout;
    mainlayout->addWidget(title);
    mainlayout->addWidget(about);
    this->setLayout(mainlayout);
    get_data();


}
void aboutTab::get_data(){
    query.exec(QString("SELECT title,content FROM contents WHERE content_id=%1").arg(10));
        while (query.next()) {

            about->setText(query.value(1).toString());
        }
    query.exec(QString("SELECT title,content FROM contents WHERE content_id=%1").arg(11));
        while (query.next()) {

            title->setText(query.value(1).toString());
        }
}

aboutTab::~aboutTab()
{
  delete about;
  delete mainlayout;
}
