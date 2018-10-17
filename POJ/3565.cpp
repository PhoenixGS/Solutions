#include <cstdio>
#include <cstring>
#include <cmath>
#include <queue>

const double eps = 1e-8;
const int INF = 1e9;
double dis[500];
int inque[500];
int pre[500];
int preedge[500];
std::queue<int> que;
int edgenum;
int vet[40000];
int cap[40000];
double val[40000];
int nextx[40000];
int head[500];
int n;
double xx1[500], yy1[500], xx2[500], yy2[500];

double calc(int x, int y)
{
	return sqrt((xx1[x] - xx2[y]) * (xx1[x] - xx2[y]) + (yy1[x] - yy2[y]) * (yy1[x] - yy2[y]));
}

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
	for (int i = 1; i <= 2 * n + 2; i++)
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
				if (dis[v] - dis[u] - cost > eps)
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

void maxflow(int s, int t)
{
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
			now = pre[now];
		}
	}
}

int main()
{
	while (scanf("%d", &n) == 1)
	{
		edgenum = 1;
		memset(head, 0, sizeof(head));
		for (int i = 1; i <= n; i++)
		{
			scanf("%lf%lf", &xx1[i], &yy1[i]);
		}
		for (int i = 1; i <= n; i++)
		{
			scanf("%lf%lf", &xx2[i], &yy2[i]);
		}
		for (int i = 1; i <= n; i++)
		{
			add(2 * n + 1, i, 1, 0);
			add(i, 2 * n + 1, 0, 0);
		}
		for (int i = 1; i <= n; i++)
		{
			add(i + n, 2 * n + 2, 1, 0);
			add(2 * n + 2, i + n, 0, 0);
		}
		for (int i = 1; i <= n; i++)
		{
			for (int j = 1; j <= n; j++)
			{
				add(i, j + n, 1, calc(i, j));
				add(j + n, i, 0, -calc(i, j));
			}
		}
		maxflow(2 * n + 1, 2 * n + 2);
		for (int u = 1; u <= n; u++)
		{
			int tmp = -1;
			for (int i = head[u]; i; i = nextx[i])
			{
				int v = vet[i];
				int c = cap[i];
				if (c == 0)
				{
					tmp = v;
					break;
				}
			}
			printf("%d\n", tmp - n);
		}
	}
	return 0;
}
