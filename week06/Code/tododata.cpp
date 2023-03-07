#include "tododata.h"

TodoData::TodoData()
{
    m_deadline="";
    m_noticion="";
    m_description="";
    m_remark="";
    m_locate="";
    m_priority=0;
    m_todoName="";
    m_todoGroup="";
    m_todoRepeat="";
}

void TodoData::setDeadline(QString str)
{
    m_deadline=str;
}
void TodoData::setNoticion(QString str)
{
    m_noticion=str;
}
void TodoData::setDescription(QString str)
{
    m_description=str;
}
void TodoData::setRemark(QString str)
{
    m_remark=str;
}
void TodoData::setLocation(QString str)
{
    m_locate=str;
}
void TodoData::setPri(int pri)
{
    m_priority=pri;
}

void TodoData::setFinish(bool finish)
{
    this->isFinish=finish;
}
void TodoData::setTodoName(QString str)
{
    m_todoName=str;
}
void TodoData::setTodoRepeat(QString str)
{
    m_todoRepeat=str;
}
void TodoData::setTodoGroup(QString str)
{
    m_todoGroup=str;
}
QString TodoData::getDeadline()
{
    return m_deadline;
}
QString TodoData::getNoticion()
{
    return m_noticion;
}
QString TodoData::getDescription()
{
    return m_description;
}
QString TodoData::getRemark()
{
    return m_remark;
}
QString TodoData::getLocation()
{
    return m_locate;
}
int TodoData::getPri()
{
    return m_priority;
}

bool TodoData::getFinish()
{
    return isFinish;
}
QString TodoData::getTodoName()
{
    return m_todoName;
}
QString TodoData::getTodoGroup()
{
    return m_todoGroup;
}
QString TodoData::getTodoRepeat()
{
    return m_todoRepeat;
}

