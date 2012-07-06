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

  query.exec("CREATE TABLE action_types "
             "(action_id INTEGER PRIMARY KEY, title VARCHAR(60))");

  query.exec("CREATE TABLE actions "
             "(id INTEGER PRIMARY KEY, action_id INTEGER NOT NULL, username VARCHAR(30) NOT NULL, description TEXT, date DATE NOT NULL ,time TIME NOT NULL, rate INTEGER)");

  query.exec("CREATE TABLE hadith "
             "(hadith_id INTEGER PRIMARY KEY,action_id INTEGER NOT NULL,narrator TEXT,hadith_text TEXT)");

  query.exec("CREATE TABLE contents"
             "(content_id INTEGER PRIMARY KEY,title VARCHAR(120),content TEXT)");


  auth = new Auth;
  auth->show();
  connect(auth, SIGNAL(authSuccessful(QString)), this, SLOT(authSuccessful(QString)));

}


Base::~Base()
{
  delete auth;
  delete mainwidget;
}

void Base::authSuccessful(QString u)
{
  auth->close();
  QApplication::setQuitOnLastWindowClosed(false);
  mainwidget = new MainWidget(u);
  mainwidget->show();
}


