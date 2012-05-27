#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <QWidget>
#include <QPushButton>
#include <QComboBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QGridLayout>
#include "record.h"

class Dashboard : public QWidget
{
    Q_OBJECT
public:
    explicit Dashboard(QWidget *parent = 0);

    QGridLayout * mainlayout;
    record *re;


signals:

public slots:

};

#endif // DASHBOARD_H
