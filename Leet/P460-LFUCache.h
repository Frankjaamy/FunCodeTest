#pragma once
//关于这道LFU的题，还有点可说的....
//首先 我最开始使用的是 链表加哈希的方式，并且用的是LFU的算法 -- 即一旦缓存命中，则对应的缓存
//object 根据频率状态向前挪动， 之后如果缓存满了 则删除链表最后的元素....

//我是觉得这种做法没有问题，但是单就leetcode这道题来说，这样做不可以，因为如果一开始就一直添加缓存元素
//知道容量溢出的话，我的这种方法会导致 最先加入的object会被删除（因为我得保证链表头是频率最高的元素，所以
//要用push_back, 但这样的话就相当于如果大家都频率相同，你一个劲儿往里加，那么就是最先加入的会被删除）。
//这样的话有些testcase跑不过。

//之后我看了答案解法，是三个哈希表，一个表示key与实际缓存物体，一个表示当前某个频率下面所有的物体，一个表示
// 某个key所对应的当前激活的迭代器。 在get和put这两个函数中合理地操作这三个链表，并且维护一个最低频率值
//即可做出这道题。 以后多看看，这题还是有点绕的。
#include "ManyPrerequisites.h"
class LFUCache : public LeetInterface
{
public:
	struct CacheObject
	{
		int keyId;
		int value;
		int visitedCount;
		CacheObject(int KeyId, int Value, int Visited = 0) : keyId(KeyId), value(Value), visitedCount(Visited)
		{ }
	};

	LFUCache(int capacity) {
		cacheCapacity = capacity;
	}

	int get(int key) {
		auto iter = mapKeyToValueAndFreq.find(key);
		if (iter == mapKeyToValueAndFreq.end())
		{
			return -1;
		}
		CacheObject * object = *(mapKeyToIter[key]);
		mapFreqToList[iter->second->visitedCount].erase(mapKeyToIter[key]);
		mapKeyToValueAndFreq[key]->visitedCount++;
		mapFreqToList[iter->second->visitedCount].push_front(object);
		mapKeyToIter[key] = mapFreqToList[iter->second->visitedCount].begin();

		if (mapFreqToList[curMinFreq].size() == 0)
		{
			curMinFreq++;
		}
		return mapKeyToValueAndFreq[key]->value;

	}

	void put(int key, int value) {
		if (get(key) == -1) {
			if (cacheCapacity > 0)
			{
				mapFreqToList[0].push_front(new CacheObject(key, value));
				mapKeyToIter[key] = mapFreqToList[0].begin();
				mapKeyToValueAndFreq[key] = *mapKeyToIter[key];

				curMinFreq = 0;
				cacheCapacity--;
				curSize++;
			}
			else 
			{
				if (curSize > 0)
				{
					mapKeyToValueAndFreq.erase(mapFreqToList[curMinFreq].back()->keyId);
					mapKeyToIter.erase(mapFreqToList[curMinFreq].back()->keyId);
					mapFreqToList[curMinFreq].pop_back();

					mapFreqToList[0].push_front(new CacheObject(key, value));
					mapKeyToIter[key] = mapFreqToList[0].begin();
					mapKeyToValueAndFreq[key] = *mapKeyToIter[key];
					curSize++;
				}
			}
		}
		else
		{
			mapKeyToValueAndFreq[key]->value = value;
		}
	}
	
public:
	unordered_map<int, list<CacheObject*>::iterator> mapKeyToIter;
	unordered_map<int, list<CacheObject*>> mapFreqToList;
	unordered_map<int, CacheObject *> mapKeyToValueAndFreq;

	int cacheCapacity;
	int curMinFreq = 0;
	int curSize = 0;
public:
	void LeetInterface::runTest()
	{
		LFUCache lru(2);
		lru.put(1, 1);
		lru.put(2, 2);
		int i = lru.get(1);
		lru.put(3, 3);
		i = lru.get(2);
		i = lru.get(3);
		lru.put(4, 4);
		i = lru.get(1);
		i = lru.get(3);
		i = lru.get(4);
		return;
	}
};