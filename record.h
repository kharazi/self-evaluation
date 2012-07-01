#ifndef RECORD_H
#define RECORD_H

#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QComboBox>
#include <QFormLayout>
#include <QSlider>
#include <QLabel>
#include <QDateEdit>
#include <QTimeEdit>
#include <QTextEdit>
#include <QDate>
#include <QGroupBox>
#include "base.h"
#include "qdateconvertor.h"

class record : public QWidget
{
    Q_OBJECT
public:
    explicit record(QString u, QWidget *parent = 0);

private:
    QString user;
    void createRecordWidget();
    QPushButton * record_button;
    QComboBox * action_type;
    QGridLayout * mainlayout;
    QGridLayout * ratelayout;
    QFormLayout * formlayout;
    QSlider * rate;
    QDateEdit * date;
    QTimeEdit * time;
    QTextEdit * description;

    QLabel *descriptionLabel;
    QLabel *typeLabel;
    QLabel * rateLabel;

    QDate defultdate;

    QGroupBox* recordGroup;



signals:

public slots:
    void record_button_clicked();

};

#endif // RECORD_H
