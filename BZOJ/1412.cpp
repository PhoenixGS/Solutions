#include <cstdio>
#include <cstring>
#include <algorithm>

const int INF = 1e9;
int edgenum;
int vet[100000];
int val[100000];
int nextx[100000];
int head[20000];
int cur[20000];
int dis[20000];
int que[20000];
int cas[200][200];
int n, m;
const int dx[4] = {0, 1, 0, -1};
const int dy[4] = {1, 0, -1, 0};

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

bool bfs(int s, int t)
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

int dfs(int u, int t, int flow)
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
		int f;
		if (dis[u] + 1 == dis[v] && (f = dfs(v, t, std::min(flow - ans, cost))) > 0)
		{
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

int maxflow(int s, int t)
{
	int flow = 0;
	while (bfs(s, t))
	{
		for (int i = 1; i <= n * m + 2; i++)
		{
			cur[i] = head[i];
		}
		flow += dfs(s, t, INF);
	}
	return flow;
}

int main()
{
	edgenum = 1;
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			scanf("%d", &cas[i][j]);
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
			if (cas[i][j] == 1)
			{
				add(n * m + 1, calc(i, j), INF);
				add(calc(i, j), n * m + 1, 0);
			}
			if (cas[i][j] == 2)
			{
				add(calc(i, j), n * m + 2, INF);
				add(n * m + 2, calc(i, j), 0);
			}
		}
	}
	printf("%d\n", maxflow(n * m + 1, n * m + 2));
	return 0;
}
