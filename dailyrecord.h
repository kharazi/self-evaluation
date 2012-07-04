#ifndef DAILYRECORD_H
#define DAILYRECORD_H

#include <QWidget>
#include <QGridLayout>
#include <QSqlRelationalTableModel>
#include <QSqlQuery>
#include <QSqlRelation>
#include <QSqlError>
#include <QSqlRelationalDelegate>
#include <QSqlRecord>
#include <QSqlField>
#include <QComboBox>
#include <QTextEdit>
#include <QDateEdit>
#include <QTimeEdit>
#include <QSlider>
#include <QIcon>
#include <QLabel>
#include <QPushButton>
#include <QDataWidgetMapper>
#include <QTableView>
#include <QHeaderView>
#include <QAbstractItemView>
#include <QModelIndex>
#include <QDebug>

class DailyRecord : public QWidget
{
    Q_OBJECT
public:
    explicit DailyRecord(QString u, QWidget *parent = 0);
    QString getUser();
private:
    void createPage();
    QString user;
    QGridLayout *mainLayout;
    QSqlRelationalTableModel *actionsModel;
    QDataWidgetMapper *mapper;
    QTableView *table;
signals:

public slots:
    void addRow();
    //    void initializeRow(int, QSqlRecord&);
    void removeRow();
    void selectFirstRow();
};

#endif // DAILYRECORD_H
