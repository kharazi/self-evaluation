#include "record.h"
#include "mainwidget.h"
#include <QDebug>
record::record(QString u, QWidget *parent) :
    QWidget(parent)
{
    user = u;
    createRecordWidget();

}

void record::createRecordWidget(){
    mainlayout= new QGridLayout;
    ratelayout =new QGridLayout;

    record_button= new QPushButton(QString::fromUtf8("record"));
    connect(record_button,SIGNAL(clicked()),this,SLOT(record_button_clicked()));

    //set combo box value
    action_type =new QComboBox;
    action_type->addItem("other");
//    action_type->setMaximumWidth(150);

    QSqlQuery q("SELECT title FROM action_types");
    qDebug()<<q.lastError().text();
    if (q.lastError().type()==0){
        while (q.next()) {
            qDebug()<<q.value(0).toString();
            action_type->addItem(q.value(0).toString());
        }
    }
    else{

        QMessageBox *error = new QMessageBox;
        error->setText("there is a problem; cannot read database");
        error->setIcon(QMessageBox::Warning);
        error->setWindowTitle("Error");
        error->exec();
    }


    date=new QDateEdit;

    time=new QTimeEdit;


//    date->show();

    rate = new QSlider(Qt::Horizontal);
    description=new QTextEdit(QString::fromUtf8("توضیحات"));
    description->setMaximumHeight(100);

    rateLabel = new QLabel("rate");
    descriptionLabel = new QLabel("description");
    descriptionLabel->setBuddy(description);

    typeLabel = new QLabel("type");

    mainlayout->addWidget(description, 0, 0,1,1);
    mainlayout->addWidget(descriptionLabel, 0, 1,1,1);
    mainlayout->addWidget(action_type, 1, 0,1,1);
    mainlayout->addWidget(typeLabel, 1, 1,1,1);
    mainlayout->addWidget(rate,2,0,1,1);
    mainlayout->addWidget(date,3,0,1,1);
    mainlayout->addWidget(time,4,0);
    mainlayout->addWidget(record_button,5,0);

    setLayout(mainlayout);

}
void record::record_button_clicked(){

    int action_id;
    QSqlQuery query;
    query.exec(QString("SELECT action_id FROM action_types WHERE title = '%1' ").arg(action_type->currentText()));
    while (query.next()){
      action_id = query.value(0).toInt();
    }
    query.prepare("INSERT INTO actions (id,action_id, description, username, date, rate) VALUES(?,?,?,?,?,?) ");
    query.addBindValue(QVariant(QVariant::Int));
    query.addBindValue(action_id);
    query.addBindValue(user);
    query.addBindValue(description->toPlainText());
    query.addBindValue("2010-01-20");
    query.addBindValue(rate->value());
    query.exec();
    if (query.lastError().type()!=0){

        QMessageBox *error = new QMessageBox;
        error->setText("there is a problem; Cannot Insert to Database ");
        qDebug() << query.lastError();
        error->setIcon(QMessageBox::Warning);
        error->setWindowTitle("Error");
        error->exec();

    }


}
