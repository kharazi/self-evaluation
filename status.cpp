#include "status.h"
#include <QDebug>
#include <algorithm>
Status::Status(QString u, QWidget *parent) :
    QWidget(parent)
{
    layout=new QGridLayout;
    this->setLayout(layout);

    qDebug()<<rand()%10;
//    for (int i=0;i<500;i++){
//    query.exec(QString("INSERT INTO actions(action_id, username, description, date,time, rate)"
//                       "VALUES(%1,'vahid','inam ye tozih','1391-%2-%3','%4:30','%5');").arg(rand()%14).arg(rand()%12).arg(rand()%30).arg(rand()%23).arg(rand()%100));

//    }
    //sum rate

    QDateConvertor date;
    QStringList today= date.Today();

          qDebug()<<today.at(0)<<"/"<<today.at(1)<<"/"<<today.at(2)<<"/"<<today.at(3)<<"/"<<today.at(4);

//          //naghes////////////////////////////
//         qDebug()<< query.exec(QString("SELECT actions.id FROM actions WHERE actions.username='vahid' AND actions.date=%1-%2-%3 ").arg(today.at(0)).arg(today.at(1)).arg(today.at(2)));
//              while (query.next()) {
//                  qDebug()<<"majmoe emtiyazat manfi in hafte:"<< query.value(0).toString();
//              }
//              ////////////////////////////////////////////////////////




    query.exec(QString("SELECT COUNT(actions.id) FROM actions WHERE actions.username='vahid'AND actions.date LIKE'%1-%2-%'").arg(today.at(0)).arg(today.at(1)));
    while (query.next()) {
        qDebug()<<"tedade in mah:"<< query.value(0).toString();
    }


    query.exec(QString("SELECT SUM(actions.rate) FROM actions WHERE actions.username='vahid'AND actions.date LIKE'%1-%2-%'").arg(today.at(0)).arg(today.at(1)));
    while (query.next()) {
        qDebug()<<"majmoe emtiyazat manfi in mah:"<< query.value(0).toString();
    }

    query.exec(QString("SELECT COUNT(actions.id) FROM actions WHERE actions.username='vahid' AND actions.date LIKE'%1%' ").arg(today.at(0)));
    while (query.next()) {
        qDebug()<<"tedade  emsal:"<< query.value(0).toString();
    }

    query.exec(QString("SELECT SUM(actions.rate) FROM actions WHERE actions.username='vahid' AND actions.date LIKE'%1%' ").arg(today.at(0)));
    while (query.next()) {
        qDebug()<<"majmoe emtiyazat manfi  emsal:"<< query.value(0).toString();
    }




    query.exec("SELECT SUM(actions.rate) FROM actions WHERE actions.username='vahid'");
    while (query.next()) {
        qDebug()<<"majmoe emtiyazat manfi:"<< query.value(0).toString();
    }

    qDebug()<<"tesad action 5:"<<get_count_of_action(5);
////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////koli
    query.exec("SELECT action_id,COUNT(id) FROM actions WHERE actions.username='vahid' GROUP BY action_id");
    QHash<int,int> Statistics;
    while (query.next()) {
        Statistics[ query.value(0).toInt()]= query.value(1).toInt();
    }
    QList<int>l;
    l=Statistics.values();
    qSort(l.begin(),l.end());
    qDebug()<<"bishtarin:"<<Statistics.key(l.last());


    //darsad giri sayer
    int sum=0;
    for (int i=0;i<Statistics.keys().length();i++){
        sum+=Statistics.value(i);
    }

    QHash<int,float> StatisticsPercent;
    for (int i=0;i<Statistics.keys().length();i++){
        StatisticsPercent[i]=(Statistics[i]*100.0)/sum;
    }
    qDebug()<<"darsade action 13:"<<StatisticsPercent[13];



    ////////////////////////////////////////////////////////////////////////emsal
    query.exec(QString("SELECT action_id,COUNT(id) FROM actions WHERE actions.date LIKE'%1%' GROUP BY action_id ").arg(today.at(0)));
    QHash<int,int> thisYearStatistics;
    while (query.next()) {
        thisYearStatistics[ query.value(0).toInt()]= query.value(1).toInt();
    }
    QList<int>year;
    l=thisYearStatistics.values();
    qSort(year.begin(),year.end());
    qDebug()<<"bishtarin:"<<thisYearStatistics.key(l.last());


    //darsad giri sayer
    sum=0;
    for (int i=0;i<thisYearStatistics.keys().length();i++){
        sum+=thisYearStatistics.value(i);
    }

    QHash<int,float> thisYearStatisticsPercent;
    for (int i=0;i<thisYearStatistics.keys().length();i++)
    {
        thisYearStatisticsPercent[i]=(thisYearStatistics[i]*100.0)/sum;
    }
    qDebug()<<"darsade action 13(emsal):"<<thisYearStatisticsPercent[13];

/////////////////////////////////////////////////////////////////in mah
    query.exec(QString("SELECT action_id,COUNT(id) FROM actions WHERE actions.date LIKE'%1-%2-%' AND actions.username='vahid' GROUP BY action_id ").arg(today.at(0)).arg(today.at(1)));
    QHash<int,int> thisMounthStatistics;
    while (query.next()) {
        thisMounthStatistics[ query.value(0).toInt()]= query.value(1).toInt();
    }
    QList<int>Mounth;
    l=thisMounthStatistics.values();
    qSort(Mounth.begin(),Mounth.end());
    qDebug()<<"bishtarin:"<<thisMounthStatistics.key(l.last());


    //darsad giri sayer
    sum=0;
    for (int i=0;i<thisMounthStatistics.keys().length();i++){
        sum+=thisMounthStatistics.value(i);
    }

    QHash<int,float> thisMounthStatisticsPercent;
    for (int i=0;i<thisMounthStatistics.keys().length();i++)
    {
        thisMounthStatisticsPercent[i]=(thisMounthStatistics[i]*100.0)/sum;
    }
    qDebug()<<"darsade action 13(inmah):"<<thisMounthStatisticsPercent[13];

/////////////////////////////////////////////////////////////////in





//////////////////////////////////////////////////////////////////
    for (int i=0;i<24;i++){
        query.exec(QString("SELECT COUNT(id) FROM actions WHERE actions.time LIKE '%1%' AND actions.username='vahid'").arg(i));

        while (query.next()) {
            qDebug()<<"tedad gonah dar saat "<<i<<"="<<query.value(0).toInt();
        }
    }

    for (int i=0;i<24;i++){
        query.exec(QString("SELECT COUNT(id) FROM actions WHERE actions.time LIKE '%1%' AND actions.date LIKE'%2%' AND actions.username='vahid'").arg(i).arg(today.at(0)));

        while (query.next()) {
            qDebug()<<"tedad gonah dar saat(emsal) "<<i<<"="<<query.value(0).toInt();
        }
    }

    for (int i=0;i<24;i++){
        query.exec(QString("SELECT COUNT(id) FROM actions WHERE actions.time LIKE '%1%' AND actions.date LIKE'%2-%3-%' AND actions.username='vahid'").arg(i).arg(today.at(0)).arg(today.at(1)));

        while (query.next()) {
            qDebug()<<"tedad gonah dar saat(inmah) "<<i<<"="<<query.value(0).toInt();
        }
    }


}
int Status::get_count_of_action(int action)
{
    //count of specific action
    query.exec(QString("SELECT COUNT(actions.id) FROM actions WHERE actions.username='vahid' AND actions.action_id=%1").arg(action));
    while (query.next()) {
        return (query.value(0).toInt());
    }
}

