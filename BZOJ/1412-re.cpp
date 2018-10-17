#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>

const int INF = 1000000000;
int n, m;
int s, t;
int edgenum;
int x[200][200];
int vet[100000], val[100000], nextx[100000], cur[100000], head[50000];
int dis[200000];
int que[200000];
int dx[4] = {0, 1, 0, -1}, dy[4] = {1, 0, -1, 0};

int calc(int x, int y)
{
	return (x - 1) * m + y;
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
	for (int &i = cur[u]; i; i = nextx[i])
	{
		int v = vet[i];
		int cost = val[i];
		if (dis[u] + 1 == dis[v])
		{
			int f = dfs(v, std::min(flow - ans, cost));
			val[i] -= f;
			val[i ^ 1] += f;
			ans += f;
			if (ans == flow)
			{
				return ans;
			}
		}
	}
	if (ans < flow)
	{
		dis[u] = -1;
	}
	return ans;
}

int maxflow(int s, int t)
{
	int maxflow = 0;
	while (bfs())
	{
		for (int i = 1; i <= n * m + 2; i++)
		{
			cur[i] = head[i];
		}
		maxflow += dfs(s, INF);
	}
	return maxflow;
}

int main()
{
	edgenum = 1;
	scanf("%d%d", &n, &m);
	s = n * m + 1;
	t = n * m + 2;
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			scanf("%d", &x[i][j]);
		}
	}
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			for (int k = 0; k < 4; k++)
			{
				int xx = i + dx[k];
				int yy = j + dy[k];
				if (xx >= 1 && xx <= n && yy >= 1 && yy <= m)
				{
					add(calc(i, j), calc(xx, yy), 1);
					add(calc(xx, yy), calc(i, j), 0);
				}
			}
		}
	}
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			if (x[i][j] == 1)
			{
				add(s, calc(i, j), INF);
				add(calc(i, j), s, 0);
			}
			if (x[i][j] == 2)
			{
				add(calc(i, j), t, INF);
				add(t, calc(i, j), 0);
			}
		}
	}
	printf("%d\n", maxflow(s, t));
	return 0;
}
