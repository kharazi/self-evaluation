#include "mainwidget.h"

#include "dashboard.h"
#include "about.h"
#include "status.h"
#include "options.h"
#include "dailyrecord.h"

MainWidget::MainWidget(QString u)
{
    user = u;
    createTrayIcon();
    connect(trayIcon, SIGNAL(messageClicked()), this, SLOT(messageClicked()));
    trayIcon->show();
    
    CreateMainWidget();
    addPages();
    createMenuIcons();

    horizontalLayout = new QHBoxLayout;
    horizontalLayout->setDirection(QBoxLayout::RightToLeft);
    horizontalLayout->addWidget(menu);
    horizontalLayout->addWidget(pagesWidget, 1);

    buttonsLayout = new QHBoxLayout;
    buttonsLayout->setDirection(QBoxLayout::RightToLeft);
    buttonsLayout->addStretch(1);

    mainLayout = new QVBoxLayout;
    mainLayout->addLayout(horizontalLayout);
    mainLayout->addStretch(1);
    mainLayout->addSpacing(12);
    mainLayout->addLayout(buttonsLayout);
    setLayout(mainLayout);

}

MainWidget::~MainWidget()
{
  delete minimizeAction;
  delete maximizeAction;
  delete restoreAction;
  delete quitAction;
  delete trayIcon;
  delete trayIconMenu;
  delete menu;
  delete pagesWidget;
  delete horizontalLayout;
  delete buttonsLayout;
  delete mainLayout;
}

void MainWidget::addPages(){
    //for adding page:

    pagesWidget = new QStackedWidget;
    pagesWidget->addWidget(new Dashboard(getUser()));
    pagesWidget->addWidget(new Status(getUser()));
    pagesWidget->addWidget(new DailyRecord(getUser()));
    pagesWidget->addWidget(new Options(getUser()));
    pagesWidget->addWidget(new About(getUser()));

}

void MainWidget::createMenuIcons()
{
    //this function for adding icon to pages
    QListWidgetItem *configButton = new QListWidgetItem(menu);
    configButton->setIcon(QIcon(":/images/Dashboard.png"));
    configButton->setText(QString::fromUtf8("پیشخوان"));
    configButton->setTextAlignment(Qt::AlignHCenter);
    configButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    QListWidgetItem *statusButton = new QListWidgetItem(menu);
    statusButton->setIcon(QIcon(":/images/Status.png"));
    statusButton->setText(QString::fromUtf8("کارنامه"));
    statusButton->setTextAlignment(Qt::AlignHCenter);
    statusButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    QListWidgetItem *dailyRecordButton = new QListWidgetItem(menu);
    dailyRecordButton->setIcon(QIcon(":/images/DailyRecord.png"));
    dailyRecordButton->setText(QString::fromUtf8("ثبت روزانه"));
    dailyRecordButton->setTextAlignment(Qt::AlignHCenter);
    dailyRecordButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    QListWidgetItem *optionButton = new QListWidgetItem(menu);
    optionButton->setIcon(QIcon(":/images/Setting.png"));
    optionButton->setText(QString::fromUtf8("‍‍‍‍‍تنظیمات"));
    optionButton->setTextAlignment(Qt::AlignHCenter);
    optionButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);


    QListWidgetItem *aboutButton = new QListWidgetItem(menu);
    aboutButton->setIcon(QIcon(":/images/About.png"));
    aboutButton->setText(QString::fromUtf8("درباره"));
    aboutButton->setTextAlignment(Qt::AlignHCenter);
    aboutButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    connect(menu,
            SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)),
            this, SLOT(changePage(QListWidgetItem*,QListWidgetItem*)));

}

void MainWidget::CreateMainWidget(){
    menu = new QListWidget;
    menu->setViewMode(QListView::IconMode);
    menu->setIconSize(QSize(75, 60));
    menu->setMovement(QListView::Static);
    menu->setMinimumHeight(500);
    menu->setMaximumWidth(100);
    menu->setMinimumWidth(100);
    menu->setSpacing(13);
    menu->setCurrentRow(0);

    this->resize(840,400);
    this->setWindowOpacity(0.97);
    setWindowTitle(QString::fromUtf8("سامانه محاسبه ی نفس"));
    QPalette palette;
    palette.setBrush(this->backgroundRole(), QBrush(QImage(":/images/backg.jpg")));
    this->setPalette(palette);


}


QString MainWidget::getUser() { return user; }


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

void MainWidget::createTrayIcon()
{
    //system tray menu action
    minimizeAction = new QAction(QString::fromUtf8("کمینه"), this);
    connect(minimizeAction, SIGNAL(triggered()), this, SLOT(hide()));

    maximizeAction = new QAction(QString::fromUtf8("تمام صفحه"), this);
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
    QIcon icon= QIcon(":/images/icon3.png");
    trayIcon->setIcon(icon);
    //setting windows Icon
    this->setWindowIcon(icon);

}
