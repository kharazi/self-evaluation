#ifndef HELPTAB_H
#define HELPTAB_H

#include <QWidget>
#include <QSqlQuery>
#include <QLabel>
#include <QScrollArea>
#include <QFormLayout>
#include <QVariant>



class Helptab : public QWidget
{
    Q_OBJECT
public:
    explicit Helptab(QWidget *parent = 0);
    ~Helptab();
private:
   QFormLayout *mainlayout;
   QLabel * about;


   QSqlQuery query;
   void get_data();
   void create_widget();


signals:

public slots:

};

#endif // HELPTAB_H
