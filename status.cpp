#include "status.h"
#include <QDebug>
#include <algorithm>
#include "dchart_percent_of_action.h"
#include "dpchart_percent_of_action.h"
#include "histogrammchart_day_of_month.h"
#include "histogrammchart_hour_of_day.h"
#include "histogrammchart_hour_of_day_monthly.h"
#include "histogrammchart_weekly.h"
#include "aboutcharts.h"



Status::Status(QString u, QWidget *parent) :
    QWidget(parent)
{
    user =u;

    CreateStatusWidget();

    //sum rate

    QDateConvertor date;
    QStringList today= date.Today();

//   query.exec(QString("SELECT COUNT(actions.id) FROM actions WHERE actions.username='vahid'AND actions.date LIKE'%1-%2-%3'").arg(today.at(0)).arg(today.at(1)).arg(today.at(2)));
//          while (query.next()) {
//          }

//    query.exec(QString("SELECT COUNT(actions.id) FROM actions WHERE actions.username='vahid'AND actions.date LIKE'%1-%2-%'").arg(today.at(0)).arg(today.at(1)));
//    while (query.next()) {
//    }

//    query.exec(QString("SELECT SUM(actions.rate) FROM actions WHERE actions.username='vahid'AND actions.date LIKE'%1-%2-%'").arg(today.at(0)).arg(today.at(1)));
//    while (query.next()) {
//    }

//    query.exec(QString("SELECT COUNT(actions.id) FROM actions WHERE actions.username='vahid' AND actions.date LIKE'%1%' ").arg(today.at(0)));
//    while (query.next()) {
//    }

//    query.exec(QString("SELECT SUM(actions.rate) FROM actions WHERE actions.username='vahid' AND actions.date LIKE'%1%' ").arg(today.at(0)));
//    while (query.next()) {
//    }

//    query.exec("SELECT SUM(actions.rate) FROM actions WHERE actions.username='vahid'");
//    while (query.next()) {
//    }

////////////////////////////////////////////////////////////////////////////////////koli
//    query.exec("SELECT action_id,COUNT(id) FROM actions WHERE actions.username='vahid' GROUP BY action_id");
//    QHash<int,int> Statistics;
//    while (query.next()) {
//        Statistics[ query.value(0).toInt()]= query.value(1).toInt();
//    }
//    QList<int>l;
//    l=Statistics.values();
//    qSort(l.begin(),l.end());

//    //darsad giri sayer
//    int sum=0;
//    for (int i=0;i<Statistics.keys().length();i++){
//        sum+=Statistics.value(i);
//    }

//    QHash<int,float> StatisticsPercent;
//    for (int i=0;i<Statistics.keys().length();i++){
//        StatisticsPercent[i]=(Statistics[i]*100.0)/sum;
//    }

//    ////////////////////////////////////////////////////////////////////////emsal
//    query.exec(QString("SELECT action_id,COUNT(id) FROM actions WHERE actions.date LIKE'%1%' GROUP BY action_id ").arg(today.at(0)));
//    QHash<int,int> thisYearStatistics;
//    while (query.next()) {
//        thisYearStatistics[ query.value(0).toInt()]= query.value(1).toInt();
//    }
//    QList<int>year;
//    l=thisYearStatistics.values();
//    qSort(year.begin(),year.end());

//    //darsad giri sayer
//    sum=0;
//    for (int i=0;i<thisYearStatistics.keys().length();i++){
//        sum+=thisYearStatistics.value(i);
//    }

//    QHash<int,float> thisYearStatisticsPercent;
//    for (int i=0;i<thisYearStatistics.keys().length();i++)
//    {
//        thisYearStatisticsPercent[i]=(thisYearStatistics[i]*100.0)/sum;
//    }

///////////////////////////////////////////////////////////////////in mah
//    query.exec(QString("SELECT action_id,COUNT(id) FROM actions WHERE actions.date LIKE'%1-%2-%' AND actions.username='vahid' GROUP BY action_id ").arg(today.at(0)).arg(today.at(1)));
//    QHash<int,int> thisMounthStatistics;
//    while (query.next()) {
//        thisMounthStatistics[ query.value(0).toInt()]= query.value(1).toInt();
//    }
//    QList<int>Mounth;
//    l=thisMounthStatistics.values();
//    qSort(Mounth.begin(),Mounth.end());

//    //darsad giri sayer
//    sum=0;
//    for (int i=0;i<thisMounthStatistics.keys().length();i++){
//        sum+=thisMounthStatistics.value(i);
//    }

//    QHash<int,float> thisMounthStatisticsPercent;
//    for (int i=0;i<thisMounthStatistics.keys().length();i++)
//    {
//        thisMounthStatisticsPercent[i]=(thisMounthStatistics[i]*100.0)/sum;
//    }

///////////////////////////////////////////////////////////////////in





////////////////////////////////////////////////////////////////////
//    for (int i=0;i<24;i++){
//        query.exec(QString("SELECT COUNT(id) FROM actions WHERE actions.time LIKE '%1%' AND actions.username='vahid'").arg(i));

//        while (query.next()) {
//        }
//    }

//    for (int i=0;i<24;i++){
//        query.exec(QString("SELECT COUNT(id) FROM actions WHERE actions.time LIKE '%1%' AND actions.date LIKE'%2%' AND actions.username='vahid'").arg(i).arg(today.at(0)));

//        while (query.next()) {
//        }
//    }

//    for (int i=0;i<24;i++){
//        query.exec(QString("SELECT COUNT(id) FROM actions WHERE actions.time LIKE '%1%' AND actions.date LIKE'%2-%3-%' AND actions.username='vahid'").arg(i).arg(today.at(0)).arg(today.at(1)));

//        while (query.next()) {
//        }
//    }


}

Status::~Status()
{
  delete year;
  delete month;
  delete tab;
  delete layout;
}

int Status::get_count_of_action(int action)
{
    //count of specific action
    query.exec(QString("SELECT COUNT(actions.id) FROM actions WHERE actions.username='vahid' AND actions.action_id=%1").arg(action));
    while (query.next()) {
        return (query.value(0).toInt());
    }
}

void Status::CreateStatusWidget(){

    tab =new QTabWidget;
    tab->addTab(new AboutCharts,QString::fromUtf8("راهنما"));

    tab->addTab(new HistogrammChart_Month_t_Total(user),QString::fromUtf8("نمودار"));
    tab->addTab(new HistogrammChart_Month_t_Total_inAction(user),QString::fromUtf8("نمودار"));
    tab->addTab(new DChart_percent_of_action(user),QString::fromUtf8("نمودار"));
    tab->addTab(new HistogrammChart_Day_of_Month(user),QString::fromUtf8("نمودار"));
    tab->addTab(new HistogrammChart_Hour_Of_Day(user),QString::fromUtf8("نمودار"));
    tab->addTab(new HistogrammChart_Hour_Of_Day_monthly(user),QString::fromUtf8("نمودار"));
    tab->addTab(new HistogrammChart_weekly(user),QString::fromUtf8("نمودار"));

    layout = new QGridLayout;
    layout->addWidget(tab);

    this->setLayout(layout);
}

void Status::draw_chart_button_clicked(){




}
