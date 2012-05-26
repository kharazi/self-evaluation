#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include "dashboard.h"
#include <QSqlDatabase>
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

class MainWidget : public QWidget
{
    Q_OBJECT

public:
  //    MainWidget();
    MainWidget(QSqlDatabase d);
    QString* getUser();
    void setUser(QString u);
    
protected:
    void closeEvent(QCloseEvent *event);

private:
    void createTrayIcon();

    QSqlDatabase db;
    QString *user;

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
