#ifndef HELPTAB_H
#define HELPTAB_H

#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <QScrollArea>

class Helptab : public QWidget
{
    Q_OBJECT
public:
    explicit Helptab(QWidget *parent = 0);
    ~Helptab();

 private:
    QGridLayout *mainlayout;
    QLabel * about;
    QScrollArea* scroll;

signals:

public slots:

};

#endif // HELPTAB_H
