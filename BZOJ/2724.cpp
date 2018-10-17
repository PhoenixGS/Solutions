#include <cstdio>
#include <cmath>
#include <algorithm>

int n, m;
int x[50000];
int vv[50000];
int vvv;
int knumber;
int knum[50000];
int cnt[50000];
int sum[300][50000];
int f[300][300];

int calc(int x, int l, int r)
{
	return cnt[x] + sum[r][x] - sum[l - 1][x];
}

bool check(int x, int y, int l, int r)
{
	return calc(x, l, r) > calc(y, l, r) || (calc(x, l, r) == calc(y, l, r) && x < y);
}

int query(int l, int r)
{
	int ll = (l - 1) % knumber == 0 ? knum[l] : knum[l] + 1;
	int rr = r % knumber == 0 ? knum[r] : knum[r] - 1;
	int ans = 0;
	if (ll <= rr)
	{
		ans = f[ll][rr];
		for (int i = l; i <= (ll - 1) * knumber; i++)
		{
			cnt[x[i]]++;
			if (check(x[i], ans, ll, rr))
			{
				ans = x[i];
			}
		}
		for (int i = rr * knumber + 1; i <= r; i++)
		{
			cnt[x[i]]++;
			if (check(x[i], ans, ll, rr))
			{
				ans = x[i];
			}
		}
		for (int i = l; i <= (ll - 1) * knumber; i++)
		{
			cnt[x[i]]--;
		}
		for (int i = rr * knumber + 1; i <= r; i++)
		{
			cnt[x[i]]--;
		}
	}
	else
	{
		ans = 0;
		for (int i = l; i <= r; i++)
		{
			cnt[x[i]]++;
			if (cnt[x[i]] > cnt[ans] || (cnt[x[i]] == cnt[ans] && x[i] < ans))
			{
				ans = x[i];
			}
		}
		for (int i = l; i <= r; i++)
		{
			cnt[x[i]]--;
		}
	}
	return ans;
}

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &x[i]);
		vv[i] = x[i];
	}
	std::sort(vv + 1, vv + n + 1);
	vvv = std::unique(vv + 1, vv + n + 1) - vv - 1;
	for (int i = 1; i <= n; i++)
	{
		x[i] = std::lower_bound(vv + 1, vv + vvv + 1, x[i]) - vv;
	}
	knumber = sqrt(n);
	for (int i = 1; i <= n; i++)
	{
		knum[i] = (i - 1) / knumber + 1;
	}
	for (int i = 1; i <= knum[n]; i++)
	{
		int tmp = 0;
		for (int j = (i - 1) * knumber + 1; j <= n; j++)
		{
			cnt[x[j]]++;
			if (cnt[x[j]] > cnt[tmp] || (cnt[x[j]] == cnt[tmp] && x[j] < tmp))
			{
				tmp = x[j];
			}
			if (j % knumber == 0 || j == n)
			{
				f[i][knum[j]] = tmp;
			}
		}
		for (int j = (i - 1) * knumber + 1; j <= n; j++)
		{
			cnt[x[j]]--;
		}
	}
	for (int i = 1; i <= n; i++)
	{
		cnt[x[i]]++;
		if (i % knumber == 0 || i == n)
		{
			for (int j = 1; j <= vvv; j++)
			{
				sum[knum[i]][j] = cnt[j];
			}
		}
	}
	for (int i = 1; i <= n; i++)
	{
		cnt[x[i]]--;
	}
	int preans = 0;
	for (int i = 1; i <= m; i++)
	{
		int l, r;
		scanf("%d%d", &l, &r);
		l = (l + preans - 1) % n + 1;
		r = (r + preans - 1) % n + 1;
		if (l > r)
		{
			std::swap(l, r);
		}
		preans = vv[query(l, r)];
		printf("%d\n", preans);
	}
	return 0;
}
