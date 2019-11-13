#include <cstdio>
#include <vector>

const int _n = 100000 + 10;
int n, m;
int edgenum;
int vet[2 * _n], nextx[2 * _n], head[_n];
int fa[_n], size[_n], top[_n], deep[_n];
int times;
int dfn[_n];
std::vector<int> vec[_n][2];
int tree[400000 + 10], poss[400000 + 10];
int ans[_n];

void add(int u, int v)
{
	edgenum++;
	vet[edgenum] = v;
	nextx[edgenum] = head[u];
	head[u] = edgenum;
}

void change(int k, int l, int r, int pos, int delta)
{
	if (l == r)
	{
		tree[k] += delta;
		poss[k] = l;
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
	if (tree[k << 1] >= tree[k << 1 | 1])
	{
		tree[k] = tree[k << 1];
		poss[k] = poss[k << 1];
	}
	else
	{
		tree[k] = tree[k << 1 | 1];
		poss[k] = poss[k << 1 | 1];
	}
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

void change(int u, int v, int key)
{
	while (top[u] != top[v])
	{
		if (deep[top[u]] < deep[top[v]])
		{
			std::swap(u, v);
		}
		vec[dfn[top[u]]][0].push_back(key);
		vec[dfn[u] + 1][1].push_back(key);
		u = fa[top[u]];
	}
	if (deep[u] < deep[v])
	{
		std::swap(u, v);
	}
	vec[dfn[v]][0].push_back(key);
	vec[dfn[u] + 1][1].push_back(key);
}

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i < n; i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		add(u, v);
		add(v, u);
	}
	dfs(1, 0);
	dfs2(1, 0, 1);
	while (m--)
	{
		int u, v, key;
		scanf("%d%d%d", &u, &v, &key);
		change(u, v, key);
	}
	for (int i = 1; i <= n; i++)
	{
		for (int j = 0; j < (int)vec[i][0].size(); j++)
		{
			change(1, 0, 100000, vec[i][0][j], 1);
		}
		for (int j = 0; j < (int)vec[i][1].size(); j++)
		{
			change(1, 0, 100000, vec[i][1][j], -1);
		}
		ans[i] = poss[1];
	}
	for (int i = 1; i <= n; i++)
	{
		printf("%d\n", ans[dfn[i]]);
	}
	return 0;
}
