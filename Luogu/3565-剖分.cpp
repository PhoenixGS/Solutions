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
int len[_n], son[_n];
int arr[8 * _n];
int *now = arr;
int *f[_n], *g[_n];
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
	for (int i = head[u]; i; i = nextx[i])
	{
		int v = vet[i];
		if (v != father)
		{
			dfs(v, u);
			if (len[v] > len[son[u]])
			{
				son[u] = v;
			}
		}
	}
	len[u] = len[son[u]] + 1;
}

void dfs2(int u, int father)
{
	if (son[u])
	{
		f[son[u]] = f[u] + 1;
		g[son[u]] = g[u] - 1;
		dfs2(son[u], u);
	}
	f[u][0] = 1;
	ans += g[u][0];
	for (int i = head[u]; i; i = nextx[i])
	{
		int v = vet[i];
		if (v != father && v != son[u])
		{
			f[v] = now;
			now += len[v] << 1;
			g[v] = now;
			now += len[v] << 1;
			dfs2(v, u);
			for (int j = 0; j <= len[v]; j++)
			{
				if (j > 0)
				{
					ans += g[u][j] * f[v][j - 1];
				}
				if (j < len[v])
				{
					ans += f[u][j - 1] * g[v][j];
				}
			}
			for (int j = 0; j <= len[v]; j++)
			{
				if (j + 1 < len[v])
				{
					g[u][j] += g[v][j + 1];
				}
				if (j > 0)
				{
					g[u][j] += f[u][j] * f[v][j - 1];
				}
			}
			for (int j = 1; j <= len[v]; j++)
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
	f[1] = now;
	now += len[1] << 1;
	g[1] = now;
	now += len[1] << 1;
	dfs2(1, 0);
	printf("%lld\n", ans);
	return 0;
}

