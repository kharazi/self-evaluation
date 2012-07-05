#ifndef OPTIONS_H
#define OPTIONS_H

#include <QSqlDatabase>
#include <QWidget>
#include <QGridLayout>
#include <QTabWidget>
#include <QListView>
#include <QPushButton>
#include <QIcon>
#include <QSqlTableModel>
#include <QSqlQuery>
#include <QVariant>
#include <QAbstractItemView>
#include <QModelIndex>
#include <QDebug>

class Options : public QWidget
{
    Q_OBJECT
public:
    explicit Options(QString u, QWidget *parent = 0);
    ~Options();
    void createTypesPage();

 private:
    QGridLayout *mainLayout;
    QTabWidget *tab;
    QListView *view;
    QSqlTableModel *typesModel;

signals:

public slots:
    void addType();
    void removeType();
};

#endif // OPTIONS_H
