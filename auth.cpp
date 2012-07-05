#include "auth.h"
#include <QDebug>
Auth::Auth()
{
   setAttribute(Qt::WA_DeleteOnClose);
   mainLayout = new QHBoxLayout;
   stackedWidget = new QStackedWidget;

   createDefaultWidget();
   stackedWidget->addWidget(defaultWidget);
   mainLayout->addWidget(stackedWidget);
   setLayout(mainLayout);
   this->setWindowTitle(QString::fromUtf8("ورود"));
   this->setWindowOpacity(0.95);
   resize(400, 200);
   QPalette palette;
   palette.setBrush(this->backgroundRole(), QBrush(QImage(":/images/backg.jpg")));
   this->setPalette(palette);
}




 Auth::~Auth()
 {
  delete user;
  delete pass;
  delete mainLayout;
  delete defaultWidget;
  delete stackedWidget;
}


void Auth::createDefaultWidget()
{
  defaultWidget = new QWidget();
  QGridLayout *layout = new QGridLayout;
  layout->setOriginCorner(Qt::TopRightCorner);
  
  QLabel *descLabel = new QLabel(QString::fromUtf8(" لطفا نام کاربری و کلمه عبور خود را وارد کنید."
"اگر برای نخستین بار از این نرم افزار استفاده می کنید یک حساب کاربری جدید ایجاد کنید."));
  descLabel->setWordWrap(true);
  descLabel->resize(descLabel->minimumSize());
  QLabel *userLabel = new QLabel(QString::fromUtf8("نام کاربری:"));
  QLabel *passLabel = new QLabel(QString::fromUtf8("کلمه عبور:"));
  
  user = new QLineEdit;
  pass = new QLineEdit;
  pass->setEchoMode(QLineEdit::Password);

  QPushButton *signInButton = new QPushButton(QString::fromUtf8("ورود"));
  QPushButton *signUpButton = new QPushButton(QString::fromUtf8("ایجاد حساب کاربری"));
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

  QLabel *userLabel = new QLabel(QString::fromUtf8("نام کاربری:"));
  QLabel *passLabel = new QLabel(QString::fromUtf8("کلمه عبور:"));

  QPushButton *backButton = new QPushButton(QString::fromUtf8("بازگشت"));
  QPushButton *submitButton = new QPushButton(QString::fromUtf8("ایجاد"));
  QPushButton *clearButton = new QPushButton(QString::fromUtf8("پاک کن"));
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


void Auth::checkAuth()
{
  QSqlQuery query;
  query.prepare("SELECT password FROM users WHERE username=?");
  query.addBindValue(user->text());
  query.exec();
  query.next();
  if (pass->text() == query.value(0))
    emit authSuccessful(user->text());
  else {
    QMessageBox *error = new QMessageBox;
    error->setText(QString::fromUtf8("ورود ناموفق بود. لطفا دوباره تلاش کنید."));
    error->setIcon(QMessageBox::Warning);
    error->setWindowTitle(QString::fromUtf8("خطا"));
    error->exec();
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
