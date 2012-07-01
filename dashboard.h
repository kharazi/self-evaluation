#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include "record.h"
#include "qdateconvertor.h"

class Dashboard : public QWidget
{
    Q_OBJECT
private:
    void get_data();
    void get_hadith();
    void get_date();
    void CreateDashboardWidget();
public:
    explicit Dashboard(QString u, QWidget *parent = 0);
    QString user;
    QVBoxLayout * mainlayout;
    record *re;
    QLabel * DateLable;
    QLabel* HadithLable;
    QLabel * statusLable;
    QLabel * mostLabel;

    QDateConvertor date;
    QStringList today;
    QSqlQuery query;


signals:

public slots:

};

#endif // DASHBOARD_H
