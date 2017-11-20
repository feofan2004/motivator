#include "mywidget.h"
#include "mainwindow.h"

MyWidget::MyWidget(QWidget *){}

void MyWidget::enterEvent(QEvent *)
{
    emit isMouseOnWindow(true);
}

void MyWidget::leaveEvent(QEvent *)
{
    emit isMouseOnWindow(false);
}

MyWidget::~MyWidget(){}
