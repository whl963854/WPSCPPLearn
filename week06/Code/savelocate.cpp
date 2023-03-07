#include "savelocate.h"
#include<groupitemwidget.h>
#include<QDebug>
#include"tododata.h"
SaveLocate::SaveLocate()
{

    if (QSqlDatabase::contains("qt_sql_default_connection"))
    {
        m_database = QSqlDatabase::database("qt_sql_default_connection");
    }
    else
    {
        m_database = QSqlDatabase::addDatabase("QSQLITE");
        m_database.setDatabaseName("MyDataBase.db");
        m_database.setUserName("whl");
        m_database.setPassword("123456");
    }
    if (!m_database.open())
    {
        qDebug() << "Error: Failed to connect database." << m_database.lastError();
    }

    createTodoTable();
    createGroupsTable();
}
QList<TodoData*> SaveLocate::initTodoDatas()
{
    QSqlQuery sqlQuery;
    QString getTodoDatas = "select * from  todoDataList order by id desc";
    sqlQuery.prepare(getTodoDatas);
    if(!sqlQuery.exec())
    {
        qDebug() << sqlQuery.lastError();
    }
    QList<TodoData*>todoDatas;
    while(sqlQuery.next())
    {
        TodoData*todoData=new TodoData;
        todoData->setDeadline(sqlQuery.value(1).toString());
        todoData->setNoticion(sqlQuery.value(2).toString());
        todoData->setDescription(sqlQuery.value(3).toString());
        todoData->setRemark(sqlQuery.value(4).toString());
        todoData->setLocation(sqlQuery.value(5).toString());
        todoData->setTodoName(sqlQuery.value(6).toString());
        todoData->setTodoGroup(sqlQuery.value(7).toString());
        todoData->setTodoRepeat(sqlQuery.value(8).toString());
        todoData->setPri(sqlQuery.value(9).toInt());
        todoData->setFinish(sqlQuery.value(10).toBool());
        todoDatas.push_back(todoData);

    }
    return todoDatas;
}
QList<QString> SaveLocate::initGroups()
{
    QSqlQuery sqlQuery;
    QString getTodoDatas = "select * from  groupsTable order by id";
    sqlQuery.prepare(getTodoDatas);
    if(!sqlQuery.exec())
    {
        qDebug() << sqlQuery.lastError();
    }
    QList<QString>groups;
    while(sqlQuery.next())
    {
        auto group=sqlQuery.value(1).toString();
        groups.push_front(group);
    }
    return groups;
}
void SaveLocate::SaveGroups(QList<QString> groups)
{
    deleteGroupsTable();
    createGroupsTable();
    QSqlQuery sqlQuery;
    QString saveGroups = "insert into groupsTable(id,groupName)values(?,?)";
    int count=0;
    for(auto groupName:groups)
    {
        sqlQuery.clear();
        sqlQuery.prepare(saveGroups);
        sqlQuery.addBindValue(count++);
        sqlQuery.addBindValue(groupName);
        if(!sqlQuery.exec())
        {
            qDebug() << "Error: Fail to save groupsTable." << sqlQuery.lastError();
        }
    }
}
void SaveLocate::saveTodoDatas(QList<TodoData*> todoDatas)
{
    deleteTodoTable();
    createTodoTable();
    QSqlQuery sqlQuery;
    QString saveTodoData = "insert into todoDataList(id,deadline,"
                           "notition,description,remark,locate,"
                           "todoName,todoGroup,repeat,pri,isFinish) "
                           "values(?,?,?,?,?,?,?,?,?,?,?)";
    int count=0;
    for(auto tododata:todoDatas)
    {
        sqlQuery.clear();
        sqlQuery.prepare(saveTodoData);
        sqlQuery.addBindValue(count++);
        sqlQuery.addBindValue(tododata->getDeadline());
        sqlQuery.addBindValue(tododata->getNoticion());
        sqlQuery.addBindValue(tododata->getDescription());
        sqlQuery.addBindValue(tododata->getRemark());
        sqlQuery.addBindValue(tododata->getLocation());
        sqlQuery.addBindValue(tododata->getTodoName());
        sqlQuery.addBindValue(tododata->getTodoGroup());
        sqlQuery.addBindValue(tododata->getTodoRepeat());
        sqlQuery.addBindValue(tododata->getPri());
        sqlQuery.addBindValue(tododata->getFinish());
        if(!sqlQuery.exec())
        {
            qDebug() << "Error: Fail to save table." << sqlQuery.lastError();
        }
    }
}

void SaveLocate::createGroupsTable()
{
    QSqlQuery sqlQuery;
    QString createGroupsTable=  "create table if not exists "
                                 "groupsTable (id int primary key, "
                                 "groupName varchar(30))";
    sqlQuery.prepare(createGroupsTable);
    if(!sqlQuery.exec())
    {
        qDebug() << "Error: Fail to create groupsTable." << sqlQuery.lastError();
    }
}
void SaveLocate::createTodoTable()
{
    QSqlQuery sqlQuery;
    QString createTodoDataSql =  "create table if not exists "
                                 "todoDataList (id int primary key, "
                                 "deadline varchar(30), "
                                 "notition varchar(30),"
                                 "description varchar(30),"
                                 "remark varchar(30),"
                                 "locate varchar(30),"
                                 "todoName varchar(30),"
                                 "todoGroup varchar(30),"
                                 "repeat varchar(30),"
                                 "pri int,isFinish bool)";
    sqlQuery.prepare(createTodoDataSql);
    if(!sqlQuery.exec())
    {
        qDebug() << "Error: Fail to create table." << sqlQuery.lastError();
    }
}
void SaveLocate::deleteGroupsTable()
{
    QSqlQuery sqlQuery;
    QString groupsTable="drop table groupsTable";
    sqlQuery.prepare(groupsTable);
    if(!sqlQuery.exec())
    {
        qDebug() << "Error: Fail to delete groupsTable." << sqlQuery.lastError();
    }
}
void SaveLocate::deleteTodoTable()
{
    QSqlQuery sqlQuery;
    QString reTodoData="drop table todoDataList";
    sqlQuery.prepare(reTodoData);
    if(!sqlQuery.exec())
    {
        qDebug() << "Error: Fail to delete table." << sqlQuery.lastError();
    }
}
