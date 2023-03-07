#ifndef      LINKLIST_LINKSOLUTION_H 	
#define      LINKLIST_LINKSOLUTION_H 

struct LinkNode;
class KLinkSolution
{
public:
    KLinkSolution();

    LinkNode* reverseKGroup(LinkNode* head, int k);

    void reverse(LinkNode*& head,int length);

    int getLength(LinkNode*head)const;
};
#endif  //     LINKLIST_LINKSOLUTION_H
