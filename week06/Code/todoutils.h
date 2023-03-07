#ifndef TODOUTILS_H
#define TODOUTILS_H

#include<QString>
#include<QDate>


class TodoUtils
{
public:
    TodoUtils();
    QString static intToQString(int size=5);
    static QDate strToDate(QString str);
private:
    static unsigned int s_count;
};

#endif // TODOUTILS_H
