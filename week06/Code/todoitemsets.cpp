#include "todoitemsets.h"
#include<QPushButton>
#include<QHBoxLayout>

ToDoItemSets::ToDoItemSets(QWidget *parent) : QDockWidget(parent)
{
    init();
}

//去掉标题栏
void ToDoItemSets::init()
{
    QWidget* lTitleBar = this->titleBarWidget();
    QWidget* lEmptyWidget = new QWidget();
    this->setTitleBarWidget(lEmptyWidget);
    this->titleBarWidget()->setMaximumHeight(50);
    delete lTitleBar;
}

