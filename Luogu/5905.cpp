#include <cstdio>
#include <cstring>
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

const int INF = 1000000000;
const int _n = 3000 + 10, _m = 6000 + 10;
int n, m;
int uuu[_m], vvv[_m], www[_m];
int edgenum;
int vet[2 * _m], val[2 * _m], nextx[2 * _m], head[_n];
std::queue<int> que;
std::priority_queue<std::pair<int, int> > heap;
int vis[_n], tim[_n], inque[_n];
int pe[_n];
int dis[_n][_n];

void add(int u, int v, int cost)
{
	edgenum++;
	vet[edgenum] = v;
	val[edgenum] = cost;
	nextx[edgenum] = head[u];
	head[u] = edgenum;
}

bool SPFA(int s)
{
	pe[s] = 0;
	inque[s] = 1;
	que.push(s);
	while (! que.empty())
	{
		int u = que.front();
		que.pop();
		tim[u]++;
		if (tim[u] >= n)
		{
			return 0;
		}
		for (int i = head[u]; i; i = nextx[i])
		{
			int v = vet[i];
			int cost = val[i];
			if (pe[u] + cost < pe[v])
			{
				pe[v] = pe[u] + cost;
				if (! inque[v])
				{
					que.push(v);
					inque[v] = 1;
				}
			}
		}
		inque[u] = 0;
	}
	return 1;
}

void dijkstra(int s)
{
	for (int i = 1; i <= n; i++)
	{
		vis[i] = 0;
		dis[s][i] = INF + 100;
	}
	dis[s][s] = 0;
	heap.push(std::make_pair(-dis[s][s], s));
	while (! heap.empty())
	{
		int u = heap.top().second;
		heap.pop();
		if (vis[u])
		{
			continue;
		}
		vis[u] = 1;
		for (int i = head[u]; i; i = nextx[i])
		{
			int v = vet[i];
			int cost = val[i];
			if (dis[s][u] + cost < dis[s][v])
			{
				dis[s][v] = dis[s][u] + cost;
				heap.push(std::make_pair(-dis[s][v], v));
			}
		}
	}
}

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; i++)
	{
		uuu[i] = read();
		vvv[i] = read();
		www[i] = read();
		add(uuu[i], vvv[i], www[i]);
	}
	for (int i = 1; i <= n; i++)
	{
		add(n + 1, i, 0);
	}

	for (int i = 1; i <= n; i++)
	{
		pe[i] = INF;
	}
	if (! SPFA(n + 1))
	{
		puts("-1");
		return 0;
	}

	edgenum = 0;
	memset(head, 0, sizeof(head));

	for (int i = 1; i <= m; i++)
	{
		add(uuu[i], vvv[i], www[i] + pe[uuu[i]] - pe[vvv[i]]);
	}
	for (int i = 1; i <= n; i++)
	{
		dijkstra(i);
	}
	for (int i = 1; i <= n; i++)
	{
		long long ans = 0;
		for (int j = 1; j <= n; j++)
		{
			ans = ans + (long long)j * ((dis[i][j] == INF + 100) ? INF : (dis[i][j] - pe[i] + pe[j]));
		}
		printf("%lld\n", ans);
	}
	return 0;
}
