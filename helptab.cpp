#include "helptab.h"

Helptab::Helptab(QWidget *parent) :
    QWidget(parent)
{
    create_widget();
    get_data();
}
void Helptab::create_widget(){
    about =new QLabel;
    about->setWordWrap(true);
    about->resize(about->minimumSize());

    mainlayout =new QFormLayout;
    mainlayout->addWidget(about);
    this->setLayout(mainlayout);
}

void Helptab::get_data(){
    query.exec(QString("SELECT title,content FROM contents WHERE content_id=%1").arg(13));
        while (query.next()) {
            about->setText(query.value(1).toString());
        }
}

Helptab::~Helptab()
{

}
