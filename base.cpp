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

  

  fillTable();

  QSqlQuery q("SELECT * FROM actions");
  qDebug() << "********";
  while (q.next()) {
      QString person = q.value(0).toString();
      qDebug()<<person << q.value(1).toString() << q.value(2).toString() << q.value(3).toString() << q.value(4).toString() << q.value(5).toString() << q.value(6).toString() << endl;
  }
  qDebug() << "********";
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
  qDebug() << u;
  mainwidget = new MainWidget(u);
  //  mainwidget->setUser(user);
  mainwidget->show();
}

void Base::fillTable(){
  //this function for test
  //and to set defualt sid in start
    QSqlQuery query;
//    for (int i=0;i<14;i++){
//        query.prepare("INSERT INTO action_types (action_id, title) VALUES(?, ?) ");
//        query.addBindValue(QVariant(QVariant::Int));
//        query.addBindValue(QString::fromUtf8("کار شماره ی")+QString::number(i) );
//    query.exec();
//    }
//    qDebug() << query.lastError();


//    query.prepare("INSERT INTO hadith (hadith_id,action_id,narrator, hadith_text) VALUES(?,?, ?, ?) ");
//    query.addBindValue(QVariant(QVariant::Int));
//    query.addBindValue(QString::fromUtf8("hah ")+QString::number(1) );
//    query.addBindValue(QString::fromUtf8("من گفتم"));
//    query.addBindValue(QString::fromUtf8("کار بد نکن پسر بابا"));
//    query.exec();

    
//    query.prepare("INSERT INTO actions (id, action_id, username, description, date, time, rate) VALUES(?, ?, ?, ?, ?, ?, ?) ");
//    query.addBindValue(QVariant(QVariant::Int));
//    query.addBindValue(1);
//    query.addBindValue("sina");
//    query.addBindValue("something");
//    query.addBindValue("2000-11-14");
//    query.addBindValue("12:34");
//    query.addBindValue(3);
//    query.exec();
//    qDebug() << query.lastError().text();
}
