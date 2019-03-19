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

const int M = 1000000007;
const int _n = 1000 + 10;
int n, m;
int C[2000 + 10][2000 + 10];
int x[_n];

int main()
{
	for (int i = 0; i <= 2000; i++)
	{
		C[i][0] = 1;
	}
	for (int i = 1; i <= 2000; i++)
	{
		for (int j = 1; j <= 2000; j++)
		{
			C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % M;
		}
	}
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; i++)
	{
		x[i] = read();
	}
	int ans = 0;
	for (int i = 0; i < n; i++)
	{
		int t = C[n][i];
		for (int j = 1; j <= m; j++)
		{
			t = (long long)t * C[x[j] + n - i - 1][n - i - 1] % M;
		}
		(ans += ((i & 1) ? -1 : 1) * t) %= M;
		ans = (ans + M) % M;
	}
	printf("%d\n", ans);
	return 0;
}
