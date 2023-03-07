#ifndef TODOITEMSETS_H
#define TODOITEMSETS_H

#include <QWidget>
#include<QDockWidget>
#include<QPushButton>

class ToDoItemSets : public QDockWidget
{
    Q_OBJECT
public:
    explicit ToDoItemSets(QWidget *parent = nullptr);

signals:

public slots:


private:
    void init();

private:
    QPushButton * m_closeBtn;
};

#endif // TODOITEMSETS_H
