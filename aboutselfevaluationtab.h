#ifndef ABOUTSELFEVALUATIONTAB_H
#define ABOUTSELFEVALUATIONTAB_H

#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <QScrollArea>

class aboutSelfEvaluationTab : public QWidget
{
    Q_OBJECT
public:
    explicit aboutSelfEvaluationTab(QWidget *parent = 0);
    QGridLayout *mainlayout;
    QLabel * about;
    QScrollArea* scroll;

signals:

public slots:

};

#endif // ABOUTSELFEVALUATIONTAB_H
