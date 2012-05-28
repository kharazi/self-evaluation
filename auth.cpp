#include "auth.h"
#include <QDebug>
Auth::Auth()
{
//    db=database;
//    bool b=db.open();
//    if (!b){
//        qDebug()<<"dsfdsf";

//    }else{



//    }

    setAttribute(Qt::WA_DeleteOnClose);
   mainLayout = new QHBoxLayout;
   stackedWidget = new QStackedWidget;

   createDefaultWidget();
   stackedWidget->addWidget(defaultWidget);
   mainLayout->addWidget(stackedWidget);
   setLayout(mainLayout);
   resize(350, 200);
}




// Auth::~Auth()
// {
//   db.close();
//   QSqlDatabase::removeDatabase("defaultConnection");
//   qDebug() << "really?";
//   delete window;
//   delete user;
//   delete pass;
//   delete defaultWidget;
//   // delete signUpWidget;
//   delete mainLayout;
//   delete stackedWidget;

// }


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
  pass->setEchoMode(QLineEdit::Password);

  QPushButton *signInButton = new QPushButton("Sign In");
  QPushButton *signUpButton = new QPushButton("Sign Up");
  signInButton->setDefault(true);
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

  QPushButton *backButton = new QPushButton("Back");
  QPushButton *submitButton = new QPushButton("Submit");
  QPushButton *clearButton = new QPushButton("Clear");
  connect(backButton, SIGNAL(clicked()), this, SLOT(changePage()));
  connect(submitButton, SIGNAL(clicked()), this, SLOT(submit()));
  connect(clearButton, SIGNAL(clicked()), this, SLOT(clearForm()));

  layout->addWidget(userLabel, 0, 0);
  layout->addWidget(user, 0, 1);
  layout->addWidget(passLabel, 1, 0);
  layout->addWidget(pass, 1, 1);
  layout->addWidget(submitButton, 4, 1);
  layout->addWidget(clearButton, 4, 2);

  signUpWidget->setLayout(layout);
}


// void Auth::closeEvent(QCloseEvent* event)
// {
//   //  emit authClosed();
//   event->accept();
// }


void Auth::checkAuth()
{
  QSqlQuery query;
  query.prepare("SELECT password FROM users WHERE username=?");
  query.addBindValue(user->text());
  bool res = query.exec();
  if (!res)
    qDebug() << query.lastError();
  else {
    query.next();
    if (pass->text() == query.value(0))
      emit authSuccessful(user->text());
    else {
      QMessageBox *error = new QMessageBox;
      error->setText("Login unsuccessful, please try again!");
      error->setIcon(QMessageBox::Warning);
      error->setWindowTitle("Error");
      error->exec();
    }
  }
}


void Auth::changePage()
{
  if (stackedWidget->count()==1){ createSignUpWidget(); stackedWidget->addWidget(signUpWidget); }
  if (stackedWidget->currentIndex()==0) {
    stackedWidget->setCurrentIndex(1);
    
  }
  else {
    stackedWidget->setCurrentIndex(0);
  }
  stackedWidget->currentWidget()->update();
}


void Auth::submit()
{
  QSqlQuery query;
  query.prepare("INSERT INTO users (username, password) "
		     "VALUES (?, ?)");
  query.addBindValue(user->text());
  query.addBindValue(pass->text());
  bool res = query.exec();

  if (!res) {
    qDebug() << query.lastError();
    QMessageBox *error = new QMessageBox;
    error->setText("User could not be created. We're sorry for this inconvinience");
    error->setIcon(QMessageBox::Warning);
    error->exec();
  }
  else emit authSuccessful(user->text());
}


void Auth::clearForm()
{
  user->clear();
  pass->clear();
}
