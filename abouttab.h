#ifndef ABOUTTAB_H
#define ABOUTTAB_H

#include <QWidget>
#include <QSqlQuery>
#include <QLabel>
#include <QScrollArea>
#include <QFormLayout>
#include <QVariant>


class aboutTab : public QWidget
{
    Q_OBJECT
public:
    explicit aboutTab(QWidget *parent = 0);
    ~aboutTab();

 private:
    QFormLayout *mainlayout;
    QLabel * about;
    QLabel * title;
    void get_data();
    QSqlQuery query;


signals:

public slots:

};

#endif // ABOUTTAB_H
