#include <cstdio>
#include <cstring>

int n, m, k;
bool flag[100][100];
int edgenum;
int vet[7000];
int nextx[7000];
int head[7000];
int vis[7000];
int match[7000];
const int dx[4] = {1, 0, -1, 0};
const int dy[4] = {0, 1, 0, -1};
int times;
int ans;

void add(int u, int v)
{
	edgenum++;
	vet[edgenum] = v;
	nextx[edgenum] = head[u];
	head[u] = edgenum;
}

int calc(int x, int y)
{
	return (x - 1) * m + y;
}

bool dfs(int u)
{
	for (int i = head[u]; i; i = nextx[i])
	{
		int v = vet[i];
		if (vis[v] != times)
		{
			vis[v] = times;
			if (match[v] == 0 || dfs(match[v]))
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
	while (scanf("%d%d%d", &n, &m, &k) == 3)
	{
		edgenum = 0;
		times = 0;
		memset(head, 0, sizeof(head));
		memset(flag, 0, sizeof(flag));
		memset(vis, 0, sizeof(vis));
		for (int i = 1; i <= k; i++)
		{
			int x, y;
			scanf("%d%d", &x, &y);
			flag[y][x] = true;
		}
		if ((n * m - k) & 1)
		{
			printf("NO\n");
			continue;
		}
		for (int i = 1; i <= n; i++)
		{
			for (int j = 1; j <= m; j++)
			{
				if (! flag[i][j])
				{
					for (int k = 0; k < 4; k++)
					{
						int xx = i + dx[k];
						int yy = j + dy[k];
						if (xx >= 1 && xx <= n && yy >= 1 && yy <= m && ! flag[xx][yy])
						{
							add(calc(i, j), calc(xx, yy));
						}
					}
				}
			}
		}
		ans = 0;
		for (int i = 1; i <= n; i++)
		{
			for (int j = 1; j <= m; j++)
			{
				if ((i + j) & 1)
				{
					times++;
					ans += dfs(calc(i, j));
				}
			}
		}
		if (ans == (n * m - k) >> 1)
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
