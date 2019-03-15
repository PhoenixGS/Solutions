// BEGIN CUT HERE

// END CUT HERE
#line 5 "NiceTable.cpp"
#include <string>
#include <vector>

using namespace std;


class NiceTable {
	public:
	int kk[40][40];
	int f[40];
	
	int findfather(int x)
	{
		return f[x] == x ? x : f[x] = findfather(f[x]);
	}

	void unionx(int x, int y)
	{
		int xx = findfather(x);
		int yy = findfather(y);
		if (xx != yy)
		{
			f[xx] = yy;
		}
	}
	
	string isNice(vector <string> t) {
		string Nice = "Nice";
		string NotNice = "Not nice";
		int n = t.size();
		int m = t[0].length();
		for (int i = 1; i <= n; i++)
		{
			for (int j = 1; j <= m; j++)
			{
				kk[i][j] = t[i - 1][j - 1] == '0' ? 0 : 1;
			}
		}
		for (int i = 1; i <= 2 * (n + m); i++)
		{
			f[i] = i;
		}
		bool flag = true;
		for (int i = 1; i <= n; i++)
		{
			for (int j = 1; j <= m; j++)
			{
				if (kk[i][j] == 0)
				{
					int x = i;
					int y = j + n;
					int k = n + m;
					if (findfather(x) == findfather(y + k))
					{
						flag = false;
						break;
					}
					unionx(x, y);
					unionx(x + k, y + k);
				}
				else
				{
					int x = i;
					int y = j + n;
					int k = n + m;
					if (findfather(x) == findfather(y))
					{
						flag = false;
						break;
					}
					unionx(x, y + k);
					unionx(x + k, y);
				}
			}
			if (! flag)
			{
				break;
			}
		}
		if (flag)
		{
			return Nice;
		}
		else
		{
			return NotNice;
		}
	}
};
