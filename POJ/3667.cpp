#include <cstdio>
#include <algorithm>

#define mid ((l + r) >> 1)

long long read()
{
	char last = '+', ch = getchar();
	while (ch < '0' || ch > '9') last = ch, ch = getchar();
	long long tmp = 0;
	while (ch >= '0' && ch <= '9') tmp = tmp * 10 + ch - 48, ch = getchar();
	if (last == '-') tmp = -tmp;
	return tmp;
}

const int _n = 50000 + 10;
int n, m;
int maxx[4 * _n], maxl[4 * _n], maxr[4 * _n], tag[4 * _n];

void pushup(int k, int l, int r)
{
	maxx[k] = std::max(std::max(maxx[k << 1], maxx[k << 1 | 1]), maxr[k << 1] + maxl[k << 1 | 1]);
	maxl[k] = std::max(maxl[k << 1], (maxx[k << 1] == mid - l + 1) * (maxx[k << 1] + maxl[k << 1 | 1]));
	maxr[k] = std::max(maxr[k << 1 | 1], (maxx[k << 1 | 1] == r - mid) * (maxx[k << 1 | 1] + maxr[k << 1]));
}

void pushdown(int k, int l, int r)
{
	if (tag[k] != -1)
	{
		tag[k << 1] = tag[k << 1 | 1] = tag[k];
		maxx[k << 1] = maxl[k << 1] = maxr[k << 1] = (1 - tag[k]) * (mid - l + 1);
		maxx[k << 1 | 1] = maxl[k << 1 | 1] = maxr[k << 1 | 1] = (1 - tag[k]) * (r - mid);
		tag[k] = -1;
	}
}

void build(int k, int l, int r)
{
	if (l == r)
	{
		maxl[k] = maxr[k] = maxx[k] = 1;
		return;
	}
	tag[k] = -1;
	build(k << 1, l, mid);
	build(k << 1 | 1, mid + 1, r);
	pushup(k, l, r);
}

int query(int k, int l, int r, int c)
{
	pushdown(k, l, r);
	if (maxx[k << 1] >= c)
	{
		return query(k << 1, l, mid, c);
	}
	if (maxr[k << 1] + maxl[k << 1 | 1] >= c)
	{
		return mid - maxr[k << 1] + 1;
	}
	return query(k << 1 | 1, mid + 1, r, c);
}

void change(int k, int l, int r, int L, int R, int cas)
{
	if (L <= l && r <= R)
	{
		tag[k] = cas;
		maxx[k] = maxl[k] = maxr[k] = (1 - cas) * (r - l + 1);
		return;
	}
	pushdown(k, l, r);
	if (L <= mid)
	{
		change(k << 1, l, mid, L, R, cas);
	}
	if (R > mid)
	{
		change(k << 1 | 1, mid + 1, r, L, R, cas);
	}
	pushup(k, l, r);
}

int main()
{
	n = read();
	m = read();
	build(1, 1, n);
	for (int i = 1; i <= m; i++)
	{
		int cas;
		cas = read();
		if (cas == 1)
		{
			int k = read();
			if (maxx[1] < k)
			{
				puts("0");
			}
			else
			{
				int pos = query(1, 1, n, k);
				printf("%d\n", pos);
				change(1, 1, n, pos, pos + k - 1, 1);
			}
		}
		else
		{
			int l = read();
			int len = read();
			change(1, 1, n, l, l + len - 1, 0);
		}
	}
	return 0;
}
