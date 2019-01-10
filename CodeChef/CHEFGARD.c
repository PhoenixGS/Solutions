#include <stdio.h>
#include <math.h>

#define _n 100000 + 10
#define INF (long long)1000000000 * 1000000000

int T, n;
char s[_n];
int x[_n], c[_n];
long long f[_n][8][3];
long long ans;

long long maxx(long long x, long long y)
{
	return x > y ? x : y;
}

long long minx(long long x, long long y)
{
	return x < y ? x : y;
}

int main()
{
	scanf("%d", &T);
	while (T--)
	{
		scanf("%d", &n);
		scanf("%s", s + 1);
		for (int i = 1; i <= n; i++)
		{
			scanf("%d", &c[i]);
			if (s[i] == 'R')
			{
				x[i] = 0;
			}
			if (s[i] == 'G')
			{
				x[i] = 1;
			}
			if (s[i] == 'B')
			{
				x[i] = 2;
			}
		}
		for (int i = 0; i <= n; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				for (int k = 0; k < 3; k++)
				{
					f[i][j][k] = INF;
				}
			}
		}
		f[0][0][0] = 0;
		f[0][0][1] = 0;
		f[0][0][2] = 0;
		for (int i = 1; i <= n; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				for (int k = 0; k < 8; k++)
				{
					if (((1 << j) & k) == 0)
					{
						f[i][k | (1 << j)][j] = minx(f[i][k | (1 << j)][j], f[i - 1][k][0] + (j != x[i]) * c[i]);
						f[i][k | (1 << j)][j] = minx(f[i][k | (1 << j)][j], f[i - 1][k][1] + (j != x[i]) * c[i]);
						f[i][k | (1 << j)][j] = minx(f[i][k | (1 << j)][j], f[i - 1][k][2] + (j != x[i]) * c[i]);
					}
					else
					{
						f[i][k][j] = minx(f[i][k][j], f[i - 1][k][j] + (j != x[i]) * c[i]);
					}
				}
			}
		}
		ans = INF;
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				ans = minx(ans, f[n][i][j]);
			}
		}
		printf("%lld\n", ans);
	}
	return 0;
}
