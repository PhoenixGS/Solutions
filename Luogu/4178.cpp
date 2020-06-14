#include <cstdio>
#include <algorithm>

const int INF = 1000000000;
const int _n = 40000 + 10, _lim = 20000 + 10;
int n, lim;
int edgenum;
int vet[2 * _n], val[2 * _n], nextx[2 * _n], head[_n];
int sum, root;
int size[_n], f[_n];
int vis[_n], dis[_n];
int ans;

namespace seg
{
	int sum[4 * _lim];

	void change(int k, int l, int r, int pos, int delta)
	{
		if (l == r)
		{
			sum[k] += delta;
			return;
		}
		int mid = (l + r) >> 1;
		if (pos <= mid)
		{
			change(k << 1, l, mid, pos, delta);
		}
		else
		{
			change(k << 1 | 1, mid + 1, r, pos, delta);
		}
		sum[k] = sum[k << 1] + sum[k << 1 | 1];
	}

	int query(int k, int l, int r, int L, int R)
	{
		if (L <= l && r <= R)
		{
			return sum[k];
		}
		int ans = 0;
		int mid = (l + r) >> 1;
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
}

void add(int u, int v, int cost)
{
	edgenum++;
	vet[edgenum] = v;
	val[edgenum] = cost;
	nextx[edgenum] = head[u];
	head[u] = edgenum;
}

void getroot(int u, int father)
{
	size[u] = 1;
	f[u] = 0;
	for (int i = head[u]; i; i = nextx[i])
	{
		int v = vet[i];
		if (v != father && ! vis[v])
		{
			getroot(v, u);
			size[u] += size[v];
			f[u] = std::max(f[u], size[v]);
		}
	}
	f[u] = std::max(f[u], sum - size[u]);
	if (f[u] < f[root])
	{
		root = u;
	}
}

void dfs(int u, int father, int cas)
{
	if (cas == 0)
	{
		if (dis[u] <= lim)
		{
			ans += seg::query(1, 0, lim, 0, lim - dis[u]);
		}
		size[u] = 1;
		for (int i = head[u]; i; i = nextx[i])
		{
			int v = vet[i];
			int cost = val[i];
			if (v != father && ! vis[v])
			{
				dis[v] = dis[u] + cost;
				dfs(v, u, cas);
				size[u] += size[v];
			}
		}
		return;
	}
	if (dis[u] <= lim)
	{
		seg::change(1, 0, lim, dis[u], cas);
	}
	for (int i = head[u]; i; i = nextx[i])
	{
		int v = vet[i];
		if (v != father && ! vis[v])
		{
			dfs(v, u, cas);
		}
	}
}

void solve(int u)
{
	vis[u] = 1;
	for (int i = head[u]; i; i = nextx[i])
	{
		int v = vet[i];
		int cost = val[i];
		if (! vis[v])
		{
			dis[v] = cost;
			dfs(v, u, 0);
			dfs(v, u, 1);
		}
	}
	for (int i = head[u]; i; i = nextx[i])
	{
		int v = vet[i];
		int cost = val[i];
		if (! vis[v])
		{
			dfs(v, u, -1);
		}
	}
	for (int i = head[u]; i; i = nextx[i])
	{
		int v = vet[i];
		if (! vis[v])
		{
			sum = size[v];
			root = 0;
			getroot(v, u);
			solve(root);
		}
	}
}

int main()
{
	scanf("%d", &n);
	for (int i = 1; i < n; i++)
	{
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		add(u, v, w);
		add(v, u, w);
	}
	scanf("%d", &lim);
	seg::change(1, 0, lim, 0, 1);
	f[0] = INF;
	sum = n;
	root = 0;
	getroot(1, 0);
	solve(root);
	printf("%d\n", ans);
	return 0;
}
