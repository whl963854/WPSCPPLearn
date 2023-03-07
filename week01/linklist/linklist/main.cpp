#include <iostream>
#include"linklist.h"
#include"linksolution.h"

int main()
{
    LinkList firstLine= LinkList();
    firstLine.createLinkList();
    firstLine.linkListPrint();
    KLinkSolution  secondLine= KLinkSolution();
    firstLine.changeLinkList(secondLine.reverseKGroup(firstLine.getHead(), 3));
    firstLine.linkListPrint();
    return 0;
}