#include<vector>
#include<unordered_map>

using namespace std;

struct TreeNode 
{
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class p16_3SumClosest {
	vector<int> findMode(TreeNode* root)
	{
		vector<int> returnResult;
		unsigned int curMaxCount = 0;
		FindTheNode(root);

		std::unordered_map<int, std::vector<int>> resMap;
		for (auto iter : m_map)
		{
			curMaxCount = iter.second > curMaxCount ? iter.second : curMaxCount;
			resMap[iter.second].push_back(iter.first);
		}
		return resMap[curMaxCount];
	}
	void FindTheNode(TreeNode * root)
	{
		if (!root) return;
		FindTheNode(root->left);
		m_map[root->val]++;
		FindTheNode(root->right);
	}
private:
	std::unordered_map<int, int> m_map;
};