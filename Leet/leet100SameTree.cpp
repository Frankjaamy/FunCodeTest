
struct TreeNode 
{
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class p16_3SumClosest {
public:
	bool isSameTree(TreeNode* p, TreeNode* q) {
		if (p == nullptr && q == nullptr){
			return true;
		}
		else if ((!p&&q) || (p && !q)) {
			return false;
		}
		else if (p && q && !p->left && !p->right &&!q->left && !q->right)
		{
			if (p->val == q->val) return true;
			else return false;
		}
		

		bool bLeft = isSameTree(p->left, q->left);
		bool bRight = isSameTree(p->right, q->right);

		if (bLeft && bRight && p->val == q->val)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
};
