#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include "record.h"
#include "qdateconvertor.h"
#include "nightcharts.h"


class Dashboard : public QWidget
{
    Q_OBJECT
private:
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


    void get_date();
    void get_hadith();

    QMap<int,int> chart_data;

    QDateConvertor date;
    QStringList today;
    QSqlQuery query;
    int test;
    void paintEvent(QPaintEvent *);



signals:

public slots:
    void get_data();
    void get_chart_data();
};

#endif // DASHBOARD_H
