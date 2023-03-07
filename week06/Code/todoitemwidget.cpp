#include "todoitemwidget.h"
#include<QFrame>
#include<QCheckBox>
#include<QLabel>
#include<QDebug>
#include<QHBoxLayout>
#include<QVBoxLayout>
#include<QGroupBox>
#include<QMouseEvent>
#include<QToolButton>
#include<QMenu>
#include <QCursor>
#include<QWidgetAction>
#include<QLineEdit>
#include<QToolButton>



TodoItemWidget::TodoItemWidget(QWidget *parent) :
    QWidget(parent)
{

}

TodoItemWidget::~TodoItemWidget()
{

}

//鼠标事件
void TodoItemWidget::enterEvent(QEvent *event)
{
    if(event)
        return;
    if (m_bSelected)
            return;
}
void TodoItemWidget::leaveEvent(QEvent *event)
{
    if(event)
        return;
    if (m_bSelected)
            return;
}


//完成状态切换
void TodoItemWidget::finishChange()
{
    if(m_checkBox->checkState()==Qt::CheckState::Checked)
    {
        m_isFinish=true;
        hasFinished();
        emit(finishStateChange(this));
    }
    else
    {
        m_isFinish=false;
        hasRecovered();
        emit(finishStateChange(this));
    }
}
void TodoItemWidget::hasFinished()
{
    QFont font;
    font.setStrikeOut(true);//删除线
    m_itemLabel->setFont(font);
}
void TodoItemWidget::hasRecovered()
{
    QFont font;
    font.setStrikeOut(false);//删除线
    m_itemLabel->setFont(font);
}

void TodoItemWidget::setFinish(bool finish)
{
    if(finish)
    {
        m_checkBox->setCheckState(Qt::CheckState::Checked);
    }
    else
    {
        m_checkBox->setCheckState(Qt::CheckState::Unchecked);
    }
    finishChange();
}


//初始化
void TodoItemWidget::initItem(QString todoName,QString groupName)
{
    m_itemName=todoName;
    m_isFinish=false;
    QVBoxLayout* vlayout=new QVBoxLayout(this);

    m_checkBox=new QCheckBox(this);
    m_checkBox->setMaximumWidth(20);

    m_itemLabel=new QToolButton();
    m_itemLabel->setText(todoName);
    m_itemLabel->setStyleSheet("background:transparent;border-width:0;border-style:outset;");

    m_priLabel=new QLabel();
    m_priLabel->setPixmap(QPixmap("://res/nonePri.svg"));
    m_priLabel->setMaximumWidth(30);

    m_deadlineToolBtn=new QToolButton(this);
    m_noticeToolBtn=new QToolButton(this);
    m_groupToolBtn=new QToolButton(this);
    m_repeatToolBtn=new QToolButton(this);

    m_deadlineToolBtn->setStyleSheet("QToolButton{border-style: flat;background: transparent;}");
    m_noticeToolBtn->setStyleSheet("QToolButton{border-style: flat;background: transparent;}");
    m_groupToolBtn->setStyleSheet("QToolButton{border-style: flat;background: transparent;}");
    m_repeatToolBtn->setStyleSheet("QToolButton{border-style: flat;background: transparent;}");

    m_deadlineToolBtn->setMinimumWidth(150);
    m_noticeToolBtn->setMinimumWidth(150);
    m_groupToolBtn->setMinimumWidth(150);
    m_repeatToolBtn->setMinimumWidth(150);

    m_deadlineToolBtn->setIcon(QIcon("://res/deadline.svg"));
    m_noticeToolBtn->setIcon(QIcon("://res/notice.svg"));
    m_groupToolBtn->setIcon(QIcon("://res/group.svg"));
    m_repeatToolBtn->setIcon(QIcon("://res/isRepeat.svg"));

    m_deadlineToolBtn->setText("none");
    m_noticeToolBtn->setText("none");
    m_groupToolBtn->setText(groupName);
    m_repeatToolBtn->setText("不重复");

    m_deadlineToolBtn->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    m_noticeToolBtn->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    m_groupToolBtn->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    m_repeatToolBtn->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    QHBoxLayout* hlayoutUp=new QHBoxLayout();
    QHBoxLayout* hlayoutDown=new QHBoxLayout();
    QSpacerItem * sparcerItem = new QSpacerItem(0,160,QSizePolicy::Expanding,QSizePolicy::Fixed);
    QSpacerItem * sparcerItem2 = new QSpacerItem(0,160,QSizePolicy::Expanding,QSizePolicy::Fixed);
    m_deadlineToolBtn->setAutoFillBackground(true);
    vlayout->addLayout(hlayoutUp);
    vlayout->addLayout(hlayoutDown);

    hlayoutDown->addWidget(m_deadlineToolBtn);
    hlayoutDown->addWidget(m_noticeToolBtn);
    hlayoutDown->addWidget(m_repeatToolBtn);
    hlayoutDown->addWidget(m_groupToolBtn);
    hlayoutDown->addItem(sparcerItem);
    hlayoutUp->addWidget(m_checkBox);
    hlayoutUp->addWidget(m_priLabel);
    hlayoutUp->addWidget(m_itemLabel);
    hlayoutUp->addItem(sparcerItem2);
    this->setLayout(vlayout);
    connect(m_checkBox,&QCheckBox::stateChanged,this,&TodoItemWidget::finishChange);
}
void TodoItemWidget::initItem(TodoData data)
{
    m_isFinish=data.getFinish();
    m_itemName=data.getTodoName().mid(5);
    QVBoxLayout* vlayout=new QVBoxLayout(this);

    m_checkBox=new QCheckBox(this);
    m_checkBox->setMaximumWidth(20);
    if(data.getFinish())
        m_checkBox->setCheckState(Qt::CheckState::Checked);
    else
        m_checkBox->setCheckState(Qt::CheckState::Unchecked);
    m_itemLabel=new QToolButton();
    m_itemLabel->setText(m_itemName);
    m_itemLabel->setStyleSheet("background:transparent;border-width:0;border-style:outset;");
    m_priLabel=new QLabel();
    m_priLabel->setPixmap(QPixmap("://res/nonePri.svg"));
    m_priLabel->setMaximumWidth(30);
    setPri(data.getPri());

    m_deadlineToolBtn=new QToolButton(this);
    m_noticeToolBtn=new QToolButton(this);
    m_groupToolBtn=new QToolButton(this);
    m_repeatToolBtn=new QToolButton(this);

    m_deadlineToolBtn->setText(data.getDeadline());
    m_noticeToolBtn->setText(data.getNoticion());
    m_groupToolBtn->setText(data.getTodoGroup().mid(5));
    m_repeatToolBtn->setText(data.getTodoRepeat());

    if(data.getDeadline()=="")
        m_deadlineToolBtn->setText("none");
    if(data.getNoticion()=="")
        m_noticeToolBtn->setText("none");
    if(data.getTodoRepeat()=="")
        m_repeatToolBtn->setText("不重复");


    m_deadlineToolBtn->setStyleSheet("QToolButton{border-style: flat;background: transparent;}");
    m_noticeToolBtn->setStyleSheet("QToolButton{border-style: flat;background: transparent;}");
    m_groupToolBtn->setStyleSheet("QToolButton{border-style: flat;background: transparent;}");
    m_repeatToolBtn->setStyleSheet("QToolButton{border-style: flat;background: transparent;}");

    m_deadlineToolBtn->setMinimumWidth(150);
    m_noticeToolBtn->setMinimumWidth(150);
    m_groupToolBtn->setMinimumWidth(150);
    m_repeatToolBtn->setMinimumWidth(150);

    m_deadlineToolBtn->setIcon(QIcon("://res/deadline.svg"));
    m_noticeToolBtn->setIcon(QIcon("://res/notice.svg"));
    m_groupToolBtn->setIcon(QIcon("://res/group.svg"));
    m_repeatToolBtn->setIcon(QIcon("://res/isRepeat.svg"));

    m_deadlineToolBtn->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    m_noticeToolBtn->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    m_groupToolBtn->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    m_repeatToolBtn->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    QHBoxLayout* hlayoutUp=new QHBoxLayout();
    QHBoxLayout* hlayoutDown=new QHBoxLayout();
    QSpacerItem * sparcerItem = new QSpacerItem(0,160,QSizePolicy::Expanding,QSizePolicy::Fixed);
    QSpacerItem * sparcerItem2 = new QSpacerItem(0,160,QSizePolicy::Expanding,QSizePolicy::Fixed);
    m_deadlineToolBtn->setAutoFillBackground(true);
    vlayout->addLayout(hlayoutUp);
    vlayout->addLayout(hlayoutDown);

    hlayoutDown->addWidget(m_deadlineToolBtn);
    hlayoutDown->addWidget(m_noticeToolBtn);
    hlayoutDown->addWidget(m_repeatToolBtn);
    hlayoutDown->addWidget(m_groupToolBtn);
    hlayoutDown->addItem(sparcerItem);
    hlayoutUp->addWidget(m_checkBox);
    hlayoutUp->addWidget(m_priLabel);
    hlayoutUp->addWidget(m_itemLabel);
    hlayoutUp->addItem(sparcerItem2);
    this->setLayout(vlayout);
    connect(m_checkBox,&QCheckBox::clicked,this,&TodoItemWidget::finishChange);
}



