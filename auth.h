#ifndef AUTH_H
#define AUTH_H

#include <QGridLayout>
#include <QHBoxLayout>
#include <QStackedWidget>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QCloseEvent>
#include <QDebug>

class Auth : public QWidget
{
  Q_OBJECT

public:
  Auth();

private:
  void createDefaultWidget();
  void createSignUpWidget();
  void closeEvent(QCloseEvent* event);

  QStackedWidget *stackedWidget;
  QBoxLayout *mainLayout;
  QWidget *defaultWidget;
  QWidget *signUpWidget;
  QLineEdit *user;
  QLineEdit *pass;
  QLineEdit *email;
public slots:
  void checkAuth();
  void changePage();
  void submit();
  void clearForm();
signals:
  void authSuccessful();
  void authClosed();
};

#endif
