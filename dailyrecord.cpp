#include "dailyrecord.h"

DailyRecord::DailyRecord(QString u, QWidget *parent) :
    QWidget(parent)
{
    user = u;
    actionsModel = new QSqlRelationalTableModel;
    today=date.Today();
    actionsModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    actionsModel->setTable("actions");
    actionsModel->setRelation(1, QSqlRelation("action_types", "action_id", "title" ));
    actionsModel->setSort(0, Qt::DescendingOrder);
    actionsModel->setFilter(QString("username = '%1'").arg(u));
    actionsModel->select();
    actionsModel->setHeaderData(1, Qt::Horizontal, "Type");
    actionsModel->setHeaderData(4, Qt::Horizontal, "Date");
    actionsModel->setHeaderData(5, Qt::Horizontal, "Time");
    actionsModel->setHeaderData(6, Qt::Horizontal, "Rate");

    mapper = new QDataWidgetMapper;

    mainLayout = new QGridLayout;
    mainLayout->setOriginCorner(Qt::TopRightCorner);
    createPage();
}


QString DailyRecord::getUser() { return user; }


void DailyRecord::createPage()
{


//    year=new QSpinBox;
//    year->setMaximum(today.at(0).toInt());
//    year->setMinimum(1389);
//    year->setValue(today.at(0).toInt());

//    hour=new QSpinBox;
//    hour->setMaximum(23);
//    hour->setMinimum(0);
//    hour->setValue(date.today.toString("h").toInt());

//    min=new QSpinBox;
//    min->setMaximum(59);
//    min->setMinimum(0);
//    min->setValue(date.today.toString("m").toInt());


//    month = new QComboBox;

//    day=new QSpinBox;
//    day->setMaximum(31);
//    day->setMinimum(1);
//    day->setValue(today.at(2).toInt());

//    for (int i=1;i<13;i++){
//        month->addItem(date.Month[i]);
//    }
//    month->setCurrentIndex(today.at(1).toInt()-1);









    QTextEdit *descriptionEdit = new QTextEdit;
    descriptionEdit->setAcceptRichText(false);
    descriptionEdit->setMaximumHeight(200);
    QLineEdit *dateEdit = new QLineEdit;

//    dateEdit->setMinimumDate(QDate(1390,0,0));
    dateEdit->setInputMask("9999-99-99");
    QLineEdit *timeEdit = new QLineEdit;
    timeEdit->setInputMask("99:99");
    QSlider *rateEdit = new QSlider(Qt::Horizontal);
    rateEdit->setMinimum(1);
    rateEdit->setMaximum(10);

    //    connect(actionsModel, SIGNAL(primeInsert(int, QSqlRecord&)), this, SLOT(initializeRow(int, QSqlRecord&)));

    mapper->setModel(actionsModel);
    mapper->addMapping(descriptionEdit, 3);
    mapper->addMapping(dateEdit, 4);
    mapper->addMapping(timeEdit, 5);
    mapper->addMapping(rateEdit, 6);
    mapper->toFirst();

    QPushButton *addRowButton = new QPushButton;
    QPushButton *removeRowButton = new QPushButton;
    addRowButton->setIcon(QIcon(":/images/add.png"));
    removeRowButton->setIcon(QIcon(":/images/remove.png"));
    connect(addRowButton, SIGNAL(clicked()), this, SLOT(addRow()));
    connect(removeRowButton, SIGNAL(clicked()), this, SLOT(removeRow()));

    table = new QTableView;
    table->setModel(actionsModel);
    table->setItemDelegate(new QSqlRelationalDelegate(table));
    table->setColumnHidden(0, true);
    table->setColumnHidden(2, true);
    table->setColumnHidden(3, true);

    table->verticalHeader()->hide();
    table->horizontalHeader()->setStretchLastSection(true);
    table->setSelectionMode(QAbstractItemView::SingleSelection);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    //    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->selectRow(0);
    connect(table->selectionModel(), SIGNAL(currentRowChanged(QModelIndex,QModelIndex)), mapper, SLOT(setCurrentModelIndex(QModelIndex)));

    QLabel *typeLabel = new QLabel(QString::fromUtf8("نوع گناه"));
    QLabel *descriptionLabel = new QLabel(QString::fromUtf8("توضیح"));
    QLabel *dateLabel = new QLabel(QString::fromUtf8("تاریخ"));
    QLabel *timeLabel = new QLabel(QString::fromUtf8("زمان"));
    QLabel *rateLabel = new QLabel(QString::fromUtf8("امتیاز منفی"));



    QPushButton *submitIt = new QPushButton(QString::fromUtf8("ذخیره "));
    connect(submitIt, SIGNAL(clicked()), actionsModel, SLOT(submitAll()));
    mainLayout->addWidget(descriptionLabel, 0, 0,1,1);
    mainLayout->addWidget(descriptionEdit, 0, 1, 1, 6);

//    mainLayout->setColumnMinimumWidth(2,100);
    mainLayout->setColumnMinimumWidth(4,300);
    mainLayout->addWidget(dateLabel, 2, 0,1,1);
    mainLayout->addWidget(dateEdit, 2, 1, 1, 1);
    mainLayout->addWidget(timeLabel, 2, 2,1,1);
    mainLayout->addWidget(timeEdit, 2, 3, 1, 1);
    mainLayout->addWidget(rateLabel, 3, 0,1,1);
    mainLayout->addWidget(rateEdit, 3, 1,1,1);
    mainLayout->addWidget(addRowButton, 4,5,1,1);
    mainLayout->addWidget(removeRowButton, 4, 6,1,1);
    mainLayout->addWidget(submitIt, 4, 1,1,1);
    mainLayout->addWidget(table, 5, 0, 5, 7);


//     mainLayout->addWidget(year,10,1);
//    mainLayout->addWidget(month,10,2);
//    mainLayout->addWidget(day,10,3);


//    mainLayout->addWidget(hour,11,1);
//    mainLayout->addWidget(min,11,2);
    this->setLayout(mainLayout);

    connect(actionsModel, SIGNAL(rowsInserted(QModelIndex, int, int)), this, SLOT(selectFirstRow()));
}


