#include <cstdio>
#include <cstring>

int edgenum;
int times;
int vet[10000];
int nextx[10000];
int head[10000];
int vis[10000];
int match[10000];
int n, m;
int ans;
char st[100][100];

int calc(int x, int y)
{
	return (x - 1) * m + y;
}

void add(int u, int v)
{
	edgenum++;
	vet[edgenum] = v;
	nextx[edgenum] = head[u];
	head[u] = edgenum;
}

bool dfs(int u)
{
	for (int i = head[u]; i; i = nextx[i])
	{
		int v = vet[i];
		if (vis[v] != times)
		{
			vis[v] = times;
			if (! match[v] || dfs(match[v]))
			{
				match[v] = u;
				return true;
			}
		}
	}
	return false;
}

int main()
{
	while (scanf("%d%d", &n, &m) == 2)
	{
		times = 0;
		edgenum = 0;
		memset(head, 0, sizeof(head));
		memset(vis, 0, sizeof(vis));
		for (int i = 1; i <= n; i++)
		{
			scanf("%s", st[i] + 1);
		}
		for (int i = 1; i <= n; i++)
		{
			for (int j = 1; j <= m; j++)
			{
				if (st[i][j] == '*')
				{
					int xx = i;
					int yy = j;
					while (xx > 1 && st[xx - 1][j] == '*')
					{
						xx--;
					}
					while (yy > 1 && st[i][yy - 1] == '*')
					{
						yy--;
					}
					add(calc(xx, j), calc(i, yy) + n * m);
				}
			}
		}
		memset(match, 0, sizeof(match));
		ans = 0;
		for (int i = 1; i <= n * m; i++)
		{
			times++;
			ans += dfs(i);
		}
		printf("%d\n", ans);
	}
	return 0;
}
