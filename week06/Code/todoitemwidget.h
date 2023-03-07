#ifndef TODOITEM_H
#define TODOITEM_H

#include <QWidget>
#include<QFrame>
#include<QCheckBox>
#include<QLabel>
#include<QDate>
#include<QDateTime>
#include<QHBoxLayout>
#include<QToolButton>
#include<QAction>
#include<QPushButton>

#include"tododata.h"


class TodoItemWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TodoItemWidget(QWidget *parent = nullptr);
    ~TodoItemWidget();

    void initItem(QString todoName,QString groupName);
    void initItem(TodoData data);
    QString getGroupName();
    void setGroupName(QString str);
    QString getDeadline();
    void setDeadline(QString str);
    QString getNotice();
    void setNotice(QString str);
    QString getRepeation();
    QString getName();
    void setName(QString str);
    void setRepeation(QString str);
    void setPri(int pri);
    bool getFinish();
    void hasFinished();
    void hasRecovered();
    void setFinish(bool finish);

    QToolButton* getNoticeToolBtn();
    QToolButton* getDeadlineBtn();
    QToolButton* getRepeatToolBtn();
    QToolButton* getGroupNameToolBtn();
    QToolButton* getTodoNameToolBtn();


signals:
    //自定义clicked()信号,在mousePressEvent事件发生时触发
    void clicked();
    void delTodoItem(TodoItemWidget*);
    void finishStateChange(TodoItemWidget*);

public slots:

    void finishChange();

protected:
    //添加并重写鼠标点击事件函数
    //virtual void mousePressEvent(QMouseEvent *e);
    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);
    //void contextMenuEvent(QContextMenuEvent *);


private:
    bool m_bSelected=false;
    int m_pri=0;

    bool m_isFinish;
    QString m_location,m_description,m_remark,m_itemName;
    //QLabel* m_itemLabel;
    QLabel* m_priLabel;
    QCheckBox* m_checkBox;
    QToolButton* m_itemLabel;
    QToolButton* m_deadlineToolBtn;
    QToolButton* m_noticeToolBtn;
    QToolButton* m_groupToolBtn;
    QToolButton* m_repeatToolBtn;
    QMenu *m_menu;
};

#endif // TODOITEM_H
