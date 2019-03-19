#include <cstdio>

const int M = 1000000007;
const int lim = 2000000;
int n, m;
int up[lim + 10], down[lim + 10];
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
	up[0] = up[1] = 1;
	for (int i = 2; i <= lim; i++)
	{
		up[i] = (long long)up[i - 1] * i % M;
	}
	down[0] = down[1] = 1;
	for (int i = 2; i <= lim; i++)
	{
		down[i] = (long long)(M - M / i) * down[M % i] % M;
	}
	for (int i = 2; i <= lim; i++)
	{
		down[i] = (long long)down[i - 1] * down[i] % M;
	}
	scanf("%d%d", &n, &m);
	if (n && m)
	{
		ans = 1;
	}
	for (int i = 2; i <= m; i++)
	{
		if (n - i >= 0)
		{
			(ans += C((n - i) / 2 + i - 1, i - 1)) %= M;
		}
		if (n - i - 1 >= 0)
		{
			(ans += C((n - i - 1) / 2 + i - 1, i - 1)) %= M;
		}
	}
	printf("%d\n", ans);
	return 0;
}
