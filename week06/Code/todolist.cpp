#include "todolist.h"
#include "ui_todolist.h"

#include<qedit.h>
#include<QLineEdit>
#include<QDebug>
#include<QPushButton>
#include<QLabel>
#include<QString>
#include<QFrame>
#include<QCheckBox>
#include<QListWidget>
#include<QSpacerItem>
#include<QToolButton>
#include<QScrollBar>
#include<QMouseEvent>
#include<QVBoxLayout>
#include<QMenu>

#include "savelocate.h"
#include"newlineedit.h"
#include"todoitemwidget.h"
#include"newcalendar.h"
#include"linewidget.h"
#include"grouplistwidget.h"
#include"groupitemwidget.h"
#include"savelocate.h"
#include "todoutils.h"
#include "itemgroupwidget.h"

TodoList::TodoList(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::todolist)
{
    ui->setupUi(this);
    init();
    showMaximized();

    connect(ui->addNewTodoEdit, &NewLineEdit::clicked,ui->addNewTodoEdit, &NewLineEdit::clearEdit);
    connect(ui->addNewTodoEdit, &NewLineEdit::editingFinished, this, &TodoList::addTodoItem);
    connect(ui->closeBtn,&QPushButton::clicked,ui->dockWidget,&ToDoItemSets::hide);
    connect(ui->addLocationBtn,&QToolButton::clicked,ui->remarkLineEdit,&QLineEdit::selectAll);
    connect(ui->groupListWidget,&QListWidget::itemPressed,this,&TodoList::groupChange);
    connect(ui->todoListWidget,&TodoListWidget::currentRowChanged,this,&TodoList::updateDockWidget);
    connect(m_addNewTodoDialog,&AddNewGroupDialog::confirm,ui->groupListWidget,&GroupListWidget::addGroup);

    connect(ui->groupChange,&QPushButton::clicked,this,&TodoList::showMethodChange);
    connect(m_groupListWidget,&GroupListWidget::groupNameChanged,this,&TodoList::refresh);
    connect(ui->refreshBtn,&QToolButton::clicked,this,&TodoList::refresh);
    connect(ui->hideFinishedBtn,&QPushButton::clicked,this,&TodoList::hideFinishedTodos);

    connect(ui->todoListWidget,&TodoListWidget::renameTodo,this,&TodoList::renameTodoItem);
    connect(ui->todoListWidget,&TodoListWidget::delTodoItem,this,&TodoList::deleteTodoItem);
    connect(ui->todoListWidget,&TodoListWidget::finishTodo,this,&TodoList::finishStateChange);
    connect(m_groupListWidget,&GroupListWidget::dropGroup,this,&TodoList::refresh);


    //????????????????????????
    connect(this,&TodoList::closeTodoWidget,this,&TodoList::saveTodoData);
    connect(this,&TodoList::closeTodoWidget,this,&TodoList::saveGroups);
    connect(ui->refreshBtn,&QToolButton::clicked,this,&TodoList::saveTodoData);
    connect(ui->refreshBtn,&QToolButton::clicked,this,&TodoList::saveGroups);


    //????????????????????????
    connect(ui->deadLineBtn,&QToolButton::clicked,m_deadlineCalendar,&DeadLineCalendar::show);
    connect(m_deadlineCalendar,&DeadLineCalendar::confirm,this,&TodoList::setDeadline);

    connect(ui->setNoticeBtn,&QToolButton::clicked,m_noticeCalendar,&NoticeCalendar::show);
    connect(m_noticeCalendar,&NoticeCalendar::confirm,this,&TodoList::setNotice);

    connect(ui->priComboBox,static_cast<void (QComboBox::*)(const QString &)>
            (&QComboBox::currentIndexChanged),this,&TodoList::setPri);

    connect(ui->addLocationBtn,&QToolButton::clicked,this,&TodoList::locateChange);
    connect(ui->locationLineEdit,&QLineEdit::editingFinished,this,&TodoList::setLocation);

    connect(ui->addRemarkBtn,&QToolButton::clicked,this,&TodoList::remarkChange);
    connect(ui->remarkLineEdit,&QLineEdit::editingFinished,this,&TodoList::setRemark);

    connect(ui->addDescriptionBtn,&QToolButton::clicked,this,&TodoList::descriptionChange);
    connect(ui->descriptionLineEdit,&QLineEdit::editingFinished,this,&TodoList::setDescription);

    //????????????????????????
    connect(ui->deadlineCloseBtn,&QPushButton::clicked,this,&TodoList::deleteDeadline);
    connect(ui->noticeCloseBtn,&QPushButton::clicked,this,&TodoList::deleteNotice);
    connect(ui->remarkCloseBtn,&QPushButton::clicked,this,&TodoList::deleteRemark);
    connect(ui->locationCloseBtn,&QPushButton::clicked,this,&TodoList::deleteLocation);
    connect(ui->descriptionCloseBtn,&QPushButton::clicked,this,&TodoList::deleteDescription);
}

