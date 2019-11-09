#include <cstdio>
#include <algorithm>
#include <cstring>

const int _n = 10000 + 10;
int T;
int n;
int uuu[2 * _n], vvv[2 * _n], cost[2 * _n];
int edgenum;
int vet[2 * _n], nextx[2 * _n], head[_n];
int times;
int fa[_n], size[_n], deep[_n], top[_n], dfn[_n];
int tree[4 * _n];
char s[100];

void add(int u, int v)
{
	edgenum++;
	vet[edgenum] = v;
	nextx[edgenum] = head[u];
	head[u] = edgenum;
}

void dfs(int u, int father)
{
	fa[u] = father;
	size[u] = 1;
	for (int i = head[u]; i; i = nextx[i])
	{
		int v = vet[i];
		if (v != father)
		{
			deep[v] = deep[u] + 1;
			dfs(v, u);
			size[u] += size[v];
		}
	}
}

void dfs2(int u, int father, int chain)
{
	times++;
	dfn[u] = times;
	top[u] = chain;
	int k = 0;
	for (int i = head[u]; i; i = nextx[i])
	{
		int v = vet[i];
		if (v != father && size[v] > size[k])
		{
			k = v;
		}
	}
	if (k)
	{
		dfs2(k, u, chain);
	}
	for (int i = head[u]; i; i = nextx[i])
	{
		int v = vet[i];
		if (v != father && v != k)
		{
			dfs2(v, u, v);
		}
	}
}

void change_(int k, int l, int r, int pos, int newvalue)
{
	if (l == r)
	{
		tree[k] = newvalue;
		return;
	}
	int mid = (l + r) >> 1;
	if (pos <= mid)
	{
		change_(k << 1, l, mid, pos, newvalue);
	}
	else
	{
		change_(k << 1 | 1, mid + 1, r, pos, newvalue);
	}
	tree[k] = std::max(tree[k << 1], tree[k << 1 | 1]);
}

int query_(int k, int l, int r, int L, int R)
{
	if (L <= l && r <= R)
	{
		return tree[k];
	}
	int mid = (l + r) >> 1;
	int ans = 0;
	if (L <= mid)
	{
		ans = std::max(ans, query_(k << 1, l, mid, L, R));
	}
	if (R > mid)
	{
		ans = std::max(ans, query_(k << 1 | 1, mid + 1, r, L, R));
	}
	return ans;
}

int query(int u, int v)
{
	int ans = 0;
	while (top[u] != top[v])
	{
		if (deep[top[u]] > deep[top[v]])
		{
			std::swap(u, v);
		}
		ans = std::max(ans, query_(1, 1, n, dfn[top[v]], dfn[v]));
		v = fa[top[v]];
	}
	if (deep[u] > deep[v])
	{
		std::swap(u, v);
	}
	if (u != v)
	{
		ans = std::max(ans, query_(1, 1, n, dfn[u] + 1, dfn[v]));
	}
	return ans;
}

int main()
{
	scanf("%d", &T);
	while (T--)
	{
		times = 0;
		edgenum = 0;
		memset(head, 0, sizeof(head));
		memset(dfn, 0, sizeof(dfn));
		for (int i = 0; i <= 4 * n; i++)
		{
			tree[i] = 0;
		}
		scanf("%d", &n);
		for (int i = 1; i < n; i++)
		{
			scanf("%d%d%d", &uuu[i], &vvv[i], &cost[i]);
			add(uuu[i], vvv[i]);
			add(vvv[i], uuu[i]);
		}
		dfs(1, 0);
		dfs2(1, 0, 1);
		for (int i = 1; i < n; i++)
		{
			if (deep[uuu[i]] > deep[vvv[i]])
			{
				change_(1, 1, n, dfn[uuu[i]], cost[i]);
			}
			else
			{
				change_(1, 1, n, dfn[vvv[i]], cost[i]);
			}
		}
		scanf("%s", s + 1);
		while (s[1] != 'D')
		{
			if (s[1] == 'C')
			{
				int id, newcost;
				scanf("%d%d", &id, &newcost);
				if (deep[uuu[id]] > deep[vvv[id]])
				{
					change_(1, 1, n, dfn[uuu[id]], newcost);
				}
				else
				{
					change_(1, 1, n, dfn[vvv[id]], newcost);
				}
			}
			else
			{
				int u, v;
				scanf("%d%d", &u, &v);
				printf("%d\n", query(u, v));
			}
			scanf("%s", s + 1);
		}
	}
	return 0;
}
