#include <cstdio>
#include <queue>
#include <algorithm>

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
const int _n = 100000 + 10, _m = 200000 + 10;
int n, m, S;
int edgenum;
int vet[_m], val[_m], nextx[_m], head[_n];
int vis[_n];
std::priority_queue<std::pair<int, int> > que;
int dis[_n];

void add(int u, int v, int cost)
{
	edgenum++;
	vet[edgenum] = v;
	val[edgenum] = cost;
	nextx[edgenum] = head[u];
	head[u] = edgenum;
}

int main()
{
	scanf("%d%d%d", &n, &m, &S);
	for (int i = 1; i <= m; i++)
	{
		int u = read();
		int v = read();
		int cost = read();
		add(u, v, cost);
	}
	for (int i = 1; i <= n; i++)
	{
		dis[i] = INF;
	}
	dis[S] = 0;
	que.push(std::make_pair(-dis[S], S));
	while (! que.empty())
	{
		int u = que.top().second;
		que.pop();
		if (vis[u])
		{
			continue;
		}
		vis[u] = 1;
		for (int i = head[u]; i; i = nextx[i])
		{
			int v = vet[i];
			int cost = val[i];
			if (dis[u] + cost < dis[v])
			{
				dis[v] = dis[u] + cost;
				que.push(std::make_pair(-dis[v], v));
			}
		}
	}
	for (int i = 1; i <= n; i++)
	{
		printf("%d ", dis[i]);
	}
	puts("");
	return 0;
}
