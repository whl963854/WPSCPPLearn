#ifndef SAVELOCATE_H
#define SAVELOCATE_H

#include<QList>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include"tododata.h"

class SaveLocate
{
public:
    SaveLocate();
    QList<TodoData*> initTodoDatas();
    QList<QString> initGroups();
    void saveTodoDatas(QList<TodoData*> todoDatas);
    void SaveGroups(QList<QString> groups);

    void createGroupsTable();
    void createTodoTable();
    void deleteGroupsTable();
    void deleteTodoTable();
private:
    QSqlDatabase m_database;
};

#endif // SAVELOCATE_H
