#ifndef HISTOGRAMMCHART_HOUR_OF_DAY_H
#define HISTOGRAMMCHART_HOUR_OF_DAY_H


#include <QWidget>
#include <QLabel>
#include <QRadioButton>
#include <QFormLayout>
#include <QSpinBox>
#include <QPushButton>
#include "nightcharts.h"
#include "qdateconvertor.h"
#include <QSqlQuery>
#include <QVariant>

class HistogrammChart_Hour_Of_Day : public QWidget
{
    Q_OBJECT
public:
    explicit HistogrammChart_Hour_Of_Day(QString u,QWidget *parent = 0);
    ~HistogrammChart_Hour_Of_Day();
    void get_data();
    void paintEvent(QPaintEvent *);

 private:
    QDateConvertor date;
    QStringList today;
    QSqlQuery query;
    QRadioButton * AM;
    QSpinBox * year;
    bool is_AM;
    QRadioButton * PM;
    QString user;
    QLabel * title;
    QPushButton * draw;

    QMap <int , int> countOfhours;


signals:

public slots:
    void draw_clicked();
};

#endif // HISTOGRAMMCHART_HOUR_OF_DAY_H
