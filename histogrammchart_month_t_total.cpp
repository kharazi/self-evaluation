#include "histogrammchart_month_t_total.h"

HistogrammChart_Month_t_Total::HistogrammChart_Month_t_Total(QString u,QWidget *parent) :
    QWidget(parent)
{    
    user=u;
    today=date.Today();
    create_widget();
    set_default_value();
}
void HistogrammChart_Month_t_Total::create_widget(){
    QFormLayout *layout = new QFormLayout;
    QGridLayout *chooseLayout=new QGridLayout;


    title=new QLabel(QString::fromUtf8("نمودار تعداد گناه در هر ماه"));

    year= new QSpinBox;
    year->setMaximum(today.at(0).toInt());
    year->setMinimum(1390);
    year->setValue(today.at(0).toInt());

    draw= new QPushButton(QString::fromUtf8("رسم"));

    connect(draw,SIGNAL(clicked()),this,SLOT(draw_cliked()));

    chooseLayout->addWidget(draw,1,1,1,1);
    chooseLayout->addWidget(year,1,2,1,1);
    layout->addRow(title);
    layout->addRow(chooseLayout);

    this->setLayout(layout);
}

void HistogrammChart_Month_t_Total::set_default_value(){
    for (int i=1;i<13;i++ ){
        month[i]=0;
    }
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
    PieChart.setCords(20,60,this->width()/1.5+100,this->height()/1.5+90);
    for (int i=1;i<13;i++ ){
        PieChart.addPiece(date.Month[i],QColor(qrand()%255,qrand()%255,qrand()%255),month[i]);
    }
    PieChart.draw(&painter);
    PieChart.drawLegend(&painter);
}
