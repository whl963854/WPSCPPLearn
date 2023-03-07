#ifndef TODODATA_H
#define TODODATA_H

#include<QString>

class TodoData
{
public:
    TodoData();
    //TodoData(TodoData& data);
    void setDeadline(QString str);
    void setNoticion(QString str);
    void setDescription(QString str);
    void setRemark(QString str);
    void setLocation(QString str);
    void setTodoName(QString str);
    void setTodoGroup(QString str);
    void setTodoRepeat(QString str);
    void setPri(int pri);
    void setFinish(bool finish);
    QString getDeadline();
    QString getNoticion();
    QString getDescription();
    QString getRemark();
    QString getLocation();
    QString getTodoName();
    QString getTodoGroup();
    QString getTodoRepeat();
    int getPri();
    bool getFinish();


private:
    bool isFinish;
    QString m_deadline;
    QString m_noticion;
    QString m_description;
    QString m_remark;
    QString m_locate;
    QString m_todoName;
    QString m_todoGroup;
    QString m_todoRepeat;

    //0--无优先级   1--低优先级  2--中优先级  3--高优先级
    int m_priority;
};

#endif // TODODATA_H
