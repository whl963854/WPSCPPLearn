#include "linewidget.h"
#include "ui_linewidget.h"

LineWidget::LineWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LineWidget)
{
    ui->setupUi(this);
}

LineWidget::~LineWidget()
{
    delete ui;
}
