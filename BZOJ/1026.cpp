#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int f[15][15];
int kk[15];
int len;

int abs(int x)
{
	return x >= 0 ? x : -x;
}

int dfs(int pos, int pre, int lead, int limit)
{
	if (pos == 0)
	{
		return ! lead;
	}
	if (! limit && ! lead && f[pos][pre] != -1)
	{
		return f[pos][pre];
	}
	int tmp = 0;
	for (int i = 0; i <= 9; i++)
	{
		if (limit && i > kk[pos])
		{
			continue;
		}
		if (lead || abs(i - pre) >= 2)
		{
			tmp += dfs(pos - 1, i, lead && i == 0, limit && i == kk[pos]);
		}
	}
	if (! limit && ! lead)
	{
		f[pos][pre] = tmp;
	}
	return tmp;
}

int solve(int x)
{
	if (x == 0)
	{
		return 0;
	}
	memset(f, -1, sizeof(f));
	len = 0;
	int tmp = x;
	while (tmp)
	{
		len++;
		kk[len] = tmp % 10;
		tmp = tmp / 10;
	}
	int ans = 0;
	for (int i = 0; i <= kk[len]; i++)
	{
		ans += dfs(len - 1, i, i == 0, i == kk[len]);
	}
	return ans;
}

int main()
{
	int l, r;
	scanf("%d%d", &l, &r);
	printf("%d\n", solve(r) - solve(l - 1));
	return 0;
}
