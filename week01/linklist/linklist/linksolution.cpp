#include"linknode.h"
#include "linksolution.h"

KLinkSolution::KLinkSolution()
{

}

LinkNode* KLinkSolution::reverseKGroup(LinkNode* head, int k)
{
	LinkNode* pre = new LinkNode(0, nullptr);
	pre->next = head;
	LinkNode* ans = pre;
	while (head)
	{
		LinkNode* temp = head;
		for (int i = 0; i < k; i++) 
		{
			if (!temp)
				return ans->next;
			else
				temp = temp->next;
		}
		LinkNode* tail;
		tail = head;
		reverse(head, k);
		pre->next = head;
		pre = tail;
		tail->next = temp;
		head = temp;
	}
	return ans->next;
}

void KLinkSolution::reverse(LinkNode*& head, int length)
{
	LinkNode* pre = head;
	LinkNode* last = head->next;
	for (int i = 0; i < length - 1; i++)
	{
		head = last;
		last = head->next;
		head->next = pre;
		pre = head;
	}
}
int KLinkSolution::getLength(LinkNode* head) const
{
	LinkNode* temp = head;
	int length = 0;
	while (temp != nullptr)
	{
		temp = temp->next;
		++length;
	}
	return length;
}



