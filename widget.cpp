#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    this->setMinimumSize(600,600);
    glWindow = new self_glWidget(this);
    mainLayout = new QHBoxLayout(this);
    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->addWidget(glWindow);
}

Widget::~Widget()
{
}

