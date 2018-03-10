
#include "ManyPrerequisites.h"
//Definition for a binary tree node.
 struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 };

 class p16_3SumClosest {
 public:
	 vector<int> inorderTraversal(TreeNode* root) {
		 vector<int> result;
		 if (!root) return result;
		 stack<TreeNode *> nodeStack;
		 if (root->left)
			 visitSubTree(root->left, result, nodeStack);
		 result.push_back(root->val);
		 if (root->right)
			 visitSubTree(root->right, result, nodeStack);
		 return result;
	 }

	 void visitSubTree(TreeNode * root, vector<int> & result, stack<TreeNode *> & nodeStack)
	 {
		 nodeStack.push(root);
		 do
		 {
			 while (root->left)
			 {
				 nodeStack.push(root->left);
				 root = root->left;
			 }
			 TreeNode * tmpNode = nodeStack.top();
			 nodeStack.pop();

			 result.push_back(tmpNode->val);
			 root = tmpNode->right;
			 if (root) nodeStack.push(root);
		 } while (!nodeStack.empty());
	 }
 };
