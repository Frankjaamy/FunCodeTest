#include<queue>
#include<list>

#include<unordered_set>
#include<unordered_map>

#include<algorithm>

#include "GraphStudyStuff.h"

void UndirectedGraph::initializeTestGraph(int V)
{
	if (nodes.empty())nodes.reserve(V);

	for (unsigned int i = 0; i < V; i++)
	{
		nodes.push_back(new GraphNode(i));
	}
}

void UndirectedGraph::addEdge(GraphNode * srcNode, GraphNode * destNode, int weight /*= 0*/)
{
	edges.push_back(new GraphEdge(weight, srcNode, destNode));
	adjacements[srcNode].push_back(new AdjacementNode(destNode,weight));
	adjacements[destNode].push_back(new AdjacementNode(srcNode,weight));
}

void UndirectedGraph::addEdge(int srcNode, int destNode, int weight /*= 0*/)
{
	edges.push_back(new GraphEdge(weight, nodes[srcNode], nodes[destNode]));
	adjacements[nodes[srcNode]].push_back(new AdjacementNode(nodes[destNode], weight));
	adjacements[nodes[destNode]].push_back(new AdjacementNode(nodes[srcNode], weight));
}

void UndirectedGraph::addEdge(GraphEdge * edge)
{
	addEdge(edge->srcNode, edge->endNode, edge->weight);
}


void UndirectedGraph::deleteEdge(GraphEdge * edge)
{

}

void UndirectedGraph::traverseBFS(GraphNode * node, std::vector<GraphNode> & outResults, std::unordered_set<GraphNode *>& visitedSet)
{
	if ( node==nullptr ) return;
	static std::unordered_set<GraphNode *> visitSet;
	std::queue<GraphNode *> nodeQueue;
	nodeQueue.push(node);
	visitSet.insert(node);

	while (!nodeQueue.empty())
	{
		GraphNode * node = nodeQueue.front();
		outResults.push_back(*node);
		nodeQueue.pop();
		for (unsigned int i = 0; i < adjacements[node].size(); i++)
		{
			if (visitSet.find(adjacements[node][i]->graphNode) == visitSet.end())
			{
				visitSet.insert(adjacements[node][i]->graphNode);
				nodeQueue.push(adjacements[node][i]->graphNode);
			}
		}
	}
}

void UndirectedGraph::traverseDFS(GraphNode * node, std::vector<GraphNode> & outResults, std::unordered_set<GraphNode *>& visitedSet)
{
	if (node == nullptr) return;
	if (visitedSet.find(node) != visitedSet.end()) return;

	visitedSet.insert(node);
	outResults.push_back(*node);

	for (unsigned int i = 0; i < adjacements[node].size(); i++)
	{
		traverseDFS(adjacements[node][i]->graphNode, outResults, visitedSet);
	}
}

void UndirectedGraph::topologicalSort(GraphNode * node, std::stack<GraphNode> & outResults, std::unordered_set<GraphNode *>& visitedSet)
{
	if (node == nullptr) return;
	if (visitedSet.find(node) != visitedSet.end()) return;

	visitedSet.insert(node);
	for (unsigned int i = 0; i < adjacements[node].size(); i++)
	{
		topologicalSort(adjacements[node][i]->graphNode, outResults, visitedSet);
	}
	outResults.push(*node);
}

void UndirectedGraph::checkCycle(GraphNode * node, std::unordered_set<GraphNode *>& visitedSet, std::unordered_map<GraphNode *, bool> & recurStack, bool & isCycle)
{
	if (node == nullptr) return;

	if (visitedSet.find(node) != visitedSet.end())
	{
		if (recurStack[node])
			isCycle = true;
		return;
	}
	
	visitedSet.insert(node);
	recurStack[node] = true;

	if (adjacements.find(node) != adjacements.end())
	{
		for (unsigned int i = 0; i < adjacements[node].size(); i++)
		{
			checkCycle(adjacements[node][i]->graphNode, visitedSet, recurStack, isCycle);
		}
	}
	recurStack[node] = false;
}

bool UndirectedGraph::checkCycle()
{
	parents.clear();
	for (auto iter : edges)
	{
		GraphNode * n1 = findNodes(iter->srcNode);
		GraphNode * n2 = findNodes(iter->endNode);
		if (n1 == n2)
		{
			return true;
		}
		unionNodes(n1, n2);
	}
	return false;
}

GraphNode * UndirectedGraph::findNodes(GraphNode * node)
{
	if (parents.find(node) == parents.end())
	{
		return node;
	}
	else 
	{
		return findNodes(parents[node]);
	}
}

void UndirectedGraph::unionNodes(GraphNode * node1, GraphNode * node2)
{
	GraphNode * n1 = findNodes(node1);
	GraphNode * n2 = findNodes(node2);
	parents[n1] = n2;
}

UndirectedGraph * UndirectedGraph::mimimumSpanningTree()
{
	UndirectedGraph * g = new UndirectedGraph();
	for (auto iter : nodes)
	{
		g->nodes.push_back(iter);
	}

	int totalEdges = nodes.size() - 1;
	sort(edges.begin(), edges.end(), [](const GraphEdge * edge1, const GraphEdge * edge2) {return edge1->weight < edge2->weight; });
	int index = 0;
	int edgesNew = 0;
	while (index < edges.size() && edgesNew < totalEdges)
	{
		GraphEdge * edge = edges[index];
		g->addEdge(edge->srcNode, edge->endNode, edge->weight);
		if (g->checkCycle())
		{
			g->edges.pop_back();
			g->adjacements[edge->srcNode].pop_back();
			g->adjacements[edge->endNode].pop_back();
		}
		else 
		{
			edgesNew++;
		}
		index++;
	}
	std::unordered_map<GraphNode *, std::vector<AdjacementNode *>>::iterator iter = g->adjacements.begin();

	for (;iter!=g->adjacements.end();)
	{
		if (iter->second.size() == 0)
		{
			iter = g->adjacements.erase(iter);
		}
		else {
			++iter;
		}
	}
	return g;
}

UndirectedGraph * UndirectedGraph::mimimumSPanningTreePrim()
{
	UndirectedGraph * graph = new UndirectedGraph();
	
	std::list<std::pair<int, int>> nodeList;

	for (unsigned int i = 0; i < nodes.size(); i++)
	{
		nodeList.push_back(std::make_pair(i,i == 0?0:10000));
	}

	do 
	{
		auto compareFunc = [](std::pair<int, int> p1, std::pair<int, int> p2) { return p1.second < p2.second; };
		//sort(nodeList.begin(), nodeList.end(),compareFunc);
		nodeList.sort(compareFunc);
		
		GraphNode * node = nodes[nodeList.front().first];
		int weightChecking = nodeList.front().second;

		graph->nodes.push_back(node);
		nodeList.pop_front();
		
		GraphNode * newSrcNode = nullptr;
		for (auto iter : adjacements[node])
		{
			if(iter->weight == weightChecking)
			{
				newSrcNode = iter->graphNode;
			}
			for (auto & iterlist : nodeList)
			{
				if (nodes[iterlist.first] == iter->graphNode)
				{
					iterlist.second = std::min(iterlist.second,iter->weight);
				}
			}
		}
		if(newSrcNode)
			graph->addEdge(newSrcNode, node, weightChecking);
	} while (!nodeList.empty());
	return graph;
}