void TodoList::addTodoItem()
{
    int groupIndex=m_groupListWidget->row(ui->groupListWidget->currentItem());
    if(groupIndex==2)
        return;
    QString todoName=ui->addNewTodoEdit->text();
    TodoData* todoData=new TodoData;
    todoData->setFinish(false);
    TodoItemWidget *widget;
    if(groupIndex<=1)
    {
        todoData->setTodoName(TodoUtils::intToQString(5)+todoName);
        todoData->setTodoGroup("00001????????????");
        widget = ui->todoListWidget->addTodoItem(*todoData);
        connect(widget->getDeadlineBtn(),&QToolButton::clicked,m_deadlineCalendar,&DeadLineCalendar::show);
        connect(widget->getNoticeToolBtn(),&QToolButton::clicked,m_noticeCalendar,&NoticeCalendar::show);
        connect(widget->getRepeatToolBtn(),&QToolButton::clicked,m_deadlineCalendar,&DeadLineCalendar::show);

        ui->groupListWidget->getGroupItemWidget(0)->addTodoData(todoData);
        ui->groupListWidget->getGroupItemWidget(1)->addTodoData(todoData);
    }
    else
    {
        GroupItemWidget * nowGroupItem =ui->groupListWidget->getGroupItemWidget(groupIndex);
        todoData->setTodoName(TodoUtils::intToQString(5)+todoName);
        todoData->setTodoGroup(nowGroupItem->getRealName());
        todoData->setFinish(false);
        widget = ui->todoListWidget->addTodoItem(*todoData);
        connect(widget->getDeadlineBtn(),&QToolButton::clicked,m_deadlineCalendar,&DeadLineCalendar::show);
        connect(widget->getNoticeToolBtn(),&QToolButton::clicked,m_noticeCalendar,&NoticeCalendar::show);
        connect(widget->getRepeatToolBtn(),&QToolButton::clicked,m_deadlineCalendar,&DeadLineCalendar::show);
        nowGroupItem->addTodoData(todoData);
        ui->groupListWidget->getGroupItemWidget(0)->addTodoData(todoData);
    }
    ui->addNewTodoEdit->initLineEdit();
    connect(widget, &TodoItemWidget::clicked, this, &TodoList::updateDockWidget);

}
void TodoList::init()
{
    //??????????????????
    m_todoListWidget=ui->todoListWidget;
    m_hideFinish=0;
    m_currentGroupMethod=0;
    QAction *deadlineSort = new QAction("????????????????????????", this);
    QAction *nameSort= new QAction("??????????????????", this);
    QAction *priSort = new QAction("?????????????????????",this);
    QMenu *todoMenu = new QMenu(this);

    todoMenu->addAction(deadlineSort);
    todoMenu->addAction(nameSort);
    todoMenu->addAction(priSort);
    todoMenu->setTitle("Settings");
    ui->sortBtn->setMenu(todoMenu);
    ui->sortBtn->setStyleSheet("QPushButton::menu-indicator{image:none;}");

    connect(deadlineSort,&QAction::triggered,this,&TodoList::deadlineSort);
    connect(nameSort,&QAction::triggered,this,&TodoList::todoNameSort);
    connect(priSort,&QAction::triggered,this,&TodoList::priSort);

    //????????????
    m_deadlineCalendar=new DeadLineCalendar;
    m_noticeCalendar=new NoticeCalendar;
    m_addNewTodoDialog=new AddNewGroupDialog;
    m_groupListWidget=ui->groupListWidget;
    QPalette palette;
    palette.setColor(QPalette::Text, QColor(30,255,30));
    ui->addNewTodoEdit->setPalette(palette);
    ui->addNewTodoEdit->setPlaceholderText("????????????????????????????????????");

    //???????????????
    SaveLocate *save=new SaveLocate;
    auto groups=save->initGroups();
    auto todoDatas=save->initTodoDatas();
    m_groupListWidget->addGroups(groups);
    m_groupListWidget->addTodoDataList(todoDatas,groups);

    //?????????????????????????????????
    beautify();
    refresh();
}

