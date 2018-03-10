/**
* Definition for a binary tree node.
*/
#include <vector>
struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 };

class p16_3SumClosest {
public:
	TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
		std::vector<TreeNode *> nodes;
		if (!getNodesBeforMeetTarget(root, p, nodes))
		{
			return nullptr;
		}
		bool isFound = false;
		for (auto iter : nodes)
		{
			if (tryFindNode(iter, q)) return iter;
		}
		return nullptr;
	}


	bool tryFindNode(TreeNode * root, TreeNode * targetNode)
	{
		if (!root) return false;
		if (!root->left && !root->right) return false ;
		if (root == targetNode || root->left == targetNode || root->right == targetNode)
		{
			return true;
		}
		else {
			return tryFindNode(root->left, targetNode) || tryFindNode(root->right, targetNode);
		}
	}

	bool getNodesBeforMeetTarget(TreeNode * root, TreeNode * targetNode, std::vector<TreeNode*> & nodes)
	{
		if (!root) return false;
		if (root == targetNode)
		{
			nodes.push_back(root);
			return true;
		}
		bool foundLeft = getNodesBeforMeetTarget(root->left, targetNode, nodes);
		bool foundRight = getNodesBeforMeetTarget(root->right, targetNode, nodes);
		if (foundLeft || foundRight)
		{
			nodes.push_back(root);
		}
		return foundLeft || foundRight;
	}
};