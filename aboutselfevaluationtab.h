#ifndef ABOUTSELFEVALUATIONTAB_H
#define ABOUTSELFEVALUATIONTAB_H

#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <QScrollArea>
#include <QFormLayout>
#include <QPushButton>
#include <QSqlQuery>
class aboutSelfEvaluationTab : public QWidget
{
    Q_OBJECT
public:
    explicit aboutSelfEvaluationTab(QWidget *parent = 0);
    ~aboutSelfEvaluationTab();

 private:
    QFormLayout *layout;
    QGridLayout *mainlayout;

    QLabel * content;
    QLabel * title;

    QPushButton * next;
    QPushButton * previous;
    QSqlQuery query;

    QScrollArea* scroll;

    int content_index;
    void get_content(int);
    
signals:

public slots:
    void next_button_clicked();
    void previous_button_clicked();

};

#endif // ABOUTSELFEVALUATIONTAB_H
