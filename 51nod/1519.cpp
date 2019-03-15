#include <cstdio>
#include <algorithm>

int n;
int x[200000];
int f[200000];

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &x[i]);
	}
	f[1] = f[n] = 1;
	for (int i = 2; i <= n; i++)
	{
		f[i] = std::min(f[i - 1] + 1, x[i]);
	}
	for (int i = n; i >= 1; i--)
	{
		f[i] = std::min(f[i + 1] + 1, f[i]);
	}
	int ans = 0;
	for (int i = 1; i <= n; i++)
	{
		ans = std::max(ans, f[i]);
	}
	printf("%d\n", ans);
	return 0;
}
