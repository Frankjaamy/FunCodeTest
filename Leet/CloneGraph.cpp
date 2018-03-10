//Definition for undirected graph.
#include<vector>
#include<unordered_map>
#include<queue>

using namespace std;

struct UndirectedGraphNode 
{
     int label;
     vector<UndirectedGraphNode *> neighbors;
     UndirectedGraphNode(int x) : label(x) {};
 };

class p16_3SumClosest {
public:
	UndirectedGraphNode *cloneGraphDFS(UndirectedGraphNode *node) 
	{
		if (node == nullptr) return nullptr;
		bool bExisted;
		UndirectedGraphNode * newNode = copyNode(node, bExisted);
		if (bExisted){
			return newNode;
		}
		else {
			for (auto iter : node->neighbors)
			{
				newNode->neighbors.push_back(cloneGraphDFS(iter));
			}
		}
		return newNode;
	}
	UndirectedGraphNode * cloneGraphBFS(UndirectedGraphNode * node)
	{
		if (!node) return nullptr;
		m_NodeQueue.push(node);
		
		bool bExisted;
		UndirectedGraphNode * newroot = copyNode(node, bExisted);

		while (!m_NodeQueue.empty())
		{
			UndirectedGraphNode * nodeInUse = m_NodeQueue.front();
			m_NodeQueue.pop();
			UndirectedGraphNode * nodeRootClone = copyNode(nodeInUse, bExisted);

			for (auto iter : nodeInUse->neighbors)
			{
				UndirectedGraphNode * nodeNeiborClone = copyNode(iter, bExisted);
				if(!bExisted)
					m_NodeQueue.push(iter);
				nodeRootClone->neighbors.push_back(nodeNeiborClone);
			}
		}
		return newroot;
	}
	UndirectedGraphNode * copyNode(UndirectedGraphNode * nodeSource, bool & alreadyExisted)
	{
		auto nodeFind = visited.find((uintptr_t)nodeSource);
		if (nodeFind == visited.end())
		{
			UndirectedGraphNode * clonedNode = new UndirectedGraphNode(nodeSource->label);
			visited[(uintptr_t)nodeSource] = (uintptr_t)clonedNode;
			alreadyExisted = false;
			return clonedNode;
		}
		else 
		{
			alreadyExisted = true;
			return (UndirectedGraphNode *)nodeFind->second;
		}
	}
private:
	std::unordered_map<uintptr_t, uintptr_t> visited;
	std::queue<UndirectedGraphNode *> m_NodeQueue;
};



