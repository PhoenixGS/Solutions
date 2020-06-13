#include <cstdio>
#include <algorithm>
#include <queue>

const int INF = 2147483647;
const int _n = 400 + 10, _m = 15000 + 10;
int n, m;
int S, T;
int edgenum;
int vet[2 * _m], cap[2 * _m], val[2 * _m], nextx[2 * _m], head[_n];
std::queue<int> que;
int dis[_n], inque[_n], pre[_n], preedge[_n], flow[_n];
int maxflow, mincost;

void add(int u, int v, int c, int cost)
{
	edgenum++;
	vet[edgenum] = v;
	cap[edgenum] = c;
	val[edgenum] = cost;
	nextx[edgenum] = head[u];
	head[u] = edgenum;
}

bool SPFA(int S, int T)
{
	for (int i = 1; i <= n; i++)
	{
		dis[i] = INF;
		flow[i] = INF;
		inque[i] = 0;
		pre[i] = 0;
		preedge[i] = 0;
		flow[i] = 0;
	}
	que.push(S);
	inque[S] = true;
	dis[S] = 0;
	flow[S] = INF;
	while (! que.empty())
	{
		int u = que.front();
		que.pop();
		for (int i = head[u]; i; i = nextx[i])
		{
			int v = vet[i];
			int c = cap[i];
			int cost = val[i];
			if (c && dis[u] + cost < dis[v])
			{
				dis[v] = dis[u] + cost;
				pre[v] = u;
				preedge[v] = i;
				flow[v] = std::min(flow[u], c);
				if (! inque[v])
				{
					que.push(v);
					inque[v] = true;
				}
			}
		}
		inque[u] = false;
	}
	return pre[T] != 0;
}

void mxflow(int S, int T)
{
	while (SPFA(S, T))
	{
		maxflow += flow[T];
		mincost += flow[T] * dis[T];
		int now = T;
		while (now != S)
		{
			cap[preedge[now]] -= flow[T];
			cap[preedge[now] ^ 1] += flow[T];
			now = pre[now];
		}
	}
}

int main()
{
	edgenum = 1;
	scanf("%d%d", &n, &m);
	S = 1;
	T = n;
	for (int i = 1; i <= m; i++)
	{
		int u, v, c, w;
		scanf("%d%d%d%d", &u, &v, &c, &w);
		add(u, v, c, w);
		add(v, u, 0, -w);
	}
	mxflow(S, T);
	printf("%d %d\n", maxflow, mincost);
	return 0;
}
