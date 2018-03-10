struct TreeNode 
{
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class p16_3SumClosest 
{
public:
	TreeNode * FindSuccessor(TreeNode * root)
	{
		TreeNode * current = root->right;
		while (current->left)
		{
			current = current->left;
		}
		return current;
	}
	TreeNode* deleteNode(TreeNode* root, int key) 
	{
		if (!root) return nullptr;
		else if (root->val < key)
		root->right = deleteNode(root->right, key);
		else if (root->val > key)
		root->left = deleteNode(root->left, key);
		else
		{
			if (!root->right) 
			{
				TreeNode * left = root->left;
				delete root;
				return left;
			}
		TreeNode * mimnumNode = FindSuccessor(root);
		root->val = mimnumNode->val;
		root->right = deleteNode(root->right, root->val);
		}
		return root;
	}
};