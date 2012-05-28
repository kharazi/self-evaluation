#ifndef AUTH_H
#define AUTH_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
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

class Auth : public QDialog
{
  Q_OBJECT

public:
  Auth();
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
signals:
  void authSuccessful(QString user);
  void authClosed();
};

#endif
