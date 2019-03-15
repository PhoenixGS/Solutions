#include <cstdio>
#include <algorithm>

long long read()
{
	char last = '+', ch = getchar();
	while (ch < '0' || ch > '9') last = ch, ch = getchar();
	long long tmp = 0;
	while (ch >= '0' && ch <= '9') tmp = tmp * 10 + ch - 48, ch = getchar();
	if (last == '-') tmp = -tmp;
	return tmp;
}

const int M = 1000000007;
const int _n = 40 + 10, _L = 1000000 + 10;
int L, n;
int x[_n];
int mx;
int up[_L], down[_L];
int f[_n][_n][_n * _n][2][2];
int ans;

int C(int n, int m)
{
	if (n < m)
	{
		return 0;
	}
	return (long long)up[n] * down[m] % M * down[n - m] % M;
}

int main()
{
#ifdef debug
	freopen("4498.in", "r", stdin);
#endif
	scanf("%d%d", &L, &n);
	up[0] = 1;
	for (int i = 1; i <= L; i++)
	{
		up[i] = (long long)up[i - 1] * i % M;
	}
	down[0] = down[1] = 1;
	for (int i = 2; i <= L; i++)
	{
		down[i] = (long long)(M - M / i) * down[M % i] % M;
	}
	for (int i = 1; i <= L; i++)
	{
		down[i] = (long long)down[i - 1] * down[i] % M;
	}
	mx = 0;
	for (int i = 1; i <= n; i++)
	{
		x[i] = read();
		mx = std::max(mx, x[i]);
	}
	mx = mx * n;
	std::sort(x + 1, x + n + 1);
	f[1][2][0][1][1] = 1;
	f[1][1][0][1][0] = 1;
	f[1][1][0][0][1] = 1;
	for (int i = 2; i <= n; i++)
	{
		for (int j = 1; j <= n + 1; j++)
		{
			for (int s = 0; s <= mx; s++)
			{
				for (int l = 0; l < 2; l++)
				{
					for (int r = 0; r < 2; r++)
					{
						if (j - l - r >= 1 && f[i - 1][j][s][l][r])
						{
//							printf("%d %d %d %d %d %d\n", i - 1, j, s, l, r, f[i - 1][j][s][l][r]);
							(f[i][j - 1 + 2][s][l][r] += (long long)f[i - 1][j][s][l][r] * (j - l - r) % M) %= M;
							(f[i][j - 1 + 1][s + x[i]][l][r] += (long long)f[i - 1][j][s][l][r] * (j - l - r) % M * 2 % M) %= M;
							(f[i][j - 1][s + 2 * x[i]][l][r] += (long long)f[i - 1][j][s][l][r] * (j - l - r) % M) %= M;
						}
					}
				}
				for (int k = 0; k < 2; k++)
				{
					if (f[i - 1][j][s][1][k])
					{
						(f[i][j - 1 + 2][s][1][k] += f[i - 1][j][s][1][k]) %= M;
						(f[i][j - 1 + 1][s + x[i]][1][k] += f[i - 1][j][s][1][k]) %= M;
						(f[i][j - 1 + 1][s][0][k] += f[i - 1][j][s][1][k]) %= M;
						(f[i][j - 1][s + x[i]][0][k] += f[i - 1][j][s][1][k]) %= M;
					}
					if (f[i - 1][j][s][k][1])
					{
						(f[i][j - 1 + 2][s][k][1] += f[i - 1][j][s][k][1]) %= M;
						(f[i][j - 1 + 1][s + x[i]][k][1] += f[i - 1][j][s][k][1]) %= M;
						(f[i][j - 1 + 1][s][k][0] += f[i - 1][j][s][k][1]) %= M;
						(f[i][j - 1][s + x[i]][k][0] += f[i - 1][j][s][k][1]) %= M;
					}
				}
			}
		}
	}
	for (int i = 0; i <= mx; i++)
	{
		if (f[n][0][i][0][0])
		{
//			printf("%d %d\n", i, f[n][0][i][0][0]);
		}
		(ans += (long long)f[n][0][i][0][0] * C(L - i - 1 + n, n) % M) %= M;
	}
	printf("%d\n", ans);
	return 0;
}
