#ifndef STATUS_H
#define STATUS_H

#include <QWidget>
#include <QGridLayout>
#include <QVariant>
#include <QSqlQuery>
#include <QSqlError>
#include <QHash>
#include "qdateconvertor.h"


class Status : public QWidget
{
    Q_OBJECT

private:

    QSqlQuery query;

    int get_count_of_action(int action);
public:
    explicit Status(QString u, QWidget *parent = 0);
    QGridLayout * layout;

signals:

public slots:

};

#endif // STATUS_H
