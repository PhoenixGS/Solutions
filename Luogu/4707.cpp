#include <cstdio>

long long read()
{
	char last = '+', ch = getchar();
	while (ch < '0' || ch > '9') last = ch, ch = getchar();
	long long tmp = 0;
	while (ch >= '0' && ch <= '9') tmp = tmp * 10 + ch - 48, ch = getchar();
	if (last == '-') tmp = -tmp;
	return tmp;
}

const int M = 998244353;
const int _n = 1000 + 10, _m = 10000 + 10, _k = 14;
int n, m, k;
int inv[_m];
int p[_n];
int f[_m][_k], g[_m][_k];
int ans;

int main()
{
	scanf("%d%d%d", &n, &k, &m);
	inv[0] = 1;
	inv[1] = 1;
	for (int i = 2; i <= m; i++)
	{
		inv[i] = (long long)(M - M / i) * inv[M % i] % M;
	}
	for (int i = 1; i <= n; i++)
	{
		p[i] = read();
	}
	k = n - k + 1;
	for (int i = 1; i <= k; i++)
	{
		f[0][i] = -1;
	}
	for (int i = 1; i <= n; i++)
	{
		for (int j = 0; j <= m; j++)
		{
			for (int t = 0; t <= k; t++)
			{
				g[j][t] = f[j][t];
				if (j >= p[i] && t >= 1)
				{
					g[j][t] = (g[j][t] + f[j - p[i]][t - 1]) % M;
				}
				if (j >= p[i])
				{
					g[j][t] = ((g[j][t] - f[j - p[i]][t]) % M + M) % M;
				}
			}
		}
		for (int j = 0; j <= m; j++)
		{
			for (int t = 0; t <= k; t++)
			{
				f[j][t] = g[j][t];
				g[j][t] = 0;
			}
		}
	}
	ans = 0;
	for (int i = 1; i <= m; i++)
	{
		ans = (ans + (long long)f[i][k] * inv[i] % M * m % M) % M;
	}
	ans = (ans + M) % M;
	printf("%d\n", ans);
	return 0;
}
