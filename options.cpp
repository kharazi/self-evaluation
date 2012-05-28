#include "options.h"

Options::Options(QWidget *parent) :
    QWidget(parent)
{
    layout=new QGridLayout;
    this->setLayout(layout);
}
