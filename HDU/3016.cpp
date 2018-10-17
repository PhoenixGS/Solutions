#include <cstdio>
#include <algorithm>

struct T
{
	int height, left, right, value;
};

int maxx[500000];
int tag[500000];
T x[500000];
int n;
const int INF = 1e9;

bool comp(T x, T y)
{
	return x.height > y.height;
}

void pushup(int k)
{
	maxx[k] = std::max(maxx[k << 1], maxx[k << 1 | 1]);
}

void pushdown(int k)
{
	if (tag[k] != -INF - 1)
	{
		maxx[k << 1] = tag[k];
		tag[k << 1] = tag[k];
		maxx[k << 1 | 1] = tag[k];
		tag[k << 1 | 1] = tag[k];
		tag[k] = -INF - 1;
	}
}

void build(int k, int l, int r)
{
	if (l == r)
	{
		maxx[k] = 100;
		tag[k] = -INF - 1;
		return;
	}
	int mid = (l + r) >> 1;
	build(k << 1, l, mid);
	build(k << 1 | 1, mid + 1, r);
	pushup(k);
	tag[k] = -INF - 1;
}

int query(int k, int l, int r, int L, int R)
{
	if (L <= l && r <= R)
	{
		return maxx[k];
	}
	pushdown(k);
	int maxx = -INF;
	int mid = (l + r) >> 1;
	if (L <= mid)
	{
		maxx = std::max(maxx, query(k << 1, l, mid, L, R));
	}
	if (R > mid)
	{
		maxx = std::max(maxx, query(k << 1 | 1, mid + 1, r, L, R));
	}
	return maxx;
}

void change(int k, int l, int r, int L, int R, int newvalue)
{
	if (L <= l && r <= R)
	{
		maxx[k] = newvalue;
		tag[k] = newvalue;
		return;
	}
	pushdown(k);
	int mid = (l + r) >> 1;
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

int main()
{
	while (scanf("%d", &n) == 1)
	{
		for (int i = 1; i <= n; i++)
		{
			scanf("%d%d%d%d", &x[i].height, &x[i].left, &x[i].right, &x[i].value);
		}
		std::sort(x + 1, x + n + 1, comp);
		build(1, 1, 100000);
		for (int i = 1; i <= n; i++)
		{
			int kk = query(1, 1, 100000, x[i].left, x[i].right);
			change(1, 1, 100000, x[i].left, x[i].right, -INF);
			change(1, 1, 100000, x[i].left - 1, x[i].left - 1, std::max(-INF, kk + x[i].value));
			change(1, 1, 100000, x[i].right + 1, x[i].right + 1, std::max(-INF, kk + x[i].value));
		}
		int ans = query(1, 1, 100000, 1, 100000);
		if (ans < 0)
		{
			puts("-1");
		}
		else
		{
			printf("%d\n", ans);
		}
	}
	return 0;
}
