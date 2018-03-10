#include<vector>
#include<unordered_map>
#include<algorithm>

using namespace std;
class P39SumCombination
{
public:
	vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
		sort(candidates.begin(), candidates.end());
		vector<vector<int>> results;
		vector<int> oneSet;
		calculate(candidates, target, oneSet, results, 0);
		return results;
	}

	void calculate(vector<int> & candidates, int target, vector<int> oneSet, vector<vector<int>> & outResult, int index)
	{
		if (target == 0)
		{
			outResult.push_back(oneSet);
			return;
		}
		for (int i = index; i < candidates.size() && target >= candidates[index]; i++)
		{
			if (i > index && candidates[i] == candidates[i - 1])
				continue;
			oneSet.push_back(candidates[i]);
			calculate(candidates, target - candidates[i], oneSet, outResult, i + 1);
			oneSet.pop_back();
		}
	}
};




