#include<vector>
#include<queue>
#include<unordered_map>
#include<algorithm>
using namespace std;

class p16_3SumClosest {
public:
	vector<int> twoSum(vector<int>& nums, int target) {
		vector<int> result;
		if (nums.size() == 0) return result;
		unordered_map<int, int> hash;

		for (int i = 0; i < nums.size(); i++)
		{
			int newTarget = target - nums[i];
			if (hash.find(newTarget) != hash.end())
			{
				result.push_back(hash[newTarget]);
				result.push_back(i);
				return result;
			}

			hash[nums[i]] = i;
		}
		return result;
	}
};