#include <cstdio>
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

const int INF = 1000000000;
const int _n = 1000 + 10, _m = 10000 + 10;
int n, m;
int x[_n];
int edgenum;
int vet[4 * _n + 2 * _m], cap[4 * _n + 2 * _m], val[4 * _n + 2 * _m], nextx[4 * _n + 2 * _m], head[_n];
int S, T;
std::queue<int> que;
int dis[_n], inque[_n], pre[_n], preedge[_n];

void add(int u, int v, int lim, int cost)
{
	edgenum++;
	vet[edgenum] = v;
	cap[edgenum] = lim;
	val[edgenum] = cost;
	nextx[edgenum] = head[u];
	head[u] = edgenum;
}

bool SPFA(int S, int T)
{
	for (int i = 1; i <= n + 4; i++)
	{
		dis[i] = INF;
		inque[i] = 0;
		pre[i] = 0;
		preedge[i] = 0;
	}
	dis[S] = 0;
	que.push(S);
	while (! que.empty())
	{
		int u = que.front();
		que.pop();
		inque[u] = 0;
		for (int i = head[u]; i; i = nextx[i])
		{
			int v = vet[i];
			int lim = cap[i];
			int cost = val[i];
			if (lim && dis[u] + cost < dis[v])
			{
				dis[v] = dis[u] + cost;
				preedge[v] = i;
				pre[v] = u;
				if (! inque[v])
				{
					que.push(v);
					inque[v] = 1;
				}
			}
		}
	}
	return pre[T] != 0;
}

int maxflow(int S, int T)
{
	int ans = 0;
	while (SPFA(S, T))
	{
		int minx = INF;
		int now = T;
		while (now != S)
		{
			minx = std::min(minx, cap[preedge[now]]);
			now = pre[now];
		}
		now = T;
		while (now != S)
		{
			cap[preedge[now]] -= minx;
			cap[preedge[now] ^ 1] += minx;
			ans += minx * val[preedge[now]];
			now = pre[now];
		}
	}
	return ans;
}

int main()
{
	edgenum = 1;
	scanf("%d%d", &n, &m);
	S = n + 3;
	T = n + 4;
	for (int i = 1; i <= n; i++)
	{
		add(i + 1, i + 2, INF, 0);
		add(i + 2, i + 1, 0, 0);
	}
	for (int i = 1; i <= n; i++)
	{
		x[i] = read();
	}
	for (int i = 1; i <= n + 1; i++)
	{
		if (x[i] - x[i - 1] > 0)
		{
			add(i + 1, T, x[i] - x[i - 1], 0);
			add(T, i + 1, 0, 0);
		}
		if (x[i] - x[i - 1] < 0)
		{
			add(S, i + 1, x[i - 1] - x[i], 0);
			add(i + 1, S, 0, 0);
		}
	}
	for (int i = 1; i <= m; i++)
	{
		int l, r, c;
		l = read();
		r = read();
		c = read();
		add(r + 2, l + 1, INF, c);
		add(l + 1, r + 2, 0, -c);
	}
	printf("%d\n", maxflow(S, T));
	return 0;
}
