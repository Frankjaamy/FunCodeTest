#include<vector>
using namespace std;
class p16_3SumClosest
{
public:
	int find_sets(vector<int> iArray, int sumTotal)
	{
		int ** results = new int*[iArray.size()+1];
		for (int i = 0; i < iArray.size()+1; i++)
		{
			results[i] = new int[sumTotal+1];
			std::fill_n(results[i], sumTotal+1, 0);
		}
		
		results[0][0] = 1;

		for (int i = 1; i < iArray.size()+1; i++)
		{
			for (int newTotal = 0; newTotal <= sumTotal; newTotal++)
			{
				if(newTotal < iArray[i-1])
					results[i][newTotal] = results[i - 1][newTotal];
				else {
					results[i][newTotal] = results[i - 1][newTotal] + results[i - 1][newTotal - iArray[i-1]];
				}
			}
		}
		return results[iArray.size()][sumTotal];
	}
};
