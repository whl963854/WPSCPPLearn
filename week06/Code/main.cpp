#include "todolist.h"
#include<QDebug>
#include <QApplication>
#include<QWidget>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TodoList w;
    w.setWindowFlags(w.windowFlags()& ~Qt::WindowMaximizeButtonHint&
    ~Qt::WindowMinimizeButtonHint);
    w.setWindowIcon(QIcon("://res/Jinshan.png"));
    w.showMaximized();
    w.show();

    return a.exec();
}
