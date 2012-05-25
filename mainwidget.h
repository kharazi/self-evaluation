#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QSystemTrayIcon>
#include <QWidget>
#include <QGridLayout>
#include <QDebug>
#include <QComboBox>
#include <QGroupBox>
#include <QListWidget>
#include <QListWidgetItem>
#include <QStackedWidget>
#include <QMenu>
#include <QPushButton>
#include <QMessageBox>
#include <QCloseEvent>
#include <QApplication>
#include "recording.h"
class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget();

protected:
    void closeEvent(QCloseEvent *event);

private:
    void createTrayIcon();


    QAction *minimizeAction;
    QAction *maximizeAction;
    QAction *restoreAction;
    QAction *quitAction;

    QSystemTrayIcon *trayIcon;
    QMenu *trayIconMenu;

    void createMenuIcons();

    QListWidget *menu;
    QStackedWidget *pagesWidget;


public slots:
    void changePage(QListWidgetItem *current, QListWidgetItem *previous);


private slots:
    void showMessage(QString title,QString planetext,int time);
    void messageClicked();


};

#endif
