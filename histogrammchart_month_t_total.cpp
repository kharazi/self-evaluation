#include "histogrammchart_month_t_total.h"

HistogrammChart_Month_t_Total::HistogrammChart_Month_t_Total(QString u,QWidget *parent) :
    QWidget(parent)
{

    for (int i=1;i<13;i++ ){
        month[i]=0;
    }
    user=u;
    today=date.Today();
    QFormLayout *layout = new QFormLayout;

    title=new QLabel(QString::fromUtf8("نمودار تعداد گناه در هر ماه"));
    year= new QSpinBox;
    year->setMaximum(today.at(0).toInt());
    year->setMinimum(1390);
    year->setValue(today.at(0).toInt());
    this->setLayout(layout);
    draw= new QPushButton(QString::fromUtf8("رسم"));
    layout->addRow(title);
    connect(draw,SIGNAL(clicked()),this,SLOT(draw_cliked()));
    layout->addWidget(year);
    layout->addWidget(draw);
}

HistogrammChart_Month_t_Total::~HistogrammChart_Month_t_Total()
{
  delete title;
  delete draw;
  delete year;
}
void HistogrammChart_Month_t_Total::draw_cliked(){
    get_data();
    this->update();
}

void HistogrammChart_Month_t_Total::get_data(){
    for (int i=1;i<13;i++ ){
    query.exec(QString("SELECT COUNT(actions.id) FROM actions WHERE actions.date LIKE'%1-%2-%'AND actions.username='%3'").arg(year->value()).arg(i).arg(user));
        while (query.next()) {
            month[i]=query.value(0).toInt();
        }
    }
}

void HistogrammChart_Month_t_Total::paintEvent(QPaintEvent *e)
{
    QWidget::paintEvent(e);
    QPainter painter;
    QFont font;
    painter.begin(this);
    Nightcharts PieChart;
    PieChart.setType(Nightcharts::Histogramm);//{Histogramm,Pie,DPie};
    PieChart.setLegendType(Nightcharts::Vertical);//{Round,Vertical}
    PieChart.setCords(20,100,this->width()/1.5+30,this->height()/1.5+30);
    for (int i=1;i<13;i++ ){
        PieChart.addPiece(date.Month[i],QColor(qrand()%255,qrand()%255,qrand()%255),month[i]);
    }
    PieChart.draw(&painter);
    PieChart.drawLegend(&painter);
}
