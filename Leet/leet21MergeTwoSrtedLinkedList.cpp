#include<algorithm>
#include<vector>
// Definition for singly-linked list.
 struct ListNode {
     int val;
     ListNode *next;
     ListNode(int x) : val(x), next(nullptr) {}
 };


 using namespace std;
 class Solution1 {
 public:
	 void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
		 int k = m + n - 1;
		 m--;
		 n--;
		 while (m >= 0 && n >= 0)
		 {
			 if (nums1[m] > nums2[n])
			 {
				 nums1[k] = nums1[m--];
			 }
			 else {
				 nums1[k] = nums2[n--];
			 }
			 k--;
		 }
		 while (k >= 0)
		 {
			 nums1[k] = m >= 0 ? nums1[k] : nums2[k];
			 k--;
		 }
	 }
 };

class p16_3SumClosest {
public:
	ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
		ListNode * p1 = l1; 
		ListNode * p2 = l2;

		ListNode * returnNode = nullptr;
		ListNode * nodeToAdd = nullptr;

		while (p1 != nullptr && p2 != nullptr)
		{
			ListNode * node = nullptr;
			if (p1->val < p2->val) {
				node = p1;
				p1 = p1->next;
			}
			else {
				node = p2;
				p2 = p2->next;
			}
			if (!returnNode) {
				returnNode = node;
				nodeToAdd = returnNode;
			}
			else {
				nodeToAdd->next = node;
				nodeToAdd = nodeToAdd->next;
			}
		}

		if (p1) {
			if (!returnNode) {
				returnNode = p1;
			}
			else {
				nodeToAdd->next = p1;
			}
		}
		else if (p2) {
			if (!returnNode) {
				returnNode = p2;
			}
			else {
				nodeToAdd->next = p2;
			}
		}

		return returnNode;
	}

	void addNewNode(ListNode ** head, ListNode * newNode, int index)
	{
		while (*head)
		{
			if (index == 0)
			{
				newNode->next = *head;
				*head = newNode;
				break;
			}
			index--;

			head = &((*head)->next);
		}
	}

	void removeNode(ListNode ** head, int index)
	{
		while (*head)
		{
			if (index == 0){
				ListNode * node = *head;
				*head = (*head)->next;
				delete(node);
				break;
			}
			index--;
			head = &((*head)->next);
		}
	}
};


