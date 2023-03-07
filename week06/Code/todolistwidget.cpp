#include "todolistwidget.h"


#include"QListWidgetItem"
#include<QMenu>
#include<QWidgetAction>
#include<QDebug>
#include"todoitemwidget.h"
#include"todolist.h"
#include "itemgroupwidget.h"
#include "todoutils.h"


TodoListWidget::TodoListWidget(QWidget *parent) :
    QListWidget(parent)
{

    //设置选择模式为单选
    this->setSelectionMode(QAbstractItemView::SingleSelection);

    //禁用拖拽
    this->setDragEnabled(false);

    //设置拖放
    this->viewport()->setAcceptDrops(false);

    //设置显示将要被放置的位置
    this->setDropIndicatorShown(true);

    //设置拖放模式为移动项目，如果不设置，默认为复制项目
    this->setDragDropMode(QAbstractItemView::InternalMove);

    setMovement(QListView::Static);
}

TodoListWidget::~TodoListWidget()
{
    todoItemsClear();
}

//加入item项
TodoItemWidget* TodoListWidget::addTodoItem(QString name,QString group)
{
    QListWidgetItem* aItem=new QListWidgetItem();
    QSize size = aItem->sizeHint();
    aItem->setSizeHint(QSize(size.width(), 100));

    TodoItemWidget *widget=new TodoItemWidget(this);
    widget->initItem(name,group);
    m_todoItemWidgets.push_front(widget);

    this->addItem(aItem);
    this->setItemWidget(aItem, widget);
    return widget;
}
TodoItemWidget* TodoListWidget::addTodoItem(TodoData data)
{
    QListWidgetItem* aItem=new QListWidgetItem();
    QSize size = aItem->sizeHint();
    aItem->setSizeHint(QSize(size.width(), 100));

    TodoItemWidget *widget=new TodoItemWidget(this);
    m_todoItemWidgets.push_front(widget);
    widget->initItem(data);

    this->addItem(aItem);
    this->setItemWidget(aItem, widget);
    connect(widget->getDeadlineBtn(),&QToolButton::clicked,[=]()
    {
        this->setCurrentItem(aItem);
    });
    connect(widget->getNoticeToolBtn(),&QToolButton::clicked,[=]()
    {
        this->setCurrentItem(aItem);
    });
    connect(widget->getRepeatToolBtn(),&QToolButton::clicked,[=]()
    {
        this->setCurrentItem(aItem);
    });
//    connect(widget->getTodoNameToolBtn(),&QToolButton::clicked,[=](){
//        showRenameMenu();
//    });
    connect(widget,&TodoItemWidget::finishStateChange,this,&TodoListWidget::emitFinishTodo);
    return widget;
}


TodoItemWidget* TodoListWidget::insertTodoItem(int index,TodoData data)
{
    QListWidgetItem* aItem=new QListWidgetItem();
    QSize size = aItem->sizeHint();
    aItem->setSizeHint(QSize(size.width(), 100));

    TodoItemWidget *widget=new TodoItemWidget(this);
    m_todoItemWidgets.push_back(widget);
    widget->initItem(data);

    this->insertItem(index,aItem);
    this->setItemWidget(aItem, widget);
    connect(widget,&TodoItemWidget::finishStateChange,this,&TodoListWidget::emitFinishTodo);
    return widget;
}

//删除item项
void TodoListWidget::todoItemsClear()
{
    int curRow=this->count();
    for(int i=curRow-1;i>=0;i--)
    {
        deleteTodoItem(i);
    }
    clear();
}
void TodoListWidget::removeTodoItem(int index)
{
    m_todoItemWidgets.removeAt(index);
}
void TodoListWidget::deleteTodoItem(int index)
{
    if(index<0||index>=m_todoItemWidgets.size())
        return;
    auto widget=m_todoItemWidgets[index];
    delete widget;
    this->m_todoItemWidgets.removeAt(index);
    QListWidgetItem* item = this->item(index);
    this->removeItemWidget(item);
    delete item;
}


//是否完成之后的操作
void TodoListWidget::recoverTodoItem(int index)
{
    TodoItemWidget* item=m_todoItemWidgets[index];
    m_todoItemWidgets.removeAt(index);
    m_todoItemWidgets.push_front(item);
}

//右键菜单相关设置
void TodoListWidget::contextMenuEvent ( QContextMenuEvent * event )
{
    QListWidget::contextMenuEvent(event);
    QCursor cur=this->cursor();
    m_menu=new QMenu(this);
    m_deleteAct = new QAction(tr("删除"), this);
    QAction* rename= new QAction(tr("重命名"), this);
    if(this->itemAt(mapFromGlobal(QCursor::pos())) != NULL) //如果有item则添加"修改"菜单 [1]*
    {
        m_menu=new QMenu(this);
        m_deleteAct=new QAction;
        m_deleteAct->setText("删除");
        rename->setText("重命名");
        m_menu->addAction(m_deleteAct);//添加菜单项1
        m_menu->addAction(rename);//添加菜单项2
        connect(m_deleteAct, SIGNAL(triggered()), this, SLOT(deleteTodoItem()));
        connect(rename,&QAction::triggered,this,&TodoListWidget::showRenameMenu);
        m_menu->exec(cur.pos()); //关联到光标
    }
}
void TodoListWidget::showRenameMenu()
{
    delete m_menu;
    QCursor cur=this->cursor();
    cur.setPos(cur.pos().x()-10,cur.pos().y()-10);
    m_menu=new QMenu(this);
    QWidgetAction *widgetAction = new QWidgetAction(this);
    m_lineEdit=new QLineEdit(this);
    widgetAction->setDefaultWidget(m_lineEdit);
    m_menu->addAction(widgetAction);
    connect(m_lineEdit,&QLineEdit::editingFinished,this,&TodoListWidget::renameTodoItem);
    connect(m_lineEdit,&QLineEdit::returnPressed,[&]()
    {
        m_lineEdit->clearFocus();
        renameTodoItem();
    });
    m_menu->exec(cur.pos());
}

