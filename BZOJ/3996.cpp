#include <cstdio>
#include <cstring>
#include <algorithm>

const int INF = 1e9;
int edgenum;
int vet[3000000];
int val[3000000];
int nextx[3000000];
int head[300000];
int cur[300000];
int dis[300000];
int que[300000];
int n;
int w[505][505];
int c[505];
int s, t;
int ans;

int calc(int x, int y)
{
	return (x - 1) * n + y;
}

void add(int u, int v, int cost)
{
	edgenum++;
	vet[edgenum] = v;
	val[edgenum] = cost;
	nextx[edgenum] = head[u];
	head[u] = edgenum;
}

bool bfs()
{
	memset(dis, -1, sizeof(dis));
	int headx = 1;
	int tailx = 0;
	tailx++;
	que[tailx] = s;
	dis[s] = 0;
	while (headx <= tailx)
	{
		int u = que[headx];
		headx++;
		for (int i = head[u]; i; i = nextx[i])
		{
			int v = vet[i];
			int cost = val[i];
			if (cost && dis[v] == -1)
			{
				dis[v] = dis[u] + 1;
				tailx++;
				que[tailx] = v;
			}
		}
	}
	return dis[t] != -1;
}

int dfs(int u, int flow)
{
	if (u == t)
	{
		return flow;
	}
	int ans = 0;
	for (int i = cur[u]; i; i = nextx[i])
	{
		int v = vet[i];
		int cost = val[i];
		if (dis[u] + 1 == dis[v])
		{
			int f = dfs(v, std::min(flow - ans, cost));
			val[i] -= f;
			val[i ^ 1] += f;
			ans += f;
			cur[u] = i;
			if (ans == flow)
			{
				break;
			}
		}
	}
	if (ans < flow)
	{
		dis[u] = -1;
	}
	return ans;
}

int maxflow()
{
	int flow = 0;
	while (bfs())
	{
		for (int i = 1; i <= n * n + n + 2; i++)
		{
			cur[i] = head[i];
		}
		flow += dfs(s, INF);
	}
	return flow;
}

int main()
{
	scanf("%d", &n);
	ans = 0;
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			scanf("%d", &w[i][j]);
			ans += w[i][j];
		}
	}
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &c[i]);
	}
	s = n * n + n + 1;
	t = n * n + n + 2;
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			add(s, calc(i, j), w[i][j]);
			add(calc(i, j), s, 0);
			add(calc(i, j), i + n * n, INF);
			add(i + n * n, calc(i, j), 0);
			add(calc(i, j), j + n * n, INF);
			add(j + n * n, calc(i, j), 0);
		}
	}
	for (int i = 1; i <= n; i++)
	{
		add(i + n * n, t, c[i]);
		add(t, i + n * n, 0);
	}
	printf("%d\n", ans - maxflow());
	return 0;
}
