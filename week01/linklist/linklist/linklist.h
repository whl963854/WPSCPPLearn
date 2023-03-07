#ifndef      LINKLIST_LINKLIST_H 	
#define      LINKLIST_LINKLIST_H 	

struct LinkNode;

struct LinkList
{
public:

    LinkList();

    void createLinkList();

    void addNode(int val);

    LinkNode* getHead()const;

    int getLength() const;

    void linkListPrint();

    void changeLinkList(LinkNode*head);

    ~LinkList();

private:
    
    LinkNode* m_head;

    //��ӳ�Ա����m_tail����������ĩβԪ�ص����
    LinkNode* m_tail;

};


#endif  //     LINKLIST_LINKLIST_H 
