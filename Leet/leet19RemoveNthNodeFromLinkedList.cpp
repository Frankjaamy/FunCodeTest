
//Definition for singly-linked list.
 struct ListNode {
     int val;
     ListNode *next;
     ListNode(int x) : val(x), next(nullptr) {}
 };


class p16_3SumClosest {
public:
	ListNode* removeNthFromEnd(ListNode* head, int n) {
		ListNode ** p1 = &head;
		ListNode * p2 = head;

		for (int i = 0; i < n - 1; i++)
		{
			p2 = p2->next;
		}

		while (p2->next != nullptr)
		{
			p1 = &((*p1)->next);
			p2 = p2->next;
		}
		*p1 = (*p1)->next;

		return head;
	}
};


