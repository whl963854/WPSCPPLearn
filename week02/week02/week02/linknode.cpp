#include "linknode.h"

template<typename T>
LinkNode<T>::LinkNode()
    : m_next(nullptr)
    , m_val(0)
{
}

template<typename T>
LinkNode<T>::LinkNode(T x)
    : m_val(x)
    , m_next(nullptr)
{
}

template<typename T>
LinkNode<T>::LinkNode(T x, LinkNode<T>* next)
    : m_val(x)
    , m_next(next)
{
};


