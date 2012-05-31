#ifndef BASE_H
#define BASE_H

#include "mainwidget.h"
#include <QSqlDatabase>
#include <QObject>
#include "auth.h"
#include <QDebug>

class Base : public QObject
{
  Q_OBJECT

public:
  Base();
  ~Base();

private:
  Auth *auth;
  MainWidget *mainwidget;
  void fillTable();

public slots:
  void authSuccessful(QString u);

};

#endif
