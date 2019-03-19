#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>

const int INF = 1e9;
int edgenum;
int vet[200000];
int cap[200000];
int val[200000];
int nextx[200000];
int head[2000];
int dis[2000];
int inque[2000];
int pre[2000];
int preedge[2000];
int n, m;
int l[20000], r[20000], w[20000];
int x[2000];
int s, t;
int T;
std::queue<int> que;

void add(int u, int v, int c, double cost)
{
	edgenum++;
	vet[edgenum] = v;
	cap[edgenum] = c;
	val[edgenum] = cost;
	nextx[edgenum] = head[u];
	head[u] = edgenum;
}

bool SPFA(int s, int t)
{
	for (int i = 1; i <= n + 3; i++)
	{
		dis[i] = INF;
		inque[i] = 0;
		pre[i] = 0;
		preedge[i] = 0;
	}
	que.push(s);
	inque[s] = true;
	dis[s] = 0;
	while (! que.empty())
	{
		int u = que.front();
		que.pop();
		for (int i = head[u]; i; i = nextx[i])
		{
			int v = vet[i];
			int c = cap[i];
			double cost = val[i];
			if (c)
			{
				if (dis[u] + cost < dis[v])
				{
					dis[v] = dis[u] + cost;
					pre[v] = u;
					preedge[v] = i;
					if (! inque[v])
					{
						que.push(v);
						inque[v] = true;
					}
				}
			}
		}
		inque[u] = false;
	}
	return pre[t] != 0;
}

int maxflow(int s, int t)
{
	int ans = 0;
	while (SPFA(s, t))
	{
		int minx = INF;
		int now = t;
		while (now != s)
		{
			minx = std::min(minx, cap[preedge[now]]);
			now = pre[now];
		}
		now = t;
		while (now != s)
		{
			cap[preedge[now]] -= minx;
			cap[preedge[now] ^ 1] += minx;
			ans += val[preedge[now]] * minx;
			now = pre[now];
		}
	}
	return ans;
}

int main()
{
	while (scanf("%d%d", &n, &m) == 2)
	{
		edgenum = 1;
		memset(head, 0, sizeof(head));
		s = n + 2;
		t = n + 3;
		x[0] = x[n + 1] = 0;
		for (int i = 1; i <= n; i++)
		{
			scanf("%d", &x[i]);
		}
		for (int i = 1; i <= n + 1; i++)
		{
			if (x[i] - x[i - 1] > 0)
			{
				add(s, i, x[i] - x[i - 1], 0);
				add(i, s, 0, 0);
			}
			if (x[i] - x[i - 1] < 0)
			{
				add(i, t, x[i - 1] - x[i], 0);
				add(t, i, 0, 0);
			}
		}
		for (int i = 1; i <= m; i++)
		{
			scanf("%d%d%d", &l[i], &r[i], &w[i]);
			add(l[i], r[i] + 1, INF, w[i]);
			add(r[i] + 1, l[i], 0, -w[i]);
		}
		for (int i = 1; i <= n; i++)
		{
			add(i + 1, i, INF, 0);
			add(i, i + 1, 0, 0);
		}
		printf("%d\n", maxflow(s, t));
	}
	return 0;
}

