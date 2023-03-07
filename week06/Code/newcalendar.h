#ifndef NEWCALENDAR_H
#define NEWCALENDAR_H

#include <QWidget>
#include<QCalendarWidget>
#include<QPushButton>
#include<QLabel>


namespace Ui {
class NewCalendar;
}

class NewCalendar : public QCalendarWidget
{
    Q_OBJECT

public:
    void initTopWidget();
    explicit NewCalendar(QWidget *parent = nullptr);
    void setDataLabelTimeText(int year,int month);
    void initControl();
    ~NewCalendar();
public slots:
    void onbtnClicked();

private:
    Ui::NewCalendar *ui;
    QPushButton * m_leftMonthBtn;
    QPushButton * m_rightMonthBtn;
    QPushButton * m_leftYearBtn;
    QPushButton * m_rightYearBtn;
    QLabel* m_dataLabel;
};

#endif // NEWCALENDAR_H
