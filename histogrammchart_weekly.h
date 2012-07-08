#ifndef HISTOGRAMMCHART_WEEKLY_H
#define HISTOGRAMMCHART_WEEKLY_H

#include <QWidget>
#include <QLabel>
#include <QFormLayout>
#include <QPushButton>
#include <QSqlQuery>
#include <QHash>

#include "nightcharts.h"
#include "qdateconvertor.h"

class HistogrammChart_weekly : public QWidget
{
    Q_OBJECT
private:
    void CreateWidget();
    void SetDefualtValue();
    void get_data();
    void paintEvent(QPaintEvent *);

    int week;

    QDateConvertor date;
    QSqlQuery query;
    QString user;

    QHash <int , int > index_value;
    QHash <int , QString> index_date;

    QPushButton * nextweek;
    QPushButton * previousweek;
    QLabel * title;
    QLabel * dateLable;

public:
    explicit HistogrammChart_weekly(QString,QWidget *parent = 0);
    ~HistogrammChart_weekly();

public slots:
    void nextweek_button_clicked();
    void previousweek_button_clicked();
};

#endif // HISTOGRAMMCHART_WEEKLY_H
