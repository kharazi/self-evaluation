#ifndef HISTOGRAMMCHART_HOUR_OF_DAY_MONTHLY_H
#define HISTOGRAMMCHART_HOUR_OF_DAY_MONTHLY_H

#include <QWidget>
#include <QComboBox>
#include <QLabel>
#include <QRadioButton>
#include <QFormLayout>
#include <QSpinBox>
#include <QPushButton>
#include "nightcharts.h"
#include "qdateconvertor.h"
#include "QSqlQuery"

class HistogrammChart_Hour_Of_Day_monthly : public QWidget
{
    Q_OBJECT
public:
    explicit HistogrammChart_Hour_Of_Day_monthly(QString u,QWidget *parent = 0);

    QDateConvertor date;
    QStringList today;
    QSqlQuery query;
    QRadioButton * AM;
    QSpinBox * year;
    QComboBox * month;
    bool is_AM;
    QRadioButton * PM;
    QString user;
    QLabel * title;
    QPushButton * draw;
    void get_data();
    void paintEvent(QPaintEvent *);

    QMap <int , int> countOfhours;

public slots:
    void draw_clicked();


};

#endif // HISTOGRAMMCHART_HOUR_OF_DAY_MONTHLY_H
