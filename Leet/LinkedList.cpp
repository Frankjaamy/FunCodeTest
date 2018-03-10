#include <stdlib.h>
#include "LinkedList.h"

void LinkedList::insertInSorted(Node * & head, Node * iNode)
{
	if (!head || head->value > iNode->value)
	{
		iNode->next = head;
		head = iNode;
	}
	else 
	{
		Node * nextNode = head;
		while (nextNode->next && nextNode->next->value < iNode->value)
		{
			nextNode = nextNode->next;
		}

		iNode->next = nextNode->next;
		nextNode->next = iNode;
	}
}

void LinkedList::delete_node(Node * head, Node * nodeDelete)
{
	if (!head || !nodeDelete) return;
	if (head == nodeDelete)
	{
		if (head->next)
		{
			head->value = head->next->value;
			Node * tmpNode = head->next->next;
			delete head->next;
			head->next = tmpNode;
		}
		else 
		{
			delete head;
			head = nullptr;
		}
	}
	else 
	{
		Node * nextNode = head;
		while (nextNode->next && nextNode->next != nodeDelete)
		{
			nextNode = nextNode->next;
		}
		if (nextNode->next)
		{
			Node * tmpNode = nextNode->next->next;
			delete nodeDelete;
			nextNode->next = tmpNode;
		}
	}
}

Node * LinkedList::add_two_lists(Node * & head1, Node * & head2)
{
	int size1 = LinkedList::getSize(head1);
	int size2 = LinkedList::getSize(head2);
	
	if (size2 > size1)
	{
		Node * tmp = head2;
		head2 = head1;
		head1 = tmp;
	}

	int diff = abs(size2 - size1);
	Node * startNode = head1;
	while (diff > 0)
	{
		diff--;
		startNode = startNode->next;
	}

	Node * resultNode = nullptr;
	bool needNewDigit = add_two_lists_inner(startNode, head2, resultNode);
	add_remaining_list(head1, startNode, resultNode, needNewDigit);
	if (needNewDigit)
	{
		Node * node = new Node(1);
		node->next = resultNode;
		resultNode = node;
	}
	return resultNode;
}

bool LinkedList::add_two_lists_inner(Node * head1, Node * head2, Node * & outNode)
{
	bool needNewDigit = false;
	if (head1->next && head2->next)
	{
		needNewDigit = add_two_lists_inner(head1->next, head2->next,outNode);
	}
	else if(!head1->next && !head2->next)
	{
		int sum = head1->value + head2->value;
		if (sum >= 10)
		{
			sum %= 10;
			outNode = new Node(sum);
			return true;
		}
		else 
		{
			outNode = new Node(sum);
			return false;
		}

	}
	int sum = 0;
	if (needNewDigit)
	{
		sum += 1;
	}
	sum += (head1->value + head2->value);
	if (sum >= 10)
	{
		sum %= 10;
		Node * node = new Node(sum);
		node->next = outNode;
		outNode = node;
		return true;
	}
	else 
	{
		Node * node= new Node(sum);
		node->next = outNode;
		outNode = node;
		return false;
	}
}

void LinkedList::add_remaining_list(Node * head, Node * end, Node * & outNode, bool & needIncrement)
{
	if (head == end)
	{
		return;
	}
	else 
	{
		add_remaining_list(head->next, end, outNode, needIncrement);
		int sum = head->value;
		if (needIncrement) sum++;
		if (sum >= 10) {
			needIncrement = true;
			sum = sum % 10;
		}
		else {
			needIncrement = false;
		}

		Node * node = new Node(sum);
		node->next = outNode;
		outNode = node;
	}
}

int LinkedList::getSize(Node * head)
{
	int size = 0;
	while (head)
	{
		size++;
		head = head->next;
	}
	return size;
}

void LinkedList::insert_two_lists_alternative(Node * head1, Node * head2)
{
	while (head1->next)
	{
		Node * p1 = head1->next;
		Node * p2 = head2->next;

		head1->next = head2;
		head2->next = p1;

		head2 = p2;
		head1 = p1;
	}
 
	{
		while (head2)
		{
			head1->next = head2;
			head1 = head1->next;
			head2 = head2->next;
		}
	}
}

Node * LinkedList::reverse_linked_lists_inner(Node * head, int & k, Node * nodeSwap)
{
	static int count = 0;
	Node * node = head;
	if (count < k-1)
	{
		count++;
		node = reverse_linked_lists_inner(head, k, nodeSwap->next);
	}
	if (!node) 
		return nullptr;
	if (nodeSwap == node)
	{
		return nullptr;
	}
	if (!nodeSwap)
	{
		k = count+1;
		return head;
	}
	if (count == k - 1)
	{
		SwapNodes(node, nodeSwap);
		count--;
		k--;
		return node->next;
	}
}

void LinkedList::reverse_linked_lists(Node * head, int k)
{
	reverse_linked_lists_inner(head, k, head);
	int a = 0;
}

Node * LinkedList::merge_two_sorted_linkedlist(Node * head1, Node * head2)
{
	Node * rtHead = nullptr;
	Node * p = head1;
	Node * prev = p;

	while (head2)
	{
		if (!p)
		{
			prev->next = head2;
			break;
		}
		if (head2->value < p->value){
			Node * tmpNode = head2->next;
			head2->next = p;
			if (p == head1){
				head1 = head2;
			}
			else {
				prev->next = head2;
				p = head2;
			}
			head2 = tmpNode;
		}
		else {
			if (p != head1){
				prev = p;
			}
			p = p->next;
		}
	}
	rtHead = head1;
	return rtHead;
}

Node * LinkedList::reverse_linked_list(Node * head1)
{
	if (!head1 || !head1->next)
		return head1;

	Node * newNode = reverse_linked_list(head1->next);
	head1->next->next = head1;
	head1->next = nullptr;

	return newNode;
}

