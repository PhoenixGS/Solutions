#include <cstdio>
#include <algorithm>

const int M = 1000000009;
int n, k;
int mi[3000];
int c[3000][3000];
int x[3000], y[3000];
int v[3000];
int f[3000][3000];
int g[3000];
int ans;

int main()
{
	scanf("%d%d", &n, &k);
	mi[0] = 1;
	for (int i = 1; i <= n; i++)
	{
		mi[i] = (long long)mi[i - 1] * i % M;
	}
	for (int i = 0; i <= n; i++)
	{
		c[i][0] = 1;
	}
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % M;
		}
	}
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &x[i]);
	}
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &y[i]);
	}
	if ((n + k) & 1)
	{
		puts("0");
		return 0;
	}
	k = (n + k) / 2;
	std::sort(x + 1, x + n + 1);
	std::sort(y + 1, y + n + 1);
	int now = n;
	for (int i = n; i >= 1; i--)
	{
		while (x[i] < y[now])
		{
			now--;
		}
		v[i] = now;
	}
	f[0][0] = 1;
	for (int i = 1; i <= n; i++)
	{
		for (int j = 0; j <= i; j++)
		{
			f[i][j] = f[i - 1][j];
			if (j)
			{
				f[i][j] = ((long long)f[i][j] + (long long)f[i - 1][j - 1] * (v[i] - (j - 1)) % M) % M;
			}
		}
	}
	for (int i = n; i >= 0; i--)
	{
		g[i] = (long long)f[n][i] * mi[n - i] % M;
		for (int j = i + 1; j <= n; j++)
		{
			g[i] = ((long long)g[i] - (long long)g[j] * c[j][i] % M + M) % M;
		}
	}
	printf("%d\n", g[k]);
	return 0;
}
