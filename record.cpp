#include "record.h"
#include "mainwidget.h"
#include <QDebug>
record::record(QWidget *parent) :
    QWidget(parent)
{

    createRecordWidget();

}

void record::createRecordWidget(){
    mainlayout= new QGridLayout;
    ratelayout =new QGridLayout;

    record_button= new QPushButton(QString::fromUtf8("record"));
    connect(record_button,SIGNAL(clicked()),this,SLOT(record_button_clicked()));

    //set combo box value
    sidtype =new QComboBox;
    sidtype->addItem("other");
//    sidtype->setMaximumWidth(150);

    QSqlQuery q("SELECT title FROM action_types");
    qDebug()<<q.lastError().text();
    if (q.lastError().type()==0){
        while (q.next()) {
            qDebug()<<q.value(0).toString();
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


    date=new QDateEdit;

    time=new QTimeEdit;


//    date->show();

    rate = new QSlider(Qt::Horizontal);
    comment=new QTextEdit(QString::fromUtf8("توضیحات"));
    comment->setMaximumHeight(100);

    rateLabel = new QLabel("rate");
    commentLabel = new QLabel("comment");
    commentLabel->setBuddy(comment);

    typeLabel = new QLabel("type");

    mainlayout->addWidget(comment, 0, 0,1,1);
    mainlayout->addWidget(commentLabel, 0, 1,1,1);
    mainlayout->addWidget(sidtype, 1, 0,1,1);
    mainlayout->addWidget(typeLabel, 1, 1,1,1);
    mainlayout->addWidget(rate,2,0,1,1);
    mainlayout->addWidget(date,3,0,1,1);
    mainlayout->addWidget(time,4,0);
    mainlayout->addWidget(record_button,5,0);

    setLayout(mainlayout);

}
void record::record_button_clicked(){


    QSqlQuery query;
    query.prepare("INSERT INTO actions (id,action_id,username, date, rate) VALUES(?,?,?,?,?) ");
    query.addBindValue(QVariant(QVariant::Int));
    query.addBindValue(1);
    query.addBindValue("user1");
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
