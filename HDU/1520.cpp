#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int n;
int x[10000];
int edgenum;
int vet[10000];
int nextx[10000];
int head[10000];
int f[10000][2];
int fa[10000];

void add(int u, int v)
{
	edgenum++;
	vet[edgenum] = v;
	nextx[edgenum] = head[u];
	head[u] = edgenum;
}

void dfs(int u)
{
	f[u][0] = 0;
	f[u][1] = x[u];
	for (int i = head[u]; i; i = nextx[i])
	{
		int v = vet[i];
		if (v != fa[u])
		{
			dfs(v);
			f[u][0] += max(f[v][0], f[v][1]);
			f[u][1] += f[v][0];
		}
	}
}

int main()
{
	while (scanf("%d", &n) == 1)
	{
		edgenum = 0;
		memset(head, 0, sizeof(head));
		memset(fa, -1, sizeof(fa));
		for (int i = 1; i <= n; i++)
		{
			scanf("%d", &x[i]);
		}
		int u, v;
		while (scanf("%d%d", &u, &v) == 2 && u && v)
		{
			fa[u] = v;
			add(v, u);
		}
		int root = 1;
		while (fa[root] != -1)
		{
			root = fa[root];
		}
		dfs(root);
		printf("%d\n", max(f[root][0], f[root][1]));
	}
	return 0;
}
