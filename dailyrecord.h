#ifndef DAILYRECORD_H
#define DAILYRECORD_H

#include <QWidget>
#include <QGridLayout>
#include <QSqlRelationalTableModel>
#include <QSqlRecord>
#include <QSpinBox>
#include <QLineEdit>
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

private:
    void createPage();

    QGridLayout *mainLayout;
    QSqlRelationalTableModel *actionsModel;
    QDataWidgetMapper *mapper;
    QTableView *table;
signals:

public slots:
    void addRow();
    void initializeRow(int, QSqlRecord&);
    void removeRow();
    void selectFirstRow();
};

#endif // DAILYRECORD_H
