#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>

const int INF = 1e9;
int T;
int edgenum;
int vet[20000];
int cap[20000];
int val[20000];
int nextx[20000];
int head[500];
bool inque[500];
int dis[500];
int pre[500];
int preedge[500];
int l[500], r[500], w[500];
int x[1000];
int s, t;
int last;
std::queue<int> que;
int n, k;

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
	for (int i = 1; i <= last + 3; i++)
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
	scanf("%d", &T);
	while (T--)
	{
		edgenum = 1;
		memset(head, 0, sizeof(head));
		scanf("%d%d", &n, &k);
		last = 0;
		for (int i = 1; i <= n; i++)
		{
			scanf("%d%d%d", &l[i], &r[i], &w[i]);
			last++;
			x[last] = l[i];
			last++;
			x[last] = r[i];
		}
		std::sort(x + 1, x + last + 1);
		last = std::unique(x + 1, x + last + 1) - x - 1;
		s = last + 2;
		t = last + 3;
		for (int i = 1; i <= n; i++)
		{
			l[i] = std::lower_bound(x + 1, x + last + 1, l[i]) - x;
			r[i] = std::lower_bound(x + 1, x + last + 1, r[i]) - x;
		}
		for (int i = 1; i <= n; i++)
		{
			add(l[i], r[i], 1, -w[i]);
			add(r[i], l[i], 0, w[i]);
		}
		for (int i = 1; i <= last; i++)
		{
			add(i, i + 1, k, 0);
			add(i + 1, i, 0, 0);
		}
		add(s, 1, k, 0);
		add(1, s, 0, 0);
		add(last + 1, t, k, 0);
		add(t, last + 1, 0, 0);
		printf("%d\n", -maxflow(s, t));
	}
	return 0;
}