//??????group
void TodoList::groupChange(QListWidgetItem* item)
{
    int index = m_groupListWidget->row(item);
    if(index==m_groupListWidget->count()-1)
    {
        this->m_addNewTodoDialog->show();
        return ;
    }
    else if(index==2)
    {
        return ;
    }
    else
    {
        ui->dockWidget->hide();
        refresh();
    }

}

void TodoList::firstPageFresh()
{
    GroupItemWidget * nowGroupItem =ui->groupListWidget->getGroupItemWidget(0);
    QList<TodoData*>todoDatas=nowGroupItem->getTodoDataList();
    ui->todoListWidget->firstPageFresh(todoDatas,m_hideFinish);
}




//???????????????
void TodoList::beautify()
{
    ui->todoListWidget->verticalScrollBar()->setStyleSheet("QScrollBar:vertical"
                        "{width:8px;background:rgba(0,0,0,0%);margin:0px,0px,0px,0px;"
                        "padding-top:9px;padding-bottom:9px;}"
                        "QScrollBar::handle:vertical{width:8px;background:rgba(0,0,0,25%);"
                        "border-radius:4px;min-height:20;}"
                        "QScrollBar::handle:vertical:hover{width:8px;background:rgba(0,0,0,50%);"
                        "border-radius:4px;min-height:20;}"
                        "QScrollBar::add-line:vertical{height:9px;width:8px;"
                        "border-image:url(:/images/a/3.png);subcontrol-position:bottom;}"
                        "QScrollBar::sub-line:vertical{height:9px;width:8px;"
                        "border-image:url(:/images/a/1.png);subcontrol-position:top;}"
                        "QScrollBar::add-line:vertical:hover{height:9px;width:8px;"
                        "border-image:url(:/images/a/4.png);subcontrol-position:bottom;}"
                        "QScrollBar::sub-line:vertical:hover{height:9px;width:8px;"
                        "border-image:url(:/images/a/2.png);subcontrol-position:top;}"
                        "QScrollBar::add-page:vertical,QScrollBar::sub-page:vertical{"
                        "background:rgba(0,0,0,10%);border-radius:4px;}");
    ui->groupListWidget->verticalScrollBar()->setStyleSheet("QScrollBar:vertical"
                        "{width:8px;background:rgba(0,0,0,0%);margin:0px,0px,0px,0px;"
                        "padding-top:9px;padding-bottom:9px;}"
                        "QScrollBar::handle:vertical{width:8px;background:rgba(0,0,0,25%);"
                        "border-radius:4px;min-height:20;}"
                        "QScrollBar::handle:vertical:hover{width:8px;background:rgba(0,0,0,50%);"
                        "border-radius:4px;min-height:20;}"
                        "QScrollBar::add-line:vertical{height:9px;width:8px;"
                        "border-image:url(:/images/a/3.png);subcontrol-position:bottom;}"
                        "QScrollBar::sub-line:vertical{height:9px;width:8px;"
                        "border-image:url(:/images/a/1.png);subcontrol-position:top;}"
                        "QScrollBar::add-line:vertical:hover{height:9px;width:8px;"
                        "border-image:url(:/images/a/4.png);subcontrol-position:bottom;}"
                        "QScrollBar::sub-line:vertical:hover{height:9px;width:8px;"
                        "border-image:url(:/images/a/2.png);subcontrol-position:top;}"
                        "QScrollBar::add-page:vertical,QScrollBar::sub-page:vertical{"
                        "background:rgba(0,0,0,10%);border-radius:4px;}");
}


//??????????????????
void TodoList::closeEvent ( QCloseEvent * e )
{
    QWidget::closeEvent(e);
    emit(closeTodoWidget());
}

TodoList::~TodoList()
{
    delete ui;
}

//SLOTS

//??????????????????
void TodoList::deadlineSort()
{
    m_groupListWidget->sortTodos(GroupListWidget::method::Deadline);
    refresh();
}
void TodoList::priSort()
{
    m_groupListWidget->sortTodos(GroupListWidget::method::Priority);
    refresh();
}
void TodoList::todoNameSort()
{
    m_groupListWidget->sortTodos(GroupListWidget::method::TodoName);
    refresh();
}




