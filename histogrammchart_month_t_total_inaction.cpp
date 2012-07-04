#include "histogrammchart_month_t_total_inaction.h"

HistogrammChart_Month_t_Total_inAction::HistogrammChart_Month_t_Total_inAction(QString u,QWidget *parent) :
    QWidget(parent)
{

    for (int i=1;i<13;i++ ){
        month[i]=0;
    }
    user=u;
    today=date.Today();
    qDebug()<<"user"<<user;
    QFormLayout *layout = new QFormLayout;

    title=new QLabel(QString::fromUtf8("نمودار تعداد یک گناه خاص در هر ماه"));
    year= new QSpinBox;
    year->setMaximum(today.at(0).toInt());
    year->setMinimum(1391);
    year->setValue(today.at(0).toInt());
    action_type = new QComboBox;


    query.exec("SELECT title FROM action_types");
    qDebug()<<query.lastError().text();
    if (query.lastError().type()==0){
        while (query.next()) {
            qDebug()<<query.value(0).toString();
            action_type->addItem(query.value(0).toString());
        }
    }
    else{

        QMessageBox *error = new QMessageBox;
        error->setText("there is a problem; cannot read database");
        error->setIcon(QMessageBox::Warning);
        error->setWindowTitle("Error");
        error->exec();
    }

    draw= new QPushButton(QString::fromUtf8("رسم"));
    connect(draw,SIGNAL(clicked()),this,SLOT(draw_cliked()));

    this->setLayout(layout);

    layout->addRow(title);
    layout->addWidget(year);
    layout->addWidget(action_type);
    layout->addWidget(draw);




}
void HistogrammChart_Month_t_Total_inAction::get_data(){
    int action_id=0;

    query.exec(QString("SELECT action_id FROM action_types WHERE title = '%1' ").arg(action_type->currentText()));
    while (query.next()){
      action_id = query.value(0).toInt();
    }
    for (int i=1;i<13;i++ ){
    query.exec(QString("SELECT COUNT(actions.id) FROM actions WHERE actions.date LIKE'%1-%2-%'AND actions.username='%3' AND actions.action_id=%4").arg(year->value()).arg(i).arg(user).arg(action_id));
        while (query.next()) {
            month[i]=query.value(0).toInt();
        }
    }
}

void HistogrammChart_Month_t_Total_inAction::draw_cliked(){
    get_data();
//    paintEvent();
    this->update();


}
void HistogrammChart_Month_t_Total_inAction::paintEvent(QPaintEvent *e)
{
    qDebug()<<"ha";
    for (int i=1;i<13;i++ ){
        qDebug()<<i<< ""<<month[i];

    }
    QWidget::paintEvent(e);
    QPainter painter;
    QFont font;
    painter.begin(this);
    Nightcharts PieChart;
    PieChart.setType(Nightcharts::Histogramm);//{Histogramm,Pie,DPie};
    PieChart.setLegendType(Nightcharts::Vertical);//{Round,Vertical}
    PieChart.setCords(20,130,this->width()/1.5,this->height()/1.5);
    for (int i=1;i<13;i++ ){
        PieChart.addPiece(date.Month[i],QColor(qrand()%255,qrand()%255,qrand()%255),month[i]);
    }
    PieChart.draw(&painter);
    PieChart.drawLegend(&painter);
}
