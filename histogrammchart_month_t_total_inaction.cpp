#include "histogrammchart_month_t_total_inaction.h"

HistogrammChart_Month_t_Total_inAction::HistogrammChart_Month_t_Total_inAction(QString u,QWidget *parent) :
    QWidget(parent)
{  
    user=u;
    today=date.Today();
    create_widget();
    set_defualt_value();
}

void HistogrammChart_Month_t_Total_inAction::set_defualt_value(){

    query.exec("SELECT title FROM action_types");
    if (query.lastError().type()==0){
        while (query.next()) {
            action_type->addItem(query.value(0).toString());
        }
    }
    else{
        QMessageBox *error = new QMessageBox;
        error->setText(QString::fromUtf8("خطا در برقراری ارتباط با پایگاه داده ای ! لطفا مجددا تلاش کنید. "));
        error->setIcon(QMessageBox::Warning);
        error->setWindowTitle(QString::fromUtf8("خطا"));
        error->exec();
    }

    for (int i=1;i<13;i++ ){
        month[i]=0;
    }

}

void HistogrammChart_Month_t_Total_inAction::create_widget(){

    QFormLayout *layout = new QFormLayout;
    QGridLayout *chooseboxlayout=new QGridLayout;

    title=new QLabel(QString::fromUtf8("نمودار تعداد یک گناه خاص در هر ماه"));
    year= new QSpinBox;
    year->setMaximum(today.at(0).toInt());
    year->setMinimum(1391);
    year->setValue(today.at(0).toInt());
    action_type = new QComboBox;

    draw= new QPushButton(QString::fromUtf8("رسم"));

    connect(draw,SIGNAL(clicked()),this,SLOT(draw_cliked()));

    this->setLayout(layout);

    chooseboxlayout->addWidget(action_type,1,1,1,1);
    chooseboxlayout->addWidget(year,1,2,1,1);

    layout->addWidget(title);
    layout->addRow(chooseboxlayout);
    layout->addWidget(draw);
}

HistogrammChart_Month_t_Total_inAction::~HistogrammChart_Month_t_Total_inAction()
{
  delete draw;
  delete title;
  delete year;
  delete action_type;
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
    this->update();
}

void HistogrammChart_Month_t_Total_inAction::paintEvent(QPaintEvent *e)
{
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
