#include <cstdio>
#include <cmath>

#define mid (l + r >> 1)

int n, m;
long long sum[500000];
int cnt[500000];
int x[500000];

void pushup(int k)
{
	sum[k] = sum[k << 1] + sum[k << 1 | 1];
	cnt[k] = cnt[k << 1] + cnt[k << 1 | 1];
}

void build(int k, int l, int r)
{
	if (l == r)
	{
		sum[k] = x[l];
		if (sum[k] == 0 || sum[k] == 1)
		{
			cnt[k] = 1;
		}
		return;
	}
	build(k << 1, l, mid);
	build(k << 1 | 1, mid + 1, r);
	pushup(k);
}

long long query(int k, int l, int r, int L, int R)
{
	if (L <= l && r <= R)
	{
		return sum[k];
	}
	long long ans = 0;
	if (L <= mid)
	{
		ans += query(k << 1, l, mid, L, R);
	}
	if (R > mid)
	{
		ans += query(k << 1 | 1, mid + 1, r, L, R);
	}
	return ans;
}

void change(int k, int l, int r, int pos)
{
	if (l == r)
	{
		sum[k] = sqrt(sum[k]);
		if (sum[k] == 0 || sum[k] == 1)
		{
			cnt[k] = 1;
		}
		return;
	}
	if (pos <= mid)
	{
		change(k << 1, l, mid, pos);
	}
	else
	{
		change(k << 1 | 1, mid + 1, r, pos);
	}
	pushup(k);
}

void modify(int k, int l, int r, int L, int R)
{
	if (L <= l && r <= R)
	{
		if (cnt[k] == r - l + 1)
		{
			return;
		}
	}
	if (l == r)
	{
		change(1, 1, n, l);
		return;
	}
	if (L <= mid)
	{
		modify(k << 1, l, mid, L, R);
	}
	if (R > mid)
	{
		modify(k << 1 | 1, mid + 1, r, L, R);
	}
}

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &x[i]);
	}
	build(1, 1, n);
	scanf("%d", &m);
	for (int i = 1; i <= m; i++)
	{
		int cas, l, r;
		scanf("%d%d%d", &cas, &l, &r);
		if (cas == 1)
		{
			printf("%lld\n", query(1, 1, n, l, r));
		}
		else
		{
			modify(1, 1, n, l, r);
		}
	}
	return 0;
}
