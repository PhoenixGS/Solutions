#include <cstdio>
#include <algorithm>
#include <cstdlib>

int n;
int x[100000];
long long f[100000][3];

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &x[i]);
	}
	for (int i = 2; i <= n; i++)
	{
		f[i][0] = std::max(f[i - 1][0], f[i - 1][1] + abs(x[i - 1] - 1));
		f[i][1] = std::max(f[i - 1][0] + abs(x[i] - 1), f[i - 1][1] + abs(x[i] - x[i - 1]));
	}
	printf("%lld\n", std::max(f[n][0], f[n][1]));
	return 0;
}
