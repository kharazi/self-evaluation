#include "aboutselfevaluationtab.h"

aboutSelfEvaluationTab::aboutSelfEvaluationTab(QWidget *parent) :
    QWidget(parent)
{
    about =new QLabel(QString::fromUtf8("مزیت استفاده از نرم افزار به جای جدولهای دستی برای محاسبه نفس این است که می توان باگرفتن گزارش های هفتگی مشکلات عمده خودمان را در هفته ای که گذشت کشف کنیم! <br>"
                     " <br>  گناهانی که بیشتر مرتکب می شوم کدام گناهان هستند؟ یا مثلاً در دو ماه اخیر چند بار غیبت کرده ام؟ بیشترین گناهان من در چه ساعاتی از شبانه روز بوده است؟"
              "  ؛      مزیت دیگر استفاده از نرم افزار محاسبه نفس نسبت به روش دستی این است که نرم افزار بعد از ثبت هر گناه یک توصیه مربوط به ما انجام می دهد! مثلاً وقتی گناه غیبت را ثبت می کنیم برای ما حدیثی در مذمّت غیبت نمایش می دهد. نمایش حدیث و پند ها و توصیه های اخلاقی بزرگان پس از ثبت هر گناه باعث متنبه شدن ما می شود."));
    mainlayout =new QGridLayout;
    about->setWordWrap(true);
   about->resize(600,400);
//    scroll=new QScrollArea;
//    scroll->setWidget(about);
    mainlayout->addWidget(about);
    this->setLayout(mainlayout);

}
