#include <cstdio>
#include <algorithm>
#include <queue>

long long read()
{
	char last = '+', ch = getchar();
	while (ch < '0' || ch > '9') last = ch, ch = getchar();
	long long tmp = 0;
	while (ch >= '0' && ch <= '9') tmp = tmp * 10 + ch - 48, ch = getchar();
	if (last == '-') tmp = -tmp;
	return tmp;
}

const long long INF = (long long)1000000000 * 1000000000;
const int _n = 1000 + 10, _m = 10000 + 10;
int n, m;
int need[_n];
int S, T;
int edgenum;
int vet[4 * _n + 2 * _m], nextx[4 * _n + 2 * _m], head[_n];
long long cap[4 * _n + 2 * _m], val[4 * _n + 2 * _m];
std::queue<int> que;
long long dis[_n], inque[_n], flow[_n];
int pre[_n], preedge[_n];
long long maxflow, mincost;

void add(int u, int v, long long c, long long cost)
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
	for (int i = 1; i <= n + 3; i++)
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
			long long c = cap[i];
			long long cost = val[i];
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
	S = n + 2;
	T = n + 3;
	for (int i = 1; i <= n; i++)
	{
		need[i] = read();
	}
	for (int i = 1; i <= n + 1; i++)
	{
		if (need[i] - need[i - 1] > 0)
		{
			add(S, i, need[i] - need[i - 1], 0);
			add(i, S, 0, 0);
		}
		if (need[i] - need[i - 1] < 0)
		{
			add(i, T, need[i - 1] - need[i], 0);
			add(T, i, 0, 0);
		}
	}
	for (int i = 1; i <= n; i++)
	{
		add(i + 1, i, INF, 0);
		add(i, i + 1, 0, 0);
	}
	for (int i = 1; i <= m; i++)
	{
		int l, r, cost;
		l = read();
		r = read();
		cost = read();
		add(l, r + 1, INF, cost);
		add(r + 1, l, 0, -cost);
	}
	mxflow(S, T);
	printf("%lld\n", mincost);
	return 0;
}

