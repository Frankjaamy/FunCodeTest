
#include "ManyPrerequisites.h"
class p16_3SumClosest {
public:
	vector<vector<int>> threeSum(vector<int>& nums) {
		vector<vector<int>> results;
		if (nums.size() == 0) return results;
		sort(nums.begin(), nums.end());

		for (int i = 0; i < nums.size() - 1; i++)
		{
			int front = i + 1;
			int back = nums.size() - 1;
			int target = -nums[i];
			while (front < back)
			{
				int triplet1 = nums[front];
				int triplet2 = nums[back];
				if (triplet1 + triplet2 == target)
				{
					results.push_back(vector<int>{nums[i], triplet1, triplet2});
					while (front < back && nums[back] == triplet2) back--;
					while (front < back && nums[front] == triplet1) front++;
				}
				else if(triplet1 + triplet2 > target)
				{
					back--;
				}
				else {
					front++;
				}
			}
			target = nums[i];
			while (i < nums.size() - 1 && nums[i + 1] == target) i++;
		}
		return results;
	}
};
#if 0
int main()
{
	vector<int> nums{ -4,-2,-2,-2,0,1,2,2,2,3,3,4,4,6,6 };
	Solution s;
	vector<vector<int>> re = s.threeSum(nums);
	return 0;
}
#endif
