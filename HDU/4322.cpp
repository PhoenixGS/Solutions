#include <cstdio>
#include <cstring>
#include <queue>

int edgenum;
int vet[2000];
int cap[2000];
int val[2000];
int nextx[2000];
int head[100];
int dis[100];
int inque[100];
int pre[100];
int preedge[100];
std::queue<int> que;
int n, m, k;
int ans;
int cnt;
int s, t;
int cas, T;
const int INF = 1e9;
int sum;

void add(int u, int v, int c, int cost)
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
	for (int i = 1; i <= n + m + 2; i++)
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
			int cost = val[i];
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
	cas = 0;
	scanf("%d", &T);
	while (T--)
	{
		edgenum = 1;
		memset(head, 0, sizeof(head));
		scanf("%d%d%d", &n, &m, &k);
		sum = 0;
		s = n + m + 1;
		t = n + m + 2;
		for (int i = 1; i <= m; i++)
		{
			int x;
			scanf("%d", &x);
			sum += x;
			add(i, t, x / k, -k);
			add(t, i, 0, k);
			if (x % k)
			{
				add(i, t, 1, -x % k);
				add(t, i, 0, x % k);
			}
		}
		for (int i = 1; i <= m; i++)
		{
			for (int j = 1; j <= n; j++)
			{
				int x;
				scanf("%d", &x);
				if (x)
				{
					add(j + m, i, 1, 0);
					add(i, j + m, 0, 0);
				}
			}
		}
		for (int i = 1; i <= n; i++)
		{
			add(s, i + m, 1, 0);
			add(i + m, s, 0, 0);
		}
		ans = -maxflow(s, t);
		cnt = 0;
		for (int i = head[s]; i; i = nextx[i])
		{
			cnt += cap[i] == 0;
		}
		cas++;
		printf("Case #%d: ", cas);
		if (ans + n - cnt >= sum)
		{
			printf("YES\n");
		}
		else
		{
			printf("NO\n");
		}
	}
	return 0;
}
