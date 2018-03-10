#include "ManyPrerequisites.h"
struct TreeNode
{
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class p16_3SumClosest {
public:
	vector<TreeNode*>  calculate(int start, int end)
	{
		vector<TreeNode * > vec;
		if (start > end)
		{
			vec.push_back(nullptr);
		}
		else if (start == end) {
			vec.push_back(new TreeNode(start));
		}
		else {
			for (int i = start; i <= end; i++)
			{
				vector<TreeNode *> left = calculate(start, i - 1);
				vector<TreeNode *> right = calculate(i + 1, end);
				for (auto iterLeft : left)
				{
					for (auto iterRight : right)
					{
						TreeNode * newNode = new TreeNode(i);
						newNode->left = iterLeft;
						newNode->right = iterRight;
						vec.push_back(newNode);
					}
				}
			} 
		}
		return vec;
	}
	vector<TreeNode*> generateTrees(int n) {
		vector<TreeNode * > results;
		if (n == 0) return results;
		return calculate(1, n);
	}
};
#if 0
int main()
{
	Solution s;
	vector<TreeNode *> nodes = s.generateTrees(3);
	return 0;
}
#endif
