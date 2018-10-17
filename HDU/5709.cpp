#include <cstdio>

int T;
int n, m;
int fa[200000], deep[200000];
int num;
int tree[10000000], ch[10000000][2];
int rt1[200000], rt2[200000];
int col[200000];
int pred;

void change(int u, int &v, int l, int r, int pos, int delta)
{
	num++;
	v = num;
	ch[v][0] = ch[u][0];
	ch[v][1] = ch[u][1];
	tree[v] = tree[u] + delta;
	if (l == r)
	{
		return;
	}
	int mid = (l + r) >> 1;
	if (pos <= mid)
	{
		change(ch[u][0], ch[v][0], l, mid, pos, delta);
	}
	else
	{
		change(ch[u][1], ch[v][1], mid + 1, r, pos, delta);
	}
}

void merge1(int x, int y, int &z, int l, int r)
{
	if (! x)
	{
		z = y;
		return;
	}
	if (! y)
	{
		z = x;
		return;
	}
	num++;
	z = num;
	tree[z] = tree[x] + tree[y];
	if (l == r)
	{
		return;
	}
	int mid = (l + r) >> 1;
	merge1(ch[x][0], ch[y][0], ch[z][0], l, mid);
	merge1(ch[x][1], ch[y][1], ch[z][1], mid + 1, r);
}

void merge2(int x, int y, int &z, int l, int r, int id)
{
	if (! x)
	{
		z = y;
		return;
	}
	if (! y)
	{
		z = x;
		return;
	}
	num++;
	z = num;
	if (l == r)
	{
		if (tree[x] < tree[y])
		{
			change(rt1[id], rt1[id], 1, n, tree[y], -1);
			tree[z] = tree[x];
		}
		else
		{
			change(rt1[id], rt1[id], 1, n, tree[x], -1);
			tree[z] = tree[y];
		}
		return;
	}
	int mid = (l + r) >> 1;
	merge2(ch[x][0], ch[y][0], ch[z][0], l, mid, id);
	merge2(ch[x][1], ch[y][1], ch[z][1], mid + 1, r, id);
}

int query(int k, int l, int r, int pos)
{
	if (r <= pos)
	{
		return tree[k];
	}
	int mid = (l + r) >> 1;
	int ans = query(ch[k][0], l, mid, pos);
	if (pos > mid)
	{
		ans += query(ch[k][1], mid + 1, r, pos);
	}
	return ans;
}

int main()
{
	scanf("%d", &T);
	while (T--)
	{
		pred = 0;
		num = 0;
		scanf("%d%d", &n, &m);
		for (int i = 1; i <= n; i++)
		{
			rt1[i] = rt2[i] = 0;
		}
		for (int i = 1; i <= n; i++)
		{
			scanf("%d", &col[i]);
		}
		for (int i = 2; i <= n; i++)
		{
			scanf("%d", &fa[i]);
		}
		for (int i = 1; i <= n; i++)
		{
			deep[i] = deep[fa[i]] + 1;
		}
		for (int i = 1; i <= n; i++)
		{
			change(rt1[i], rt1[i], 1, n, deep[i], 1);
			change(rt2[i], rt2[i], 1, n, col[i], deep[i]);
		}
		for (int i = n; i > 1; i--)
		{
			merge1(rt1[fa[i]], rt1[i], rt1[fa[i]], 1, n);
			merge2(rt2[fa[i]], rt2[i], rt2[fa[i]], 1, n, fa[i]);
		}
		while (m--)
		{
			int x, d;
			scanf("%d%d", &x, &d);
			x ^= pred;
			d ^= pred;
			d += deep[x];
			if (d > n)
			{
				d = n;
			}
			printf("%d\n", pred = query(rt1[x], 1, n, d));
		}
	}
	return 0;
}
