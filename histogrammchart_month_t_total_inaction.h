#ifndef HISTOGRAMMCHART_MONTH_T_TOTAL_INACTION_H
#define HISTOGRAMMCHART_MONTH_T_TOTAL_INACTION_H

#include <QWidget>
#include <QLabel>
#include <QSpinBox>
#include <QFormLayout>
#include <QComboBox>
#include <QMessageBox>
#include <QPushButton>

#include "nightcharts.h"
#include "qdateconvertor.h"
#include <QSqlQuery>
#include <QSqlError>

class HistogrammChart_Month_t_Total_inAction : public QWidget
{
    Q_OBJECT
public:
    explicit HistogrammChart_Month_t_Total_inAction(QString u,QWidget *parent = 0);
    ~HistogrammChart_Month_t_Total_inAction();
    void paintEvent(QPaintEvent *);
    void get_data();

 private:
    QDateConvertor date;
    QStringList today;
    QSqlQuery query;
    QString user;
    QPushButton * draw;

    QLabel * title;

    QSpinBox * year;
    QComboBox * action_type;

    QHash <int, int> month;

    void create_widget();
    void set_defualt_value();
signals:

public slots:
    void draw_cliked();


};

#endif // HISTOGRAMMCHART_MONTH_T_TOTAL_INACTION_H
