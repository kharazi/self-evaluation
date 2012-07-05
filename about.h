#ifndef ABOUT_H
#define ABOUT_H

#include <QWidget>
#include <QTabWidget>
#include <QLabel>
#include <QGridLayout>

#include "abouttab.h"
#include "aboutselfevaluationtab.h"
#include "helptab.h"

class About : public QWidget
{
    Q_OBJECT
public:
    explicit About(QString u, QWidget *parent = 0);
    ~About();

 private:
    QTabWidget *tab;
    QGridLayout *layout;

signals:

public slots:

};

#endif // ABOUT_H
