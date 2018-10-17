#include <cstdio>
#include <cstring>
#include <algorithm>

const int INF = 1e9;
int edgenum;
int vet[20000000];
int cap[20000000];
int val[20000000];
int nextx[20000000];
int head[90000];
int dis[900000];
int inque[900000];
int pre[900000];
int preedge[900000];
int n, m;
int s, t;
int c[1000000];
int x[1000][1000];
int que[3000000];
int T;
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
	for (int i = 1; i <= n + m * sum + 2; i++)
	{
		dis[i] = INF;
		inque[i] = 0;
		pre[i] = 0;
		preedge[i] = 0;
	}
	int headx = 1;
	int tailx = 1;
	que[headx] = s;
	inque[s] = true;
	dis[s] = 0;
	while (headx <= tailx)
	{
		int u = que[headx];
		headx++;
		for (int i = head[u]; i; i = nextx[i])
		{
			int v = vet[i];
			int c = cap[i];
			int cost = val[i];
			if (c)
			{
				if (dis[u] + cost < dis[v])
				{
                    //printf("%d %d\n", u, v);
					dis[v] = dis[u] + cost;
					pre[v] = u;
					preedge[v] = i;
					if (! inque[v])
					{
						tailx++;
						que[tailx] = v;
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
        int kk = now;
		while (now != s)
		{
            minx = std::min(minx, cap[preedge[now]]);
			if (pre[now] == s)
			{
				kk = now;
			}
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
        int times = (kk - n - 1) / m + 2;
        int u = (kk - n - 1) % m + 1;
        add(s, n + (times - 1) * m + u, 1, 0);
        add(n + (times - 1) * m + u, s, 0, 0);
        for (int i = 1; i <= n; i++)
        {
            add(n + (times - 1) * m + u, i, 1, times * x[i][u]);
            add(i, n + (times - 1) * m + u, 0, -times * x[i][u]);
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
		sum = 0;
        for (int i = 1; i <= n; i++)
        {
            scanf("%d", &c[i]);
			sum += c[i];
        }
        s = n + sum * m + 1;
        t = n + sum * m + 2;
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= m; j++)
            {
                scanf("%d", &x[i][j]);
            }
        }
        for (int i = 1; i <= n; i++)
        {
            add(i, t, c[i], 0);
            add(t, i, 0, 0);
        }
        for (int i = 1; i <= m; i++)
        {
            add(s, n + i, 1, 0);
            add(n + i, s, 0, 0);
        }
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= m; j++)
            {
                add(n + j, i, 1, x[i][j]);
                add(i, n + j, 0, -x[i][j]);
            }
        }
        printf("%d\n", maxflow(s, t));
    }
    return 0;
}
