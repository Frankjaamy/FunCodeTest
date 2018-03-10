struct Node
{
	int value;
	Node * next;

	Node() :value(0), next(nullptr)
	{}

	Node(int iValue):value(iValue), next(nullptr)
	{}
};

class LinkedList
{

public:
	void insertInSorted(Node * & head, Node * iNode);
	void delete_node(Node * head, Node * nodeDelete);
	Node * head;

	Node * add_two_lists(Node * & head1, Node * & head2);
	bool add_two_lists_inner(Node * head1, Node * head2, Node * & outNode);
	void add_remaining_list(Node * head, Node * end, Node * & outNode, bool & needIncrement);
	static int getSize(Node * head);

	void insert_two_lists_alternative(Node * head1, Node * head2);
	Node * reverse_linked_lists_inner(Node * head, int & k, Node * nodeSwap);
	void reverse_linked_lists(Node * head, int k);
	void SwapNodes(Node * node1, Node * node2) 
	{
		int tmpValue = node1->value;
		node1->value = node2->value;
		node2->value = tmpValue;
	}

	Node * merge_two_sorted_linkedlist(Node * head1, Node * head2);

	Node * reverse_linked_list(Node * head1);
};