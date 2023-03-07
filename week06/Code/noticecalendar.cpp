#include "noticecalendar.h"
#include "ui_noticecalendar.h"

NoticeCalendar::NoticeCalendar(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NoticeCalendar)
{
    ui->setupUi(this);
    setModal(true);
    connect(ui->okBtn,&QPushButton::clicked,this,&NoticeCalendar::emitConfirm);
    connect(ui->cancelBtn,&QPushButton::clicked,this,&NoticeCalendar::emitCancel);
    setWindowFlags(Qt::FramelessWindowHint);
}

NoticeCalendar::~NoticeCalendar()
{
    delete ui;
}

void NoticeCalendar::emitConfirm()
{
    int month=ui->calendarWidget->selectedDate().month();
    int day=ui->calendarWidget->selectedDate().day();
    QString date=QString::number(month)+"月"+QString::number(day)+"日";
    date+=ui->timeEdit->text()+"提醒我";
    emit(confirm(date));
    this->hide();
}
void NoticeCalendar::emitCancel()
{
    this->hide();
    //emit(cancel());
}
