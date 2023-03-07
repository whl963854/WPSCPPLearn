#include "groupitemwidget.h"
#include "ui_groupitemwidget.h"
#include "todoutils.h"
#include<algorithm>

GroupItemWidget::GroupItemWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GroupListItemWidget)
{
    ui->setupUi(this);
    m_groupLabel=ui->nameLabel;
    m_idMark=TodoUtils::intToQString(5);
}

GroupItemWidget::~GroupItemWidget()
{
    delete ui;
}
void GroupItemWidget::setName(QString name)
{
    ui->nameLabel->setText(name);
}
QString GroupItemWidget::getName()
{
    return ui->nameLabel->text();
}
void GroupItemWidget::addTodoData(TodoData *data)
{
    m_todoDatas.push_front(data);
}
QList<TodoData*>& GroupItemWidget::getTodoDataList()
{
    return m_todoDatas;
}
void GroupItemWidget::setTodoName(int index, QString name)
{
    m_todoDatas[index]->setTodoName(TodoUtils::intToQString(5)+name);
}

void GroupItemWidget::removeTodoData(int index)
{
    m_todoDatas.removeAt(index);
}

void GroupItemWidget::removeTodoData(QString str)
{
    int ii=0;
    while(ii<m_todoDatas.size())
    {
        if(m_todoDatas[ii]->getTodoGroup()==str)
        {
            m_todoDatas.removeAt(ii);
        }
        else
        {
            ii++;
        }
    }
}

TodoData* GroupItemWidget::getTodoData(int index)
{
    return m_todoDatas[index];
}
void GroupItemWidget::finishTodo(int index)
{
    auto data=m_todoDatas[index];
    m_todoDatas.removeAt(index);
    m_todoDatas.push_back(data);
}
void GroupItemWidget::recoverTodo(int index)
{
    auto data=m_todoDatas[index];
    m_todoDatas.removeAt(index);
    m_todoDatas.push_front(data);
}

QString GroupItemWidget::getIdMark()
{
    return m_idMark;
}
void GroupItemWidget::deleteTodoItem(int index)
{
    m_todoDatas.removeAt(index);
}

int GroupItemWidget::getIndex(QString todoName)
{
    for(int i=0;i<m_todoDatas.size();i++)
    {
        if(m_todoDatas[i]->getTodoName()==todoName)
        {
            return i;
        }
    }
    return -1;
}

QString GroupItemWidget::getRealName()
{
    return m_idMark+m_groupLabel->text();
}

void GroupItemWidget::finishSort(int method)
{
    if(method==0)
    {
         std::sort(m_todoDatas.begin(),m_todoDatas.end(),finishCmp);
    }
    else if(method ==1)
    {
         std::sort(m_todoDatas.begin(),m_todoDatas.end(),deadlineCmp);
    }
    else if(method==2)
    {
         std::sort(m_todoDatas.begin(),m_todoDatas.end(),priCmp);
    }
    else if(method==3)
    {
         std::sort(m_todoDatas.begin(),m_todoDatas.end(),nameCmp);
    }

}

bool GroupItemWidget::finishCmp(TodoData *a,TodoData *b)
{
    return a->getFinish()<b->getFinish();
}

bool GroupItemWidget::deadlineCmp(TodoData *a, TodoData *b)
{

    if(a->getFinish()==b->getFinish())
    {
        return a->getDeadline()<b->getDeadline();
    }
    else
    {
        return a->getFinish()<b->getFinish();
    }
}

bool GroupItemWidget::priCmp(TodoData *a, TodoData *b)
{
    if(a->getFinish()==b->getFinish())
    {
        return a->getPri()>b->getPri();
    }
    else
    {
        return a->getFinish()<b->getFinish();
    }
}

bool GroupItemWidget::nameCmp(TodoData *a, TodoData *b)
{
    std::string aa=a->getTodoName().mid(5).toLocal8Bit().toStdString();
    std::string bb=b->getTodoName().mid(5).toLocal8Bit().toStdString();
    if(a->getFinish()==b->getFinish())
    {
        return aa<bb;
    }
    else
    {
        return a->getFinish()<b->getFinish();
    }
}


