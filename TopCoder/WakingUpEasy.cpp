// BEGIN CUT HERE

// END CUT HERE
#line 5 "WakingUpEasy.cpp"
#include <string>
#include <vector>

using namespace std;

class WakingUpEasy {
	public:
	int countAlarms(vector <int> volume, int S) {
		int ans = 0;
		int now = 0;
		int size = volume.size();
		while (S > 0)
		{
			S = S - volume[now];
			now = (now + 1) % size;
			ans++;
		}
		return ans;
	}
};
