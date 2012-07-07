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


  for (int i=1;i<=1000;i++){
      qDebug()<<qrand()%50;
        query.prepare("INSERT INTO actions (id,action_id,username,description,date,time,rate) VALUES(?,?,?,?,?,?,?) ");
        query.addBindValue(QVariant(QVariant::Int));
              query.addBindValue(qrand()%15);
              query.addBindValue("vahid");
              query.addBindValue(QString::fromUtf8("توضیح این عمل"));

              query.addBindValue(QString("%1-%2-%3").arg("1391").arg(qrand()%12).arg(qrand()%30));

              query.addBindValue(QString("%1:%2").arg(qrand()%23).arg(qrand()%59));
              query.addBindValue(qrand()%5);
              query.exec();

  }

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


