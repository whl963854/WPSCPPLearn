#include"iostream"
#include"cwchar"
#include "ksostring.h"
#include "linknode.h"
#include "linknode.cpp"
#include <iterator>
#include"ksostring_iterator.h"


template<class T>
KsoString<T>::KsoString()
	: m_linkHead ( nullptr)
	,m_length(0)
	,m_linkTail(nullptr)
{
	assert(typeid(T) == typeid(char) || typeid(T) == typeid(wchar_t));
}

template<class T>
KsoString<T>::KsoString(const KsoString<T>& nodeList)
{
	assert(typeid(T)== typeid(char) || typeid(T) == typeid(wchar_t));
	if (nodeList.m_linkHead == nullptr)
	{
		m_linkHead = nullptr;
		m_length = 0;
		m_linkHead = nullptr;
		return;
	}
	LinkNode<T> *temp = new LinkNode<T>;
	m_linkHead = temp;
	LinkNode<T> *linknode = nodeList.m_linkHead;
	while (linknode) 
	{
		temp->m_val = linknode->m_val;
		temp->m_next = linknode->m_next;
		m_length++;
		if (linknode->m_next == nullptr)
			m_linkTail = linknode;
		else temp->m_next = new LinkNode<T>;
		temp = temp->m_next;
		linknode = linknode->m_next;
	}
}

template<class T>
KsoString<T>::~KsoString()
{
	while (m_linkHead != nullptr)
	{
		LinkNode<T>* temp = m_linkHead->m_next;
		delete m_linkHead;
		m_linkHead = temp;
	}
}

template<class T>
void KsoString<T>::addNode(T data)
{
	if (m_length==0)
	{
		m_linkHead = new LinkNode<T>(data);
		m_linkTail = m_linkHead;
	}
	else
	{
		m_linkTail->m_next = new LinkNode<T>;
		m_linkTail = m_linkTail->m_next;
		m_linkTail->m_val = data;
		m_linkTail->m_next = nullptr;
	}
	++m_length;
	
}

template<class T>
int KsoString<T>::getLength() const noexcept
{
	return m_length;
}

template<class T>
void KsoString<T>::insert(int index, T data)
{
	if (index<0 || index>m_length) 
	{
		std::cout << "out of range"<<std::endl;
		return;
	}
	LinkNode<T> *temp = new LinkNode<T>;
	temp->m_next = nullptr;
	temp->m_val = data;
	if (!index)
	{
		temp->m_next = m_linkHead;
		m_linkHead = temp;
		if (!m_linkTail) {
			m_linkTail = m_linkHead;
		}
	}
	else if (index == m_length)
	{
		m_linkTail->m_next = temp;
		m_linkTail = temp;
	}
	else
	{
		LinkNode<T> *location = m_linkHead;
		while (--index)
		{
			location = location->m_next;
		}
		temp->m_next = location->m_next;
		location->m_next = temp;
	}
	m_length++;
}

template<class T>
void KsoString<T>::deleteNode(int index)
{
	if (index<0 || index>=m_length)
	{
		std::cout << "out of range" << std::endl;
		return;
	}
	LinkNode<T> *temp = m_linkHead;
	if (!index)
	{
		m_linkHead = m_linkHead->m_next;
		delete temp;
	}
	else if (index == m_length)
	{
		delete m_linkTail;
		m_linkTail = nullptr;
		while (temp->m_next) {
			temp = temp->m_next;
		}
		m_linkTail = temp;
	}
	else
	{
		LinkNode<T> *location = m_linkHead;
		while (--index)
		{
			location = location->m_next;
		}
		temp = location->m_next;
		location->m_next = location->m_next->m_next;
		delete(temp);
	}
	m_length--;
}

template<class T>
bool KsoString<T>::isEmpty() const noexcept
{
	return !!m_length;
}

template<class T>
T KsoString<T>::getData(int index) const
{
	if (index < 0 || index >= m_length)
	{
		throw "index out of range";
		return 0;
	}
	LinkNode<T>* location = m_linkHead;
	while (index--)
	{
		location = location->m_next;
	}
	return location->m_val;
}

template<class T>
T KsoString<T>::operator[](int index) const
{
	return getData(index);
}

template<class T>
int KsoString<T>::getIndex(const T& data) const noexcept
{
	LinkNode<T>* temp = m_linkHead;
	int index = 0;
	while (temp)
	{
		if (temp->m_val == data)
			return index;
		temp = temp->m_next;
		index++;
	}
	return -1;
}

template<class T>
void KsoString<T>::printLink() const noexcept
{
	LinkNode<T>* temp = m_linkHead;
	int length = 0;
	while (temp != nullptr)
	{
		length++;
		if (typeid(T) == typeid(char))
			std::cout << temp->m_val << " ";
		else 
			std::wcout << temp->m_val << " ";
		temp = temp->m_next;
		if (length == 15)
		{
			std::cout << std::endl;
			length = 0;
		}
	}
	std::cout << std::endl;
}

template<class T>
KsoString_Iterator<T> KsoString<T>::begin()
{
	//if (!this)
	//	throw" NULL LinkNode";
	return KsoString_Iterator<T>(*this);
}

template<class T>
KsoString_Iterator<T> KsoString<T>::end()
{
	KsoString_Iterator<T> end_iter(*this);
	if (m_linkTail)
		end_iter.m_startIterator = m_linkTail->m_next;
	else
		end_iter.m_startIterator = nullptr;
	return end_iter;
}



