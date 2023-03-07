#ifndef TODOLIST_H
#define TODOLIST_H


#include"todoitemwidget.h"
#include <QMainWindow>
#include <QPushButton>
#include<QListWidgetItem>

#include"newcalendar.h"
#include"deadlinecalendar.h"
#include "noticecalendar.h"
#include "addnewgroupdialog.h"
#include"grouplistwidget.h"
#include "noticecalendar.h"
#include "todolistwidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class todolist; }
QT_END_NAMESPACE

class TodoList : public QMainWindow
{
    Q_OBJECT

public:
    enum GroupMethod{All,NoArrangement,SevenDays,LaterDays,Overdue};

    TodoList(QWidget *parent = nullptr);
    ~TodoList();
    void addTodoItem();
    void updateDockWidget();
    void groupChange(QListWidgetItem* item);
    void initPos();
    void firstPageFresh();


signals:
    void closeTodoWidget();


public slots:
    void showMethodChange();

    void deadlineSort();
    void priSort();
    void todoNameSort();

    void locateChange();
    void remarkChange();
    void descriptionChange();

    void saveTodoData();
    void saveGroups();
    void closeEvent ( QCloseEvent * e )override;
    void refresh();

    void finishStateChange(int index,bool finish);

    void deleteTodoItem();
    void renameTodoItem(int index,QString name);
    void hideFinishedTodos();

    //设置内容
    void setDeadline(QString name,QString repeat);
    void setNotice(QString str);
    void setPri();
    void setDescription();
    void setLocation();
    void setRemark();

    //清除设置内容
    void deleteDeadline();
    void deleteNotice();
    void deleteDescription();
    void deleteRemark();
    void deleteLocation();


private:
    Ui::todolist *ui;
    DeadLineCalendar*m_deadlineCalendar;
    NoticeCalendar* m_noticeCalendar;
    AddNewGroupDialog* m_addNewTodoDialog;
    GroupListWidget* m_groupListWidget;
    TodoListWidget* m_todoListWidget;
    int m_hideFinish;
    int m_currentGroupMethod;

    void beautify();
    void init();
    void addTodoDataList(QList<TodoData*> todoDatas,QList<QString>groups);

};
#endif // TODOLIST_H
