#ifndef HADITHOPTION_H
#define HADITHOPTION_H

#include <QWidget>
#include <QSqlQuery>
#include <QSqlError>
#include <QComboBox>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QGridLayout>
#include <QPushButton>
#include <QMessageBox>
class HadithOption : public QWidget
{
    Q_OBJECT
private:
    void CreateHadithOptionWidget();
public:
    explicit HadithOption(QWidget *parent = 0);
    QComboBox * action_type;
    QLineEdit * narrator;
    QTextEdit * hadith;
    QGridLayout * layout;
    QPushButton * record;

signals:

public slots:
    void record_button_clicked();


};

#endif // HADITHOPTION_H
