#include <cstdio>
#include <cstring>
#include <algorithm>

const long long INF = (long long)1e9 * (long long)1e9;
int edgenum;
int vet[200000];
long long val[200000];
int nextx[200000];
int head[6000];
int cur[6000];
int dis[6000];
int que[6000];
int vis[6000];
int x[6000];
int n, m;
long long ans;

void add(int u, int v, long long cost)
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

long long dfs(int u, int t, long long flow)
{
	if (u == t)
	{
		return flow;
	}
	long long ans = 0;
	for (int i = cur[u]; i; i = nextx[i])
	{
		int v = vet[i];
		long long cost = val[i];
		long long f;
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

long long maxflow(int s, int t)
{
	long long flow = 0;
	while (bfs(s, t))
	{
		for (int i = 1; i <= n + 2; i++)
		{
			cur[i] = head[i];
		}
		flow += dfs(s, t, INF);
	}
	return flow;
}

int D(int u)
{
	vis[u] = true;
	int cnt = 1;
	for (int i = head[u]; i; i = nextx[i])
	{
		int v = vet[i];
		int cost = val[i];
		if (! vis[v] && cost)
		{
			cnt += D(v);
		}
	}
	return cnt;
}

int main()
{
	while (scanf("%d%d", &n, &m) == 2)
	{
		edgenum = 1;
		memset(head, 0, sizeof(head));
		memset(vis, 0, sizeof(vis));
		ans = 0;
		for (int i = 1; i <= n; i++)
		{
			scanf("%d", &x[i]);
			if (x[i] >= 0)
			{
				ans += x[i];
				add(n + 1, i, x[i]);
				add(i, n + 1, 0);
			}
			else
			{
				add(i, n + 2, -x[i]);
				add(n + 2, i, 0);
			}
		}
		for (int i = 1; i <= m; i++)
		{
			int x, y;
			scanf("%d%d", &x, &y);
			add(x, y, INF);
			add(y, x, 0);
		}
		ans = ans - maxflow(n + 1, n + 2);
		printf("%d %lld\n", D(n + 1) - 1, ans);
	}
	return 0;
}
