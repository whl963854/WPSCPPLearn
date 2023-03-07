#include "todoutils.h"
unsigned int TodoUtils::s_count=2;
TodoUtils::TodoUtils()
{

}
//返回数字的指定位数字符串，过长则截断，过短前面补0，
//这里用于区分重名的分组以及待办
QString TodoUtils::intToQString(int size)
{
    int temp=1;
    for(int i=0;i<size;i++)
    {
        temp*=10;
    }
    if(s_count==0)
        s_count=2;
    s_count%=temp;
    QString str=QString::number(s_count);
    while(str.size()<size)
    {
        str='0'+str;
    }
    s_count++;
    return str;
}
QDate TodoUtils::strToDate(QString str)
{
    int i=0;
    QString year,month,day;
    while(str[i]<='9'&&str[i]>='0')
    {
        year+=str[i];
        i++;
    }
    i++;
    while(str[i]<='9'&&str[i]>='0')
    {
        month+=str[i];
        i++;
    }
    i++;
    while(str[i]<='9'&&str[i]>='0')
    {
        day+=str[i];
        i++;
    }
    auto date=QDate(year.toInt(),month.toInt(),day.toInt());
    return date;
}
