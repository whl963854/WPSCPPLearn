#include "addnewgroupdialog.h"
#include "ui_addnewgroupdialog.h"

AddNewGroupDialog::AddNewGroupDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddNewTodoDialog)
{
    ui->setupUi(this);
    this->setModal(true);
    setWindowFlags(Qt::FramelessWindowHint);
    connect(ui->confirmBtn,&QPushButton::clicked,this,&AddNewGroupDialog::emitConfirm);
    connect(ui->cannelBtn,&QPushButton::clicked,this,&AddNewGroupDialog::emitCancel);
}

AddNewGroupDialog::~AddNewGroupDialog()
{
    delete ui;
}

void AddNewGroupDialog::emitConfirm()
{
    QString str =ui->groupNameLineEdit->text();
    this->hide();
    ui->groupNameLineEdit->setText("");
    emit(confirm(str));
}

void AddNewGroupDialog::emitCancel()
{
    ui->groupNameLineEdit->setText("");
    this->hide();
    emit(cancel());
}
