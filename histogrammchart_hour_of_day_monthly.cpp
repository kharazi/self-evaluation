#include "histogrammchart_hour_of_day_monthly.h"

HistogrammChart_Hour_Of_Day_monthly::HistogrammChart_Hour_Of_Day_monthly(QString u,QWidget *parent) :
    QWidget(parent)
{
    user =u;
    today=date.Today();
    QGridLayout * checklayout= new QGridLayout;

    year= new QSpinBox;
    year->setMaximum(today.at(0).toInt());
    year->setMinimum(1390);
    year->setValue(today.at(0).toInt());

    month = new QComboBox;
    for (int i=1;i<13;i++){
        month->addItem(date.Month[i]);
    }
    month->setCurrentIndex(today.at(1).toInt()-1);

    title=new QLabel(QString::fromUtf8("نمودار تعداد گناه در یک ماه بر حسب ساعت های روز"));
    QFormLayout *layout = new QFormLayout;
    this->setLayout(layout);

    draw= new QPushButton(QString::fromUtf8("رسم"));
    checklayout->addWidget(year,1,3,1,1);
    checklayout->addWidget(month,1,4,1,1);
    layout->addRow(title);
    layout->addRow(checklayout);
    layout->addWidget(draw);
    connect(draw,SIGNAL(clicked()),this,SLOT(draw_clicked()));

}

HistogrammChart_Hour_Of_Day_monthly::~HistogrammChart_Hour_Of_Day_monthly()
{
  delete year;
  delete month;
  delete title;
  delete draw;
}

void HistogrammChart_Hour_Of_Day_monthly::get_data(){
    for (int i=0;i<24;i++){
        query.exec(QString("SELECT COUNT(actions.id) FROM actions WHERE actions.username='%1'AND actions.time LIKE'%2:%' AND actions.date LIKE '%3-%4-%' ").arg(user).arg(i).arg(year->value()).arg(month->currentIndex()-1));
        while (query.next()) {
            countOfhours[i]=query.value(0).toInt();
        }
    }
}

void HistogrammChart_Hour_Of_Day_monthly::draw_clicked(){
    get_data();
    this->update();
}
void HistogrammChart_Hour_Of_Day_monthly::paintEvent(QPaintEvent *e)
{

        QWidget::paintEvent(e);
        QPainter painter;
        QFont font;
        painter.begin(this);
        Nightcharts PieChart;
        PieChart.setType(Nightcharts::Histogramm);//{Histogramm,Pie,DPie};
        PieChart.setLegendType(Nightcharts::Vertical);//{Round,Vertical}
        PieChart.setCords(20,130,this->width()/1.5+100,this->height()/1.5);
        PieChart.setTwoLineLables();
        for (int i=0;i<24;i++ ){
            PieChart.addPiece(QString::number(i),QColor(qrand()%255,qrand()%255,qrand()%255),countOfhours[i]);
        }
        PieChart.draw(&painter);
        PieChart.drawLegend(&painter);


}
