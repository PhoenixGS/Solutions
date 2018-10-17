#include <cstdio>
#include <cstring>

typedef long long ll;

ll X;
ll f[20];
ll ff[20];
int len;
int kk[20];

ll dfs(int pos, int lead, int limit, int ii)
{
//	printf("%d %d %d %d\n", pos, lead, limit, ii);
	if (pos == 1)
	{
		if (limit && ii > kk[pos])
		{
			return 0;
		}
		if (lead && ii == 0)
		{
			return 0;
		}
		return 1;
	}
	if (! limit && ! lead && f[pos] != -1)
	{
		return f[pos];
	}
	ll ans = 0;
	for (int i = 0; i <= 9; i++)
	{
		if (limit && i > kk[pos])
		{
			continue;
		}
		ans += dfs(pos - 1, lead && i == 0, limit && i == kk[pos], ii);
		if (ii == i)
		{
			if (lead && ii == 0)
			{
				continue;
			}
//			printf("X%lld\n", ff[pos - 1]);
			if (limit && i == kk[pos])
			{
				ans += X % ff[pos - 1] + 1;
			}
			else
			{
				ans += ff[pos - 1];
			}
		}
	}
	if (! limit && ! lead)
	{
		f[pos] = ans;
	}
//	printf("%d %d %d %d %lld\n", pos, lead, limit, ii, ans);
	return ans;
}

ll solve(ll x, int ii)
{
	X = x;
	if (x == 0)
	{
		return 0;
	}
	len = 0;
	while (x)
	{
		len++;
		kk[len] = x % 10;
		x = x / 10;
	}
	return dfs(len, 1, 1, ii);
}

int main()
{
	memset(f, -1, sizeof(f));
	ll l, r;
	scanf("%lld%lld", &l, &r);
	ff[0] = 1;
	for (int i = 1; i <= 14; i++)
	{
		ff[i] = ff[i - 1] * 10;
	}
	for (int i = 0; i <= 8; i++)
	{
//		solve(r, i);
		printf("%lld ", solve(r, i) - solve(l - 1, i));
	}
	printf("%lld\n", solve(r, 9) - solve(l - 1, 9));
	return 0;
}
