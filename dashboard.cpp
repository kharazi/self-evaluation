#include "dashboard.h"

Dashboard::Dashboard(QString u, QWidget *parent) :
    QWidget(parent)
{
    mainlayout= new QVBoxLayout;
    DateLable =new QLabel;
    HadithLable=new QLabel("hadith");
    QLabel * statusLabelTitle=new QLabel(QString::fromUtf8("<b>وضعیت من:</b>"));
    statusLable=new QLabel();
//    statusLable
    re =new record(u);
    today= date.Today();

    get_date();
    get_hadith();

    mainlayout->addWidget(DateLable);
    mainlayout->addWidget(HadithLable);
    mainlayout->addWidget(statusLabelTitle);
    mainlayout->addWidget(statusLable,0,Qt::AlignRight);
    mainlayout->addWidget(re);
    this->setLayout(mainlayout);

}
void Dashboard::get_hadith(){
    query.exec("SELECT hadith_text,narrator FROM hadith ORDER BY RANDOM() LIMIT 1");
    while (query.next()) {
        HadithLable->setText( query.value(1).toString()+":" +query.value(0).toString());
    }
}
void Dashboard::get_date(){
    QString Date;
    Date=QString::fromUtf8("امروز %4 %3 %2 سال %1 ").arg(today.at(0)).arg(today.at(3)).arg(today.at(2)).arg(today.at(4));
    DateLable->setText(Date);
}
void Dashboard::get_data(){

    statusLable->setText(QString::fromUtf8("<table ><tr><td>سلام ۱۱</td>  <td>سلام ۱۲</td><td>inam</td><td>inyeki</td></tr>"
                                           "<tr><td>      سلام ۲۱</td><td>سلام۲۲"
                                           "</td>"
                                           "</tr>"
                                           "</table>"));
}
