#include <cstdio>
#include <cstring>
#include <algorithm>

#define mid ((l + r) >> 1)

int T, n;
int edgenum;
int vet[30000], val[30000], nextx[30000], head[30000];
int fa[20000], deep[20000], size[20000], top[20000], pos[20000], sop[20000];
int tree[50000];
int vv[20000];
int knum;
int uuu[20000], vvv[20000];
char s[100];

void add(int u, int v, int cost)
{
	edgenum++;
	vet[edgenum] = v;
	val[edgenum] = cost;
	nextx[edgenum] = head[u];
	head[u] = edgenum;
}

void dfs(int u, int father, int dep)
{
	fa[u] = father;
	deep[u] = dep;
	size[u] = 1;
	for (int i = head[u]; i; i = nextx[i])
	{
		int v = vet[i];
		int cost = val[i];
		if (v != father)
		{
			vv[v] = cost;
			dfs(v, u, dep + 1);
			size[u] += size[v];
		}
	}
}

void dfs2(int u, int chain)
{
	knum++;
	top[u] = chain;
	pos[u] = knum;
	sop[knum] = u;
	int k = 0;
	for (int i = head[u]; i; i = nextx[i])
	{
		int v = vet[i];
		if (v != fa[u])
		{
			if (size[v] > size[k])
			{
				k = v;
			}
		}
	}
	if (! k)
	{
		return;
	}
	dfs2(k, chain);
	for (int i = head[u]; i; i = nextx[i])
	{
		int v = vet[i];
		if (v != fa[u] && v != k)
		{
			dfs2(v, v);
		}
	}
}

void pushup(int k)
{
	tree[k] = std::max(tree[k << 1], tree[k << 1 | 1]);
}

void build(int k, int l, int r)
{
	if (l == r)
	{
		tree[k] = vv[sop[l]];
		return;
	}
	build(k << 1, l, mid);
	build(k << 1 | 1, mid + 1, r);
	pushup(k);
}

int querymax(int k, int l, int r, int L, int R)
{
	if (L <= l && r <= R)
	{
		return tree[k];
	}
	int ans = 0;
	if (L <= mid)
	{
		ans = std::max(ans, querymax(k << 1, l, mid, L, R));
	}
	if (R > mid)
	{
		ans = std::max(ans, querymax(k << 1 | 1, mid + 1, r, L, R));
	}
	return ans;
}

void change(int k, int l, int r, int pos, int newvalue)
{
	if (l == r)
	{
		tree[k] = newvalue;
		return;
	}
	if (pos <= mid)
	{
		change(k << 1, l, mid, pos, newvalue);
	}
	if (pos > mid)
	{
		change(k << 1 | 1, mid + 1, r, pos, newvalue);
	}
	pushup(k);
}

int querylca(int u, int v)
{
	while (top[u] != top[v])
	{
		if (deep[top[u]] > deep[top[v]])
		{
			std::swap(u, v);
		}
		v = fa[top[v]];
	}
	if (deep[u] > deep[v])
	{
		std::swap(u, v);
	}
	return u;
}

int query(int u, int lca)
{
	int ans = 0;
	while (top[u] != top[lca])
	{
		ans = std::max(ans, querymax(1, 1, n, pos[top[u]], pos[u]));
		u = fa[top[u]];
	}
	if (u != lca)
	{
		ans = std::max(ans, querymax(1, 1, n, pos[lca] + 1, pos[u]));
	}
	return ans;
}

int main()
{
	scanf("%d", &T);
	while (T--)
	{
		knum = 0;
		edgenum = 0;
		memset(head, 0, sizeof(head));
		scanf("%d", &n);
		for (int i = 1; i < n; i++)
		{
			int cost;
			scanf("%d%d%d", &uuu[i], &vvv[i], &cost);
			add(uuu[i], vvv[i], cost);
			add(vvv[i], uuu[i], cost);
		}
		dfs(1, 0, 0);
		dfs2(1, 1);
		build(1, 1, n);
		while (scanf("%s", s + 1) != EOF && s[1] != 'D')
		{
			if (s[1] == 'Q')
			{
				int u, v;
				scanf("%d%d", &u, &v);
				int lca = querylca(u, v);
				printf("%d\n", std::max(query(u, lca), query(v, lca)));
			}
			else
			{
				int id, newvalue;
				scanf("%d%d", &id, &newvalue);
				if (deep[uuu[id]] < deep[vvv[id]])
				{
					change(1, 1, n, pos[vvv[id]], newvalue);
				}
				else
				{
					change(1, 1, n, pos[uuu[id]], newvalue);
				}
			}
		}
	}
	return 0;
}
