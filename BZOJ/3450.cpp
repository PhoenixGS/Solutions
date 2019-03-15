#include <cstdio>

const int _n = 300000 + 10;
int n;
char st[_n];
long double f[_n], g[_n];

int main()
{
#ifdef debug
	freopen("3450.in", "r", stdin);
#endif
	scanf("%d", &n);
	scanf("%s", st + 1);
	for (int i = 1; i <= n; i++)
	{
		if (st[i] == 'x')
		{
			g[i] = 0.0;
			f[i] = f[i - 1];
		}
		if (st[i] == 'o')
		{
			g[i] = g[i - 1] + 1;
			f[i] = f[i - 1] + 2 * g[i] - 1;
		}
		if (st[i] == '?')
		{
			f[i] = f[i - 1] + (2 * (g[i - 1] + 1) - 1) / 2;
			g[i] = (g[i - 1] + 1) / 2;
		}
	}
	printf("%.4f\n", (double)f[n]);
	return 0;
}
