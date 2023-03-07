#ifndef      LINKLIST_LINKNODE_H 	
#define      LINKLIST_LINKNODE_H 	
struct LinkNode
{
    int val;
    LinkNode* next;
    LinkNode();
    LinkNode(int x);
    LinkNode(int x, LinkNode* next);
};


#endif  //     LINKLIST_LINKNODE_H 
