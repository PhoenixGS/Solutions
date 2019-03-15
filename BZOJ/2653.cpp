#include <cstdio>
#include <algorithm>

struct T
{
	int x, id;
};

struct res
{
	int sum, left, right;
};

int num;
int left[500000], right[500000], sum[500000];
int ch[500000][2];
int root[500000];
int v[10];
int n, m;
int pred;
T x[40000];

bool comp(T x, T y)
{
	return x.x < y.x;
}

void pushup(int k)
{
	sum[k] = sum[ch[k][0]] + sum[ch[k][1]];
	left[k] = std::max(left[ch[k][0]], sum[ch[k][0]] + left[ch[k][1]]);
	right[k] = std::max(right[ch[k][1]], sum[ch[k][1]] + right[ch[k][0]]);
}

void build(int &k, int l, int r)
{
	num++;
	k = num;
	if (l == r)
	{
		left[k] = right[k] = sum[k] = 1;
		return;
	}
	int mid = (l + r) >> 1;
	build(ch[k][0], l, mid);
	build(ch[k][1], mid + 1, r);
	pushup(k);
}

void change(int u, int &v, int l, int r, int key, int newvalue)
{
	num++;
	v = num;
	ch[v][0] = ch[u][0];
	ch[v][1] = ch[u][1];
	if (l == r)
	{
		sum[v] = newvalue;
		left[v] = right[v] = std::max(newvalue, 0);
		return;
	}
	int mid = (l + r) >> 1;
	if (key <= mid)
	{
		change(ch[u][0], ch[v][0], l, mid, key, newvalue);
	}
	else
	{
		change(ch[u][1], ch[v][1], mid + 1, r, key, newvalue);
	}
	pushup(v);
}

res query(int k, int l, int r, int L, int R)
{
	if (L <= l && r <= R)
	{
		return (res){sum[k], left[k], right[k]};
	}
	int mid = (l + r) >> 1;
	if (! (L <= mid))
	{
		return query(ch[k][1], mid + 1, r, L, R);
	}
	if (! (R > mid))
	{
		return query(ch[k][0], l, mid, L, R);
	}
	res lans = query(ch[k][0], l, mid, L, R);
	res rans = query(ch[k][1], mid + 1, r, L, R);
	return (res){lans.sum + rans.sum, std::max(lans.left, lans.sum + rans.left), std::max(rans.right, rans.sum + lans.right)};
}

bool check(int k, int a, int b, int c, int d)
{
	return (a <= b - 1 ? query(root[k], 1, n, a, b - 1).right : 0) + (b <= c ? query(root[k], 1, n, b, c).sum : 0) + (c + 1 <= d ? query(root[k], 1, n, c + 1, d).left : 0) >= 0;
}

int main()
{
#ifdef debug
	freopen("2653.in", "r", stdin);
#endif
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &x[i].x);
		x[i].id = i;
	}
	std::sort(x + 1, x + n + 1, comp);
	build(root[1], 1, n);
	for (int i = 2; i <= n; i++)
	{
		change(root[i - 1], root[i], 1, n, x[i - 1].id, -1);
	}
	scanf("%d", &m);
	pred = 0;
	while (m--)
	{
		scanf("%d%d%d%d", &v[1], &v[2], &v[3], &v[4]);
		for (int i = 1; i <= 4; i++)
		{
			v[i] = (v[i] + pred) % n + 1;
		}
		std::sort(v + 1, v + 4 + 1);
		int l = 1;
		int r = n;
		while (l < r)
		{
			int mid = (l + r + 1) >> 1;
			if (check(mid, v[1], v[2], v[3], v[4]))
			{
				l = mid;
			}
			else
			{
				r = mid - 1;
			}
		}
		printf("%d\n", x[l].x);
		pred = x[l].x;
	}
	return 0;
}
