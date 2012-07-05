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
public:
    explicit Dashboard(QString u, QWidget *parent = 0);
    ~Dashboard();

    void get_date();
    void get_hadith();

    void paintEvent(QPaintEvent *);

 private:
    void CreateDashboardWidget();

    QString user;
    QVBoxLayout * mainlayout;
    record *re;
    QLabel * DateLable;
    QLabel* HadithLable;
    QLabel * statusLable;
    QLabel * mostLabel;
    QMap<int,int> chart_data;

    QDateConvertor date;
    QStringList today;
    QSqlQuery query;

signals:

public slots:
    void get_data();
    void get_chart_data();
};

#endif // DASHBOARD_H
