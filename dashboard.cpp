#include "dashboard.h"
#include <QDebug>
Dashboard::Dashboard(QWidget *parent) :
    QWidget(parent)
{

        mainlayout= new QGridLayout;
        recordlayout=new QGridLayout;
        this->setLayout(mainlayout);

        record= new QPushButton(QString::fromUtf8("record"));
        sidtype =new QComboBox;

        Base::getdatabase().open();
        QSqlQuery q("SELECT sidTitle FROM sidtype");
        if (q.lastError().type()==0){
            while (q.next()) {
                sidtype->addItem(q.value(0).toString());
            }
        }
        else{

            QMessageBox *error = new QMessageBox;
            error->setText("there is a problem; cannot read database");
            error->setIcon(QMessageBox::Warning);
            error->setWindowTitle("Error");
            error->exec();
        }




        mainlayout->addWidget(sidtype);
        mainlayout->addWidget(record);
}

void Dashboard::record_button_clicked(){


}
