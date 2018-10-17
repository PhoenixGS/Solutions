#include <cstdio>
#include <cstring>
#include <algorithm>

long long l, r;
long long f[13][11][11][2][2][2];
int last;
int k[20];

long long dfs(int pos, int last2, int last1, int check, int check4, int check8, int limit)
{
	if (pos == 0)
	{
		return check && (! (check4 && check8));
	}
	if (! limit)
	{
		if (f[pos][last2][last1][check][check4][check8] != -1)
		{
			return f[pos][last2][last1][check][check4][check8];
		}
	}
	int up = 9;
	if (limit)
	{
		up = std::min(up, k[pos]);
	}
	int down = 0;
	if (pos == 11)
	{
		down = 1;
	}
	long long ans = 0;
	for (int i = down; i <= up; i++)
	{
		ans += dfs(pos - 1, last1, i, check || (last2 == last1 && last1 == i), check4 || (i == 4), check8 || (i == 8), limit && i == up);
	}
	if (! limit)
	{
		f[pos][last2][last1][check][check4][check8] = ans;
	}
	return ans;
}

long long solve(long long x)
{
	last = 0;
	while (x)
	{
		last++;
		k[last] = x % 10;
		x /= 10;
	}
	memset(f, -1, sizeof(f));
	return dfs(last, 0, 0, 0, 0, 0, 1);
}

int main()
{
	scanf("%lld%lld", &l, &r);
	printf("%lld %lld\n", solve(r), solve(l - 1));
	if (l == 10000000000)
	{
		printf("%lld\n", solve(r));
	}
	else
	{
		printf("%lld\n", solve(r) - solve(l - 1));
	}
	return 0;
}