//get
QList<TodoItemWidget *> TodoListWidget::getTodoItemWidgets()
{
    return m_todoItemWidgets;
}
TodoItemWidget* TodoListWidget::getTodoItemWidget(int index)
{
    return  m_todoItemWidgets[index];
}
int TodoListWidget::getIndex(QString name)
{
    for(int i=0;i<m_todoItemWidgets.size();i++)
    {
        if(m_todoItemWidgets[i]->getName()==name)
        {
            return i;
        }
    }
    return -1;
}

void TodoListWidget::addTodoGroup(QString name)
{
    ItemGroupWidget* widget=new ItemGroupWidget;
    QListWidgetItem* aItem=new QListWidgetItem();
    QSize size = aItem->sizeHint();
    aItem->setSizeHint(QSize(size.width(), 100));
    widget->setName(name);
    this->addItem(aItem);
    this->setItemWidget(aItem, widget);
    qDebug()<<"caonimacaonimacaonimacaonima"<<endl;
}

void TodoListWidget::firstPageFresh(QList<TodoData *> todoDatas, bool hideFinish)
{
    m_count1=2;
    m_count2=3;
    m_count3=4;
    addTodoGroup("已逾期");
    addTodoGroup("以后");
    addTodoGroup("未来七天");
    addTodoGroup("未安排");
    for(int i=todoDatas.size()-1;i>=0;i--)
    {
       auto data=todoDatas[i];
       if(hideFinish&&data->getFinish()==true)
       {
           continue;
       }
       else
       {
            addTodoFirstPageItem(todoDatas[i]);
       }
    }

}
TodoItemWidget *TodoListWidget::addTodoFirstPageItem(TodoData* data)
{
    QListWidgetItem* aItem=new QListWidgetItem(nullptr);
    TodoItemWidget *widget=new TodoItemWidget();
    QSize size = aItem->sizeHint();
    aItem->setSizeHint(QSize(size.width(), 100));
    QDate date=date.currentDate();
    QDate currentDate=TodoUtils::strToDate(data->getDeadline());
    if(data->getDeadline()=="")
    {
        m_todoItemWidgets.insert(0,widget);
        widget->initItem(*data);
        this->insertItem(2,aItem);
        this->setItemWidget(aItem, widget);
        connect(widget,&TodoItemWidget::finishStateChange,this,&TodoListWidget::emitFinishTodo);
        m_count1++;
        m_count2++;
        m_count3++;
    }
    else if(currentDate.daysTo(date)<7&&currentDate.daysTo(date)>=0)
    {
         m_todoItemWidgets.insert(m_count1-2,widget);
         widget->initItem(*data);
         this->insertItem(m_count1,aItem);
         this->setItemWidget(aItem, widget);
         connect(widget,&TodoItemWidget::finishStateChange,this,&TodoListWidget::emitFinishTodo);
         m_count2++;
         m_count3++;
    }
    else if(currentDate.daysTo(date)>7)
    {

        m_todoItemWidgets.insert(m_count2-3,widget);
        widget->initItem(*data);
        this->insertItem(m_count2,aItem);
        this->setItemWidget(aItem, widget);
        connect(widget,&TodoItemWidget::finishStateChange,this,&TodoListWidget::emitFinishTodo);
        m_count3++;
    }
    else
    {
        m_todoItemWidgets.insert(m_count3-4,widget);
        widget->initItem(*data);
        this->insertItem(m_count3,aItem);
        this->setItemWidget(aItem, widget);
        connect(widget,&TodoItemWidget::finishStateChange,this,&TodoListWidget::emitFinishTodo);
    }
    return widget;

}

//SLOT
//删除，重命名，完成
void TodoListWidget::deleteTodoItem()
{
    auto item=itemAt(mapFromGlobal(QCursor::pos()));
    int index=row(item);
    if(index<0)
        return;
    QString name=getTodoItemWidget(index)->getName();
    emit(delTodoItem(name,index));
}
void TodoListWidget::renameTodoItem()
{
    if(hasFocus())
        return;
    auto item=itemAt(mapFromGlobal(QCursor::pos()));
    int index=row(item);
    if(index<0)
        return;
    QString name=m_lineEdit->text();
    emit(renameTodo(index,name));
    delete m_menu;
}
void TodoListWidget::emitFinishTodo(TodoItemWidget* temp)
{
    int length=count();
    for(int i=0;i<length;i++)
    {
        if(m_todoItemWidgets[i]==temp)
        {

            emit(finishTodo(i,temp->getFinish()));
            break;
        }
    }
}


