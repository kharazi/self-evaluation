#ifndef MAINWIDGET_H
#define MAINWIDGET_H

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
    MainWidget(QString);
    ~MainWidget();
    QString getUser();

    QString user;
    
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
    void addPages();
    void CreateMainWidget();

    QListWidget *menu;
    QStackedWidget *pagesWidget;

    QHBoxLayout *horizontalLayout;
    QHBoxLayout *buttonsLayout;
    QVBoxLayout *mainLayout;


public slots:
    void changePage(QListWidgetItem *current, QListWidgetItem *previous);


};

#endif
