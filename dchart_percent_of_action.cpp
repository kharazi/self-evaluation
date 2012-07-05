#include "dchart_percent_of_action.h"

DChart_percent_of_action::DChart_percent_of_action(QString u,QWidget *parent) :
    QWidget(parent)
{
      user=u;
      title=new QLabel(QString::fromUtf8("نمودار دایره ای درصد گناهان مختلف "));
      QFormLayout *layout = new QFormLayout;
      layout->addWidget(title);
      this->setLayout(layout);

      today=date.Today();
      get_data();
}

DChart_percent_of_action::~DChart_percent_of_action()
{
  delete title;
}

void DChart_percent_of_action::get_data(){
    int sum1=0;
    query.exec(QString("SELECT action_id,COUNT(id) FROM actions WHERE actions.username='%1' GROUP BY action_id").arg(user));
    QHash<int,int> Statistics;
    while (query.next()) {
        sum1+=query.value(1).toInt();
        Statistics[ query.value(0).toInt()]= query.value(1).toInt();
    }


    //darsad giri sayer
    int sum=0;
    for (int i=0;i<Statistics.keys().length();i++){
        sum+=Statistics.value(i);
    }

    for (int i=0;i<Statistics.keys().length();i++){
        StatisticsPercent[i]=(Statistics[i]*100.0)/sum;
    }

    for (int i=1;i<=Statistics.keys().length();i++){
        query.exec(QString("SELECT title FROM action_types WHERE action_id =%1").arg(i));
         while (query.next()) {
             action_type[i]=query.value(0).toString();
         }
    }
}

void DChart_percent_of_action::paintEvent(QPaintEvent *e){
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
        PieChart.addPiece(action_type[i+1],QColor(qrand()%255,qrand()%255,qrand()%255),StatisticsPercent[i]);
    }
    PieChart.draw(&painter);
    PieChart.drawLegend(&painter);
}
