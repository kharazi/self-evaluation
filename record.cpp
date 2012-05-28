#include "record.h"
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
    comment->setMaximumSize(400,180);
//    mainlayout->addWidget(data);
//    mainlayout->addWidget(time);
//    mainlayout->addWidget(sidtype,0,0,1,1,Qt::AlignRight);
//    mainlayout->addWidget(rate,1,1,1,5);
//    mainlayout->addWidget(comment,2,2,2,3,Qt::AlignRight);
//    mainlayout->addWidget(record_button);

    rateLabel = new QLabel("rate");
    commentLabel = new QLabel("comment");
    commentLabel->setBuddy(comment);

    typeLabel = new QLabel("type");

    mainlayout->addWidget(comment, 0, 0);
    mainlayout->addWidget(commentLabel, 0, 1);
    mainlayout->addWidget(sidtype, 1, 0);
    mainlayout->addWidget(typeLabel, 1, 1);
    mainlayout->addWidget(rate,2,0);
    mainlayout->addWidget(date,3,0);
    mainlayout->addWidget(time,4,0);
    mainlayout->addWidget(record_button,5,0);

    setLayout(mainlayout);

}
void record::record_button_clicked(){


}
