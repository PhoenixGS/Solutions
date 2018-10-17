#include <cstdio>
#include <cstring>
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

int dis[2000];
int que[2000];
int edgenum;
int vet[40000];
long long val[40000];
int nextx[40000];
int head[2000];
int cur[2000];
const long long INF = 1ll << 50;
int n, m;
long long sumB, sumW, numB, numW;
long long maxx;
long long x[100][100];
int T;
const int dx[4] = {0, 1, 0, -1};
const int dy[4] = {1, 0, -1, 0};
int s, t;

int calc(int x, int y)
{
	return (x - 1) * m + y;
}

void add(int u, int v, long long cost)
{
	edgenum++;
	vet[edgenum] = v;
	val[edgenum] = cost;
	nextx[edgenum] = head[u];
	head[u] = edgenum;
}

bool bfs()
{
	memset(dis, -1, sizeof(dis));
	int headx = 1;
	int tailx = 0;
	tailx++;
	que[tailx] = s;
	dis[s] = 0;
	while (headx <= tailx)
	{
		int u = que[headx];
		headx++;
		for (int i = head[u]; i; i = nextx[i])
		{
			int v = vet[i];
			long long cost = val[i];
			//printf("%d %d %lld %d\n", u, v, cost, i);
			if (cost && dis[v] == -1)
			{
				dis[v] = dis[u] + 1;
				tailx++;
				que[tailx] = v;
			}
		}
	}
	//puts("");
	return dis[t] != -1;
}

long long dfs(int u, long long flow)
{
	if (u == t)
	{
		return flow;
	}
	long long ans = 0;
	for (int i = cur[u]; i; i = nextx[i])
	{
		int v = vet[i];
		long long cost = val[i];
		if (dis[u] + 1 == dis[v])
		{
			long long f = dfs(v, std::min(flow - ans, cost));
			val[i] -= f;
			val[i ^ 1] += f;
			ans += f;
			cur[u] = i;
			if (ans == flow)
			{
				break;
			}
		}
	}
	if (ans < flow)
	{
		dis[u] = -1;
	}
	return ans;
}

long long maxflow()
{
	long long flow = 0;
	while (bfs())
	{
		for (int i = 1; i <= n * m + 2; i++)
		{
			cur[i] = head[i];
		}
		flow += dfs(s, INF);
	}
	return flow;
}

bool check(long long mid)
{
	edgenum = 1;
	memset(head, 0, sizeof(head));
	s = n * m + 1;
	t = n * m + 2;
	long long tot = 0;
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			if ((i + j) & 1)
			{
				add(s, calc(i, j), mid - x[i][j]);
				add(calc(i, j), s, 0);
				tot += mid - x[i][j];
				for (int k = 0; k < 4; k++)
				{
					int xx = i + dx[k];
					int yy = j + dy[k];
					if (xx >= 1 && xx <= n && yy >= 1 && yy <= m)
					{
						add(calc(i, j), calc(xx, yy), INF);
						add(calc(xx, yy), calc(i, j), 0);
					}
				}
			}
			else
			{
				add(calc(i, j), t, mid - x[i][j]);
				add(t, calc(i, j), 0);
			}
		}
	}
	long long flow = maxflow();
	return flow == tot;
}

int main()
{
	scanf("%d", &T);
	while (T--)
	{
		numB = numW = sumB = sumW = 0;
		maxx = 0;
		scanf("%d%d", &n, &m);
		for (int i = 1; i <= n; i++)
		{
			for (int j = 1; j <= m; j++)
			{
				scanf("%lld", &x[i][j]);
				maxx = std::max(maxx, x[i][j]);
				if ((i + j) & 1)
				{
					sumB += x[i][j];
					numB++;
				}
				else
				{
					sumW += x[i][j];
					numW++;
				}
			}
		}
		if (numB != numW)
		{
			long long kk = (sumB - sumW) / (numB - numW);
			if (kk >= maxx)
			{
				if (check(kk))
				{
					printf("%lld\n", kk * numB - sumB);
					continue;
				}
			}
			printf("-1\n");
		}
		else
		{
			if (sumB != sumW)
			{
				printf("-1\n");
				continue;
			}
			long long l = maxx;
			long long r = INF;
			while (l < r)
			{
				long long mid = (l + r) >> 1;
				if (check(mid))
				{
					r = mid;
				}
				else
				{
					l = mid + 1;
				}
			}
			if (check(l))
			{
				printf("%lld\n", l * numB - sumB);
			}
			else
			{
				printf("-1\n");
			}
		}
	}
	return 0;
}
