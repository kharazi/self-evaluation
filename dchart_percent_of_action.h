#ifndef DCHART_PERCENT_OF_ACTION_H
#define DCHART_PERCENT_OF_ACTION_H

#include <QWidget>
#include <QFormLayout>
#include <QLabel>
#include "nightcharts.h"
#include "qdateconvertor.h"
#include <QSqlQuery>
#include <QVariant>

class DChart_percent_of_action : public QWidget
{
    Q_OBJECT
public:
    explicit DChart_percent_of_action(QString u,QWidget *parent = 0);
    ~DChart_percent_of_action();
    void paintEvent(QPaintEvent *);

 private:
    QDateConvertor date;
    QStringList today;
    QSqlQuery query;
    QString user;
    void get_data();
    QHash<int,float> StatisticsPercent;
    QHash<int , QString>action_type;

    QLabel * title;
    QHash<QString,float> percent;
    
signals:

public slots:

};

#endif // DCHART_PERCENT_OF_ACTION_H
