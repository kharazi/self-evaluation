#include "histogrammchart_month_t_total.h"

HistogrammChart_Month_t_Total::HistogrammChart_Month_t_Total(QString u,QWidget *parent) :
    QWidget(parent)
{
    user=u;
    today=date.Today();
    qDebug()<<"user"<<user;
//    layout = new QGridLayout;
//    this->setLayout(layout);



}
void HistogrammChart_Month_t_Total::Create_Widget(){

//    /*year*/= new QSpinBox;
//    year->setMaximum(today.at(0).toInt());
//    year->setMinimum(1389);
//    year->setValue(today.at(0).toInt());

//    layout->addWidget(year);
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
    PieChart.setCords(5,80,270,180);
    PieChart.addPiece(date.nRoz(-6),QColor(200,10,50),10.645);
    PieChart.addPiece(date.nRoz(-5),Qt::green,54);
    PieChart.addPiece(date.nRoz(-4),Qt::cyan,65);
    PieChart.addPiece(date.nRoz(-3),Qt::yellow,6);
    PieChart.addPiece(date.nRoz(-2),Qt::blue,54);
    PieChart.addPiece(date.nRoz(-1),Qt::black,6);
    PieChart.addPiece(date.nRoz(0),Qt::white,67);
    PieChart.draw(&painter);
    PieChart.drawLegend(&painter);
}
