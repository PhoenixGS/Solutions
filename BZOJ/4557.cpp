#include <cstdio>

void dfs(int u, int father)
{
	f[u][0] = g[u][0] = mark[u] ? w[u] : 0;
	for (int i = 1; i <= d; i++)
	{
		g[u][i] = w[u];
	}
	g[u][d + 1] = 1000000000;
	for (int i = head[u]; i; i = nextx[i])
	{
		int v = vet[i];
		if (v != father)
		{
			dfs(v, u);
			for (int j = 0; j <= d; j++)
			{
				g[u][j] = std::min(j == 0 ? 1000000000 : (g[u][j] + f[v][j - 1]), g[v][j + 1] + f[u][j]);
			}
			for (int j = d; j >= 0; j--)
			{
				g[u][j] = std::min(g[u][j], g[u][j + 1]);
			}
			f[u][0] = g[u][0];
			for (int j = 1; j <= d; j++)
			{
				f[u][j] += f[v][j - 1];
			}

		}
	}
}

int main()
{
	n = read();
	d = read();
	for (int i = 1; i <= n; i++)
	{
		w[i] = read();
	}
	m = read();
	for (int i = 1; i <= m; i++)
	{
		int tmp = read();
		mark[tmp] = true;
	}
	for (int i = 1; i < n; i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		add(u, v);
		add(v, u);
	}
	dfs(1, 0);
	printf("%d\n", f[1][0]);
	return 0;
}
