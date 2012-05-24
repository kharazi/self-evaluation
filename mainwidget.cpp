#include <QtGui>

#include "mainwidget.h"

MainWidget::MainWidget()
{
    createIconGroupBox();
    createActions();
    createTrayIcon();

    connect(iconComboBox, SIGNAL(currentIndexChanged(int)),
            this, SLOT(setIcon(int)));
    connect(trayIcon, SIGNAL(messageClicked()), this, SLOT(messageClicked()));
    connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
            this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));

    iconComboBox->setCurrentIndex(1);
    trayIcon->show();

    contentsWidget = new QListWidget;
    contentsWidget->setViewMode(QListView::IconMode);
    contentsWidget->setIconSize(QSize(96, 84));
    contentsWidget->setMovement(QListView::Static);
    contentsWidget->setMinimumHeight(400);
    contentsWidget->setMaximumWidth(128);
    contentsWidget->setSpacing(10);
    pagesWidget = new QStackedWidget;
    //
    //for adding page:
    //
//    pagesWidget->addWidget(new ConfigurationPage);
//    pagesWidget->addWidget(new UpdatePage);
//    pagesWidget->addWidget(new QueryPage);

    QPushButton *closeButton = new QPushButton(QString::fromUtf8("بستن"));

    createIcons();
    contentsWidget->setCurrentRow(0);

    connect(closeButton, SIGNAL(clicked()), this, SLOT(close()));

    QHBoxLayout *horizontalLayout = new QHBoxLayout;
    horizontalLayout->addWidget(contentsWidget);
    horizontalLayout->addWidget(pagesWidget, 1);

    QHBoxLayout *buttonsLayout = new QHBoxLayout;
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


void MainWidget::createIcons()
{
    //this function for adding icon to pages
    QListWidgetItem *configButton = new QListWidgetItem(contentsWidget);
    configButton->setIcon(QIcon(":/images/config.png"));
    configButton->setText(QString::fromUtf8("خرید"));
    configButton->setTextAlignment(Qt::AlignHCenter);
    configButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    QListWidgetItem *updateButton = new QListWidgetItem(contentsWidget);
    updateButton->setIcon(QIcon(":/images/update.png"));
    updateButton->setText(QString::fromUtf8("فروش"));
    updateButton->setTextAlignment(Qt::AlignHCenter);
    updateButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    QListWidgetItem *queryButton = new QListWidgetItem(contentsWidget);
    queryButton->setIcon(QIcon(":/images/query.png"));
    queryButton->setText(QString::fromUtf8("‍‍‍‍‍پشتیبانی"));
    queryButton->setTextAlignment(Qt::AlignHCenter);
    queryButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);


    connect(contentsWidget,
            SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)),
            this, SLOT(changePage(QListWidgetItem*,QListWidgetItem*)));
}

void MainWidget::changePage(QListWidgetItem *current, QListWidgetItem *previous)
{
    if (!current)
        current = previous;

    pagesWidget->setCurrentIndex(contentsWidget->row(current));
}


void MainWidget::setVisible(bool visible)
{
    QWidget::setVisible(visible);
}


void MainWidget::closeEvent(QCloseEvent *event)
{
    if (trayIcon->isVisible()) {
        hide();
        event->ignore();
    }
}



void MainWidget::setIcon(int index)
{
//seting system tray Icon
    QIcon icon= QIcon(":/images/bad.svg");//inja icon o vared konim
    trayIcon->setIcon(icon);

}




void MainWidget::iconActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason) {
    case QSystemTrayIcon::Trigger:
        qDebug()<<"QSystemTrayIcon::Trigger";

        break;
    case QSystemTrayIcon::MiddleClick:
        showMessage("click","middleclick",15);
        break;
    default:
        ;
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


void MainWidget::createIconGroupBox()
{
    iconGroupBox = new QGroupBox(tr("Tray Icon"));
    iconComboBox = new QComboBox;
    iconComboBox->addItem(QIcon(":/images/bad.svg"), tr("bad"));
}





void MainWidget::createActions()
{
    //system tray menu action
    //....w QAction(tr("Mi&nimize"), this)....     you can using from &
    minimizeAction = new QAction(tr("Mi&nimize"), this);
    connect(minimizeAction, SIGNAL(triggered()), this, SLOT(hide()));

    maximizeAction = new QAction(tr("Ma&ximize"), this);
    connect(maximizeAction, SIGNAL(triggered()), this, SLOT(showMaximized()));

    restoreAction = new QAction(QString::fromUtf8("نمایش برنامه"), this);
    connect(restoreAction, SIGNAL(triggered()), this, SLOT(showNormal()));

    quitAction = new QAction(QString::fromUtf8("خروج"), this);
    connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
}


void MainWidget::createTrayIcon()
{
    //system tray menu
    trayIconMenu = new QMenu(this);
    trayIconMenu->addAction(minimizeAction);
    trayIconMenu->addAction(maximizeAction);
    trayIconMenu->addAction(restoreAction);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(quitAction);

    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setContextMenu(trayIconMenu);
}
