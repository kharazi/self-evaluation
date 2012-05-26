#include "base.h"

Base::Base()
{
  mainwidget = NULL;
  db = QSqlDatabase::addDatabase("QSQLITE");
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
  	     "(username VARCHAR(30) NOT NULL, password VARCHAR(20) NOT NULL, "
  	     "PRIMARY KEY (username) )");

  auth = new Auth(db);
  auth->show();
  connect(auth, SIGNAL(authSuccessful(QString)), this, SLOT(authSuccessful(QString)));
}


Base::~Base()
{
  db.close();
  QSqlDatabase::removeDatabase("defaultConnection");
  delete auth;
  delete mainwidget;
}


QSqlDatabase Base::getDb()
{
  return db;
}


void Base::authSuccessful(QString user)
{
  auth->close();
  QApplication::setQuitOnLastWindowClosed(false);
  mainwidget = new MainWidget(db);
  mainwidget->setUser(user);
  mainwidget->show();
}
