#ifndef OPTIONS_H
#define OPTIONS_H

#include <QWidget>
#include <QGridLayout>
#include <QTabWidget>
class Options : public QWidget
{
    Q_OBJECT
public:
    explicit Options(QString u, QWidget *parent = 0);
    QGridLayout *layout;
    QTabWidget* tab;

signals:

public slots:

};

#endif // OPTIONS_H
