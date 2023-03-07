#ifndef NEWLINEEDIT_H
#define NEWLINEEDIT_H

#include<QLineEdit>
#include<QMouseEvent>
class NewLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    explicit NewLineEdit(QWidget *parent = nullptr);

    void initLineEdit();

    void clearEdit();

    void focusOutEvent(QFocusEvent *);

signals:
    //自定义clicked()信号,在mousePressEvent事件发生时触发
    void clicked();
protected:
    //添加并重写鼠标点击事件函数
    virtual void mousePressEvent(QMouseEvent *e);

private:
    bool flag=false;

};

#endif // NEWLINEEDIT_H
