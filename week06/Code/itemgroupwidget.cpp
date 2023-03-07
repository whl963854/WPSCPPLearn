#include "itemgroupwidget.h"
#include "ui_itemgroupwidget.h"

ItemGroupWidget::ItemGroupWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GroupWidget)
{
    ui->setupUi(this);
}

ItemGroupWidget::~ItemGroupWidget()
{
    delete ui;
}

void ItemGroupWidget::setName(QString name)
{
    ui->itemGroupLabel->setText(name);
}

