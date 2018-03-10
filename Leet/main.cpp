//Definition for a binary tree node.
#include"LinkedList.h"
#include "LeetCodeTestInterface.h"
#include "P300LongestSubsequenceArray.h"
#include "P16-3SumClosest.h"
#include "P18-4Sum.h"
#include "P460-LFUCache.h"
#include<iostream>


int main()
{
	LeetInterface * l = new LFUCache(2);
	l->runTest();
	delete l;
	return 0;
}