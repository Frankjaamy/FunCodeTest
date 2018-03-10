struct TreeNode
{
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};
class p16_3SumClosest {
public:
	bool isValidBSTInOrder(TreeNode * root, TreeNode * &prev)
	{
		if (!root) return true;
		if (!isValidBSTInOrder(root->left, prev)) return false;
		if (prev && prev->val >= root->val) return false;
		prev = root;
		return (isValidBSTInOrder(root->right, prev));
	}
	bool isValidBST(TreeNode* root) {
		TreeNode * prev = nullptr;
		return isValidBSTInOrder(root, prev);
	}
};
/*
int main()
{
	TreeNode * node = new TreeNode(1);
	node->left = new TreeNode(1);

	Solution s;
	bool b = s.isValidBST(node);
	return 0;
}
*/