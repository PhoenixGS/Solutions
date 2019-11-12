#include <cstdio>
#include <cstring>
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
const int _n = 2000 + 10, _m = 3000 + 10;
int T;
int n, m;
int edgenum;
int vet[2 * _m], val[2 * _m], nextx[2 * _m], head[_n];
std::queue<int> que;
int inque[_n], dis[_n], cnt[_n];

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
	scanf("%d", &T);
	while (T--)
	{
		edgenum = 0;
		memset(head, 0, sizeof(head));
		scanf("%d%d", &n, &m);
		for (int i = 1; i <= m; i++)
		{
			int u = read();
			int v = read();
			int cost = read();
			add(u, v, cost);
			if (cost >= 0)
			{
				add(v, u, cost);
			}
		}
		while (! que.empty())
		{
			que.pop();
		}
		for (int i = 1; i <= n; i++)
		{
			inque[i] = cnt[i] = 0;
			dis[i] = INF;
		}
		que.push(1);
		bool ff = 0;
		inque[1] = 1;
		cnt[1] = 1;
		dis[1] = 0;
		while (! que.empty())
		{
			int u = que.front();
			que.pop();
			if (cnt[u] > n)
			{
				ff = 1;
				break;
			}
			inque[u] = 0;
			for (int i = head[u]; i; i = nextx[i])
			{
				int v = vet[i];
				int cost = val[i];
				if (dis[u] + cost < dis[v])
				{
					dis[v] = dis[u] + cost;
					cnt[v] = cnt[u] + 1;
					if (! inque[v])
					{
						que.push(v);
						inque[v] = 1;
					}
				}
			}
		}
		puts(ff ? "YE5" : "N0");
	}
	return 0;
}
