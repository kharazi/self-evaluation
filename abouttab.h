#ifndef ABOUTTAB_H
#define ABOUTTAB_H

#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <QScrollArea>


class aboutTab : public QWidget
{
    Q_OBJECT
public:
    explicit aboutTab(QWidget *parent = 0);
    ~aboutTab();

 private:
    QGridLayout *mainlayout;
    QLabel * about;

signals:

public slots:

};

#endif // ABOUTTAB_H