//??????????????????
void TodoList::deleteTodoItem()
{
    int groupIndex=m_groupListWidget->currentRow();
    auto todoDatas=ui->groupListWidget->getGroupItemWidget(groupIndex)->getTodoDataList();
    int curIndex=ui->todoListWidget->currentRow();
    auto todoName=todoDatas[curIndex]->getTodoName();
    auto todoGroupName=todoDatas[curIndex]->getTodoGroup();
    if(groupIndex==0)
    {
        if(todoGroupName=="00001????????????")
        {
            ui->groupListWidget->getGroupItemWidget(0)->deleteTodoItem(curIndex);
            int dataItem=m_groupListWidget->getGroupItemWidget(1)->getIndex(todoName);
            ui->groupListWidget->getGroupItemWidget(1)->deleteTodoItem(dataItem);
        }
        else{
            ui->groupListWidget->getGroupItemWidget(0)->deleteTodoItem(curIndex);
            int firstIndex=m_groupListWidget->findGroup(todoGroupName);
            int dataItem=m_groupListWidget->getGroupItemWidget(firstIndex+3)->getIndex(todoName);
            m_groupListWidget->getGroupItemWidget(firstIndex+3)->deleteTodoItem(dataItem);
        }
    }
    else
    {
        ui->groupListWidget->getGroupItemWidget(groupIndex)->deleteTodoItem(curIndex);
        int dataIndex=m_groupListWidget->getGroupItemWidget(0)->getIndex(todoName);
        ui->groupListWidget->getGroupItemWidget(0)->deleteTodoItem(dataIndex);
    }
    refresh();
}
void TodoList::renameTodoItem(int index,QString name)
{
    int groupIndex=m_groupListWidget->currentRow();
    auto todoDatas=ui->groupListWidget->getGroupItemWidget(groupIndex)->getTodoDataList();
    ui->groupListWidget->getGroupItemWidget(groupIndex)->setTodoName(index,name);
    refresh();
}

//???????????????
void TodoList::hideFinishedTodos()
{
    if(ui->hideFinishedBtn->text()=="???????????????")
    {
        ui->hideFinishedBtn->setText("???????????????");
    }
    else
    {
        ui->hideFinishedBtn->setText("???????????????");
    }
    m_hideFinish^=1;
    refresh();
}
void TodoList::finishStateChange(int index, bool finish)
{
    int groupIndex=m_groupListWidget->currentRow();
    auto datas=m_groupListWidget->getGroupItemWidget(groupIndex)->getTodoDataList();
    m_groupListWidget->getGroupItemWidget(groupIndex)->getTodoData(index)->setFinish(finish);
    m_groupListWidget->sortTodos(GroupListWidget::method::Finished);
    m_groupListWidget->getGroupItemWidget(0)->setFocus();
    refresh();
}

void TodoList::showMethodChange()
{
    if(m_currentGroupMethod==GroupMethod::All)
    {
        m_currentGroupMethod++;
        ui->groupChange->setText("?????????");
    }
    else if(m_currentGroupMethod==GroupMethod::NoArrangement)
    {
        m_currentGroupMethod++;
        ui->groupChange->setText("????????????");
    }
    else if(m_currentGroupMethod==GroupMethod::SevenDays)
    {
        m_currentGroupMethod++;
        ui->groupChange->setText("??????");
    }
    else if(m_currentGroupMethod==GroupMethod::LaterDays)
    {
        m_currentGroupMethod++;
        ui->groupChange->setText("?????????");
    }
    else if(m_currentGroupMethod==GroupMethod::Overdue)
    {
        m_currentGroupMethod=GroupMethod::All;
        ui->groupChange->setText("??????");
    }
    refresh();
}

