#ifndef GROUPLISTITEMWIDGET_H
#define GROUPLISTITEMWIDGET_H

#include <QWidget>
#include<QLabel>
#include"tododata.h"

namespace Ui {
class GroupListItemWidget;
}

class GroupItemWidget : public QWidget
{
    Q_OBJECT

public:
    explicit GroupItemWidget(QWidget *parent = nullptr);
    ~GroupItemWidget();
    void setName(QString name);
    QString getName();
    void addTodoData(TodoData  *data);
    QList<TodoData*>& getTodoDataList();
    void removeTodoData(int index);
    void removeTodoData(QString str);
    void setTodoName(int index,QString name);
    TodoData* getTodoData(int index);
    void finishTodo(int index);
    void recoverTodo(int index);
    QString getIdMark();
    void deleteTodoItem(int index);
    int getIndex(QString todoName);
    QString getRealName();
    void finishSort(int method);
    bool static finishCmp(TodoData *a,TodoData *b);
    bool static deadlineCmp(TodoData *a,TodoData *b);
    bool static priCmp(TodoData *a,TodoData *b);
    bool static nameCmp(TodoData *a,TodoData *b);

private:
    QLabel* m_groupLabel;
    Ui::GroupListItemWidget *ui;
    QList<TodoData*> m_todoDatas;
    QString m_idMark;
};

#endif // GROUPLISTITEMWIDGET_H
