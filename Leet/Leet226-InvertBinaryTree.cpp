#include<algorithm>
#include<vector>
#include<stack>

//Definition for a binary tree node.
struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 };

class p16_3SumClosest {
public:
	TreeNode* invertTree(TreeNode* root)
	{
		return invertTreeBFS(root);
	}

	TreeNode * invertTreeRecursive(TreeNode * root)
	{
		if (!root)
			return nullptr;
		std::swap(root->left, root->right);
		invertTreeRecursive(root->right);
		invertTreeRecursive(root->left);
		return root;
	}

	TreeNode * invertTreeBFS(TreeNode * root)
	{
		std::stack<TreeNode *> nodes;
		nodes.push(root);

		while (!nodes.empty())
		{
			TreeNode * currentRoot = nodes.top();
			std::swap(currentRoot->left, currentRoot->right);
			nodes.pop();

			if (currentRoot->left)
				nodes.push(currentRoot->left);
			if (currentRoot->right)
				nodes.push(currentRoot->right);
		}
		return root;
	}
};
