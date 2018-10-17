#include <cstdio>

void dfs(int u, int father)
{
	fa[u][0] = father;
	for (int i = 1; i <= 20; i++)
	{
		fa[u][i] = fa[fa[u][i - 1]][i - 1];
	}
	times++;
	in[u] = times;
	pos[times] = u;
	for (int i = head[u]; i; i = nextx[i])
	{
		int v = vet[i];
		if (v != father)
		{
			dfs(v, u);
		}
	}
	times++;
	out[u] = times;
	pos[times] = i;
}

int main()
{
	scanf("%d%d%d", &n, &m, &q);
	for (int i = 1; i <= m; i++)
	{
		scanf("%d", &v[i]);
	}
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &w[i]);
	}
	for (int i = 1; i < n; i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		add(u, v);
		add(v, u);
	}
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &x[i]);
	}
	knumber = pow(n, 2.0 / 3);
	for (int i = 1; i <= n; i++)
	{
		knum[i] = (i - 1) / knumber + 1;
	}
	dfs(1, 0);
	for (int i = 1; i <= q; i++)
	{
	}
}
