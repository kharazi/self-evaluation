#include "dashboard.h"

Dashboard::Dashboard(QString u, QWidget *parent) :
    QWidget(parent)
{
    user=u;
    CreateDashboardWidget();
    today= date.Today();
    get_date();
    get_hadith();
    get_data();

}
void Dashboard::CreateDashboardWidget(){

    mainlayout= new QVBoxLayout;
    DateLable =new QLabel;
    HadithLable=new QLabel(QString::fromUtf8("حدیث"));
    HadithLable->setMaximumWidth(700);
    mostLabel = new QLabel;
    QLabel * statusLabelTitle=new QLabel(QString::fromUtf8("<b>وضعیت من:</b>"));
    statusLable=new QLabel();
    re =new record(user);
    mainlayout->addWidget(DateLable,0,Qt::AlignCenter);
    mainlayout->addWidget(HadithLable);
    mainlayout->addWidget(statusLabelTitle);
    mainlayout->addWidget(statusLable,0,Qt::AlignRight);
    mainlayout->addWidget(mostLabel,0,Qt::AlignRight);
    mainlayout->addWidget(re);
    this->setLayout(mainlayout);

}

void Dashboard::get_hadith(){
    query.exec("SELECT hadith_text,narrator FROM hadith ORDER BY RANDOM() LIMIT 1");
    while (query.next()) {
        HadithLable->setText( query.value(1).toString()+":" +query.value(0).toString());
    }
}
void Dashboard::get_date(){
    QString Date;
    Date=QString::fromUtf8("امروز %4 %3 %2 سال %1 ").arg(today.at(0)).arg(today.at(3)).arg(today.at(2)).arg(today.at(4));
    DateLable->setText(Date);
}
void Dashboard::get_data(){
    //
    QString CountToday="0";
    query.exec(QString("SELECT COUNT(actions.id) FROM actions WHERE actions.date LIKE'%1-%2-%3' AND actions.username='%4'").arg(today.at(0)).arg(today.at(1)).arg(today.at(2)).arg(user));
    while (query.next()) {
        CountToday=query.value(0).toString();
    }
    //
    QString RateToday="0";
    query.exec(QString("SELECT SUM(actions.rate) FROM actions WHERE actions.date LIKE'%1-%2-%3' AND actions.username='%4'").arg(today.at(0)).arg(today.at(1)).arg(today.at(2)).arg(user));
    while (query.next()) {
        RateToday=query.value(0).toString();
    }
    //
    QString CountMonth="0";
    query.exec(QString("SELECT COUNT(actions.id) FROM actions WHERE actions.date LIKE'%1-%2-%'  AND actions.username='%3'").arg(today.at(0)).arg(today.at(1)).arg(user));
    while (query.next()) {
        CountMonth=query.value(0).toString();
    }
    //
    QString RateMonth="0";
    query.exec(QString("SELECT SUM(actions.rate) FROM actions WHERE actions.date LIKE'%1-%2-%' AND actions.username='%3'").arg(today.at(0)).arg(today.at(1)).arg(user));
    while (query.next()) {
        RateMonth=query.value(0).toString();
    }
    //
    QString CountYear="0";
    query.exec(QString("SELECT COUNT(actions.id) FROM actions WHERE actions.date LIKE'%1%' AND actions.username='%2'").arg(today.at(0)).arg(user));
    while (query.next()) {
        CountYear=query.value(0).toString();
    }
    //
    QString RateYear="0";
    query.exec(QString("SELECT SUM(actions.rate) FROM actions WHERE actions.date LIKE'%1%' AND actions.username='%2'").arg(today.at(0)).arg(user));
    while (query.next()) {
        RateYear=query.value(0).toString();
    }
    //
    QString Count="0";
    query.exec(QString("SELECT COUNT(actions.id) FROM actions WHERE actions.username='%1'").arg(user));
    while (query.next()) {
        Count=query.value(0).toString();
    }
    //
    QString Rate="0";
    query.exec(QString("SELECT SUM(actions.rate) FROM actions WHERE actions.username='%1'").arg(user));
    while (query.next()) {
        Rate=query.value(0).toString();
    }
    //
    QString CountWeek="0";
    query.exec(QString("SELECT COUNT(actions.id) FROM actions WHERE actions.username='%1' AND actions.date BETWEEN '%2' AND '%3'").arg(user).arg(date.firstdayofweek).arg(date.lastdayofweek));
    while (query.next()) {
        CountWeek=query.value(0).toString();
    }
    //
    QString RateWeek="0";
    query.exec(QString("SELECT SUM(actions.rate) FROM actions WHERE actions.username='%1' AND actions.date BETWEEN '%2' AND '%3'").arg(user).arg(date.firstdayofweek).arg(date.lastdayofweek));
    while (query.next()) {
        RateWeek=query.value(0).toString();
    }
    //in this month
    int max_action_id;
    query.exec(QString("SELECT action_id,COUNT(id) FROM actions WHERE actions.date LIKE'%1-%2-%' AND actions.username='%3' GROUP BY action_id ORDER BY COUNT(id) LIMIT 1 ").arg(today.at(0)).arg(today.at(1)).arg(user));
    while (query.next()) {
        max_action_id=query.value(0).toInt();
    }

    QString max_action_title;
    query.exec(QString("SELECT title FROM action_types WHERE action_id=%1").arg(max_action_id));
    while (query.next()) {
        max_action_title=query.value(0).toString();
    }
    //

    qDebug()<<"first day of week"<<date.FirstDayOfWeek.at(0);
    qDebug()<<"last day of week"<<date.LastDayOfWeek;
    qDebug()<<date.lastdayofweek;
    qDebug()<<date.firstdayofweek;

    mostLabel->setText(QString::fromUtf8("<table border='1'>"
                                         "<tr><td>%1 </td><td>پرتکرار ترین این ماه </td></tr>"
                                         "</table>").arg(max_action_title));
    statusLable->setText(QString::fromUtf8("<table border='1'>"
                                           "<tr><td><pre>   </pre></td>  <td><pre><b>امتیاز منفی</b></pre></td><td><pre>    </pre> </td><td><pre><b>تعداد </b></pre></td></tr>"

                                           "<tr><td><pre> %1</pre></td>  <td><pre>امروز</pre></td><td><pre>%2</pre> </td><td><pre>امروز</pre></td></tr>"
                                           "<tr><td><pre> %3</pre></td>  <td><pre>این هفته</pre></td><td><pre>%4</pre> </td><td><pre>این هفته</pre></td></tr>"
                                           "<tr><td><pre> %5</pre></td>  <td><pre>این ماه</pre></td><td><pre>%6</pre> </td><td><pre>این ماه</pre></td></tr>"
                                           "<tr><td><pre> %7</pre></td>  <td><pre>امسال</pre></td><td><pre>%8</pre> </td><td><pre>امسال</pre></td></tr>"
                                           "<tr><td><pre> %9</pre></td>  <td><pre>کل</pre></td><td><pre>%10</pre> </td><td><pre>تعداد کل</pre></td></tr>"
                                           "</table>").arg(RateToday).arg(CountToday).arg(RateWeek).arg(CountWeek).arg(RateMonth).arg(CountMonth).arg(RateYear).arg(CountYear).arg(Rate).arg(Count));
}
