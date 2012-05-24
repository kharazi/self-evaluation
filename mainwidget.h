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

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget();

protected:
    void closeEvent(QCloseEvent *event);

private:
    void createTrayIcon();

<<<<<<< HEAD
    //for pages:
    void createIcons();
    //


    //for system tray
    QGroupBox *iconGroupBox;
    QComboBox *iconComboBox;

=======
>>>>>>> f08816ca44a146cc174fd145ce901928ccc1023f
    QAction *minimizeAction;
    QAction *maximizeAction;
    QAction *restoreAction;
    QAction *quitAction;

    QSystemTrayIcon *trayIcon;
    QMenu *trayIconMenu;
    //for system tray

<<<<<<< HEAD
    //for pages:
    QListWidget *contentsWidget;
    QStackedWidget *pagesWidget;
    //
=======
    void createMenuIcons();

    QListWidget *menu;
    QStackedWidget *pagesWidget;

>>>>>>> f08816ca44a146cc174fd145ce901928ccc1023f

public slots:
    void changePage(QListWidgetItem *current, QListWidgetItem *previous);

<<<<<<< HEAD



=======
private slots:
    void showMessage(QString title,QString planetext,int time);
    void messageClicked();
>>>>>>> f08816ca44a146cc174fd145ce901928ccc1023f

};

#endif
