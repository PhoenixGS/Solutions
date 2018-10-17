#include <cstdio>
#include <queue>

using namespace std;

int edgenum;
int vet[10000000];
int val[10000000];
int nextx[10000000];
int head[3000000];
bool flag[3000000];
int dis[3000000];
priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > Q;
int n, m;

void addedge(int u, int v, int cost)
{
	edgenum++;
	vet[edgenum] = v;
	val[edgenum] = cost;
	nextx[edgenum] = head[u];
	head[u] = edgenum;
}

void add(int u, int v, int cost)
{
	addedge(u, v, cost);
	addedge(v, u, cost);
}

int main()
{
	edgenum = 0;
	scanf("%d%d", &n, &m);
	int rightup = 2 * (n - 1) * (m - 1) + 1;
	int leftdown = 2 * (n - 1) * (m - 1) + 2;
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j < m; j++)
		{
			int cost;
			scanf("%d", &cost);
			int up = (i - 2) * 2 * (m - 1) + (j - 1) * 2 + 1;
			int down = (i - 1) * 2 * (m - 1) + j * 2;
			if (i == 1)
			{
				add(down, rightup, cost);
			}
			if (i == n)
			{
				add(up, leftdown, cost);
			}
			if (i > 1 && i < n)
			{
				add(up, down, cost);
			}
		}
	}
	for (int i = 1; i < n; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			int cost;
			scanf("%d", &cost);
			int left = (i - 1) * 2 * (m - 1) + (j - 1) * 2;
			int right = (i - 1) * 2 * (m - 1) + (j - 1) * 2 + 1;
			if (j == 1)
			{
				add(right, leftdown, cost);
			}
			if (j == m)
			{
				add(left, rightup, cost);
			}
			if (j > 1 && j < m)
			{
				add(left, right, cost);
			}
		}
	}
	for (int i = 1; i < n; i++)
	{
		for (int j = 1; j < m; j++)
		{
			int cost;
			scanf("%d", &cost);
			int ld = (i - 1) * 2 * (m - 1) + 2 * (j - 1) + 1;
			int ru = (i - 1) * 2 * (m - 1) + 2 * j;
			add(ld, ru, cost);
		}
	}
	for (int i = 1; i <= 2 * (n - 1) * (m - 1) + 2; i++)
	{
		dis[i] = 1000000000;
	}
	Q.push(make_pair(0, rightup));
	dis[rightup] = 0;
	while (! Q.empty())
	{
		int u = Q.top().second;
		Q.pop();
		if (flag[u])
		{
			continue;
		}
		flag[u] = true;
		for (int i = head[u]; i; i = nextx[i])
		{
			int v = vet[i];
			int cost = val[i];
			if (dis[u] + cost < dis[v])
			{
				dis[v] = dis[u] + cost;
				Q.push(make_pair(dis[v], v));
			}
		}
	}
	printf("%d\n", dis[leftdown]);
	return 0;
}
