#ifndef DCHART_PERCENT_OF_ACTION_YEARLY_H
#define DCHART_PERCENT_OF_ACTION_YEARLY_H

#include <QWidget>
#include <QFormLayout>
#include <QLabel>
#include <QSpinBox>
#include <QPushButton>
#include "nightcharts.h"
#include "qdateconvertor.h"
#include "QSqlQuery"

class DChart_percent_of_action_yearly : public QWidget
{
    Q_OBJECT
public:
    explicit DChart_percent_of_action_yearly(QString u,QWidget *parent = 0);
    void paintEvent(QPaintEvent *);
    QDateConvertor date;
    QStringList today;
    QSqlQuery query;
    QString user;
    void get_data();
    QHash<int,float> StatisticsPercent;
    QHash<int , QString>action_type;

    QSpinBox * year;
    QPushButton * draw;

    QLabel * title;
    QHash<QString,float> percent;
signals:

public slots:
    void draw_clicked();

};

#endif // DCHART_PERCENT_OF_ACTION_YEARLY_H
