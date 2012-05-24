#include "auth.h"

Auth::Auth()
{
  mainLayout = new QHBoxLayout;
  stackedWidget = new QStackedWidget;

  createDefaultWidget();
  stackedWidget->addWidget(defaultWidget);
  mainLayout->addWidget(stackedWidget);
  setLayout(mainLayout);
  resize(350, 200);
}


void Auth::createDefaultWidget()
{
  defaultWidget = new QWidget();
  QGridLayout *layout = new QGridLayout;
  layout->setOriginCorner(Qt::TopRightCorner);
  
  QLabel *descLabel = new QLabel("Please enter your login information. \
If this is the first time you're using this software you have to sign up.");
  descLabel->setWordWrap(true);
  descLabel->resize(descLabel->minimumSize());
  QLabel *userLabel = new QLabel(" :Username");
  QLabel *passLabel = new QLabel(" :Password");
  
  user = new QLineEdit;
  pass = new QLineEdit;

  QPushButton *signInButton = new QPushButton("Sign In");
  QPushButton *signUpButton = new QPushButton("Sign Up");
  connect(signInButton, SIGNAL(clicked()), this, SLOT(checkAuth()));
  connect(signUpButton, SIGNAL(clicked()), this, SLOT(changePage()));
  
  layout->addWidget(descLabel, 0, 0, 3, 1);
  layout->setColumnMinimumWidth(1, 15);
  layout->addWidget(userLabel, 0, 2);
  layout->addWidget(user, 0, 3);
  layout->addWidget(passLabel, 1, 2);
  layout->addWidget(pass, 1, 3);
  layout->addWidget(signInButton, 2, 2);
  layout->addWidget(signUpButton, 2, 3);

  defaultWidget->setLayout(layout);
}


void Auth::createSignUpWidget()
{
  signUpWidget = new QWidget;
  QGridLayout *layout = new QGridLayout;
  layout->setOriginCorner(Qt::TopRightCorner);

  QLabel *userLabel = new QLabel(" :Username");
  QLabel *passLabel = new QLabel(" :Password");
  QLabel *emailLabel = new QLabel(" :Email");

  email = new QLineEdit;

  QPushButton *backButton = new QPushButton("Back");
  QPushButton *submitButton = new QPushButton("Submit");
  QPushButton *clearButton = new QPushButton("Clear");
  connect(backButton, SIGNAL(clicked()), this, SLOT(changePage()));
  connect(submitButton, SIGNAL(clicked()), this, SLOT(submit()));
  connect(clearButton, SIGNAL(clicked()), this, SLOT(clearForm()));

  //  layout->addWidget(backButton, 0, 2);
  //  layout->setSpacing(10);
  layout->addWidget(userLabel, 0, 0);
  layout->addWidget(user, 0, 1);
  layout->addWidget(passLabel, 1, 0);
  layout->addWidget(pass, 1, 1);
  layout->addWidget(emailLabel, 2, 0);
  layout->addWidget(email, 2, 1);
  layout->addWidget(submitButton, 4, 1);
  layout->addWidget(clearButton, 4, 2);

  signUpWidget->setLayout(layout);
}


void Auth::closeEvent(QCloseEvent* event)
{
  emit authClosed();
  event->accept();
}


void Auth::checkAuth()
{
  emit authSuccessful();
}


void Auth::changePage()
{
  if (stackedWidget->count()==1){ createSignUpWidget(); stackedWidget->addWidget(signUpWidget); }
  stackedWidget->currentIndex()==0 ? stackedWidget->setCurrentIndex(1) : stackedWidget->setCurrentIndex(0);
  stackedWidget->currentWidget()->update();
}


void Auth::submit()
{
}


void Auth::clearForm()
{
}
