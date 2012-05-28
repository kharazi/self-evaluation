#ifndef OPTIONS_H
#define OPTIONS_H

#include <QWidget>
#include <QGridLayout>
class Options : public QWidget
{
    Q_OBJECT
public:
    explicit Options(QWidget *parent = 0);
    QGridLayout *layout;
signals:

public slots:

};

#endif // OPTIONS_H
