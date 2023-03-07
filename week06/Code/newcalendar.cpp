#include "newcalendar.h"
#include<QHBoxLayout>
#include<QTextCharFormat>
#include<QLocale>
#include<QDebug>
NewCalendar::NewCalendar(QWidget *parent) :
    QCalendarWidget(parent)
{
    this->setNavigationBarVisible(false);
    initControl();
}
NewCalendar::~NewCalendar()
{

}
void NewCalendar::initTopWidget()
{
    QWidget* topWidget = new QWidget(this);
    topWidget->setObjectName("CalendarTopWidget");
    topWidget->setFixedHeight(40);
    topWidget->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);

    QHBoxLayout* hboxLayout = new QHBoxLayout;
    hboxLayout->setContentsMargins(12, 0, 12, 0);
    hboxLayout->setSpacing(4);

    m_leftMonthBtn  = new QPushButton(this);
    m_leftMonthBtn->setText("<");
    m_rightMonthBtn = new QPushButton(this);
    m_rightMonthBtn->setText(">");
    m_leftYearBtn  = new QPushButton(this);
    m_leftYearBtn->setText("<<");
    m_rightYearBtn = new QPushButton(this);
    m_rightYearBtn->setText(">>");
    m_dataLabel     = new QLabel(this);

    m_leftMonthBtn->setObjectName("CalendarLeftMonthBtn");
    m_rightMonthBtn->setObjectName("CalendarRightMonthBtn");
    m_leftYearBtn->setObjectName("CalendarLeftYearBtn");
    m_rightYearBtn->setObjectName("CalendarRightYearBtn");
    m_dataLabel->setObjectName("CalendarDataLabel");

    m_leftMonthBtn->setFixedSize(16, 16);
    m_rightMonthBtn->setFixedSize(16, 16);
    m_leftYearBtn->setFixedSize(16, 16);
    m_rightYearBtn->setFixedSize(16, 16);

    hboxLayout->addWidget(m_leftYearBtn);
    hboxLayout->addStretch();
    hboxLayout->addWidget(m_leftMonthBtn);
    hboxLayout->addWidget(m_dataLabel);
    hboxLayout->addWidget(m_rightMonthBtn);
    hboxLayout->addStretch();
    hboxLayout->addWidget(m_rightYearBtn);
    topWidget->setLayout(hboxLayout);

    QVBoxLayout *vBodyLayout = qobject_cast<QVBoxLayout *>(layout());
    vBodyLayout->insertWidget(0, topWidget);

    connect(m_leftMonthBtn,&QPushButton::clicked,this,&NewCalendar::onbtnClicked);
    connect(m_rightMonthBtn,&QPushButton::clicked,this,&NewCalendar::onbtnClicked);
    connect(m_leftYearBtn,&QPushButton::clicked,this,&NewCalendar::onbtnClicked);
    connect(m_rightYearBtn,&QPushButton::clicked,this,&NewCalendar::onbtnClicked);
    setDataLabelTimeText(selectedDate().year(), selectedDate().month());
}
void NewCalendar::setDataLabelTimeText(int year,int month)
{
    QString str=QString::number(year)+"年"+QString::number(month)+"月";
    m_dataLabel->setText(str);
}
void NewCalendar::onbtnClicked()
{
    QPushButton *senderBtn = qobject_cast<QPushButton *>(sender());
    if (senderBtn == m_leftMonthBtn)
    {
        showPreviousMonth();
    }
    else if (senderBtn == m_rightMonthBtn)
    {
        showNextMonth();
    }
    else if (senderBtn == m_leftYearBtn)
    {
        showPreviousYear();
    }
    else if (senderBtn == m_rightYearBtn)
    {
        showNextYear();
    }
}
void NewCalendar::initControl()
{
    setLocale(QLocale(QLocale::Chinese));//设置中文
    setVerticalHeaderFormat(QCalendarWidget::NoVerticalHeader);//去掉列表头
    setHorizontalHeaderFormat(QCalendarWidget::LongDayNames);//星期几的行表头
    setSelectionMode(QCalendarWidget::SingleSelection);//单选
    //设置星期风格
    QTextCharFormat format;
    format.setForeground(QColor(51, 51, 51));
    format.setBackground(QColor(247,247,247));
    format.setFontFamily("Microsoft YaHei");
    format.setFontPointSize(9);
    format.setFontWeight(QFont::Medium);
    setWeekdayTextFormat(Qt::Saturday, format);
    setWeekdayTextFormat(Qt::Sunday,format);
    initTopWidget();

    connect(this,&NewCalendar::currentPageChanged,this,&NewCalendar::setDataLabelTimeText);
}


