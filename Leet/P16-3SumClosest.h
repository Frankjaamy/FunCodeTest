#pragma once
/*
Given an array S of n integers, find three integers in S such that the sum is closest to a given number, target. Return the sum of the three integers. You may assume that each input would have exactly one solution.
For example, given array S = {-1 2 1 -4}, and target = 1.

The sum that is closest to the target is 2. (-1 + 2 + 1 = 2).
*/

// 头一次尝试，做出来了，用了一个map,简直了，245毫秒，名列后茅
// 第二次尝试，看了解答，原来却是应该用头尾指针法，我一开始想到了，但是对两点没有认识到，导致没做出来
// 1 对已经排好序的数组，确定 i 值以后，我们可以知道 最小的三值和一定是(nums[i]+nums[i+1]+nums[i+2])
// 如果这个值都比目标值大的话，那么后面的一定会更大，所以碰到此种情况，直接输出这个三值之和就好了

//2 有了双值以后，我原来的老思路也是去记录所有sum和最小间距的map,所以卡住了。 
//  但是其实我们不需要这样做，因为我们要输出的是间距最小的和，我们只需要算出最小的间距，然后用原来给的target
//  与我们得到的最小和一加，就好了
//  此题比较考智商，好好记着吧。

#include "ManyPrerequisites.h"
class p16_3SumClosest : public LeetInterface{
public:
	int threeSumClosestVerySlow(vector<int>& nums, int target) {
		if (nums.size() == 0) return 0;
		sort(nums.begin(), nums.end());
		map<int, int> resultMap;
		for (unsigned int i = 0; i < nums.size()-2; i++)
		{
			for (unsigned j = i + 1; j < nums.size() - 1; j++)
			{
				int targetIndex = j + 1;
				int wanted = target - nums[i] - nums[j];
				int min = INT_MAX;
				for (unsigned k = j + 1; k < nums.size(); k++)
				{
					int tmp = abs(nums[k] - wanted);
					if (tmp < min)
					{
						min = tmp;
						targetIndex = k;
					}
				}
				resultMap[min] = nums[i] + nums[j] + nums[targetIndex];
			}
		}
		//sort(resultMap.begin(), resultMap.end(), [](pair<int, int> p1, pair<int, int> p2) {return p1.second < p2.second; });
		return resultMap.begin()->second;
	}
	int threeSumClosestFast(vector<int>& nums, int target)
	{
		if (nums.size() == 0) return 0;
		sort(nums.begin(), nums.end());
		int lowestDIff = INT_MAX;
		for (unsigned int i = 0; i < nums.size() - 2; i++)
		{
			int low = i + 1;
			int hight = nums.size() - 1;
			int newTarget = target - nums[i];
			int min_diff = nums[i] + nums[low] + nums[low + 1] - target;
			if (min_diff > 0)
			{
				if (abs(min_diff) < abs(lowestDIff)) lowestDIff = min_diff;
				break;
			}

			while (low < hight)
			{
				int newSum = nums[low] + nums[hight];
				if (newSum == newTarget) return target;

				if (newSum > newTarget) hight--;
				else low++;

				int new_diff = newSum - newTarget;
				if (abs(new_diff) < abs(lowestDIff)) lowestDIff = new_diff;
			}
		}
		return target + lowestDIff;
	}
	void runTest() 
	{
		vector<int> teset{ 1,1,-1 };
		p16_3SumClosest s;
		s.threeSumClosestFast(teset, 2);
	}
};