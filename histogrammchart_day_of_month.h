#ifndef HISTOGRAMMCHART_DAY_OF_MONTH_H
#define HISTOGRAMMCHART_DAY_OF_MONTH_H

#include <QWidget>
#include <QLabel>
#include <QSpinBox>
#include <QFormLayout>
#include <QComboBox>
#include <QPushButton>
#include "nightcharts.h"
#include "qdateconvertor.h"
#include <QSqlQuery>

class HistogrammChart_Day_of_Month : public QWidget
{
    Q_OBJECT
public:
    explicit HistogrammChart_Day_of_Month(QString u,QWidget *parent = 0);
    ~HistogrammChart_Day_of_Month();
    void get_data();
    void paintEvent(QPaintEvent *);

 private:
    QDateConvertor date;
    QStringList today;
    QSqlQuery query;
    QString user;
    QComboBox *month;
    QLabel * title;
    QPushButton * draw;

    QMap <int , int> countOfmonth;

    QSpinBox * year;

signals:

public slots:
    void draw_clicked();
};

#endif // HISTOGRAMMCHART_DAY_OF_MONTH_H
