#ifndef HISTOGRAMMCHART_MONTH_T_TOTAL_H
#define HISTOGRAMMCHART_MONTH_T_TOTAL_H

#include <QWidget>
#include <QLabel>
#include <QSpinBox>
#include <QFormLayout>
#include <QComboBox>
#include <QPushButton>
#include "nightcharts.h"
#include "qdateconvertor.h"
#include <QSqlQuery>

class HistogrammChart_Month_t_Total : public QWidget
{
    Q_OBJECT
public:
    explicit HistogrammChart_Month_t_Total(QString u,QWidget *parent = 0);
    ~HistogrammChart_Month_t_Total();
    void paintEvent(QPaintEvent *);
    void get_data();

 private:
    QDateConvertor date;
    QStringList today;
    QSqlQuery query;
    QString user;

    QLabel * title;
    QPushButton * draw;
    QSpinBox * year;

    QHash <int, int> month;
    
signals:

public slots:
    void draw_cliked();

};

#endif // HISTOGRAMMCHART_MONTH_T_TOTAL_H
