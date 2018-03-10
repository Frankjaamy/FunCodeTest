#pragma once
#include "ManyPrerequisites.h"
class P144BinTreePreTraverse : public LeetInterface
{
public :
	//Definition for a binary tree node.
	struct TreeNode {
	     int val;
	     TreeNode *left;
	     TreeNode *right;
	     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
	 };
	
	vector<int> preorderTraversal(TreeNode* root) {
		vector<int> results;
		if (root == nullptr) return results;

		stack<TreeNode *> stackUsed;
		stackUsed.push(root);

		while (!stackUsed.empty())
		{
			TreeNode * node = stackUsed.top();
			stackUsed.pop();
			results.push_back(node->val);

			if (node->right) stackUsed.push(node->right);
			if (node->left) stackUsed.push(node->left);
		}

		return results;
	}
public:
	void LeetInterface::runTest()
	{
		P144BinTreePreTraverse solusion;
		
	}
};