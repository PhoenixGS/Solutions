#include <cstdio>

long long read()
{
    char last = '+', ch = getchar();
    while (ch < '0' || ch > '9') last = ch, ch = getchar();
    long long tmp = 0;
    while (ch >= '0' && ch <= '9') tmp = tmp * 10 + ch - 48, ch = getchar();
    if (last == '-') tmp = -tmp;
    return tmp;
}

const int _n = 5000 + 10;
int n;
int edgenum;
int vet[2 * _n], nextx[2 * _n], head[_n];
int f[_n][_n], g[_n][_n];
long long ans;

void add(int u, int v)
{
	edgenum++;
	vet[edgenum] = v;
	nextx[edgenum] = head[u];
	head[u] = edgenum;
}

void dfs(int u, int father)
{
	f[u][0] = 1;
	for (int i = head[u]; i; i = nextx[i])
	{
		int v = vet[i];
		if (v != father)
		{
			dfs(v, u);
			for (int j = 1; j <= n; j++)
			{
				ans += g[u][j] * f[v][j - 1] + g[v][j] * f[u][j - 1];
			}
			for (int j = 0; j <= n; j++)
			{
				if (j < n)
				{
					g[u][j] += g[v][j + 1];
				}
				if (j > 0)
				{
					g[u][j] += f[u][j] * f[v][j - 1];
				}
			}
			for (int j = 1; j <= n; j++)
			{
				f[u][j] += f[v][j - 1];
			}
		}
	}
}

int main()
{
	scanf("%d", &n);
	for (int i = 1; i < n; i++)
	{
		int u = read();
		int v = read();
		add(u, v);
		add(v, u);
	}
	dfs(1, 0);
	printf("%lld\n", ans);
	return 0;
}
