#ifndef BASE_H
#define BASE_H

#include "mainwidget.h"
#include "auth.h"
#include <QSqlDatabase>
#include <QObject>

class Base : public QObject
{
  Q_OBJECT

public:
  Base();
  ~Base();
  QSqlDatabase getDb();


  static QSqlDatabase getdatabase();
private:
  Auth *auth;
  MainWidget *mainwidget;
  void fillTable(QSqlDatabase);
  QSqlDatabase db;


public slots:
  void authSuccessful(QString user);

};

#endif
