#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QSystemTrayIcon>
#include <QWidget>
#include <QGridLayout>

QT_BEGIN_NAMESPACE
class QgetAction;
class QComboBox;
class QGroupBox;
class QListWidget;
class QListWidgetItem;
class QStackedWidget;
class QMenu;
class QPushButton;
QT_END_NAMESPACE



class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget();

    void setVisible(bool visible);

protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void setIcon(int index);
    void iconActivated(QSystemTrayIcon::ActivationReason reason);
    void showMessage(QString title,QString planetext,int time);
    void messageClicked();

private:
    void createIconGroupBox();
    void createMessageGroupBox();
    void createActions();
    void createTrayIcon();

    QGroupBox *iconGroupBox;
    QComboBox *iconComboBox;

    QAction *minimizeAction;
    QAction *maximizeAction;
    QAction *restoreAction;
    QAction *quitAction;

    QSystemTrayIcon *trayIcon;
    QMenu *trayIconMenu;



public slots:
    void changePage(QListWidgetItem *current, QListWidgetItem *previous);

private:
    void createIcons();

    QListWidget *contentsWidget;
    QStackedWidget *pagesWidget;



};
//! [0]

#endif
