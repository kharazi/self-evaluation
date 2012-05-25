#ifndef AUTH_H
#define AUTH_H

#include <QtSql>
#include <QDialog>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QStackedWidget>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QCloseEvent>
#include <QMessageBox>
#include <QApplication>
#include <QDebug>

class Auth : public QWidget
{
  Q_OBJECT

public:
  Auth();
  Auth(QSqlDatabase d);
  //  ~Auth();

private:
  void createDefaultWidget();
  void createSignUpWidget();
  //  void closeEvent(QCloseEvent* event);

  QSqlDatabase db;

  QStackedWidget *stackedWidget;
  QBoxLayout *mainLayout;
  QWidget *defaultWidget;
  QWidget *signUpWidget;
  QLineEdit *user;
  QLineEdit *pass;
public slots:
  void checkAuth();
  void changePage();
  void submit();
  void clearForm();
  void openMain();
signals:
  void authSuccessful();
  void authClosed();
};

#endif
