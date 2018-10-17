#include <cstdio>
#include <cstring>

int edgenum;
int vet[50000];
int nextx[50000];
int head[500];
int vis[500];
int match[500];
int ans;
int times;
int n, m;

void add(int u, int v)
{
	edgenum++;
	vet[edgenum] = v;
	nextx[edgenum] = head[u];
	head[u] = edgenum;
}

bool dfs(int u)
{
	for (int i = head[u]; i; i = nextx[i])
	{
		int v = vet[i];
		if (vis[v] != times)
		{
			vis[v] = times;
			if (match[v] == 0 || dfs(match[v]))
			{
				match[v] = u;
				return true;
			}
		}
	}
	return false;
}

int main()
{
	while (scanf("%d%d", &n, &m) == 2)
	{
		edgenum = 0;
		memset(head, 0, sizeof(head));
		for (int i = 1; i <= n; i++)
		{
			int k;
			scanf("%d", &k);
			for (int j = 1; j <= k; j++)
			{
				int x;
				scanf("%d", &x);
				add(i, x + n);
			}
		}
		ans = 0;
		memset(match, 0, sizeof(match));
		for (int i = 1; i <= n; i++)
		{
			times++;
			ans += dfs(i);
		}
		printf("%d\n", ans);
	}
	return 0;
}
