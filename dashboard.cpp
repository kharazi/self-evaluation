#include "dashboard.h"

Dashboard::Dashboard(QWidget *parent) :
    QWidget(parent)
{

        mainlayout= new QGridLayout;
        recordlayout=new QGridLayout;
        this->setLayout(mainlayout);

//        record= new QPushButton(QString::fromUtf8("record"));
//        sidtype =new QComboBox;
//        QSqlDatabase db= Base::getDb();
//        db.open();
//        QSqlQuery q("SELECT * FROM sidtype");


//        while (q.next()) {
//            QString sid = q.value(1).toString();
//            sidtype->addItem(sid);
//        }




}

void Dashboard::record_button_clicked(){


}
