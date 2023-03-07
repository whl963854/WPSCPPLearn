#ifndef TODOLISTWIDGET_H
#define TODOLISTWIDGET_H

#include <QWidget>
#include<QListWidget>

#include"todoitemwidget.h"
#include"tododata.h"

class TodoListWidget : public QListWidget
{
    Q_OBJECT

public:

    explicit TodoListWidget(QWidget *parent = nullptr);
    ~TodoListWidget();
    TodoItemWidget* addTodoItem(QString name,QString group);
    void removeTodoItem(int index);
    void recoverTodoItem(int index);
    TodoItemWidget* addTodoItem(TodoData data);
    TodoItemWidget* addTodoFirstPageItem(TodoData* data);
    TodoItemWidget* getTodoItemWidget(int index);
    void todoItemsClear();
    TodoItemWidget* insertTodoItem(int index,TodoData data);
    QList<TodoItemWidget*> getTodoItemWidgets();
    QString getName();
    int getIndex(QString name);

    void addTodoGroup(QString name);
    void firstPageFresh(QList<TodoData*>todoDatas,bool hideFinish);
    //删除列表项
    void deleteTodoItem(int index);


public slots:
    void deleteTodoItem();
    void showRenameMenu();
    void renameTodoItem();
    void emitFinishTodo(TodoItemWidget* temp);

protected:
    void contextMenuEvent(QContextMenuEvent *);


signals:
    void delTodoItem(QString name,int index);
    void finishTodo(int index,bool isFinished);
    void renameTodo(int index,QString name);


private:
    QList<TodoItemWidget*>m_todoItemWidgets;
    bool memuOpen;
    QMenu *m_menu;
    QAction *m_deleteAct;
    QLineEdit* m_lineEdit;
    int m_count1=1;
    int m_count2=2;
    int m_count3=3;
};

#endif // TODOLISTWIDGET_H
