#include "mainwidget.h"

MainWidget::MainWidget(QSqlDatabase d)
{
    db = d;
    createTrayIcon();
    connect(trayIcon, SIGNAL(messageClicked()), this, SLOT(messageClicked()));
    trayIcon->show();
    
    menu = new QListWidget;
    menu->setViewMode(QListView::IconMode);
    menu->setIconSize(QSize(96, 84));
    menu->setMovement(QListView::Static);
    menu->setMinimumHeight(400);
    menu->setMaximumWidth(128);
    menu->setSpacing(10);
    pagesWidget = new QStackedWidget;
    //
    //for adding page:
    //
//    pagesWidget->addWidget(new ConfigurationPage);
//    pagesWidget->addWidget(new UpdatePage);
//    pagesWidget->addWidget(new QueryPage);

    QPushButton *closeButton = new QPushButton(QString::fromUtf8("بستن"));
    connect(closeButton, SIGNAL(clicked()), this, SLOT(close()));

    createMenuIcons();
    menu->setCurrentRow(0);

    QHBoxLayout *horizontalLayout = new QHBoxLayout;
    horizontalLayout->setDirection(QBoxLayout::RightToLeft);
    horizontalLayout->addWidget(menu);
    horizontalLayout->addWidget(pagesWidget, 1);

    QHBoxLayout *buttonsLayout = new QHBoxLayout;
    buttonsLayout->setDirection(QBoxLayout::RightToLeft);
    buttonsLayout->addStretch(1);
    buttonsLayout->addWidget(closeButton);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(horizontalLayout);
    mainLayout->addStretch(1);
    mainLayout->addSpacing(12);
    mainLayout->addLayout(buttonsLayout);
    setLayout(mainLayout);
    this->resize(600,400);
    setWindowTitle(QString::fromUtf8("adel jon"));
}


// void MainWidget::authenticate()
// {
//   authentication = new Auth;
//   authentication->show();
//   connect(authentication, SIGNAL(authSuccessful()), this, SLOT(authSuccessful()));
//   connect(authentication, SIGNAL(authClosed()), this, SLOT(authClosed()));
// }


// void MainWidget::authSuccessful()
// {
//   createTrayIcon();
//   connect(trayIcon, SIGNAL(messageClicked()), this, SLOT(messageClicked()));
//   trayIcon->show();
//   authSuccess = true;
//   authentication->close();
//   show();
// }


// void MainWidget::authClosed()
// {
//   if (!authSuccess){ trayIcon = NULL; close(); }
// }


void MainWidget::createMenuIcons()
{
    //this function for adding icon to pages
    QListWidgetItem *configButton = new QListWidgetItem(menu);
    configButton->setIcon(QIcon(":/images/config.png"));
    configButton->setText(QString::fromUtf8("خرید"));
    configButton->setTextAlignment(Qt::AlignHCenter);
    configButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    QListWidgetItem *updateButton = new QListWidgetItem(menu);
    updateButton->setIcon(QIcon(":/images/update.png"));
    updateButton->setText(QString::fromUtf8("فروش"));
    updateButton->setTextAlignment(Qt::AlignHCenter);
    updateButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    QListWidgetItem *queryButton = new QListWidgetItem(menu);
    queryButton->setIcon(QIcon(":/images/query.png"));
    queryButton->setText(QString::fromUtf8("‍‍‍‍‍پشتیبانی"));
    queryButton->setTextAlignment(Qt::AlignHCenter);
    queryButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);


    connect(menu,
            SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)),
            this, SLOT(changePage(QListWidgetItem*,QListWidgetItem*)));
}


void MainWidget::changePage(QListWidgetItem *current, QListWidgetItem *previous)
{
    if (!current)
        current = previous;

    pagesWidget->setCurrentIndex(menu->row(current));
}


void MainWidget::closeEvent(QCloseEvent *event)
{
    if (!trayIcon) qApp->quit();
    else if (trayIcon->isVisible()) {
        hide();
        event->ignore();
    }
}


void MainWidget::showMessage(QString title,QString plaintext,int time=15)
{
//for setting messege icon and show a message
    //tabe ro intori taghir dadam ke se ta parametr begire: QString title,QString plaintext,int time=15
    //time modat zamaniye k pegham namayesh dade mishe.
    QSystemTrayIcon::MessageIcon icon = QSystemTrayIcon::MessageIcon(QSystemTrayIcon::Critical);//enum={Information,warning,Critical,noIcon}type icon az inja taghir bedim
    trayIcon->showMessage(title,plaintext, icon,
                          time * 1000);
}


void MainWidget::messageClicked()
{
    QMessageBox::information(0, tr("Systray"),
                             tr("Sorry, I already gave what help I could.\n"
                                "Maybe you should try asking a human?"));
}


void MainWidget::createTrayIcon()
{
    //system tray menu action
    minimizeAction = new QAction(tr("Mi&nimize"), this);
    connect(minimizeAction, SIGNAL(triggered()), this, SLOT(hide()));

    maximizeAction = new QAction(tr("Ma&ximize"), this);
    connect(maximizeAction, SIGNAL(triggered()), this, SLOT(showMaximized()));

    restoreAction = new QAction(QString::fromUtf8("نمایش برنامه"), this);
    connect(restoreAction, SIGNAL(triggered()), this, SLOT(showNormal()));

    quitAction = new QAction(QString::fromUtf8("خروج"), this);
    connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));

    //system tray menu
    trayIconMenu = new QMenu(this);
    trayIconMenu->addAction(minimizeAction);
    trayIconMenu->addAction(maximizeAction);
    trayIconMenu->addAction(restoreAction);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(quitAction);

    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setContextMenu(trayIconMenu);

    //setting system tray Icon
    QIcon icon= QIcon(":/images/bad.svg");
    trayIcon->setIcon(icon);
}
