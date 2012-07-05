#include "histogrammchart_day_of_month.h"

HistogrammChart_Day_of_Month::HistogrammChart_Day_of_Month(QString u,QWidget *parent) :
    QWidget(parent)

{
    user =u;
    today=date.Today();
    month = new QComboBox;
    for (int i=1;i<13;i++){
        month->addItem(date.Month[i]);
    }
    month->setCurrentIndex(today.at(1).toInt()-1);

    QFormLayout *layout = new QFormLayout;

    title=new QLabel(QString::fromUtf8(" نمودار تعداد گناه در روز های یک ماه"));
    year= new QSpinBox;
    year->setMaximum(today.at(0).toInt());
    year->setMinimum(1390);
    year->setValue(today.at(0).toInt());
    this->setLayout(layout);
    draw= new QPushButton(QString::fromUtf8("رسم"));
    layout->addRow(title);
    connect(draw,SIGNAL(clicked()),this,SLOT(draw_clicked()));
    layout->addWidget(year);
    layout->addWidget(month);
    layout->addWidget(draw);
    get_data();
}

HistogrammChart_Day_of_Month::~HistogrammChart_Day_of_Month()
{
  delete month;
  delete title;
  delete draw;
  delete year;
}

void HistogrammChart_Day_of_Month::get_data(){
    for (int i=1;i<=31;i++){
        query.exec(QString("SELECT COUNT(actions.id) FROM actions WHERE actions.username='%1'AND actions.date LIKE'%2-%3-%4'").arg(user).arg(year->value()).arg(month->currentIndex()+1).arg(i));
        while (query.next()) {
            countOfmonth[i]=query.value(0).toInt();
        }
    }
}

void HistogrammChart_Day_of_Month::draw_clicked(){

    get_data();
    this->update();
}

void HistogrammChart_Day_of_Month::paintEvent(QPaintEvent *e)
{

    QWidget::paintEvent(e);
    QPainter painter;
    QFont font;
    painter.begin(this);
    Nightcharts PieChart;
    PieChart.setType(Nightcharts::Histogramm);//{Histogramm,Pie,DPie};
    PieChart.setLegendType(Nightcharts::Vertical);//{Round,Vertical}
    PieChart.setCords(20,150,this->width()/1.5+200,this->height()/1.5);
    for (int i=1;i<32;i++ ){
        PieChart.addPiece(QString::number(i),QColor(qrand()%255,qrand()%255,qrand()%255),countOfmonth[i]);
    }
    PieChart.draw(&painter);
    PieChart.drawLegend(&painter);
}
