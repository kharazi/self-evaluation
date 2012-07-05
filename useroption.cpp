#include "useroption.h"
#include <QDebug>

UserOption::UserOption(QString u,QWidget *parent) :
    QWidget(parent)
{
    user=u;
    CreateUserOption();
    connect(change,SIGNAL(clicked()),this,SLOT(change_button_clicked()));

}

UserOption::~UserOption()
{
  delete label;
  delete prePassLabel;
  delete newPassLabel;
  delete verificationPassLabel;
  delete prePass;
  delete newPass;
  delete verificationPass;
  delete change;
  delete mainlayout;
}

void UserOption::CreateUserOption(){
    mainlayout= new QGridLayout;

    prePass =new QLineEdit;
    prePass->setEchoMode(QLineEdit::Password);
    verificationPass=new QLineEdit;
    verificationPass->setEchoMode(QLineEdit::Password);

    newPass =new QLineEdit;
    newPass->setEchoMode(QLineEdit::Password);

    prePassLabel= new QLabel(QString::fromUtf8("رمز"));
    prePassLabel->setBuddy(prePass);

    newPassLabel = new QLabel(QString::fromUtf8("رمز جدید"));
    newPassLabel->setBuddy(newPass);

    verificationPassLabel = new QLabel(QString::fromUtf8("تایید رمز"));
    verificationPassLabel->setBuddy(verificationPass);

    change=new QPushButton(QString::fromUtf8("تغییر دادن"));

    mainlayout->addWidget(prePassLabel, 1, 1,1,1);
    mainlayout->addWidget(prePass, 1, 0,1,1);
    mainlayout->addWidget(newPassLabel, 2, 1,1,1);
    mainlayout->addWidget(newPass, 2, 0,1,1);
    mainlayout->addWidget(verificationPassLabel, 3, 1,1,1);
    mainlayout->addWidget(verificationPass, 3, 0,1,1);
    mainlayout->addWidget(change,4,1,1,1);
    this->setLayout(mainlayout);

}
void UserOption::change_button_clicked(){
    if (newPass->text()!=verificationPass->text() || newPass->text()=="" || prePass->text()==""){
        QMessageBox *error = new QMessageBox;
        error->setText(QString::fromUtf8(".همه فیلد ها را با دقت وارد کنید"));
        error->setIcon(QMessageBox::Warning);
        error->setWindowTitle("Error");
        error->exec();

    }else{

        //badan age tonestim user namo begirim bezarim ja vahid
       QSqlQuery query;
       query.exec(QString("SELECT password FROM users WHERE username= '%1' ").arg(user));
       while (query.next()) {
           if (query.value(0).toString()==prePass->text()){
                 query.exec(QString("UPDATE users SET password='%1' WHERE password='%2' AND username = '%3' ").arg(newPass->text()).arg(query.value(0).toString()).arg(user));
                 if (query.lastError().type()==0){
                     prePass->setText("");
                     newPass->setText("");
                     verificationPass->setText("");

                     QMessageBox *error = new QMessageBox;
                     error->setText(QString::fromUtf8(".همه فیلد ها را با دقت وارد کنید"));
                     error->setIcon(QMessageBox::Information);
                     error->setWindowTitle("Information");
                     error->exec();

                 }

           }else{

               QMessageBox *error = new QMessageBox;
               error->setText(QString::fromUtf8("رمز عبور صحیح نمی باشد."));
               error->setIcon(QMessageBox::Warning);
               error->setWindowTitle(QString::fromUtf8("خطا"));
               error->exec();

           }
       }

        if (query.lastError().type()!=0){

            QMessageBox *error = new QMessageBox;
            error->setText(QString::fromUtf8("خطا در اتصال به پایگاه داده. مجددا تلاش کنید!"));
            error->setIcon(QMessageBox::Warning);
            error->setWindowTitle(QString::fromUtf8("خطا"));
            error->exec();

        }

    }
}




