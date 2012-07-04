#include "options.h"
#include "useroption.h"
#include "hadithoption.h"
Options::Options(QString u, QWidget *parent) :
    QWidget(parent)
{
    mainLayout=new QGridLayout;
    tab =new QTabWidget;
    tab->addTab(new UserOption,QString::fromUtf8("تنظیمات کاربری"));
    tab->addTab(new HadithOption,QString::fromUtf8("افزودن حدیث"));
    tab->addTab(new QWidget, "Types");
    mainLayout->addWidget(tab);
    this->setLayout(mainLayout);
    createTypesPage();
}

void Options::createTypesPage()
{
  //  QSqlDatabase secondDb = QSqlDatabase::addDatabase("QSQLITE", "secondDb");
  //  secondDb.setDatabaseName("selfeval.db");


  QVBoxLayout *vLayout = new QVBoxLayout;
  QHBoxLayout *hLayout = new QHBoxLayout;
  view = new QListView;
  typesModel = new QSqlTableModel;
  typesModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
  //  connect(typesModel, SIGNAL(rowsInserted(QTypesModelIndex, int, int)), this, SLOT(selectFirstRow()));
  typesModel->setTable("action_types");
  //  typesModel->filter();
  typesModel->setSort(0, Qt::DescendingOrder);
  typesModel->select();

  view->setModel(typesModel);
  view->setModelColumn(1);
  view->setMovement(QListView::Static);
  view->setResizeMode(QListView::Fixed);
  view->setSelectionMode(QAbstractItemView::SingleSelection);

  QPushButton *submitButton = new QPushButton("Submit");
  QPushButton *addButton = new QPushButton;
  QPushButton *removeButton = new QPushButton;
  addButton->setIcon(QIcon(":/images/add.png"));
  removeButton->setIcon(QIcon(":/images/remove.png"));
  connect(submitButton, SIGNAL(clicked()), typesModel, SLOT(submitAll()));
  connect(addButton, SIGNAL(clicked()), this, SLOT(addType()));
  connect(removeButton, SIGNAL(clicked()), this, SLOT(removeType()));
  hLayout->addWidget(submitButton);
  hLayout->addWidget(removeButton);
  hLayout->addWidget(addButton);
  hLayout->insertSpacing(1, 500);

  vLayout->addLayout(hLayout);
  vLayout->addWidget(view);

  tab->widget(2)->setLayout(vLayout);
  		    
}

void Options::addType()
{
  QSqlQuery query;
  query.prepare("INSERT INTO action_types (action_id, title) VALUES (?, ?) ");
  query.addBindValue(QVariant(QVariant::Int));
  query.addBindValue("");
  query.exec();
  typesModel->submitAll();
}

void Options::removeType()
{
  QModelIndex index = view->selectionModel()->currentIndex();
  typesModel->removeRow(index.row());
  typesModel->submitAll();
}

void Options::selectFirstRow()
{
  //  view->selectRow(0);
}
