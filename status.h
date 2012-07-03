#ifndef STATUS_H
#define STATUS_H

#include <QWidget>
#include <QGridLayout>
#include <QSqlQuery>
#include <QPushButton>
#include <QSqlError>
#include <QRadioButton>
#include <QHash>
#include <QSpinBox>
#include <QComboBox>
#include "qdateconvertor.h"
#include "histogrammchart_month_t_total.h"


class Status : public QWidget
{
    Q_OBJECT

private:
    QSqlQuery query;
    int get_count_of_action(int action);
    void CreateStatusWidget();

public:
    explicit Status(QString u, QWidget *parent = 0);
    QGridLayout * layout;
    QString user;
    QSpinBox *year;
    QComboBox *month;

    QDateConvertor date;

    QTabWidget* tab;

signals:

public slots:
    void draw_chart_button_clicked();
};

#endif // STATUS_H
