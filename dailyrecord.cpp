#include "dailyrecord.h"

DailyRecord::DailyRecord(QString u, QWidget *parent) :
    QWidget(parent)
{
    actionsModel = new QSqlRelationalTableModel;

    actionsModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    actionsModel->setTable("actions");
    actionsModel->setRelation(1, QSqlRelation("action_types", "action_id", "title" ));
    actionsModel->setSort(0, Qt::DescendingOrder);
    actionsModel->setFilter(QString("username = '%1'").arg(u));
    actionsModel->select();
    actionsModel->setHeaderData(1, Qt::Horizontal, "Type");
    actionsModel->setHeaderData(4, Qt::Horizontal, "Date");
    actionsModel->setHeaderData(5, Qt::Horizontal, "Time");
    actionsModel->setHeaderData(6, Qt::Horizontal, "Rate");

    mapper = new QDataWidgetMapper;

    mainLayout = new QGridLayout;
    mainLayout->setOriginCorner(Qt::TopRightCorner);
    createPage();
}


void DailyRecord::createPage()
{
    QComboBox *typeEdit = new QComboBox;
    QTextEdit *descriptionEdit = new QTextEdit;
    QDateEdit *dateEdit = new QDateEdit;
    QTimeEdit *timeEdit = new QTimeEdit;
    QSlider *rateEdit = new QSlider(Qt::Horizontal);

    connect(actionsModel, SIGNAL(primeInsert(int, QSqlRecord&)), this, SLOT(initializeRow(int, QSqlRecord&)));

    mapper->setModel(actionsModel);
    mapper->addMapping(typeEdit, 1);
    mapper->addMapping(descriptionEdit, 3);
    mapper->addMapping(dateEdit, 4);
    mapper->addMapping(timeEdit, 5);
    mapper->addMapping(rateEdit, 6);
    mapper->toFirst();

    QPushButton *addRowButton = new QPushButton;
    QPushButton *removeRowButton = new QPushButton;
    addRowButton->setIcon(QIcon(":/images/add.png"));
    removeRowButton->setIcon(QIcon(":/images/remove.png"));
    connect(addRowButton, SIGNAL(clicked()), this, SLOT(addRow()));
    connect(removeRowButton, SIGNAL(clicked()), this, SLOT(removeRow()));

    table = new QTableView;
    table->setModel(actionsModel);
    table->setItemDelegate(new QSqlRelationalDelegate(table));
    table->setColumnHidden(0, true);
    table->setColumnHidden(2, true);
    table->setColumnHidden(3, true);

    table->verticalHeader()->hide();
    table->horizontalHeader()->setStretchLastSection(true);
    table->setSelectionMode(QAbstractItemView::SingleSelection);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->selectRow(0);
    connect(table->selectionModel(), SIGNAL(currentRowChanged(QModelIndex,QModelIndex)), mapper, SLOT(setCurrentModelIndex(QModelIndex)));

    QLabel *typeLabel = new QLabel("Type");
    QLabel *descriptionLabel = new QLabel("Description");
    QLabel *dateLabel = new QLabel("Date");
    QLabel *timeLabel = new QLabel("Time");
    QLabel *rateLabel = new QLabel("Rate");

    QPushButton *submitIt = new QPushButton("Submit It");
    connect(submitIt, SIGNAL(clicked()), actionsModel, SLOT(submitAll()));
    mainLayout->addWidget(typeLabel, 0, 0);
    mainLayout->addWidget(typeEdit, 0, 1);
    mainLayout->addWidget(descriptionLabel, 1, 0);
    mainLayout->addWidget(descriptionEdit, 1, 1);
    mainLayout->addWidget(dateLabel, 2, 0);
    mainLayout->addWidget(dateEdit, 2, 1);
    mainLayout->addWidget(timeLabel, 2, 2);
    mainLayout->addWidget(timeEdit, 2, 3);
    mainLayout->addWidget(rateLabel, 3, 0);
    mainLayout->addWidget(rateEdit, 3, 1);
    mainLayout->addWidget(addRowButton, 3, 2);
    mainLayout->addWidget(removeRowButton, 3, 3);
    mainLayout->addWidget(table, 4, 0, 4, 2);
    mainLayout->addWidget(submitIt, 4, 3);
    this->setLayout(mainLayout);

    connect(actionsModel, SIGNAL(rowsInserted(QModelIndex, int, int)), this, SLOT(selectFirstRow()));
}


void DailyRecord::addRow()
{
  actionsModel->insertRows(0, 1);
}


void DailyRecord::initializeRow(int row, QSqlRecord& record)
{

}


void DailyRecord::removeRow()
{
  actionsModel->removeRow(mapper->currentIndex());
  actionsModel->submitAll();
}


void DailyRecord::selectFirstRow()
{
  table->selectRow(0);
}
