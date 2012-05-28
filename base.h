#ifndef BASE_H
#define BASE_H

#include "mainwidget.h"
#include <QSqlDatabase>
#include <QObject>
#include "auth.h"
class Base : public QObject
{
  Q_OBJECT

public:
  Base();
  ~Base();
  QSqlDatabase database;


  //  static QSqlDatabase getdatabase();
private:
  Auth *auth;
  MainWidget *mainwidget;
  void fillTable();


public slots:
  void authSuccessful(QString user);

};

#endif
