#ifndef USEROPTION_H
#define USEROPTION_H

#include <QWidget>
#include <QLabel>
#include <QGridLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>

class UserOption : public QWidget
{
    Q_OBJECT
public:
    explicit UserOption(QWidget *parent = 0);
private:
    QGridLayout *mainlayout;

    QLabel * label;
    QLabel *prePassLabel;
    QLabel *newPassLabel;
    QLabel *verificationPassLabel;

    QLineEdit*prePass;
    QLineEdit*newPass;
    QLineEdit*verificationPass;
    QPushButton * change;
    void CreateUserOption();


signals:

public slots:
    void change_button_clicked();

};

#endif // USEROPTION_H
