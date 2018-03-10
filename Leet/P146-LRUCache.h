#pragma once
//这是一道我在学习System Design的时候 想好好思考一下LRU的Cache队列 从而做的题
//因为之前有一定思路了，所以我一开始就采用了 list(就是双向链表） 之后可以考虑加 哈希表 缩短大O的做法
//但是我做完以后，发现卧槽，程序跑的好慢，就否认了自己的思路，开始往别处想，就走歪了，浪费了很多时间

//实际上，我最重要的问题出在： 我的代码之所以慢，是因为我TM在删除结点的时候，使用了 List 的 Remove, 而
//不是List 的 Erase. 前者TM遍历寻找链表删除指定元素，后者直接删除指定的迭代器所对应的元素，高下立判。
//而我没仔细看这一点，而草草地去思考别的思路了，实在是不应该。

//教训： List的Remove以及 Erase的区别， 要更加冷静，认真地审题。
#include "ManyPrerequisites.h"
class LRUCache : public LeetInterface
{
public:
	struct CacheObject
	{
		int keyId;
		int value;
		CacheObject(int KeyId, int Value) : keyId(KeyId), value(Value)
		{ }
	};

	LRUCache(int capacity) {
		cacheCapacity = capacity;
	}

	int get(int key) {
		auto iter = cachedHash.find(key);
		if (iter == cachedHash.end())
		{
			return -1;
		}
		CacheObject * object = *(iter->second);
		cachedList.erase(iter->second);
		cachedList.push_front(object);
		cachedHash[key] = cachedList.begin();
		return (*cachedHash[key])->value;
	}

	void put(int key, int value) {
		if (get(key) == -1) {
			if (cacheCapacity > 0)
			{
				cachedList.push_front(new CacheObject(key, value));
				cacheCapacity--;
			}
			else
			{
				if (cachedList.size() > 0)
				{
					cachedHash.erase(cachedList.back()->keyId);
					cachedList.pop_back();
					cachedList.push_front(new CacheObject(key, value));
				}
			}
		}
		else
		{
			cachedList.front()->value = value;
		}
		cachedHash[key] = cachedList.begin();
	}

public:
	list<CacheObject *> cachedList;
	unordered_map<int, list<CacheObject*>::iterator> cachedHash;
	int cacheCapacity;

public:
	void LeetInterface::runTest()
	{
		LRUCache lru(2);
		lru.put(1, 1);
		lru.put(2, 2);
		int i = lru.get(1);
		lru.put(3, 3);
		i = lru.get(2);
		lru.put(4, 4);
		i = lru.get(1);
		i = lru.get(3);
		i = lru.get(4);
		return;
	}
};