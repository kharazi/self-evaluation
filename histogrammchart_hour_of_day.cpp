#include "histogrammchart_hour_of_day.h"

HistogrammChart_Hour_Of_Day::HistogrammChart_Hour_Of_Day(QString u,QWidget *parent) :
    QWidget(parent)
{
    user =u;
    today=date.Today();
    QGridLayout * checklayout= new QGridLayout;

    year= new QSpinBox;
    year->setMaximum(today.at(0).toInt());
    year->setMinimum(1390);
    year->setValue(today.at(0).toInt());

    title=new QLabel(QString::fromUtf8("نمودار تعداد گناه در یک سال بر حسب ساعت های روز"));
    QFormLayout *layout = new QFormLayout;
    this->setLayout(layout);
    AM= new QRadioButton("AM");
//    AM->setChecked();
    PM=new QRadioButton("PM");
    draw= new QPushButton(QString::fromUtf8("رسم"));
    checklayout->addWidget(AM,1,1,1,1);
    checklayout->addWidget(PM,1,2,1,1);
    checklayout->addWidget(year,1,3,1,1);
    layout->addRow(title);
    layout->addRow(checklayout);
    layout->addWidget(draw);
    connect(draw,SIGNAL(clicked()),this,SLOT(draw_clicked()));
    is_AM=1;
}
void HistogrammChart_Hour_Of_Day::get_data(){
    for (int i=0;i<24;i++){
        query.exec(QString("SELECT COUNT(actions.id) FROM actions WHERE actions.username='%1'AND actions.time LIKE'%2:%' AND actions.date LIKE '%3-%' ").arg(user).arg(i).arg(year->value()));
        while (query.next()) {
            countOfhours[i]=query.value(0).toInt();
        }
    }
}

void HistogrammChart_Hour_Of_Day::draw_clicked(){
    if (!PM->isChecked()){
        is_AM=0;
    }
    if (AM->isChecked()){
        is_AM=1;

    }

    get_data();
    this->update();
}


void HistogrammChart_Hour_Of_Day::paintEvent(QPaintEvent *e)
{
    if (is_AM){
        QWidget::paintEvent(e);
        QPainter painter;
        QFont font;
        painter.begin(this);
        Nightcharts PieChart;
        PieChart.setType(Nightcharts::Histogramm);//{Histogramm,Pie,DPie};
        PieChart.setLegendType(Nightcharts::Vertical);//{Round,Vertical}
        PieChart.setCords(20,130,this->width()/1.5+100,this->height()/1.5);
        for (int i=0;i<12;i++ ){
            PieChart.addPiece(QString::number(i),QColor(qrand()%255,qrand()%255,qrand()%255),countOfhours[i]);
        }
        PieChart.draw(&painter);
        PieChart.drawLegend(&painter);

    }else{

        QWidget::paintEvent(e);
        QPainter painter;
        QFont font;
        painter.begin(this);
        Nightcharts PieChart;
        PieChart.setType(Nightcharts::Histogramm);//{Histogramm,Pie,DPie};
        PieChart.setLegendType(Nightcharts::Vertical);//{Round,Vertical}
        PieChart.setCords(20,130,this->width()/1.5+100,this->height()/1.5);
        for (int i=12;i<24;i++ ){
            PieChart.addPiece(QString::number(i),QColor(qrand()%255,qrand()%255,qrand()%255),countOfhours[i]);
        }
        PieChart.draw(&painter);
        PieChart.drawLegend(&painter);




    }

}

