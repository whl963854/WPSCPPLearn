#include "newlineedit.h"
#include<QLineEdit>
#include<QDebug>

NewLineEdit::NewLineEdit(QWidget *parent) :
    QLineEdit(parent)
{

}

//重写mousePressEvent事件,检测事件类型是不是点击了鼠标左键
void NewLineEdit::mousePressEvent(QMouseEvent *e) {
    if(flag)
        return;
    //如果单击了就触发clicked信号
    if (e->button() == Qt::LeftButton) {
        //触发clicked信号
        emit clicked();

    }
}

void NewLineEdit::clearEdit()
{
    setText("");
    QPalette palette;
    palette.setColor(QPalette::Text, QColor(0, 0, 0));
    setPalette(palette);
    setReadOnly(false);
    flag=1;
}

void NewLineEdit::initLineEdit()
{
    this->clearFocus();
    this->setText("+ 点击新建待办");
    QPalette palette;
    palette.setColor(QPalette::Text, QColor(0,255,0));
    this->setPalette(palette);
    setReadOnly(true);
    flag=false;
}
void NewLineEdit::focusOutEvent(QFocusEvent *)
{
    return;
}
