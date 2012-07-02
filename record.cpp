#include "record.h"
#include "mainwidget.h"
#include <QDebug>
record::record(QString u, QWidget *parent) :
    QWidget(parent)
{
    user = u;
    today=date.Today();
    createRecordWidget();
}

void record::createRecordWidget(){
    QGridLayout *main= new QGridLayout;


    mainlayout= new QGridLayout;
    QLabel * title =new QLabel(QString::fromUtf8("<b>ثبت یک عمل</b>"));
    record_button= new QPushButton(QString::fromUtf8("ثبت"));
    action_type =new QComboBox;
    time=new QTimeEdit;
    rate = new QSlider(Qt::Horizontal);
    rate->setMaximumWidth(150);
    rate->setMaximum(10);
    rate->setMinimum(1);
    rate->setValue(5);



    description=new QTextEdit(QString::fromUtf8("توضیحات"));
    description->setMaximumHeight(60);

    rateLabel = new QLabel(QString::fromUtf8("امتیاز"));
    QLabel *blankLabel = new QLabel(QString::fromUtf8("<pre>       </pre>"));
    QLabel *blankLabel1 = new QLabel(QString::fromUtf8("<pre>      </pre>"));
    QLabel *blankLabel2 = new QLabel(QString::fromUtf8("<pre>      </pre>"));



    QLabel *dateLabel = new QLabel(QString::fromUtf8("تاریخ"));

    QLabel *minLabel = new QLabel(QString::fromUtf8(":دقیقه"));
    QLabel *hourLabel = new QLabel(QString::fromUtf8(":ساعت"));

    QLabel *timeLabel = new QLabel(QString::fromUtf8("زمان"));

    QGroupBox *groupBox = new QGroupBox();
    groupBox->setLayout(mainlayout);

    main->addWidget(groupBox);

    typeLabel = new QLabel(QString::fromUtf8("نوع"));

    year=new QSpinBox;
    year->setMaximum(today.at(0).toInt());
    year->setMinimum(1389);
    year->setValue(today.at(0).toInt());

    hour=new QSpinBox;
    hour->setMaximum(23);
    hour->setMinimum(0);
    hour->setValue(date.today.toString("h").toInt());

    min=new QSpinBox;
    min->setMaximum(59);
    min->setMinimum(0);
    min->setValue(date.today.toString("m").toInt());


    month = new QComboBox;

    day=new QSpinBox;
    day->setMaximum(31);
    day->setMinimum(1);
    day->setValue(today.at(2).toInt());

    mainlayout->addWidget(title,0,6,1,1);
    mainlayout->addWidget(typeLabel,1,6,1,1);
    mainlayout->addWidget(action_type,1,5,1,1);
    mainlayout->addWidget(blankLabel2,1,4,1,1);
    mainlayout->addWidget(blankLabel1,1,3,1,1);
    mainlayout->addWidget(blankLabel,1,2,1,1);
    mainlayout->addWidget(rateLabel,1,1,1,1);
    mainlayout->addWidget(rate,1,0,1,1);
    mainlayout->addWidget(dateLabel,2,6,1,1);
    mainlayout->addWidget(day,2,5,1,1);
    mainlayout->addWidget(month,2,4,1,1);
    mainlayout->addWidget(year,2,3,1,1);
    mainlayout->addWidget(timeLabel,3,6,1,1);
    mainlayout->addWidget(hourLabel,3,4,1,1);
    mainlayout->addWidget(hour,3,5,1,1);
    mainlayout->addWidget(min,3,3,1,1);
    mainlayout->addWidget(minLabel,3,2,1,1);
    mainlayout->addWidget(description,4,0,1,7);
    mainlayout->addWidget(record_button,5,0,1,1);
    setLayout(main);

    for (int i=1;i<13;i++){
        month->addItem(date.Month[i]);
    }
    month->setCurrentIndex(today.at(1).toInt()-1);


    connect(record_button,SIGNAL(clicked()),this,SLOT(record_button_clicked()));

    //set combo box value
    //action_type->setMaximumWidth(150);

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



//    date->show();




}
void record::record_button_clicked(){
    //when record button clicked -> Dashboard::getdata()

    int action_id=0;
    QSqlQuery query;
    query.exec(QString("SELECT action_id FROM action_types WHERE title = '%1' ").arg(action_type->currentText()));
    while (query.next()){
      action_id = query.value(0).toInt();
    }

    query.prepare("INSERT INTO actions (id,action_id,username,description,date,time,rate) VALUES(?,?,?,?,?,?,?) ");
    query.addBindValue(QVariant(QVariant::Int));
    query.addBindValue(action_id);
    query.addBindValue(user);
    query.addBindValue(description->toPlainText());


    query.addBindValue(QString("%1-%2-%3").arg(year->value()).arg(month->currentIndex()+1).arg(day->value()));

    query.addBindValue(QString("%1:%2").arg(hour->value()).arg(min->value()));
    query.addBindValue(rate->value());
    query.exec();

    qDebug()<<"hour is:"<<hour->value();
    qDebug()<<"min is:"<<min->value();

    qDebug()<<"year is:"<<year->value();
    qDebug()<<"month is:"<<month->currentIndex()+1;
    qDebug()<<"day is:"<<day->value();
    qDebug()<<"action id is:"<<action_id;
    qDebug()<<description->toPlainText();

//    for test
    if (query.lastError().type()!=0){

        QMessageBox *error = new QMessageBox;
        error->setText("there is a problem; Cannot Insert to Database ");
        qDebug() << query.lastError();
        error->setIcon(QMessageBox::Warning);
        error->setWindowTitle("Error");
        error->exec();
    }


}
