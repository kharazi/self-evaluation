#ifndef HISTOGRAMMCHART_WEEKLY_H
#define HISTOGRAMMCHART_WEEKLY_H

#include <QWidget>
#include <QLabel>
#include <QSpinBox>
#include <QFormLayout>
#include <QComboBox>
#include <QPushButton>
#include "nightcharts.h"
#include "qdateconvertor.h"
#include "QSqlQuery"

class HistogrammChart_weekly : public QWidget
{
    Q_OBJECT
private:
    void CreateWidget();
    void SetDefualtValue();    QDateConvertor date;
    QSqlQuery query;
    QString user;
    QLabel * title;
     void get_data();

    int week;
    void paintEvent(QPaintEvent *);


    QHash <int , int > index_value;
    QHash <int , QString> index_date;



    QPushButton * nextweek;
    QPushButton * previousweek;

    QLabel * dateLable;

public:
    explicit HistogrammChart_weekly(QString,QWidget *parent = 0);



signals:

public slots:
    void nextweek_button_clicked();
    void previousweek_button_clicked();
};

#endif // HISTOGRAMMCHART_WEEKLY_H
