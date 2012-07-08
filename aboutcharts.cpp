#include "aboutcharts.h"

AboutCharts::AboutCharts(QWidget *parent) :
    QWidget(parent)
{
    create_widget();
    get_data();
}

void AboutCharts::create_widget(){
    about =new QLabel;
    about->setWordWrap(true);
    about->resize(about->minimumSize());

    mainlayout =new QFormLayout;
    mainlayout->addWidget(about);
    this->setLayout(mainlayout);
}

void AboutCharts::get_data(){
    query.exec(QString("SELECT title,content FROM contents WHERE content_id=%1").arg(12));
        while (query.next()) {
            about->setText(query.value(1).toString());
        }
}

AboutCharts::~AboutCharts()
{
  delete about;
  delete mainlayout;
}
