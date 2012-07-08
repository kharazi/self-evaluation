#ifndef ABOUTCHARTS_H
#define ABOUTCHARTS_H

#include <QWidget>
#include <QSqlQuery>
#include <QLabel>
#include <QScrollArea>
#include <QFormLayout>
#include <QVariant>


class AboutCharts : public QWidget
{
    Q_OBJECT
public:
    explicit AboutCharts(QWidget *parent = 0);
    ~AboutCharts();
private:
   QFormLayout *mainlayout;
   QLabel * about;


   QSqlQuery query;
   void get_data();
   void create_widget();

signals:

public slots:

};

#endif // ABOUTCHARTS_H
