#include "addnewstackwidget.h"

#include<QHBoxLayout>
#include<QListWidget>
#include<QDebug>
AddNewStackWidget::AddNewStackWidget(QWidget *parent) :
    QStackedWidget(parent)
{
    initStackWidget();
}

AddNewStackWidget::~AddNewStackWidget()
{

}
void AddNewStackWidget::initStackWidget()
{
    QListWidget* homePage=new QListWidget;
    QListWidget* ownPage=new QListWidget;
    QWidget* pageWidgetFirst=new QWidget;
    QWidget* pageWidgetSecond=new QWidget;
    m_todoListWidget.push_back(homePage);
    m_todoListWidget.push_back(ownPage);
    this->addWidget(pageWidgetFirst);
    this->addWidget(pageWidgetSecond);
    QHBoxLayout*hHomeLayout=new QHBoxLayout;
    QHBoxLayout*hOwnLayout=new QHBoxLayout;
    pageWidgetFirst->setLayout(hOwnLayout);
    pageWidgetSecond->setLayout(hHomeLayout);
    hHomeLayout->addWidget(homePage);
    hOwnLayout->addWidget(ownPage);
}
void AddNewStackWidget::addNewPage()
{
    QListWidget* newPage=new QListWidget;
    QWidget* pageWidget=new QWidget;
    m_todoListWidget.push_back(newPage);
    this->addWidget(pageWidget);
    QHBoxLayout*newHLayout=new QHBoxLayout;
    pageWidget->setLayout(newHLayout);
    newHLayout->addWidget(newPage);
}
QListWidget* AddNewStackWidget::getPageList(int index)
{
    if(index>=m_todoListWidget.count())
        return m_todoListWidget[index];
    qDebug()<<"cccccccccccccccccccccccccccccccccccccccccccccccc"<<endl;
    return m_todoListWidget[index];
}
