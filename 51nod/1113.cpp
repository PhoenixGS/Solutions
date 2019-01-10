#include <cstdio>
#include <algorithm>

int n, m;
long long x[105][105];
long long tmp[105][105];
long long ans[105][105];
long long tt[105][105];
long long M = 1000000007;

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			scanf("%lld", &x[i][j]);
		}
	}
	for (int i = 1; i <= n; i++)
	{
		ans[i][i] = 1;
	}
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			tmp[i][j] = x[i][j];
		}
	}
	while (m)
	{
		if (m & 1)
		{
			for (int i = 1; i <= n; i++)
			{
				for (int j = 1; j <= n; j++)
				{
					tt[i][j] = 0;
				}
			}
			for (int i = 1; i <= n; i++)
			{
				for (int j = 1; j <= n; j++)
				{
					for (int k = 1; k <= n; k++)
					{
						tt[i][j] = (tt[i][j] + ans[i][k] * tmp[k][j] % M) % M;
					}
				}
			}
			for (int i = 1; i <= n; i++)
			{
				for (int j = 1; j <= n; j++)
				{
					ans[i][j] = tt[i][j];
				}
			}
		}
		for (int i = 1; i <= n; i++)
		{
			for (int j = 1; j <= n; j++)
			{
				tt[i][j] = 0;
			}
		}
		for (int i = 1; i <= n; i++)
		{
			for (int j = 1; j <= n; j++)
			{
				for (int k = 1; k <= n; k++)
				{
					tt[i][j] = (tt[i][j] + tmp[i][k] * tmp[k][j] % M) % M;
				}
			}
		}
		for (int i = 1; i <= n; i++)
		{
			for (int j = 1; j <= n; j++)
			{
				tmp[i][j] = tt[i][j];
			}
		}
		m >>= 1;
	}
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			printf("%lld ", ans[i][j]);
		}
		printf("\n");
	}
	return 0;
}
