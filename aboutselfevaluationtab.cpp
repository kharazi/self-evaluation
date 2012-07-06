#include "aboutselfevaluationtab.h"
#include <QDebug>
aboutSelfEvaluationTab::aboutSelfEvaluationTab(QWidget *parent) :
    QWidget(parent)
{
//    about =new QLabel(QString::fromUtf8("مزیت استفاده از نرم افزار به جای جدولهای دستی برای محاسبه نفس این است که می توان باگرفتن گزارش های هفتگی مشکلات عمده خودمان را در هفته ای که گذشت کشف کنیم! <br>"
//                     " <br>  گناهانی که بیشتر مرتکب می شوم کدام گناهان هستند؟ یا مثلاً در دو ماه اخیر چند بار غیبت کرده ام؟ بیشترین گناهان من در چه ساعاتی از شبانه روز بوده است؟"
//              "  ؛      مزیت دیگر استفاده از نرم افزار محاسبه نفس نسبت به روش دستی این است که نرم افزار بعد از ثبت هر گناه یک توصیه مربوط به ما انجام می دهد! مثلاً وقتی گناه غیبت را ثبت می کنیم برای ما حدیثی در مذمّت غیبت نمایش می دهد. نمایش حدیث و پند ها و توصیه های اخلاقی بزرگان پس از ثبت هر گناه باعث متنبه شدن ما می شود."));

    layout=new QFormLayout;
    mainlayout =new QGridLayout;

   next=new QPushButton();
   previous=new QPushButton();
    mainlayout->addWidget(previous,1,1,1,1);
    mainlayout->addWidget(next,1,2,1,1);


    next->setIcon(QIcon(":/images/next.png"));
    previous->setIcon(QIcon(":/images/previous.png"));
    title=new QLabel(QString::fromUtf8("نمودار تعداد عمل در هر هفته"));
    content=new QLabel(QString::fromUtf8("نمودار تعداد عمل در هر هفته"));

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
    content_index=1;
    get_content(1);

}
void aboutSelfEvaluationTab::get_content(int index){
    query.exec(QString("SELECT title,content FROM contents WHERE content_id=%1").arg(index));
        while (query.next()) {
            qDebug()<<query.value(0).toString();
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

  delete scroll;
  delete mainlayout;
}
void aboutSelfEvaluationTab::next_button_clicked(){
    if (content_index<9){
        content_index++;
        qDebug()<<content_index;
        if (content_index<10){
            get_content(content_index);
        }

    }




}

void aboutSelfEvaluationTab::previous_button_clicked(){
    if (content_index>=2){
        content_index--;
        qDebug()<<content_index;
        if (content_index>0){
            get_content(content_index);
        }

    }



}
