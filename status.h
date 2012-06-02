#ifndef STATUS_H
#define STATUS_H

#include <QWidget>
#include <QGridLayout>
#include <QSqlQuery>


class Status : public QWidget
{
    Q_OBJECT
public:
    explicit Status(QString u, QWidget *parent = 0);
    QGridLayout * layout;

signals:

public slots:

};

#endif // STATUS_H
