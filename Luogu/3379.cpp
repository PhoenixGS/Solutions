#include <cstdio>
#include <algorithm>

long long read()
{
	char last = '+', ch = getchar();
	while (ch < '0' || ch > '9') last = ch, ch = getchar();
	long long tmp = 0;
	while (ch >= '0' && ch <= '9') tmp = tmp * 10 + ch - 48, ch = getchar();
	if (last == '-') tmp = -tmp;
	return tmp;
}

const int _n = 500000 + 10;
int n, m, root;
int edgenum;
int vet[2 * _n], nextx[2 * _n], head[_n];
int fa[_n], size[_n], deep[_n];
int top[_n];

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

int query(int x, int y)
{
	while (top[x] != top[y])
	{
		if (deep[top[x]] < deep[top[y]])
		{
			std::swap(x, y);
		}
		x = fa[top[x]];
	}
	return deep[x] > deep[y] ? y : x;
}

int main()
{
	scanf("%d%d%d", &n, &m, &root);
	for (int i = 1; i < n; i++)
	{
		int u = read();
		int v = read();
		add(u, v);
		add(v, u);
	}
	dfs(root, 0);
	dfs2(root, 0, root);
	while (m--)
	{
		int u = read();
		int v = read();
		printf("%d\n", query(u, v));
	}
	return 0;
}