//????????????
void TodoList::refresh()
{
    int index = m_groupListWidget->currentRow();
    if(index<0)
    {
        return;
    }
    if(index==m_groupListWidget->count()+1)
    {
        index=0;
    }
    ui->todoListWidget->todoItemsClear();
    if(index>2)ui->nowGroupNameLabel->setText(m_groupListWidget->getGroupItemWidget(index)->getName());
    if(index==1)ui->nowGroupNameLabel->setText("????????????");
    if(index==0)ui->nowGroupNameLabel->setText("????????????");

    GroupItemWidget * nowGroupItem =ui->groupListWidget->getGroupItemWidget(index);
    QList<TodoData*>todoDatas=nowGroupItem->getTodoDataList();
    for(int i=todoDatas.size()-1;i>=0;i--)
    {
       auto data=todoDatas[i];
       if(m_hideFinish&&data->getFinish()==true)
       {
           continue;
       }
       else
       {
           QDate date;
           QDate currentDate=date.currentDate();
           QDate ddlDate=TodoUtils::strToDate(data->getDeadline());
           if(m_currentGroupMethod==GroupMethod::All
               ||(data->getDeadline()==""&&m_currentGroupMethod==GroupMethod::NoArrangement)
               ||(data->getDeadline()!=""&&currentDate.daysTo(ddlDate)<7&&currentDate.daysTo(ddlDate)>=0&&m_currentGroupMethod==GroupMethod::SevenDays)
               ||(data->getDeadline()!=""&&currentDate.daysTo(ddlDate)>7&&m_currentGroupMethod==GroupMethod::LaterDays)
               ||(data->getDeadline()!=""&&currentDate.daysTo(ddlDate)<0&&m_currentGroupMethod==GroupMethod::Overdue))
           {
               qDebug()<<currentDate.daysTo(date)<<endl;
               auto widget=ui->todoListWidget->addTodoItem(*data);
               connect(widget->getDeadlineBtn(),&QToolButton::clicked,m_deadlineCalendar,&DeadLineCalendar::show);
               connect(widget->getNoticeToolBtn(),&QToolButton::clicked,m_noticeCalendar,&NoticeCalendar::show);
               connect(widget->getRepeatToolBtn(),&QToolButton::clicked,m_deadlineCalendar,&DeadLineCalendar::show);
           }
           else
           {
               continue;
           }
        }
    }
}

//????????????????????????
void TodoList::saveGroups()
{
    QList<QString > groupNames;
    int length =m_groupListWidget->count()-1;
    for(int i=3;i<length;i++)
    {
        groupNames.push_back(m_groupListWidget->getGroupItemWidget(i)->getName());
    }
    SaveLocate *save=new SaveLocate;
    save->SaveGroups(groupNames);
}
void TodoList::saveTodoData()
{
    SaveLocate *save=new SaveLocate;
    auto groupItemWidget=ui->groupListWidget->getGroupItemWidget(0);
    auto todoDatas=groupItemWidget->getTodoDataList();
    save->saveTodoDatas(todoDatas);
}


//??????todoitem????????????????????????
void TodoList::updateDockWidget()
{
    int todoIndex=ui->todoListWidget->currentRow();
    int groupIndex=m_groupListWidget->currentRow();
    if(groupIndex<0)
        return;
    auto groupItemWidget=ui->groupListWidget->getGroupItemWidget(groupIndex);
    if(todoIndex<0||todoIndex>=groupItemWidget->getTodoDataList().size())
        return ;

    ui->dockWidget->show();
    QString str=ui->todoListWidget->getTodoItemWidget(todoIndex)->getName();
    ui->todoItemNameCheckBox->setText(str);

    auto datas=groupItemWidget->getTodoDataList();
    auto data=datas[todoIndex];
    ui->deadLineEdit->setText(data->getDeadline());
    ui->noticeLineEdit->setText(data->getNoticion());
    ui->descriptionLineEdit->setText(data->getDescription());
    ui->remarkLineEdit->setText(data->getRemark());
    ui->priComboBox->setCurrentIndex(data->getPri());
    ui->locationLineEdit->setText(data->getLocation());
    ui->todoItemNameCheckBox->setText(data->getTodoName().mid(5));
    ui->todoItemNameCheckBox->setChecked(data->getFinish());

    connect(ui->todoItemNameCheckBox,&QCheckBox::stateChanged,[&]()
    {
        int index=m_todoListWidget->currentRow();
        auto item=m_todoListWidget->getTodoItemWidget(index);
        bool nowState;
        if(Qt::CheckState::Checked==ui->todoItemNameCheckBox->checkState())
        {
            nowState=true;
        }
        else
        {
            nowState=false;
        }
        item->setFinish(nowState);
    });
}


//????????????????????????
void TodoList::locateChange()
{
    if(ui->todoListWidget->currentRow()<0)
        return;
    ui->locationLineEdit->setReadOnly(false);
    ui->locationLineEdit->setFocus();

}
void TodoList::remarkChange()
{
    if(ui->todoListWidget->currentRow()<0)
        return;
    ui->remarkLineEdit->setReadOnly(false);
    ui->remarkLineEdit->setFocus();
}
void TodoList::descriptionChange()
{
    if(ui->todoListWidget->currentRow()<0)
        return;
    ui->descriptionLineEdit->setReadOnly(false);
    ui->descriptionLineEdit->setFocus();
}


