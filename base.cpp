#include "base.h"

Base::Base()
{
  mainwidget =NULL;
  QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
  db.setDatabaseName("selfeval.db");
  bool ok = db.open();
  if (!ok){
    QMessageBox *error = new QMessageBox();
    error->setText("Couldn't connect to the database. Please inform us.");
    error->setIcon(QMessageBox::Critical);
    error->setStandardButtons(QMessageBox::Ok);
    error->setDefaultButton(QMessageBox::Ok);
    connect(error->defaultButton(), SIGNAL(clicked()), this, SLOT(close()));
    error->exec();
  }



  QSqlQuery query;
  query.exec("CREATE TABLE users "
             "(username VARCHAR(30) NOT NULL UNIQUE, password VARCHAR(20) NOT NULL, "
             "PRIMARY KEY (username) )");

  query.exec("CREATE TABLE action_types"
             "(action_id INT NOT NULL ,title VARCHAR(60))");

  qDebug()<<query.lastError();
  query.exec("CREATE TABLE actions "
             "(id INT NOT NULL,action_id INT NOT NULL,username VARCHAR(30) NOT NULL, date DATETIME , rate INT)");


  fillTable();

  QSqlQuery q("SELECT * FROM sidtype");
  while (q.next()) {
      QString person = q.value(0).toString();
      qDebug()<<person;
  }


  auth = new Auth();
  auth->show();
  connect(auth, SIGNAL(authSuccessful(QString)), this, SLOT(authSuccessful(QString)));
//  QSqlDatabase::removeDatabase("defaultConnection");
}


Base::~Base()
{
  delete auth;
  delete mainwidget;
}

void Base::authSuccessful(QString user)
{
  auth->close();
  QApplication::setQuitOnLastWindowClosed(false);
  mainwidget = new MainWidget();
  mainwidget->setUser(user);
  mainwidget->show();
}

void Base::fillTable(){
//this function for test
    //and to set defualt sid in start
    QSqlQuery query;
    for (int i=20;i<40;i++){
        query.prepare("INSERT INTO action_types (title) VALUES(?) ");
        query.addBindValue(QString::fromUtf8("hah ")+QString::number(i) );
        query.exec();
    }
}

QSqlDatabase Base::getdatabase(){
    QSqlDatabase database;
    database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName("selfeval.db");
    return database;
}
