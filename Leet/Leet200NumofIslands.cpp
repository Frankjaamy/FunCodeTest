#include "ManyPrerequisites.h"
typedef pair<int, int> NodeCoord;
class p16_3SumClosest {
public:
	int numIslands(vector<vector<char>>& grid) {
		bool ** visited = new bool *[grid.size()];
		for (int i = 0; i < grid.size(); i++)
		{
			visited[i] = new bool[grid[i].size()];
			fill_n(visited[i], grid[0].size(), false);
		}

		int countRet = 0;
		int directions[4][2] = {
			{ -1,0 },
			{ 1,0 },
			{ 0,1 },
			{ 0,-1 }
		};

		for (int row = 0; row < grid.size(); row++)
		{
			for (int col = 0; col < grid[row].size(); col++)
			{
				if (visited[row][col]) continue;
				if (!grid[row][col]) continue;

				stack<NodeCoord> nodes;
				nodes.push(make_pair(row, col));
				visited[row][col] = true;
				while (!nodes.empty())
				{
					NodeCoord nodeCoor = nodes.top();
					nodes.pop();

					for (int i = 0; i < 4; i++)
					{
						int newRow = nodeCoor.first + directions[i][0];
						int newCol = nodeCoor.second + directions[i][1];

						if (newRow < 0 || newRow >= grid.size() || newCol < 0 || newCol >= grid[0].size())
						{
							continue;
						}
						if (!visited[newRow][newCol] && grid[newRow][newCol] != 0)
						{
							nodes.push(make_pair(newRow, newCol));
							visited[newRow][newCol] = true;
						}
					}
				}
				countRet++;
			}
		}
		return countRet;
	}
};
