#include "hadithoption.h"
HadithOption::HadithOption(QWidget *parent) :
    QWidget(parent)
{
    CreateHadithOptionWidget();
}

HadithOption::~HadithOption()
{
  delete action_type;
  delete narrator;
  delete hadith;
  delete record;
  delete layout;
}

void HadithOption::CreateHadithOptionWidget(){
    layout =new QGridLayout;
    hadith =new QTextEdit(QString::fromUtf8("متن حدیث"));
    narrator =new QLineEdit (QString::fromUtf8("گوینده"));
    record = new QPushButton(QString::fromUtf8("افزودن"));
    connect(record,SIGNAL(clicked()),this,SLOT(record_button_clicked()));
    action_type =new QComboBox;

    QSqlQuery q("SELECT title FROM action_types");
    if (q.lastError().type()==0){
        while (q.next()) {
            action_type->addItem(q.value(0).toString());
        }
    }

    QLabel * action_type_label=new QLabel(QString::fromUtf8("موضوع"));
    layout->addWidget(action_type,0,0,1,1);
    layout->addWidget(action_type_label,0,1,1,1);
    layout->addWidget(narrator,1,0,1,2);
    layout->addWidget(hadith,2,0,1,2);
    layout->addWidget(record,3,0,1,2);

    this->setLayout(layout);
}
void HadithOption::record_button_clicked(){

    QSqlQuery query;
    int action_id;

    query.exec(QString("SELECT action_id FROM action_types WHERE title = '%1' ").arg(action_type->currentText()));
    while (query.next()){
      action_id = query.value(0).toInt();
    }
    query.prepare("INSERT INTO hadith (hadith_id,action_id,narrator,hadith_text) VALUES(?,?,?,?) ");
    query.addBindValue(QVariant(QVariant::Int));
    query.addBindValue(action_id);
    query.addBindValue(narrator->text());
    query.addBindValue(hadith->toPlainText());
    query.exec();

    if (query.lastError().type()==0){
        QMessageBox *error = new QMessageBox;
        error->setText(QString::fromUtf8("حدیث شما با موفقیت ذخیره شد."));
        error->setIcon(QMessageBox::Warning);
        error->setWindowTitle(QString::fromUtf8("ذخیره"));
        error->exec();
        narrator->setText(QString::fromUtf8("گوینده"));
        hadith->setText(QString::fromUtf8("متن حدیث"));

    }else{
        QMessageBox *error = new QMessageBox;
        error->setText(QString::fromUtf8("خطا در برقراری ارتباط با پایگاه داده ای ! لطفا مجددا تلاش کنید. "));
        error->setIcon(QMessageBox::Warning);
        error->setWindowTitle(QString::fromUtf8("خطا"));
        error->exec();
    }
}
