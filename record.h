#ifndef RECORD_H
#define RECORD_H

#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QComboBox>
#include <QFormLayout>
#include <QSlider>
#include <QSpinBox>
#include <QLabel>
#include <QTimeEdit>
#include <QTextEdit>
#include <QDate>
#include <QTime>
#include <QGroupBox>
#include "base.h"
#include "qdateconvertor.h"

class record : public QWidget
{
    Q_OBJECT
public:
    explicit record(QString u, QWidget *parent = 0);
    QStringList today;
    QDateConvertor date;

private:
    QString user;
    void createRecordWidget();
    QPushButton * record_button;
    QComboBox * action_type;
    QGridLayout * mainlayout;
    QSlider * rate;
    QTimeEdit * time;
    QTextEdit * description;

    QTime  currenttime;
    QSpinBox *year;
    QComboBox *month;
    QSpinBox * day;

    QSpinBox *hour;
    QSpinBox *min;

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
