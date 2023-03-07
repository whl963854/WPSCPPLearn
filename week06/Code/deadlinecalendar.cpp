#include "deadlinecalendar.h"
#include<QHBoxLayout>
#include<QVBoxLayout>
#include<QPushButton>
#include<QLabel>
#include<QComboBox>


DeadLineCalendar::DeadLineCalendar(QWidget *parent) :
    QDialog(parent)
{
    initDialog();
    this->setModal(true);
    connect(m_okBtn,&QPushButton::clicked,this,&DeadLineCalendar::emitConfirm);
    connect(m_cancelBtn,&QPushButton::clicked,this,&DeadLineCalendar::emitCancel);
    setWindowFlags(Qt::FramelessWindowHint);
}

DeadLineCalendar::~DeadLineCalendar()
{

}
void DeadLineCalendar::initDialog()
{
    QHBoxLayout* hlayoutUp=new QHBoxLayout;
    QHBoxLayout* hlayoutDown=new QHBoxLayout;
    QVBoxLayout* vlayout=new QVBoxLayout;
    m_calaendar=new NewCalendar(this);
    m_okBtn=new QPushButton(this);
    m_cancelBtn=new QPushButton(this);
    m_okBtn->setText("确认");
    m_cancelBtn->setText("取消");
    m_repeatLabel=new QLabel(this);
    m_repeatLabel->setPixmap(QPixmap("://image/res/isRepeat.png"));
    m_repeatLabel->setMaximumWidth(20);
    m_repeatLabel->setMaximumHeight(20);
    hlayoutUp->addWidget(m_repeatLabel);
    m_chooseRepeatComboBox  =new QComboBox(this);
    QStringList strList;
    strList<<"不重复"<<"每月"<<"每周"<<"每天";
    m_chooseRepeatComboBox->addItems(strList);
    hlayoutUp->addWidget(m_repeatLabel);
    hlayoutUp->addWidget(m_chooseRepeatComboBox);
    hlayoutUp->addStretch();
    hlayoutDown->addStretch();
    hlayoutDown->addWidget(m_cancelBtn);
    hlayoutDown->addStretch();
    hlayoutDown->addWidget(m_okBtn);
    hlayoutDown->addStretch();
    vlayout->addWidget(m_calaendar);
    vlayout->addItem(hlayoutUp);
    vlayout->addItem(hlayoutDown);
    this->setLayout(vlayout);
}
void DeadLineCalendar::emitConfirm()
{
    int year=this->m_calaendar->selectedDate().year();
    int month=this->m_calaendar->selectedDate().month();
    int day=this->m_calaendar->selectedDate().day();
    QString date=QString::number(year)+"年"+QString::number(month)+"月"+QString::number(day)+"日";
    QString repeat=m_chooseRepeatComboBox->currentText();
    emit(confirm(date,repeat));
    this->hide();
}
void DeadLineCalendar::emitCancel()
{
    this->hide();
    //emit(cancel());
}

