#ifndef NOTICECALENDAR_H
#define NOTICECALENDAR_H

#include <QWidget>
#include<QDialog>

namespace Ui {
class NoticeCalendar;
}

class NoticeCalendar : public QDialog
{
    Q_OBJECT

public:
    explicit NoticeCalendar(QWidget *parent = nullptr);
    ~NoticeCalendar();

    void initDialog();

signals:
    void confirm(QString date);
    void cancel();


private slots:
    void emitConfirm();
    void emitCancel();

private:
    Ui::NoticeCalendar *ui;
};

#endif // NOTICECALENDAR_H
