#include <cstdio>

const int _n = 100 + 10;
double ff[_n];
double g[_n][_n], f[_n][_n], s[_n][_n];
double ans;

void solve_1(int n)
{
	ff[1] = 0.0;
	for (int i = 2; i <= n; i++)
	{
		ff[i] = ff[i - 1] + 2.0 / i;
	}
	printf("%.6f\n", ff[n]);
}

void solve_2(int n)
{
	g[1][0] = 1.0;
	g[2][1] = 1.0;
	for (int i = 3; i <= n; i++)
	{
		for (int j = 1; j < i; j++)
		{
			g[i][j] = g[i - 1][j] * (i - 1 - j) / (i - 1) + g[i - 1][j - 1] * (j - 1) / (i - 1);
		}
	}
	f[1][0] = 1.0;
	s[1][0] = 1.0;
	for (int i = 1; i <= n; i++)
	{
		s[1][i] = s[1][i - 1];
	}
	for (int i = 2; i <= n; i++)
	{
		for (int j = 1; j < i; j++)
		{
			for (int k = 1; k < i; k++)
			{
				double tmp = 0.0;
				tmp += f[i - k][j - 1] * s[k][j - 2];
				tmp += f[k][j - 1] * s[i - k][j - 2];
				tmp += f[k][j - 1] * f[i - k][j - 1];
				tmp = tmp * g[i][k];
				f[i][j] += tmp;
			}
		}
		s[i][0] = f[i][0];
		for (int j = 1; j <= n; j++)
		{
			s[i][j] = s[i][j - 1] + f[i][j];
		}
	}
	ans = 0.0;
	for (int i = 0; i <= n; i++)
	{
		ans += i * f[n][i];
	}
	printf("%.6f\n", ans);
}

int main()
{
	int cas, n;
	scanf("%d%d", &cas, &n);
	if (cas == 1)
	{
		solve_1(n);
	}
	else
	{
		solve_2(n);
	}
	return 0;
}