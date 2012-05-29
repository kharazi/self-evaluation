#include "useroption.h"


#include <QDebug>
UserOption::UserOption(QWidget *parent) :
    QWidget(parent)
{
    CreateUserOption();
    connect(change,SIGNAL(clicked()),this,SLOT(change_button_clicked()));

}

void UserOption::CreateUserOption(){
    mainlayout= new QGridLayout;

    prePass =new QLineEdit;
    prePass->setEchoMode(QLineEdit::Password);
    verificationPass=new QLineEdit;
    verificationPass->setEchoMode(QLineEdit::Password);

    newPass =new QLineEdit;
    newPass->setEchoMode(QLineEdit::Password);


//       label = new QLabel("change password");

    prePassLabel= new QLabel(tr("prePass"));
    prePassLabel->setBuddy(prePass);

    newPassLabel = new QLabel(tr("newPass"));
    newPassLabel->setBuddy(newPass);

    verificationPassLabel = new QLabel("verificationPass");
    verificationPassLabel->setBuddy(verificationPass);

    change=new QPushButton(QString::fromUtf8("change"));
//    mainlayout->addWidget(label, 0, 0,1,1);
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

        //badan age tonestim user namo begirim bezarim ja ali
       QSqlQuery query;
       query.exec(QString("SELECT password FROM users WHERE username= '%1' ").arg("vahid"));
       while (query.next()) {
           qDebug()<< query.value(0).toString();
           if (query.value(0).toString()==prePass->text()){
                 query.exec(QString("UPDATE users SET password='%1' WHERE password='%2' AND username = '%3' ").arg(newPass->text()).arg(query.value(0).toString()).arg("vahid"));
                 if (query.lastError().type()==0){
                     prePass->setText("");
                     newPass->setText("");
                     verificationPass->setText("");

                     QMessageBox *error = new QMessageBox;
                     error->setText("sucsessfull;your password changed");
                     qDebug() << query.lastError();
                     error->setIcon(QMessageBox::Information);
                     error->setWindowTitle("Information");
                     error->exec();

                 }

           }else{

               QMessageBox *error = new QMessageBox;
               error->setText("password not correct");
               qDebug() << query.lastError();
               error->setIcon(QMessageBox::Warning);
               error->setWindowTitle("Error");
               error->exec();

           }
       }

        if (query.lastError().type()!=0){

            QMessageBox *error = new QMessageBox;
            error->setText("there is a problem; Cannot update Database ");
            qDebug() << query.lastError();
            error->setIcon(QMessageBox::Warning);
            error->setWindowTitle("Error");
            error->exec();

        }

    }
    }