void DailyRecord::addRow()
{
    QSqlQuery query;
    query.prepare("INSERT INTO actions (id, action_id, username, description, date, time, rate) VALUES(?, ?, ?, ?, ?, ?, ?) ");
    query.addBindValue(QVariant(QVariant::Int));
    query.addBindValue(1);
    query.addBindValue(getUser());
    query.addBindValue(QString::fromUtf8("بدون توضیح"));
    qDebug()<<"alllllllllllllllllllllllllan"<<date.nRoz(0)<<date.today.toString("hh:mm");
    query.addBindValue(date.nRoz(0));
    query.addBindValue(date.today.toString("hh:mm"));

    query.addBindValue(5);
    query.exec();
    actionsModel->submitAll();
    qDebug()<<"EROOOOOOOOOOOOOOOOOOOOOOOOOOOOOOR" << query.lastError() << actionsModel->lastError();
  // record.setValue("id", QVariant(100));
  // record.setValue("action_id", QVariant(5));
  // record.setValue("user", getUser());
  // record.setValue("date", "1993-10-03");
  // record.setValue("time", "15:31");
  // qDebug() <<  record.value("action_id").toInt()  << record.value("user").toString();
  // actionsModel->submitAll();

  //qDebug() << actionsModel->lastError().text() << " <- before";
  //actionsModel->insertRows(0, 1);
//    actionsModel->submitAll();
//   QSqlRecord record;
//   QSqlField f1("id", QVariant::Int);
//   QSqlField f2("action_id", QVariant::Int);
// n  QSqlField f3("date", QVariant::String);
//   QSqlField f4("time", QVariant::String);
//   QSqlField f5("user", QVariant::String);
//   f1.setValue(QVariant(20));
//   f2.setValue(QVariant(15));
//   f3.setValue(QVariant("1992-11-06"));
//   f4.setValue(QVariant("14:14"));
//   f5.setValue(QVariant(user));
//   record.append(f1);
//   record.append(f2);
//   record.append(f3);
//   record.append(f4);
//   record.append(f5);
//   // record.setValue("id", QVariant(QVariant::Int));
//   // record.setValue("action_id", 5);
//   // record.setValue("description", "what the?");
//   // record.setValue("user", getUser());
//   // record.setValue("date", "1993-10-03");
//   // record.setValue("time", "15:31");
//   // record.setValue("rate", 20);
//   qDebug() << record.value("id").toInt() << record.value("action_id").toInt()
//   	   << record.value("description").toString() << record.value("user").toString()
//   	   << record.value("date").toString() << record.value("time").toString() 
//   	   << record.value("rate").toInt();


//   qDebug() << actionsModel->insertRecord(0, record);
//   actionsModel->submitAll();
//   qDebug() << record.value("id").toInt() << record.value("action_id").toInt()
//   	   << record.value("description").toString() << record.value("user").toString()
//   	   << record.value("date").toString() << record.value("time").toString() 
//   	   << record.value("rate").toInt();
//   qDebug() << record.isNull(1) << "its Null";
//   qDebug() << actionsModel->lastError().text();

}


// void DailyRecord::initializeRow(int row, QSqlRecord& record)
// {
//     // QSqlQuery query;
//     // // query.exec("SELECT * FROM actions ORDER BY id DESCENDING");
//     // // qDebug() << query.value(0).toInt();
//     // // qDebug() << query.next();
//     // // qDebug() << query.value(0).toInt();

//     // qDebug() << actionsModel->lastError();
// }


void DailyRecord::removeRow()
{
  actionsModel->removeRow(mapper->currentIndex());
  actionsModel->submitAll();
}


void DailyRecord::selectFirstRow()
{
  table->selectRow(0);
}
