// BEGIN CUT HERE

// END CUT HERE
#line 5 "LexmaxReplace.cpp"
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class LexmaxReplace {
	public:
	string get(string s, string t) {
		sort(t.begin(), t.end(), greater<char>());
		int now = 0;
		for (int i = 0; i < s.length(); i++)
		{
			if (t[now] > s[i])
			{
				s[i] = t[now];
				now++;
			}
			if (now == t.length())
			{
				break;
			}
		}
		return s;
	}
};
