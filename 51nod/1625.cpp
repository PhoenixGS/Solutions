#include <cstdio>
#include <algorithm>
#include <functional>

typedef long long ll;

int matrix[20][300];
int tmp[20][300];
ll kk[300];
ll ans;
int t[20];
int n, m;
int x;
int k;

void calc(int rest)
{
	ll ttt = 0;
	for (int i = 1; i <= n; i++)
	{
		if (t[i])
		{
			for (int j = 1; j <= m; j++)
			{
				ttt += (ll)(x - matrix[i][j]);
				tmp[i][j] = x;
			}
		}
		else
		{
			for (int j = 1; j <= m; j++)
			{
				tmp[i][j] = matrix[i][j];
			}
		}
	}
	for (int i = 1; i <= m; i++)
	{
		kk[i] = 0;
		for (int j = 1; j <= n; j++)
		{
			kk[i] += (ll)(x - tmp[j][i]);
		}
	}
	std::sort(kk + 1, kk + m + 1, std::greater<ll>());
	for (int i = 1; i <= std::min(m, rest) && kk[i] > 0; i++)
	{
		ttt += kk[i];
	}
	ans = std::max(ans, ttt);
}

void dfs(int tt, int s)
{
	if (tt > n || s == k)
	{
		calc(k - s);
		return;
	}
	dfs(tt + 1, s);
	t[tt] = 1;
	dfs(tt + 1, s + 1);
	t[tt] = 0;
}

int main()
{
	scanf("%d%d%d%d", &n, &m, &x, &k);
	ll tans = 0;
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			scanf("%d", &matrix[i][j]);
			tans += matrix[i][j];
		}
	}
	ans = 0;
	dfs(1, 0);
	printf("%lld\n", ans + tans);
	return 0;
}
