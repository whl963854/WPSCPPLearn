#ifndef      WEEKTWO_LINKNODE_H 	
#define      WEEKTWO_LINKNODE_H 	

template<class T>
struct LinkNode
{
    T m_val;
    LinkNode<T> * m_next;
    LinkNode();
    LinkNode(T x);
    LinkNode(T x, LinkNode<T>* next);
};


#endif  //     WEEKTWO_LINKNODE_H 
