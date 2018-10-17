#include <cstdio>

int n, m;
int x[200000];
int tmp[200000];
int sum[1000000], tag[1000000];
int cas[200000], l[200000], r[200000];
int pos;

void pushup(int k)
{
	sum[k] = sum[k << 1] + sum[k << 1 | 1];
}

void pushdown(int k, int l, int r)
{
	if (tag[k] != -1)
	{
		int mid = l + r >> 1;
		tag[k << 1] = tag[k];
		sum[k << 1] = tag[k] * (mid - l + 1);
		tag[k << 1 | 1] = tag[k];
		sum[k << 1 | 1] = tag[k] * (r - mid);
		tag[k] = -1;
	}
}

void build(int k, int l, int r)
{
	if (l == r)
	{
		sum[k] = tmp[l];
		tag[k] = -1;
		return;
	}
	int mid = l + r >> 1;
	build(k << 1, l, mid);
	build(k << 1 | 1, mid + 1, r);
	pushup(k);
	tag[k] = -1;
}

void change(int k, int l, int r, int L, int R, int newvalue)
{
	if (L <= l && r <= R)
	{
		tag[k] = newvalue;
		sum[k] = newvalue * (r - l + 1);
		return;
	}
	pushdown(k, l, r);
	int mid = l + r >> 1;
	if (L <= mid)
	{
		change(k << 1, l, mid, L, R, newvalue);
	}
	if (R > mid)
	{
		change(k << 1 | 1, mid + 1, r, L, R, newvalue);
	}
	pushup(k);
}

int query(int k, int l, int r, int L, int R)
{
	if (L <= l && r <= R)
	{
		return sum[k];
	}
	pushdown(k, l, r);
	int ans = 0;
	int mid = l + r >> 1;
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

bool check(int mid)
{
	for (int i = 1; i <= n; i++)
	{
		tmp[i] = x[i] > mid;
	}
	build(1, 1, n);
	for (int i = 1; i <= m; i++)
	{
		if (cas[i] == 0)
		{
			int cnt1 = query(1, 1, n, l[i], r[i]);
			int cnt0 = r[i] - l[i] + 1 - cnt1;
			if (cnt0 > 0)
			{
				change(1, 1, n, l[i], l[i] + cnt0 - 1, 0);
			}
			if (cnt1 > 0)
			{
				change(1, 1, n, l[i] + cnt0, r[i], 1);
			}
		}
		else
		{
			int cnt1 = query(1, 1, n, l[i], r[i]);
			int cnt0 = r[i] - l[i] + 1 - cnt1;
			if (cnt1 > 0)
			{
				change(1, 1, n, l[i], l[i] + cnt1 - 1, 1);
			}
			if (cnt0 > 0)
			{
				change(1, 1, n, l[i] + cnt1, r[i], 0);
			}
		}
	}
	return query(1, 1, n, pos, pos) == 0;
}

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &x[i]);
	}
	for (int i = 1; i <= m; i++)
	{
		scanf("%d%d%d", &cas[i], &l[i], &r[i]);
	}
	scanf("%d", &pos);
	int ll = 1;
	int rr = n;
	while (ll < rr)
	{
		int mid = ll + rr >> 1;
		if (check(mid))
		{
			rr = mid;
		}
		else
		{
			ll = mid + 1;
		}
	}
	printf("%d\n", ll);
	return 0;
}

