#include <cstdio>
#include <algorithm>

using namespace std;

int n, m;
int edgenum;
int vet[1500000];
int nextx[1500000];
int head[200000];
long long size[200000];
long long ans[200000];
int times;
int dfn[200000];
int low[200000];

void add(int u, int v)
{
	edgenum++;
	vet[edgenum] = v;
	nextx[edgenum] = head[u];
	head[u] = edgenum;
}

void dfs(int u)
{
	size[u] = 1;
	times++;
	dfn[u] = times;
	low[u] = times;
	long long tmp = 0;
	ans[u] = 0;
	for (int i = head[u]; i; i = nextx[i])
	{
		int v = vet[i];
		if (dfn[v])
		{
			low[u] = min(low[u], dfn[v]);
		}
		else
		{
			dfs(v);
			size[u] += size[v];
			low[u] = min(low[u], low[v]);
			if (low[v] >= dfn[u])
			{
				ans[u] += tmp * size[v];
				tmp += size[v];
			}
		}
	}
	ans[u] += tmp * (n - tmp - 1);
}

int main()
{
	edgenum = 0;
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		add(u, v);
		add(v, u);
	}
	dfs(1);
	for (int i = 1; i <= n; i++)
	{
		printf("%lld\n", (ans[i] + n - 1) * 2);
	}
	return 0;
}