//??????????????????????????????
void TodoList::setLocation()
{
    QString str=ui->locationLineEdit->text();
    int todoIndex=ui->todoListWidget->currentRow();
    if(todoIndex<0)
        return;
    int groupIndex=m_groupListWidget->currentRow();
    auto groupItemWidget=m_groupListWidget->getGroupItemWidget(groupIndex);
    auto todoDatas=groupItemWidget->getTodoDataList();
    todoDatas[todoIndex]->setLocation(str);
    ui->locationLineEdit->setText(str);
    ui->locationLineEdit->setReadOnly(true);
}
void TodoList::setRemark()
{
    QString str=ui->remarkLineEdit->text();
    int todoIndex=ui->todoListWidget->currentRow();
    if(todoIndex<0)
        return;
    int groupIndex=m_groupListWidget->currentRow();
    auto groupItemWidget=m_groupListWidget->getGroupItemWidget(groupIndex);
    auto todoDatas=groupItemWidget->getTodoDataList();
    todoDatas[todoIndex]->setRemark(str);
    ui->remarkLineEdit->setText(str);
    ui->remarkLineEdit->setReadOnly(true);
}
void TodoList::setDeadline(QString name,QString repeat)
{
    int todoIndex=ui->todoListWidget->currentRow();
    if(todoIndex<0)
        return;
    TodoItemWidget* itemWidget=ui->todoListWidget->getTodoItemWidget(todoIndex);
    itemWidget->setDeadline(name);
    itemWidget->setRepeation(repeat);
    int groupIndex=m_groupListWidget->currentRow();
    auto groupItemWidget=m_groupListWidget->getGroupItemWidget(groupIndex);
    auto todoDatas=groupItemWidget->getTodoDataList();
    todoDatas[todoIndex]->setDeadline(name);
    todoDatas[todoIndex]->setTodoRepeat(repeat);
    ui->deadLineEdit->setText(name);
}
void TodoList::setNotice(QString str)
{
    int todoIndex=ui->todoListWidget->currentRow();
    if(todoIndex<0)
        return;
    TodoItemWidget* itemWidget=ui->todoListWidget->getTodoItemWidget(todoIndex);
    itemWidget->setNotice(str);
    int groupIndex=m_groupListWidget->currentRow();
    auto groupItemWidget=m_groupListWidget->getGroupItemWidget(groupIndex);
    auto todoDatas=groupItemWidget->getTodoDataList();
    todoDatas[todoIndex]->setNoticion(str);
    ui->noticeLineEdit->setText(str);
}
void TodoList::setPri()
{
    int todoIndex=ui->todoListWidget->currentRow();
    int pri=ui->priComboBox->currentIndex();
    if(todoIndex<0)
        return;
    TodoItemWidget* itemWidget=ui->todoListWidget->getTodoItemWidget(todoIndex);
    itemWidget->setPri(pri);
    int groupIndex=m_groupListWidget->currentRow();
    auto groupItemWidget=m_groupListWidget->getGroupItemWidget(groupIndex);
    auto todoDatas=groupItemWidget->getTodoDataList();
    todoDatas[todoIndex]->setPri(pri);
    ui->priComboBox->setCurrentIndex(pri);
}
void TodoList::setDescription()
{
    int todoIndex=ui->todoListWidget->currentRow();
    if(todoIndex<0)
        todoIndex=0;
    int groupIndex=m_groupListWidget->currentRow();
    auto groupItemWidget=m_groupListWidget->getGroupItemWidget(groupIndex);
    auto todoDatas=groupItemWidget->getTodoDataList();
    todoDatas[todoIndex]->setDescription(ui->descriptionLineEdit->text());
}


//??????????????????
void TodoList::deleteDeadline()
{
    ui->deadLineEdit->clear();
    //setDeadline("none","?????????");
    setDeadline("","");
}
void TodoList::deleteNotice()
{
    ui->noticeLineEdit->clear();
    //setNotice("none");
    setNotice("");
}
void TodoList::deleteDescription()
{
    ui->descriptionLineEdit->clear();
    setDescription();
}
void TodoList::deleteRemark()
{
    ui->remarkLineEdit->clear();
    setRemark();
}
void TodoList::deleteLocation()
{
    ui->locationLineEdit->clear();
    setLocation();
}
