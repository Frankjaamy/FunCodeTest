#pragma once
/*
Given an array S of n integers, are there elements a, b, c, and d in S such that a + b + c + d = target? Find all unique quadruplets in the array which gives the sum of target.

Note: The solution set must not contain duplicate quadruplets.
*/
#include "ManyPrerequisites.h"
class P18_4Sum : public LeetInterface
{
public:
	vector<vector<int>> fourSum(vector<int> & nums, int target = 0)
	{
		vector<vector<int>> results;
		if (nums.size() < 4) return results;

		int numLen = nums.size();
		sort(nums.begin(), nums.end());
		unsigned int i = 0;
		for (i = 0; i < nums.size() - 3; i++)
		{
			if (nums[i] + nums[i + 1] + nums[i + 2] + nums[i + 3] > target) break;
			if(nums[i] + nums[numLen-1] + nums[numLen-2] + nums[numLen-3] < target) continue;

			for (unsigned j = i + 1; j < nums.size() - 2; j++)
			{
				if (nums[i] + nums[j] + nums[j + 1] + nums[j + 2] > target) break;
				if (nums[i] + nums[j] + nums[numLen - 2] + nums[numLen - 1] < target) continue;

				int left = j + 1;
				int right = numLen - 1;
				while (left < right)
				{
					int sum = nums[i] + nums[j] + nums[left] + nums[right];
					if (sum < target) left++;
					else if (sum > target) right--;
					else
					{
						results.push_back(vector<int>{nums[i], nums[j], nums[left], nums[right]});
						do { left++; } while (left < right && nums[left] == nums[left - 1]);
						do { right--; } while (left < right && nums[right] == nums[right + 1]);
					}
				}
				while (j<nums.size() && nums[j] == nums[j + 1]) j++;
			}
			while (i < nums.size() && nums[i] == nums[i + 1]) i++;
		}
		return results;
	}
	vector<vector<int>> threeSum(vector<int> & nums, int target)
	{
		vector<vector<int>> results;
		if (nums.size() < 3) return results;
		sort(nums.begin(), nums.end());
		
		for (unsigned i = 0; i < nums.size() - 2; i++)
		{
			int front = i + 1;
			int end = nums.size() - 1;
			while (front < end)
			{
				int newTarget = target - nums[i];
				int sum = nums[front] + nums[end];
				if (sum > newTarget) end--;
				else if (sum < newTarget)front++;
				else 
				{
					results.push_back(vector<int>{nums[i], nums[front], nums[end]});
					do {
						front++;
					} while (front < end && nums[front] == nums[front-1]);
					
					do {
						end--;
					}
					while (front < end && nums[end] ==nums[end+1]);
				}
			}
			while (i < nums.size() - 1 && nums[i] == nums[i + 1]) i++;
		}
		return results;
	}

	void runTest()
	{
		vector<int> nums{ -1, 0, -5, -2, -2, -4, 0, 1, -2 };
		P18_4Sum s;
		vector<vector<int>> a = s.fourSum(nums,-9);
	}
};