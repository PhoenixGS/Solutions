#include <cstdio>

int m, n;
int f[1005][1005];
const int M = 1000000007;

int main()
{
	scanf("%d%d", &m, &n);
	f[0][1] = 1;
	for (int i = 1; i <= m; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			f[i][j] = (f[i - 1][j] + f[i][j - 1]) % M;
		}
	}
	printf("%d\n", f[m][n]);
	return 0;
}
