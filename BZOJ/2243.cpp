#include <cstdio>
#include <algorithm>

#define mid (l + r >> 1)

int edgenum;
int vet[300000], nextx[300000], head[300000];
int pos[300000], top[300000], fa[300000], deep[300000], size[300000];
int col[300000], cc[300000];;
char s[100];
int n, m;
int left[1200000], right[1200000], cnt[1200000], tag[1200000];
int sz;

void add(int u, int v)
{
	edgenum++;
	vet[edgenum] = v;
	nextx[edgenum] = head[u];
	head[u] = edgenum;
}

void dfs(int u, int father)
{
	size[u] = 1;
	for (int i = head[u]; i; i = nextx[i])
	{
		int v = vet[i];
		if (v != father)
		{
			deep[v] = deep[u] + 1;
			fa[v] = u;
			dfs(v, u);
			size[u] += size[v];
		}
	}
}

void dfs2(int u, int chain)
{
	int k = 0;
	sz++;
	pos[u] = sz;
	top[u] = chain;
	for (int i = head[u]; i; i = nextx[i])
	{
		int v = vet[i];
		if (deep[v] > deep[u] && size[v] > size[k])
		{
			k = v;
		}
	}
	if (k == 0)
	{
		return;
	}
	dfs2(k, chain);
	for (int i = head[u]; i; i = nextx[i])
	{
		int v = vet[i];
		if (deep[v] > deep[u] && v != k)
		{
			dfs2(v, v);
		}
	}
}

void pushup(int k)
{
	left[k] = left[k << 1];
	right[k] = right[k << 1 | 1];
	cnt[k] = cnt[k << 1] + cnt[k << 1 | 1] - (right[k << 1] == left[k << 1 | 1]);
}

void pushdown(int k)
{
	if (tag[k] != -1)
	{
		left[k << 1] = right[k << 1] = tag[k];
		left[k << 1 | 1] = right[k << 1 | 1] = tag[k];
		cnt[k << 1] = cnt[k << 1 | 1] = 1;
		tag[k << 1] = tag[k << 1 | 1] = tag[k];
		tag[k] = -1;
	}
}

void build(int k, int l, int r)
{
	if (l == r)
	{
		left[k] = right[k] = cc[l];
		cnt[k] = 1;
		tag[k] = -1;
		return;
	}
	build(k << 1, l, mid);
	build(k << 1 | 1, mid + 1, r);
	pushup(k);
	tag[k] = -1;
}

void change(int k, int l, int r, int L, int R, int newvalue)
{
	if (L <= l && r >= R)
	{
		left[k] = right[k] = tag[k] = newvalue;
		cnt[k] = 1;
		return;;
	}
	pushdown(k);
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

std::pair<int, std::pair<int, int> > query(int k, int l, int r, int L, int R)
{
	if (L <= l && r <= R)
	{
		std::pair<int, std::pair<int, int> > tmp;
		tmp.first = cnt[k];
		tmp.second.first = right[k];
		tmp.second.second = left[k];
		return tmp;
	}
	pushdown(k);
	if (! (L <= mid))
	{
		return query(k << 1 | 1, mid + 1, r, L, R);
	}
	if (! (R > mid))
	{
		return query(k << 1, l, mid, L, R);
	}
	std::pair<int, std::pair<int, int> > t1, t2, t;
	t1 = query(k << 1, l, mid, L, R);
	t2 = query(k << 1 | 1, mid + 1, r, L, R);
	t.first = t1.first + t2.first - (t1.second.first == t2.second.second);
	t.second.first = t2.second.first;
	t.second.second = t1.second.second;
	return t;
}

void solvechange(int u, int v, int newvalue)
{
	printf("#:\n");
	while (top[u] != top[v])
	{
		if (deep[top[u]] < deep[top[v]])
		{
			std::swap(u, v);
		}
		printf("%d %d\n", pos[top[u]], pos[u]);
		change(1, 1, n, pos[top[u]], pos[u], newvalue);
		u = fa[top[u]];
	}
	if (deep[u] > deep[v])
	{
		std::swap(u, v);
	}
	printf("%d %d\n", pos[u], pos[v]);
	change(1, 1, n, pos[u], pos[v], newvalue);
	printf("G%d %d\n", query(1, 1, n, 6, 6).second.first, query(1, 1, n, 6, 6).second.second);
}

int solvequery(int u, int v)
{
	int ans = 0;
	int lastu = -1, lastv = -1;
	while (top[u] != top[v])
	{
		if (deep[top[u]] < deep[top[v]])
		{
			std::swap(u, v);
			std::swap(lastu, lastv);
		}
		std::pair<int, std::pair<int, int> > tmp = query(1, 1, n, pos[top[u]], pos[u]);
//		printf("%d %d %d %d %d\n", pos[top[u]], pos[u], tmp.first, tmp.second.first, tmp.second.second);
		ans += tmp.first - (lastu == tmp.second.first);
		lastu = tmp.second.second;
		u = fa[top[u]];
	}
	if (deep[u] > deep[v])
	{
		std::swap(u, v);
	}
	std::pair<int, std::pair<int, int> > tmp = query(1, 1, n, pos[u], pos[v]);
//	printf("%d %d %d\n", ans + tmp.first, lastu, lastv);
	ans += tmp.first - (lastu == tmp.second.second) - (lastv == tmp.second.first);
	return ans;
}

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &col[i]);
	}
	for (int i = 1; i < n; i++)
	{
		int x, y;
		scanf("%d%d", &x, &y);
		add(x, y);
		add(y, x);
	}
	deep[1] = 1;
	dfs(1, -1);
	dfs2(1, 1);
	for (int i = 1; i <= n; i++)
	{
		cc[pos[i]] = col[i];
	}
	build(1, 1, n);
	for (int i = 1; i <= n; i++)
	{
		printf("%d %d\n", i, pos[i]);
	}
	while (m--)
	{
		scanf("%s", s + 1);
		if (s[1] == 'C')
		{
			int u, v, newvalue;
			scanf("%d%d%d", &u, &v, &newvalue);
			solvechange(u, v, newvalue);
		}
		else
		{
			int u, v;
			scanf("%d%d", &u, &v);
			printf("%d\n", solvequery(u, v));
		}
	}
	return 0;
}
