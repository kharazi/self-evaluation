#include "dchart_percent_of_action_yearly.h"

DChart_percent_of_action_yearly::DChart_percent_of_action_yearly(QString u,QWidget *parent) :
    QWidget(parent)
{
    user=u;
    title=new QLabel(QString::fromUtf8("نمودار دایره ای درصد گناهان مختلف در یک سال  "));
    QFormLayout *layout = new QFormLayout;
    layout->addWidget(title);
    this->setLayout(layout);

    year= new QSpinBox;
    year->setMaximum(today.at(0).toInt());
    year->setMinimum(1390);
    year->setValue(today.at(0).toInt());

    draw= new QPushButton(QString::fromUtf8("رسم"));
    layout->addRow(title);
    connect(draw,SIGNAL(clicked()),this,SLOT(draw_cliked()));

    today=date.Today();
    get_data();
}


void DChart_percent_of_action_yearly::get_data(){
  query.exec(QString("SELECT action_id,COUNT(id) FROM actions WHERE actions.username='%1' GROUP BY action_id").arg(user));
  QHash<int,int> Statistics;
  while (query.next()) {
      Statistics[ query.value(0).toInt()]= query.value(1).toInt();
      qDebug()<<"Statistics"<<query.value(0).toInt()<<"00"<<query.value(1).toInt();
  }

//    QList<int>l;
//    l=Statistics.values();
//    qSort(l.begin(),l.end());
//    qDebug()<<"bishtarin:"<<Statistics.key(l.last());


  //darsad giri sayer
  int sum=0;
  for (int i=0;i<Statistics.keys().length();i++){
      qDebug()<<i;
      sum+=Statistics.value(i);
  }


  for (int i=0;i<Statistics.keys().length();i++){
      StatisticsPercent[i]=(Statistics[i]*100.0)/sum;

//         qDebug()<<"percent"<<i<< 0000 <<(Statistics[i]*100.0)/sum;
  }

  for (int i=1;i<=Statistics.keys().length();i++){
      query.exec(QString("SELECT title FROM action_types WHERE action_id =%1").arg(i));
       while (query.next()) {
           action_type[i]=query.value(0).toString();

       }
       qDebug()<<"to roh qt"<<i<<action_type[i];


  }
//    qDebug()<<"darsade action 13:"<<StatisticsPercent[13];

//    qDebug()<<"keys"<< percent.keys().length();
//    qDebug()<<"values"<<percent.values();

}
void DChart_percent_of_action_yearly::draw_clicked(){
    get_data();
    this->update();


}

void DChart_percent_of_action_yearly::paintEvent(QPaintEvent *e){
      get_data();
      QWidget::paintEvent(e);
      QPainter painter;
      QFont font;
      painter.begin(this);
      Nightcharts PieChart;
      PieChart.setType(Nightcharts::Dpie);//{Histogramm,Pie,DPie};
      PieChart.setLegendType(Nightcharts::Round);//{VRound,Vertical}
      PieChart.setCords(210,170,this->width()/2.5,this->height()/2.5);
      for (int i=0;i<StatisticsPercent.keys().length();i++){
          qDebug()<<"vaaaaaaaaaaaaaaaaaaaaaaaay"<<i;
          PieChart.addPiece(action_type[i+1],QColor(qrand()%255,qrand()%255,qrand()%255),StatisticsPercent[i]);
      }

      PieChart.draw(&painter);
      PieChart.drawLegend(&painter);
}
