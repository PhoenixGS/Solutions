#include <cstdio>
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

const long long INF = (long long)1000000000 * 1000000000;
const int _n = 250000 + 10;
int n, m;
int edgenum;
int vet[2 * _n], nextx[2 * _n], head[_n];
long long val[2 * _n];
int times;
int dfn[_n], deep[_n], fa[_n][22];
long long cut[_n];
int flag[_n];
long long f[_n];
int cnt;
int x[2 * _n];
int top;
int stack[_n];

bool comp(int x, int y)
{
	return dfn[x] < dfn[y];
}

void add(int u, int v, long long cost)
{
	edgenum++;
	vet[edgenum] = v;
	val[edgenum] = cost;
	nextx[edgenum] = head[u];
	head[u] = edgenum;
}

void dfs(int u, int father)
{
	times++;
	dfn[u] = times;
	fa[u][0] = father;
	for (int i = 1; i <= 20; i++)
	{
		fa[u][i] = fa[fa[u][i - 1]][i - 1];
	}
	for (int i = head[u]; i; i = nextx[i])
	{
		int v = vet[i];
		long long cost = val[i];
		if (v != father)
		{
			cut[v] = std::min(cut[u], cost);
			deep[v] = deep[u] + 1;
			dfs(v, u);
		}
	}
}

int querylca(int x, int y)
{
	if (deep[x] > deep[y])
	{
		std::swap(x, y);
	}
	for (int i = 20; i >= 0; i--)
	{
		if ((1 << i) & (deep[y] - deep[x]))
		{
			y = fa[y][i];
		}
	}
	if (x == y)
	{
		return x;
	}
	for (int i = 20; i >= 0; i--)
	{
		if (fa[x][i] != fa[y][i])
		{
			x = fa[x][i];
			y = fa[y][i];
		}
	}
	return fa[x][0];
}

void solve(int u, int father)
{
	if (flag[u])
	{
		f[u] = cut[u];
		return;
	}
	f[u] = 0;
	for (int i = head[u]; i; i = nextx[i])
	{
		int v = vet[i];
		if (v != father)
		{
			solve(v, u);
			f[u] += f[v];
		}
	}
	f[u] = std::min(f[u], cut[u]);
}

int main()
{
	scanf("%d", &n);
	for (int i = 1; i < n; i++)
	{
		int u = read();
		int v = read();
		long long w = read();
		add(u, v, w);
		add(v, u, w);
	}

	cut[1] = INF;
	dfs(1, 0);

	edgenum = 0;
	for (int i = 1; i <= n; i++)
	{
		head[i] = 0;
	}

	scanf("%d", &m);
	while (m--)
	{
		int cnt = read();
		for (int i = 1; i <= cnt; i++)
		{
			x[i] = read();
			flag[x[i]] = 1;
		}
		cnt++;
		x[cnt] = 1;
		std::sort(x + 1, x + cnt + 1, comp);
		cnt = std::unique(x + 1, x + cnt + 1) - x - 1;
		for (int i = 1, tmp = cnt; i < tmp; i++)
		{
			cnt++;
			x[cnt] = querylca(x[i], x[i + 1]);
		}
		std::sort(x + 1, x + cnt + 1, comp);
		cnt = std::unique(x + 1, x + cnt + 1) - x - 1;
		top = 1;
		stack[top] = x[1];
		for (int i = 2; i <= cnt; i++)
		{
			while (top > 0 && deep[stack[top]] > deep[querylca(stack[top], x[i])])
			{
				top--;
			}
			if (stack[top])
			{
				add(stack[top], x[i], 0);
			}
			top++;
			stack[top] = x[i];
		}
		solve(1, 0);
		printf("%lld\n", f[1]);

		edgenum = 0;
		for (int i = 1; i <= cnt; i++)
		{
			flag[x[i]] = 0;
			head[x[i]] = 0;
		}
	}
	return 0;
}
