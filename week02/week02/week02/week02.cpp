#include <iostream>
#include <iterator>
#include"ksostring.h"
#include"ksostring_iterator.cpp"
#include<string> 
void test01() {
    int choice = 1;
    int index = 0;
    char val;
    KsoString<char>* str1 = new KsoString<char>();
    KsoString<char>* str2 = nullptr;
    while (choice) 
    {
        std::cout <<std::endl<< std::endl << "请输入命令" << std::endl;
        std::cout << "0: exit              1:print" << std::endl;
        std::cout << "2: length            3:shallow copy" << std::endl;
        std::cout << "4: visit with []     5:delete linknode" << std::endl;
        std::cout << "6: addNode           7:insert" << std::endl;
        std::cout << "8: getIndex          9:iterator" << std::endl;
        std::cin >> choice;
        std::cout << "----------------------------------------------" << std::endl;
        switch (choice)
        {
        case 0:
            delete str1;
            return;
        case 1:
            std::cout << "链表内容为：" << std::endl;
            str1->printLink();
            break;
        case 2:
            std::cout << "链表长度为：";
            std::cout << str1->getLength() << std::endl;
            break;
        case 3:
            std::cout << "深拷贝构造：" << std::endl;
            str2 = new KsoString<char>(*str1);
            std::cout << "str2：" ;
            str2->printLink();
            delete str2;
            str2 = nullptr;
            break;
        case 4:
            for (int i = 0; i < str1->getLength(); i++)
            {
                std::cout << (*str1)[i] << "  ";
            }
            break;
        case 5:
            std::cout << "请输入index：" << std::endl;
            std::cin >> index;
            str1->deleteNode(index);
            str1->printLink();
            break;
        case 6:
            std::cout << "请输入要添加的字母val：" << std::endl;
            std::cin >> val;
            str1->addNode(val);
            str1->printLink();
            break;
        case 7:
            std::cout << "在index处插入val，请输入index val" << std::endl;
            std::cin >> index >> val;
            str1->insert(index, val);
            str1->printLink();
            break;
        case 8:
            std::cout << "请输入要获取index的value：";
            std::cout << str1->getIndex(val) << std::endl;
            str1->printLink();
            break;
        case 9:
            for (auto begin = str1->begin(); begin != str1->end(); ++begin)
            {
                std::cout << *begin<<" ";
            }
            break;
        default:
            std::cout << "请输入合理序号："<<std::endl;
            break;
        }
    }
}
int main()
{
    test01();
    return 0;
}
