#include "histogrammchart_weekly.h"

HistogrammChart_weekly::HistogrammChart_weekly(QString u,QWidget *parent) :
    QWidget(parent)
{
    week =0;
    user=u;

    CreateWidget();
    SetDefualtValue();
    this->get_data();
    dateLable->setText(QString::fromUtf8("از تاریخ %1 تا تاریخ %2").arg(index_date[1]).arg(index_date[7]));
    for (int i=1;i<=7;i++){
        qDebug()<<"rozeeeeeeeeeeeee:"<<i<<"haaaaaaaaaaaaaaaaaaaaaaaaaaastesh"<<index_date[i];
    }

    qDebug()<<"week is:"<<week;


    for (int i=1;i<=7;i++){
        qDebug()<<"rozeeeeeeeeeeeee:"<<i<<"haaaaaaaa"<<index_value[i];
    }
}
void HistogrammChart_weekly::SetDefualtValue(){
    //set defulalt values

    for (int i=1;i<=7;i++){
        index_value[i]=0;
    }
    qDebug()<<"diiiiiiiiiiiiiiiiiiif"<<date.diff;
    index_date[7-date.diff]=date.nRoz(0);
    for (int i=1;i<(7-date.diff);i++){
        index_date[7-i]=date.nRoz(-(date.diff+i));
        qDebug()<<"[7-i-1"<<7-i<<date.nRoz(-(date.diff+i));
    }
    for (int i=1;i<=date.diff;i++){
        index_date[7-date.diff+i]=date.nRoz(i);
    }




}
void HistogrammChart_weekly::CreateWidget(){
    nextweek=new QPushButton();
    previousweek=new QPushButton();
    dateLable=new QLabel();
    nextweek->setIcon(QIcon(":/images/next.png"));
    previousweek->setIcon(QIcon(":/images/previous.png"));
    title=new QLabel(QString::fromUtf8("نمودار تعداد عمل در هر هفته"));

    connect(nextweek,SIGNAL(clicked()),this,SLOT(nextweek_button_clicked()));
    connect(previousweek,SIGNAL(clicked()),this,SLOT(previousweek_button_clicked()));



    QGridLayout * layout= new QGridLayout;
    QFormLayout *mainLayout=new QFormLayout;

    layout->addWidget(nextweek,1,2,1,1);
    layout->setColumnMinimumWidth(1,this->width()-100);

    layout->addWidget(previousweek,1,0,1,1);

    mainLayout->addWidget(title);

    mainLayout->addWidget(dateLable);
        mainLayout->addRow(layout);


    this->setLayout(mainLayout);






}

void HistogrammChart_weekly::get_data(){
    for (int i=1;i<=7;i++){
        query.exec(QString("SELECT COUNT(actions.id) FROM actions WHERE actions.date='%1'AND actions.username='%2'").arg(index_date[i]).arg(user));
            while (query.next()) {
                index_value[i]=query.value(0).toInt();
            }
    }
}

void HistogrammChart_weekly::nextweek_button_clicked(){
    qDebug()<<"week is:"<<week;
    for (int i=1;i<=7;i++){
        index_date[i]=date.nRoz(date.diff+i+(week*7));
    }
    get_data();
    for (int i=1;i<=7;i++){
        qDebug()<<"rozeeeeeeeeeeeee:"<<i<<"haaaaaaaaaaaaaaaaaaaaaaaaaaastesh"<<index_date[i]<<index_value[i];
    }
    this->update();
    week++;
    dateLable->setText(QString::fromUtf8("از تاریخ %1 تا تاریخ %2").arg(index_date[1]).arg(index_date[7]));


}
void HistogrammChart_weekly::previousweek_button_clicked(){
    qDebug()<<"week is:"<<week;
    for (int i=1;i<=7;i++){
        index_date[7-i+1]=date.nRoz(week*7+date.diff-i+1);
    }
    get_data();
    for (int i=1;i<=7;i++){
        qDebug()<<"rozeeeeeeeeeeeee:"<<i<<"haaaaaaaaaaaaaaaaaaaaaaaaaaastesh"<<index_date[i]<<index_value[i];
    }
    week--;
    this->update();
    dateLable->setText(QString::fromUtf8("از تاریخ %1 تا تاریخ %2").arg(index_date[1]).arg(index_date[7]));


}

void HistogrammChart_weekly::paintEvent(QPaintEvent *e)
{

    QWidget::paintEvent(e);
    QPainter painter;
    QFont font;
    painter.begin(this);
    Nightcharts PieChart;
    PieChart.setType(Nightcharts::Histogramm);//{Histogramm,Pie,DPie};
    PieChart.setLegendType(Nightcharts::Vertical);//{Round,Vertical}
    PieChart.setCords(80,110,this->width()/1.5,this->height()/1.5);
    for (int i=1;i<=7;i++){
        PieChart.addPiece(date.JalaliDayNumber[i],QColor(qrand()%255,qrand()%255,qrand()%255),index_value[i]);
    }
    PieChart.draw(&painter);
    PieChart.drawLegend(&painter);
}
