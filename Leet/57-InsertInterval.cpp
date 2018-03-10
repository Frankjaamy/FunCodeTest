#include<vector>
#include<math.h>
#include<algorithm>

struct Interval {
     int start;
     int end;
     Interval() : start(0), end(0) {}
     Interval(int s, int e) : start(s), end(e) {}
 };

using namespace std;
class p16_3SumClosest {
public:
	enum mergeResult
	{
		eNotOverlapping,
		ePartOverlapping,
		eOverlapping
	};
public:
	vector<Interval> insert(vector<Interval>& intervals, Interval newInterval) {
		vector<Interval> results;
		results.push_back(newInterval);
		if (intervals.empty()) return results;
		size_t indexMain = 0;
		size_t indexReturn = 0;
		while (indexMain < intervals.size())
		{
			switch (tryMerge(results[indexReturn], intervals[indexMain], newInterval))
			{
				case eOverlapping:
				{
				}
				break;
				case ePartOverlapping:
				{
					results.pop_back();
					results.push_back(newInterval);
				}
				break;
				case eNotOverlapping:
				{
					results.push_back(intervals[indexMain]);
					indexReturn++;
					sort(results.begin(), results.end(), 
						[](const Interval & i1, const Interval i2) {
						return i1.start < i2.start;
					});
				}
				break;
			default:
				break;
			}
			indexMain++;
		}
		return results;
	}

	mergeResult tryMerge(const Interval & i1, const Interval & i2, Interval & newInterval)
	{
		if (i1.start<i2.start && i1.end > i2.end)
		{
			return eOverlapping;
		}
		else if (i1.start > i2.end || i1.end < i2.start)
		{
			return eNotOverlapping;
		}
		else 
		{
			newInterval = Interval(min(i1.start, i2.start), max(i1.end, i2.end));
			return ePartOverlapping;
		}
	}
};