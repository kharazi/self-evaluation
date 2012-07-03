#ifndef HISTOGRAMMCHART_MONTH_T_TOTAL_H
#define HISTOGRAMMCHART_MONTH_T_TOTAL_H

#include <QWidget>
#include <QLabel>
#include <QSpinBox>
#include <QFormLayout>
#include <QComboBox>
#include "nightcharts.h"
#include "qdateconvertor.h"
#include "QSqlQuery"
class HistogrammChart_Month_t_Total : public QWidget
{
    Q_OBJECT
public:
    explicit HistogrammChart_Month_t_Total(QString u,QWidget *parent = 0);
    void paintEvent(QPaintEvent *);
    QDateConvertor date;
    QStringList today;
    QSqlQuery query;
    QString user;

    QLabel * title;


    QSpinBox * year;

    QHash <int, int> month;

    void get_data();

signals:

public slots:

};

#endif // HISTOGRAMMCHART_MONTH_T_TOTAL_H
