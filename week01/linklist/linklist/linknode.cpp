#include "linknode.h"


LinkNode::LinkNode()
    : val(0)
    , next(nullptr)
{
}

LinkNode::LinkNode(int x)
    : val(x)
    , next(nullptr)
{
}

LinkNode::LinkNode(int x, LinkNode* next)
    : val(x)
    , next(next)
{
}


