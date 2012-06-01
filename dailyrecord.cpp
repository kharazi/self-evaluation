#include "dailyrecord.h"

DailyRecord::DailyRecord(QString u, QWidget *parent) :
    QWidget(parent)
{
    actionsModel = new QSqlRelationalTableModel;
    actionsModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    actionsModel->setTable("action_types");
    actionsModel->setSort(0, Qt::DescendingOrder);
    //    actionsModel->setFilter("");
    actionsModel->select();
    //    actionsModel->setRelation(1, QSqlRelation("action_types", "action_id", "title" ));
    mapper = new QDataWidgetMapper;

    mainLayout = new QGridLayout;
    createPage();
}


void DailyRecord::createPage()
{
    QSpinBox *mySpinBox = new QSpinBox;
    mySpinBox->setMaximum(99999999);
    QLineEdit *myLine = new QLineEdit;
    
    connect(actionsModel, SIGNAL(primeInsert(int, QSqlRecord&)), this, SLOT(initializeRow(int, QSqlRecord&)));

    mapper->setModel(actionsModel);
    mapper->addMapping(mySpinBox, 0);
    mapper->addMapping(myLine, 1);
    mapper->toFirst();
    // mapper->addMapping(QLineEdit, 2);
    // mapper->addMapping(QCalendarWidget, 3);
    // mapper->auddMapping(QSpinBox, 4);

    QPushButton *addRowButton = new QPushButton("Add");
    QPushButton *removeRowButton = new QPushButton("Remove");
    connect(addRowButton, SIGNAL(clicked()), this, SLOT(addRow()));
    connect(removeRowButton, SIGNAL(clicked()), this, SLOT(removeRow()));

    table = new QTableView;
    table->setModel(actionsModel);
    table->verticalHeader()->hide();
    table->horizontalHeader()->setStretchLastSection(true);
    table->setSelectionMode(QAbstractItemView::SingleSelection);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->selectRow(0);
    connect(table->selectionModel(), SIGNAL(currentRowChanged(QModelIndex,QModelIndex)), mapper, SLOT(setCurrentModelIndex(QModelIndex)));

    QPushButton *submitIt = new QPushButton("Submit It");
    connect(submitIt, SIGNAL(clicked()), actionsModel, SLOT(submitAll()));
    mainLayout->addWidget(submitIt, 1, 1);
    mainLayout->addWidget(mySpinBox, 0, 0);
    mainLayout->addWidget(myLine, 0, 1);
    mainLayout->addWidget(addRowButton, 2, 0);
    mainLayout->addWidget(removeRowButton, 2, 1);
    mainLayout->addWidget(table, 3, 0, 3, 2);
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
