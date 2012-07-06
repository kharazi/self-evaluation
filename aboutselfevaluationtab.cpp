#include "aboutselfevaluationtab.h"
aboutSelfEvaluationTab::aboutSelfEvaluationTab(QWidget *parent) :
    QWidget(parent)
{
    create_widget();
    content_index=1;
    get_content(1);

}
void aboutSelfEvaluationTab::create_widget(){

    layout=new QFormLayout;
    mainlayout =new QGridLayout;

    next=new QPushButton();
    previous=new QPushButton();
    mainlayout->addWidget(previous,1,1,1,1);
    mainlayout->addWidget(next,1,2,1,1);

    next->setIcon(QIcon(":/images/next.png"));
    previous->setIcon(QIcon(":/images/previous.png"));
    title=new QLabel;
    content=new QLabel;

    title->setWordWrap(true);
    title->resize(title->minimumSize());

    content->setWordWrap(true);
    content->resize(content->minimumSize());

    connect(next,SIGNAL(clicked()),this,SLOT(next_button_clicked()));
    connect(previous,SIGNAL(clicked()),this,SLOT(previous_button_clicked()));
    this->setLayout(layout);

    layout->addWidget(title);
    layout->addWidget(content);
    layout->addRow(mainlayout);

}

void aboutSelfEvaluationTab::get_content(int index){

    query.exec(QString("SELECT title,content FROM contents WHERE content_id=%1").arg(index));
        while (query.next()) {
            title->setText(query.value(0).toString());
            content->setText(query.value(1).toString());
        }

    if (content_index==1){
        previous->setEnabled(false);
    }else{
        previous->setEnabled(true);
    }
    if (content_index==9){
        next->setEnabled(false);
    }else{
        next->setEnabled(true);
    }
}

aboutSelfEvaluationTab::~aboutSelfEvaluationTab()
{
  delete next;
  delete previous;
  delete layout;
  delete title;
  delete content;
  delete mainlayout;
}

void aboutSelfEvaluationTab::next_button_clicked(){
    if (content_index<9){
        content_index++;
        if (content_index<10){
            get_content(content_index);
        }
    }
}

void aboutSelfEvaluationTab::previous_button_clicked(){
    if (content_index>=2){
        content_index--;
        if (content_index>0){
            get_content(content_index);
        }
    }
}
