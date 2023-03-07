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

    //添加成员变量m_tail，方便链表末尾元素的添加
    LinkNode* m_tail;

};


#endif  //     LINKLIST_LINKLIST_H 
