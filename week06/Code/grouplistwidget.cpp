#include "grouplistwidget.h"

#include<algorithm>
#include"linewidget.h"
#include"QFont"
#include<QMenu>
#include<QDebug>
#include<QWidgetAction>
#include<QLineEdit>

#include "groupitemwidget.h"


GroupListWidget::GroupListWidget(QWidget *parent) :
    QListWidget(parent)
{
    initGroup();
}

GroupListWidget::~GroupListWidget()
{

}
void GroupListWidget::initGroup()
{
    m_firstGroupItemWidget=new GroupItemWidget;
    m_ownGroupItemWidget=new GroupItemWidget;
    m_firstGroup=new QListWidgetItem();
    m_ownTodoGroup=new QListWidgetItem();
    m_addGroupItem=new QListWidgetItem();
    QListWidgetItem* aItem=new QListWidgetItem();

    QSize size = aItem->sizeHint();
    aItem->setSizeHint(QSize(size.width(), 30));
    LineWidget *widget=new LineWidget();
    widget->setMaximumHeight(30);

    m_firstGroup->setText("我的首页");
    m_ownTodoGroup->setText("我的待办");
    m_addGroupItem->setText("添加分组");
    m_firstGroupItemWidget->setName("我的首页");
    m_ownGroupItemWidget->setName("我的待办");


    QFont* font=new QFont;
    font->setPointSize(12);
    m_firstGroup->setFont(*font);
    m_ownTodoGroup->setFont(*font);
    m_addGroupItem->setFont(*font);

    this->addItem(m_firstGroup);
    this->addItem(m_ownTodoGroup);
    this->addItem(aItem);
    aItem->setSelected(false);
    addItem(m_addGroupItem);
    this->setItemWidget(aItem, widget);

    item(2)->setSelected(false);
    this->setStyleSheet("QListView{font:12pt;}");
}

void GroupListWidget::sortTodos(int method)
{
    m_firstGroupItemWidget->finishSort(method);
    m_ownGroupItemWidget->finishSort(method);
    int length=count()-4;
    for(int i=0;i<length;i++)
    {
        m_groupItemsWidget[i]->finishSort(method);
    }
}



GroupItemWidget* GroupListWidget::getGroupItemWidget(int index)
{
    if(index<=0)
        return m_firstGroupItemWidget;
    else if(index==1||index==2)
        return m_ownGroupItemWidget;
    else
        return m_groupItemsWidget[index-3];
}
void GroupListWidget::addGroups(QList<QString> groups)
{
    for(auto group:groups)
    {
        addGroup(group);
    }
}
int GroupListWidget::findGroup(QString groupName)
{
    int index=0;
    for(index=0;index<m_groupItemsWidget.size();index++)
    {
        if(groupName==m_groupItemsWidget[index]->getRealName())
        {
            return index;
        }
    }
    return -1;
}
void GroupListWidget::addTodoDataList(QList<TodoData*> todoDatas,QList<QString>groups)
{
    for(auto data:todoDatas)
    {
        m_firstGroupItemWidget->getTodoDataList().push_front(data);
        if(data->getTodoGroup().mid(5)=="我的待办")
        {
            m_ownGroupItemWidget->addTodoData(data);
        }
        else
        {
            for(int i=0;i<groups.size();i++)
            {
                if(m_groupItemsWidget[i]->getIdMark()+groups[i]==data->getTodoGroup())
                {
                    m_groupItemsWidget[i]->addTodoData(data);
                }
            }
        }
    }
}
void GroupListWidget::contextMenuEvent ( QContextMenuEvent * event )
{
    QListWidget::contextMenuEvent(event);
    QCursor cur=this->cursor();
    m_menu=new QMenu();
    QAction* deleteAct = new QAction(tr("删除"), this);
    QAction* renameAct = new QAction(tr("重命名"), this);
    if(this->itemAt(mapFromGlobal(QCursor::pos())) != NULL) //如果有item则添加"修改"菜单 [1]*
    {
        int curRow=row(this->itemAt(mapFromGlobal(QCursor::pos())));
        if(curRow<=2)
            return ;
        m_menu=new QMenu(this);
        deleteAct=new QAction;
        deleteAct->setText("删除");
        m_menu->addAction(deleteAct);//添加菜单项1
        m_menu->addAction(renameAct);//添加菜单项1
        connect(deleteAct, SIGNAL(triggered()), this, SLOT(deleteGroupItem()));
        connect(renameAct, SIGNAL(triggered()), this, SLOT(showRenameMenu()));
        m_menu->exec(cur.pos()); //关联到光标
    }
}


//SLOT
void GroupListWidget::deleteGroupItem()
{
    int index=currentRow();
    auto temp=getGroupItemWidget(index);
    auto groupName=temp->getRealName();
    m_groupItemsWidget.removeAt(index-3);
    QListWidgetItem* item = this->takeItem(index);
    this->removeItemWidget(item);
    delete item;
    m_firstGroupItemWidget->removeTodoData(groupName);
    setCurrentRow(0);
    emit(dropGroup());
}

void GroupListWidget::showRenameMenu()
{
    delete m_menu;
    QCursor cur=this->cursor();
    cur.setPos(cur.pos().x()-10,cur.pos().y()-10);
    m_menu=new QMenu(this);
    QWidgetAction *widgetAction = new QWidgetAction(this);
    m_lineEdit=new QLineEdit(this);
    widgetAction->setDefaultWidget(m_lineEdit);
    m_menu->addAction(widgetAction);
    connect(m_lineEdit,&QLineEdit::editingFinished,this,&GroupListWidget::renameGroupItem);
    connect(m_lineEdit,&QLineEdit::returnPressed,[&]()
    {
        m_lineEdit->clearFocus();
        renameGroupItem();
    });
    m_menu->exec(cur.pos());
}

void GroupListWidget::renameGroupItem()
{
    if(hasFocus())
        return;
    int index=currentRow();
    if(index<0)
        return;
    QString name=m_lineEdit->text();
    auto datas=getGroupItemWidget(currentRow())->getTodoDataList();
    for(auto& data:datas)
    {
        data->setTodoGroup(getGroupItemWidget(currentRow())->getIdMark()+name);
    }
    getGroupItemWidget(currentRow())->setName(name);
    emit(groupNameChanged());
}
void GroupListWidget::addGroup(QString groupName)
{
    GroupItemWidget* itemWidget=new GroupItemWidget();
    m_groupItemsWidget.push_back(itemWidget);
    itemWidget->setName(groupName);
    QListWidgetItem*item=new QListWidgetItem;
    QFont* font=new QFont;
    font->setPointSize(12);
    item->setFont(*font);
    QSize size = item->sizeHint();
    item->setSizeHint(QSize(size.width(), 60));
    this->insertItem(this->count()-1,item);
    this->setItemWidget(item,itemWidget);
    itemWidget->setFocus();
}
