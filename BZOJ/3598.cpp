#include <cstdio>

long long dfs(int pos, int limit, int S, int cas)
{
	if (pos == 0)
	{
		return 
	}
}

long long solve(int x)
{
	last = 0;
	while (x)
	{
		last++;
		v[last] = x % 10;
		x = x / 10;
	}
	long long ans = 0;
	for (int i = 0; i <= 9 * last; i++)
	{
		ans = ans + dfs(last, 1, i, 0);
	}
	return ans;
}

int main()
{
	l = read();
	r = read();
	k = read();
	printf("%lld\n", solve(r) - solve(l - 1));
	return 0;
}