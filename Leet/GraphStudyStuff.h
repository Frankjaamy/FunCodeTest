#pragma once
#include<vector>
#include<stack>
#include<unordered_map>
#include<unordered_set>

struct GraphNode
{
	int label;
	GraphNode() :label(0) {}
	GraphNode(int x) : label(x) {}
};
struct GraphEdge
{
	GraphNode * srcNode;
	GraphNode * endNode;
	int weight;

	GraphEdge():srcNode(nullptr),endNode(nullptr),weight(0)
	{}

	GraphEdge(int iWeight, GraphNode * start, GraphNode * end)
		: weight(iWeight),srcNode(start),endNode(end)
	{}
};
struct AdjacementNode
{
	GraphNode * graphNode;
	int weight;
	AdjacementNode(GraphNode * gNode, int iWeight)
		: graphNode(gNode), weight(iWeight)
	{}
};

class UndirectedGraph
{
public:
	void initializeTestGraph(int V);
	void addEdge(GraphNode * srcNode, GraphNode * destNode, int weight = 0);
	void addEdge(int srcNode, int destNode, int weight = 0);
	void addEdge(GraphEdge * edge);

	void deleteEdge(GraphEdge * edge);
public:
	void traverseBFS(GraphNode * node, std::vector<GraphNode> & outResults, std::unordered_set<GraphNode *>& visitedSet);
	void traverseDFS(GraphNode * node, std::vector<GraphNode> & outResults, std::unordered_set<GraphNode *>& visitedSet);
	void topologicalSort(GraphNode * node, std::stack<GraphNode> & outResults, std::unordered_set<GraphNode *>& visitedSet);
	
	void checkCycle(GraphNode * node, std::unordered_set<GraphNode *>& visitedSet, std::unordered_map<GraphNode *, bool> & recurStack, bool & isCycle);
	bool checkCycle();
private:
	GraphNode * findNodes(GraphNode * node);
	void unionNodes(GraphNode * node1, GraphNode * node2);
public:
	UndirectedGraph * mimimumSpanningTree();
	UndirectedGraph * mimimumSPanningTreePrim();
public:
	std::vector<GraphNode *> nodes;
	std::vector<GraphEdge *> edges;

	std::unordered_map<GraphNode *, std::vector<AdjacementNode *>> adjacements;
	std::unordered_map<GraphNode *, GraphNode *> parents;
	
	std::unordered_set<GraphNode *> visitedSet;
};