void TodoItemWidget::setPri(int pri)
{
    this->m_pri=pri;
    QString strPri="://res/";
    if(pri==0)
        strPri+="nonePri.svg";
    else if(pri==1)
        strPri+="lowPri.svg";
    else if(pri==2)
        strPri+="midPri.svg";
    else if(pri==3)
        strPri+="highPri.svg";
    m_priLabel->setPixmap(QPixmap(strPri));
}
void TodoItemWidget::setGroupName(QString str)
{
    m_groupToolBtn->setText(str);
}
void TodoItemWidget::setDeadline(QString str)
{
    m_deadlineToolBtn->setText(str);
}
void TodoItemWidget::setNotice(QString str)
{
    m_noticeToolBtn->setText(str);
}
void TodoItemWidget::setName(QString str)
{
    m_itemLabel->setText(str);
}
void TodoItemWidget::setRepeation(QString str)
{
    m_repeatToolBtn->setText(str);
}


QString TodoItemWidget::getGroupName()
{
    return m_groupToolBtn->text();
}
QString TodoItemWidget::getDeadline()
{
    return m_deadlineToolBtn->text();
}
QString TodoItemWidget::getRepeation()
{
    return m_repeatToolBtn->text();
}
QString TodoItemWidget::getName()
{
    return m_itemLabel->text();
}
QString TodoItemWidget::getNotice()
{
    return m_noticeToolBtn->text();
}
bool TodoItemWidget::getFinish()
{
    return m_isFinish;
}
QToolButton *TodoItemWidget::getNoticeToolBtn()
{
    return m_noticeToolBtn;
}
QToolButton *TodoItemWidget::getDeadlineBtn()
{
    return m_deadlineToolBtn;
}
QToolButton *TodoItemWidget::getRepeatToolBtn()
{
    return m_repeatToolBtn;
}
QToolButton *TodoItemWidget::getGroupNameToolBtn()
{
    return m_groupToolBtn;
}

QToolButton *TodoItemWidget::getTodoNameToolBtn()
{
    return m_itemLabel;
}

