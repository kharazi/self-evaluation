#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QtGui/QWidget>
#include <QGridLayout>
#include <QLabel>
#include <QListWidgetItem>
#include <QPushButton>
#include <QHBoxLayout>
#include <QStackedWidget>
class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = 0);
    ~MainWidget();
    QLabel * lable;
    QGridLayout * layout ;


public slots:
    void changePage(QListWidgetItem *current, QListWidgetItem *previous);

private:
    void createIcons();

    QListWidget *contentsWidget;
    QStackedWidget *pagesWidget;
};

#endif // MAINWIDGET_H
