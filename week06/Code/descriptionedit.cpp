#include "descriptionedit.h"
#include "ui_descriptionedit.h"

DescriptionEdit::DescriptionEdit(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DescriptionEdit)
{
    ui->setupUi(this);
}

DescriptionEdit::~DescriptionEdit()
{
    delete ui;
}
