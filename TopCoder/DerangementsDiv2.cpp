// BEGIN CUT HERE

// END CUT HERE
#line 5 "DerangementsDiv2.cpp"
#include <string>
#include <vector>

typedef long long ll;

using namespace std;

class DerangementsDiv2 {
	public:
	ll f[100][100];

	int count(ll n, ll m) {
		ll M = 1000000007;
		f[0][0] = 1;
		for (int i = 1; i <= m; i++)
		{
			for (int j = 0; j <= m; j++)
			{
				f[i][j] = ((n - (i - 1 - j)) % M * f[i - 1][j] % M + (m - (j - 1)) % M * f[i - 1][j - 1] % M) % M;
			}
		}
		ll tmp = 1;
		for (ll i = 1; i <= n; i++)
		{
			tmp = tmp * i % M;
		}
		tmp = tmp * f[m][m] % M;
		printf("%lld\n", tmp);
		return (int)tmp;
	}
};
