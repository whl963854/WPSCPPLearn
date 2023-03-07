#ifndef CANDERDIALOG_H
#define CANDERDIALOG_H

#include <QDialog>
#include<QLabel>
#include<QComboBox>
#include"newcalendar.h"

class DeadLineCalendar : public QDialog
{
    Q_OBJECT

public:
    void initDialog();
    explicit DeadLineCalendar(QWidget *parent = nullptr);
    ~DeadLineCalendar();

signals:
    void confirm(QString date,QString repeat);
    void cancel();

private:
    NewCalendar*m_calaendar;
    QLabel* m_repeatLabel;
    QPushButton* m_okBtn;
    QPushButton* m_cancelBtn;
    QComboBox*m_chooseRepeatComboBox;

private slots:
    void emitConfirm();
    void emitCancel();
};

#endif // CANDERDIALOG_H
