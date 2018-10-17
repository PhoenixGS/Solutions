#include <cstdio>
#include <cstring>
#include <map>

const int INF = 1e9;
int edgenum;
int vet[20000];
int val[20000];
int nextx[20000];
int head[1000];
int cur[1000];
int que[1000];
int dis[1000];
int uuu[20000];
int vvv[20000];
int ccc[20000];
std::map<int, int> map;
int n, m;

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
	for (int i = 1; i <= n; i++)
	{
		dis[i] = -1;
	}
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
		if (dis[u] + 1 == dis[v])
		{
			int f = dfs(v, t, std::min(flow - ans, cost));
			if (f > 0)
			{
				val[i] -= f;
				val[i ^ 1] += f;
				ans += f;
				cur[u] = i;
				if (ans == flow)
				{
					return ans;
				}
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
		for (int i = 1; i <= n; i++)
		{
			cur[i] = head[i];
		}
		flow += dfs(s, t, INF);
	}
	return flow;
}

int main()
{
	scanf("%d%d", &n, &m);
	if (n > 200)
	{
		puts("field!");
		return 0;
	}
	for (int i = 1; i <= m; i++)
	{
		scanf("%d%d%d", &uuu[i], &vvv[i], &ccc[i]);
	}
	int ans = 0;
	for (int i = 1; i < n; i++)
	{
		for (int j = i + 1; j <= n; j++)
		{
			edgenum = 1;
			memset(head, 0, sizeof(head));
			for (int k = 1; k <= m; k++)
			{
				add(uuu[k], vvv[k], ccc[k]);
				add(vvv[k], uuu[k], ccc[k]);
			}
			int tmp = maxflow(i, j);
			if (map[tmp] == 0)
			{
				map[tmp] = 1;
				ans++;
			}
		}
	}
	printf("%d\n", ans);
	return 0;
}
