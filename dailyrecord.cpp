#include "dailyrecord.h"

DailyRecord::DailyRecord(QString u, QWidget *parent) :
    QWidget(parent)
{
    user = u;
    actionsModel = new QSqlRelationalTableModel;

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
    QTextEdit *descriptionEdit = new QTextEdit;
    descriptionEdit->setAcceptRichText(false);
    QDateEdit *dateEdit = new QDateEdit;
    QTimeEdit *timeEdit = new QTimeEdit;
    QSlider *rateEdit = new QSlider(Qt::Horizontal);

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

    QLabel *typeLabel = new QLabel("Type");
    QLabel *descriptionLabel = new QLabel("Description");
    QLabel *dateLabel = new QLabel("Date");
    QLabel *timeLabel = new QLabel("Time");
    QLabel *rateLabel = new QLabel("Rate");

    QPushButton *submitIt = new QPushButton("Submit");
    connect(submitIt, SIGNAL(clicked()), actionsModel, SLOT(submitAll()));
    mainLayout->addWidget(descriptionLabel, 1, 0);
    mainLayout->addWidget(descriptionEdit, 1, 1, 2, 3);
    mainLayout->addWidget(dateLabel, 3, 0);
    mainLayout->addWidget(dateEdit, 3, 1, 3, 2);
    mainLayout->addWidget(timeLabel, 3, 3);
    mainLayout->addWidget(timeEdit, 3, 4, 3, 5);
    mainLayout->addWidget(rateLabel, 5, 0);
    mainLayout->addWidget(rateEdit, 6, 1);
    mainLayout->addWidget(addRowButton, 6, 3);
    mainLayout->addWidget(removeRowButton, 6, 4);
    mainLayout->addWidget(table, 7, 1, 8, 4);
    mainLayout->addWidget(submitIt, 9, 6);
    this->setLayout(mainLayout);

    connect(actionsModel, SIGNAL(rowsInserted(QModelIndex, int, int)), this, SLOT(selectFirstRow()));
}


void DailyRecord::addRow()
{
  QSqlQuery query;
    query.prepare("INSERT INTO actions (id, action_id, username, description, date, time, rate) VALUES(?, ?, ?, ?, ?, ?, ?) ");
    query.addBindValue(QVariant(QVariant::Int));
    query.addBindValue(0);
    query.addBindValue(getUser());
    //    query.addBindValue("");
    query.addBindValue("2030-11-14");
    query.addBindValue("15:36");
    query.addBindValue(50);
    query.exec();
    actionsModel->submitAll();
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
