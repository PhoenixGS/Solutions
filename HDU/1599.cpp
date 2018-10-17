#include <cstdio>
#include <algorithm>

const int INF = 1000000000;
int n, m;
int map[200][200];
int dis[200][200];
int ans;

int main()
{
	while (scanf("%d%d", &n, &m) == 2)
	{
		for (int i =  1; i <= n; i++)
		{
			for (int j = 1; j <= n; j++)
			{
				map[i][j] = INF;
			}
		}
		for (int i = 1; i <= m; i++)
		{
			int u, v, cost;
			scanf("%d%d%d", &u, &v, &cost);
			map[u][v] = std::min(map[u][v], cost);
			map[v][u] = std::min(map[v][u], cost);
		}
		for (int i = 1; i <= n; i++)
		{
			for (int j = 1; j <= n; j++)
			{
				dis[i][j] = map[i][j];
			}
		}
		ans = INF;
		for (int k = 1; k <= n; k++)
		{
			for (int i = 1; i <= n; i++)
			{
				for (int j = 1; j <= n; j++)
				{
					if (i != j && j != k && i != k)
					{
						if (dis[i][j] != INF)
						{
							ans = std::min(ans, dis[i][j] + map[i][k] + map[j][k]);
						}
					}
				}
			}
			for (int i = 1; i <= n; i++)
			{
				for (int j = 1; j <= n; j++)
				{
					if (i != j && j != k && i != k)
					{
						dis[i][j] = std::min(dis[i][j], dis[i][k] + dis[k][j]);
					}
				}
			}
		}
		if (ans == INF)
		{
			puts("It's impossible.");
		}
		else
		{
			printf("%d\n", ans);
		}
	}
	return 0;
}
