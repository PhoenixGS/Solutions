#include <cstdio>
#include <cmath>
#include <algorithm>

int n, m;
int x[60000];
int knumber;
int knum[60000];
int vvv;
int vv[60000];
int bit[60000];
int f[240][240];
int sum[240][60000];

int lowbit(int x)
{
	return x & -x;
}

void add(int *bit, int x, int delta)
{
	for (int i = x; i <= vvv; i += lowbit(i))
	{
		bit[i] += delta;
	}
}

int query(int *bit, int x)
{
	int ans = 0;
	for (int i = x; i; i -= lowbit(i))
	{
		ans += bit[i];
	}
	return ans;
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
			ans += query(sum[rr], x[i] - 1) - query(sum[ll - 1], x[i] - 1);
		}
		for (int i = rr * knumber + 1; i <= r; i++)
		{
			ans += (query(sum[rr], vvv) - query(sum[rr], x[i])) - (query(sum[ll - 1], vvv) - query(sum[ll - 1], x[i]));
		}
		for (int i = l; i <= (ll - 1) * knumber; i++)
		{
			ans += query(bit, vvv) - query(bit, x[i]);
			add(bit, x[i], 1);
		}
		for (int i = rr * knumber + 1; i <= r; i++)
		{
			ans += query(bit, vvv) - query(bit, x[i]);
			add(bit, x[i], 1);
		}
		for (int i = l; i <= (ll - 1) * knumber; i++)
		{
			add(bit, x[i], -1);
		}
		for (int i = rr * knumber + 1; i <= r; i++)
		{
			add(bit, x[i], -1);
		}
	}
	else
	{
		for (int i = l; i <= r; i++)
		{
			ans += query(bit, vvv) - query(bit, x[i]);
			add(bit, x[i], 1);
		}
		for (int i = l; i <= r; i++)
		{
			add(bit, x[i], -1);
		}
	}
	return ans;
}

int main()
{
	scanf("%d", &n);
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
		int now = 0;
		for (int j = (i - 1) * knumber + 1; j <= n; j++)
		{
			now += query(bit, vvv) - query(bit, x[j]);
			add(bit, x[j], 1);
			if (j % knumber == 0 || j == n)
			{
				f[i][knum[j]] = now;
			}
		}
		for (int j = (i - 1) * knumber + 1; j <= n; j++)
		{
			add(bit, x[j], -1);
		}
	}
	for (int i = 1; i <= n; i++)
	{
		add(bit, x[i], 1);
		if (i % knumber == 0 || i == n)
		{
			for (int j = 1; j <= vvv; j++)
			{
				sum[knum[i]][j] = bit[j];
			}
		}
	}
	for (int i = 1; i <= n; i++)
	{
		add(bit, x[i], -1);
	}
	int preans = 0;
	scanf("%d", &m);
	while (m--)
	{
		int l, r;
		scanf("%d%d", &l, &r);
		l = l ^ preans;
		r = r ^ preans;
		if (l > r)
		{
			std::swap(l, r);
		}
		preans = query(l, r);
		printf("%d\n", preans);
	}
	return 0;
}

