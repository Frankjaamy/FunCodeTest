#include <vector>
#include <queue>
#include <algorithm>

typedef std::pair<int, int> coord;
using namespace std;
class p16_3SumClosest {
public:
	int minPathSum(vector<vector<int>>& grid)
	{
		int n = grid.size();
		int m = grid[0].size();

		int **sum = new int*[n];
		for (int i = 0; i < n; i++)
		{
			sum[i] = new int[m];
			std::fill_n(sum[i], m, -1);
		}
		
		std::queue<coord> graphNodes;
		graphNodes.push(std::make_pair(0,0));
		sum[0][0] = grid[0][0];

		int directions[2][2] = {
			{ 0,1 },
			{ 1,0 }
		};

		while (!graphNodes.empty())
		{
			coord curCoord = graphNodes.front();
			graphNodes.pop();
			
			int curRow = curCoord.first;
			int curCol = curCoord.second;

			for (int i = 0; i < 2; i++)
			{
				if(curRow + directions[i][0] >=n || curCol + directions[i][1] >= m)
					continue;

				int * pValue = &sum[curRow + directions[i][0]][curCol + directions[i][1]];
				if (*pValue < 0)
				{
					*pValue = 0;
					*pValue = sum[curRow][curCol]+grid[curRow + directions[i][0]][curCol + directions[i][1]];
					graphNodes.push(std::make_pair(curRow + directions[i][0], curCol + directions[i][1]));
				}
				else 
				{
					int newValue = grid[curRow + directions[i][0]][curCol+directions[i][1]] + sum[curRow][curCol];
					*pValue = std::min(newValue, *pValue);
				}
			}
		}
		return sum[n - 1][m - 1];
	}
};
