#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <QWidget>
#include <QHBoxLayout>
#include "record.h"

class Dashboard : public QWidget
{
    Q_OBJECT
public:
    explicit Dashboard(QString u, QWidget *parent = 0);

    QHBoxLayout * mainlayout;
    record *re;


signals:

public slots:

};

#endif // DASHBOARD_H
