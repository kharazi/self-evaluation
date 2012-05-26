#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <QWidget>
#include <QPushButton>
#include <QComboBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QGridLayout>
#include "base.h"
class Dashboard : public QWidget
{
    Q_OBJECT
public:
    explicit Dashboard(QWidget *parent = 0);
    QPushButton * record;
    QComboBox * sidtype;
    QGridLayout * mainlayout;
    QGridLayout * recordlayout;

signals:

public slots:
    void record_button_clicked();
};

#endif // DASHBOARD_H
