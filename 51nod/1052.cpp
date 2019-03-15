#include <cstdio>
#include <algorithm>

int n, m;
int x[10000];
long long f[2][10000];
long long g[2][10000];

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &x[i]);
	}
	long long ans = 0;
	for (int i = 1; i <= n; i++)
	{
		int now = i & 1;
		int pre = now ^ 1;
		for (int j = 1; j <= m; j++)
		{
			f[now][j] = std::max(f[pre][j] + x[i], g[pre][j - 1] + x[i]);
			g[now][j] = std::max(g[pre][j], f[now][j]);
		}
		ans = std::max(ans, f[now][m]);
	}
	printf("%lld\n", ans);
	return 0;
}
