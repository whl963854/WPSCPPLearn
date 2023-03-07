#ifndef GROUPLISTWIDGET_H
#define GROUPLISTWIDGET_H

#include <QWidget>
#include<QString>
#include<QListWidgetItem>
#include<groupitemwidget.h>

namespace Ui {
class GroupListWidget;
}

class GroupListWidget : public QListWidget
{
    Q_OBJECT

public:
    enum method{Finished,Deadline,Priority,TodoName};
    explicit GroupListWidget(QWidget *parent = nullptr);
    ~GroupListWidget();
    GroupItemWidget* getGroupItemWidget(int index);
    void addTodoDataList(QList<TodoData*> todoDatas,QList<QString>groups);
    void addGroups(QList<QString> groups);
    int findGroup(QString groupName);
    void contextMenuEvent ( QContextMenuEvent * event );
    void sortTodos(int method);

signals:
    void dropGroup();
    void renameGroup(int index,QString name);
    void groupNameChanged();


public slots:
    void addGroup(QString groupName);
    void deleteGroupItem();
    void showRenameMenu();
    void renameGroupItem();

private:
    QListWidgetItem* m_addGroupItem;
    QListWidgetItem* m_firstGroup;
    QListWidgetItem* m_ownTodoGroup;
    GroupItemWidget* m_firstGroupItemWidget;
    GroupItemWidget* m_ownGroupItemWidget;
    QList<GroupItemWidget*> m_groupItemsWidget;
    QMenu *m_menu;
    QAction *m_deleteAct;
    QLineEdit* m_lineEdit;
    void initGroup();

};

#endif // GROUPLISTWIDGET_H
