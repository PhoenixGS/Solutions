#include <cstdio>
#include <algorithm>

struct matrix
{
	int x1, y1, x2, y2;
};

struct changes
{
	int l, r, pos, cas;
};

const int lim = 10000;
const int _n = 5000 + 10;
int n;
int knum, root;
int ch[2 * 2 * 20 * _n][2], tag[2 * 2 * 20 * _n], sum[2 * 2 * 20 * _n];
matrix x[_n];
int last;
changes v[2 * _n];
long long ans;

inline int abss(int x)
{
	return x > 0 ? x : -x;
}

inline bool comp(changes x, changes y)
{
	return x.pos < y.pos || (x.pos == y.pos && x.cas < y.cas);
}

inline void pushup(int k, int l, int r)
{
	if (tag[k])
	{
		sum[k] = r - l + 1;
	}
	else
	{
		sum[k] = sum[ch[k][0]] + sum[ch[k][1]];
	}
}

void change(int &k, int l, int r, int L, int R, int delta)
{
	if (! k)
	{
		knum++;
		k = knum;
		ch[k][0] = ch[k][1] = 0;
		tag[k] = sum[k] = 0;
	}
	if (L <= l && r <= R)
	{
		tag[k] += delta;
		if (tag[k])
		{
			sum[k] = r - l + 1;
		}
		else
		{
			sum[k] = (l == r) ? 0 : (sum[ch[k][0]] + sum[ch[k][1]]);
		}
		return;
	}
	int mid = (l + r) >> 1;
	if (L <= mid)
	{
		change(ch[k][0], l, mid, L, R, delta);
	}
	if (R > mid)
	{
		change(ch[k][1], mid + 1, r, L, R, delta);
	}
	pushup(k, l, r);
}

int main()
{
#ifdef debug
	freopen("1828.in", "r", stdin);
#endif
	while (scanf("%d", &n) != EOF)
	{
		ans = 0;

		for (int i = 1; i <= n; i++)
		{
			scanf("%d%d%d%d", &x[i].x1, &x[i].y1, &x[i].x2, &x[i].y2);
		}

		root = 0;
		knum = 0;
		last = 0;
		for (int i = 1; i <= n; i++)
		{
			last++;
			v[last].l = x[i].x1;
			v[last].r = x[i].x2;
			v[last].pos = x[i].y1;
			v[last].cas = 1;
			last++;
			v[last].l = x[i].x1;
			v[last].r = x[i].x2;
			v[last].pos = x[i].y2 + 1;
			v[last].cas = -1;
		}
		std::sort(v + 1, v + last + 1, comp);
		for (int i = 1; i <= last; )
		{
			int first = i;
			while (i <= last && v[i].pos == v[first].pos)
			{
				int pre = sum[root];
				change(root, -lim, lim, v[i].l, v[i].r - 1, v[i].cas);
				i++;
				ans += abss(pre - sum[root]);
			}
		}

		root = 0;
		knum = 0;
		last = 0;
		for (int i = 1; i <= n; i++)
		{
			last++;
			v[last].l = x[i].y1;
			v[last].r = x[i].y2;
			v[last].pos = x[i].x1;
			v[last].cas = 1;
			last++;
			v[last].l = x[i].y1;
			v[last].r = x[i].y2;
			v[last].pos = x[i].x2 + 1;
			v[last].cas = -1;
		}
		std::sort(v + 1, v + last + 1, comp);
		for (int i = 1; i <= last; )
		{
			int first = i;
			while (i <= last && v[i].pos == v[first].pos)
			{
				int pre = sum[root];
				change(root, -lim, lim, v[i].l, v[i].r - 1, v[i].cas);
				i++;
				ans += abss(pre - sum[root]);
			}
		}

		printf("%lld\n", ans);
	}
	return 0;
}
