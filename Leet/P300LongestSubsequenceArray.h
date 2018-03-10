#pragma once
#include "ManyPrerequisites.h"

/*
Given an unsorted array of integers, find the length of longest increasing subsequence.

For example,
Given [10, 9, 2, 5, 3, 7, 101, 18],
The longest increasing subsequence is [2, 3, 7, 101], therefore the length is 4. Note that there may be more than one LIS combination, it is only necessary for you to return the length.

Your algorithm should run in O(n2) complexity.

Follow up: Could you improve it to O(n log n) time complexity?

Credits:
Special thanks to @pbrother for adding this problem and creating all test cases.

*/
//不行不行 完全不会做，完全不会做, DP 都他妈晕了，更别提优化解了，真他妈怀疑人生
//

class P300_LongestSubArray : public LeetInterface
{
public:
	int lengthOfLIS(vector<int>& nums)
	{
		int maxLength = 0;
		int currentMax = 1;
		int * results = new int[nums.size()];
		fill_n(results, nums.size(), 1);

		for (unsigned int i = 1; i < nums.size(); i++)
		{
			for (unsigned j = 0; j < i; j++)
			{
				if (nums[i] > nums[j] && results[j] + 1 > results[i])
					results[i] = results[j] + 1;
			}
		}
		for (unsigned int i = 0; i < nums.size(); i++)
		{
			maxLength = max(maxLength, results[i]);
		}
		return maxLength;
	}
public:
	void LeetInterface::runTest()
	{
		P300_LongestSubArray s;
		vector<int> test{ 1,3,6,7,9,4,10,5,6 };
		int result = s.lengthOfLIS(test);
		return;
	}
};
