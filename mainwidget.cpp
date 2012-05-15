#include "mainwidget.h"

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
{
    layout = new QGridLayout;
    lable = new QLabel("salam");
    this->setLayout(layout);
    layout->addWidget(lable);

}

MainWidget::~MainWidget()
{

}
