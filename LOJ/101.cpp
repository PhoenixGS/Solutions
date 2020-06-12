#include <cstdio>
#include <algorithm>
#include <queue>

const long long INF = (long long)1000000000 * 1000000000;
const int _n = 100 + 10, _m = 5000 + 10;
int n, m, S, T;
int dis[_n];
int edgenum;
int vet[2 * _m], val[2 * _m], nextx[2 * _m], head[_n], cur[_n];
std::queue<int> que;

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
	for (int i = 1; i <= n; i++)
	{
		dis[i] = -1;
	}
	dis[S] = 0;
	que.push(S);
	while (! que.empty())
	{
		int u = que.front();
		que.pop();
		for (int i = head[u]; i; i = nextx[i])
		{
			int v = vet[i];
			int cost = val[i];
			if (cost && dis[v] == -1)
			{
				dis[v] = dis[u] + 1;
				que.push(v);
			}
		}
	}
	return dis[T] != -1;
}

long long flow(int u, long long maxflow)
{
	if (u == T)
	{
		return maxflow;
	}
	long long ans = 0;
	for (int i = cur[u]; i; i = nextx[i])
	{
		int v = vet[i];
		int cost = val[i];
		if (dis[v] == dis[u] + 1)
		{
			long long f = flow(v, std::min(maxflow - ans, (long long)cost));
			ans += f;
			val[i] -= f;
			val[i ^ 1] += f;
			cur[u] = i;
			if (ans == maxflow)
			{
				break;
			}
		}
	}
	if (ans < maxflow)
	{
		dis[u] = -1;
	}
	return ans;
}

long long maxflow()
{
	long long ans = 0;
	while (bfs())
	{
		for (int i = 1; i <= n; i++)
		{
			cur[i] = head[i];
		}
		ans += flow(S, INF);
	}
	return ans;
}

int main()
{
	edgenum = 1;
	scanf("%d%d%d%d", &n, &m, &S, &T);
	for (int i = 1; i <= m; i++)
	{
		int u, v, cost;
		scanf("%d%d%d", &u, &v, &cost);
		add(u, v, cost);
		add(v, u, 0);
	}
	printf("%lld\n", maxflow());
	return 0;
}
