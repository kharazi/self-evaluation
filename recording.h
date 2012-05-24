#ifndef RECORDING_H
#define RECORDING_H

#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
class Recording : public QWidget
{
    Q_OBJECT
public:
    explicit Recording(QWidget *parent = 0);
    QLabel* lable;
    QGridLayout* layout;
    QPushButton * record;

signals:

public slots:

};

#endif // RECORDING_H
