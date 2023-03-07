#include "LinkList.h"
#include <iostream>
#include"linknode.h"


LinkList::LinkList()
	: m_head(nullptr)
	, m_tail(nullptr)
{
}

void LinkList::createLinkList()
{
	int length;
	std::cout << "请输入链表的大小：" << std::endl;
	std::cin >> length;
	std::cout << "请依次输入链表节点的数值：" << std::endl;
	int value;
	for (int i = 0; i < length; i++)
	{
		std::cin >> value;
		addNode(value);
	}
}

void LinkList::addNode(int val)
{
	if (m_head == nullptr)
	{
		m_head = new LinkNode(val, nullptr);
		m_tail = m_head;
	}
	else
	{
		m_tail->next = new LinkNode(val, nullptr);
		m_tail = m_tail->next;
	}
}

LinkNode* LinkList::getHead() const
{
	return m_head;
}

int LinkList::getLength() const
{
	LinkNode* temp = m_head;
	int length = 0;
	while (temp != nullptr)
	{
		temp = temp->next;
		++length;
	}
	return length;
}

void LinkList::linkListPrint()
{
	LinkNode* temp = m_head;
	while (temp != nullptr)
	{
		std::cout << temp->val << "  ";
		temp = temp->next;
	}
	std::cout << std::endl;
}

//改变实例对象指向的链表，本处用于指向反转后的链表
void LinkList::changeLinkList(LinkNode* head)
{
	this->m_head = head;
	LinkNode* temp=head;
	while (temp&&temp->next != nullptr) {
		temp = temp->next;
	}
	m_tail = temp;

}


LinkList::~LinkList()
{
	LinkNode* temp;
	while (m_head != nullptr)
	{
		temp = m_head->next;
		delete(m_head);
		m_head = temp;
	}
}


