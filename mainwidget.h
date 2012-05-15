#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QtGui/QWidget>
#include <QGridLayout>
#include <QLabel>
class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = 0);
    ~MainWidget();
    QLabel * lable;
    QGridLayout * layout ;

};

#endif // MAINWIDGET_H
