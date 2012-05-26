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
private:
  Auth *auth;
  MainWidget *mainwidget;
  QSqlDatabase db;
  void fillTable(QSqlDatabase);

public slots:
  void authSuccessful(QString user);

};

#endif
