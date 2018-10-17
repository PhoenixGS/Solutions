#include <cstdio>
#include <cstring>
#include <algorithm>

const long long INF = (long long)1000000000 * 1000000000;
int n, m;
int edgenum;
int vet[600000], val[600000], nextx[600000], head[300000];
int times;
int dfn[300000], deep[300000], fa[300000][22];
int flag[300000];
long long f[300000];
int x[300000];
int top;
int stack[300000];
long long ccc[300000];
int cc[300000];

bool comp(int x, int y)
{
	return dfn[x] < dfn[y];
}

void add(int u, int v, int cost)
{
	edgenum++;
	vet[edgenum] = v;
	val[edgenum] = cost;
	nextx[edgenum] = head[u];
	head[u] = edgenum;
}

void dfs(int u, int father, int dep)
{
	times++;
	dfn[u] = times;
	deep[u] = dep;
	fa[u][0] = father;
	for (int i = 1; i <= 20; i++)
	{
		fa[u][i] = fa[fa[u][i - 1]][i - 1];
	}
	for (int i = head[u]; i; i = nextx[i])
	{
		int v = vet[i];
		int cost = val[i];
		if (v != father)
		{
			ccc[v] = std::min(ccc[u], (long long)cost);
			dfs(v, u, dep + 1);
		}
	}
}

int querylca(int x, int y)
{
	if (deep[x] < deep[y])
	{
		std::swap(x, y);
	}
	for (int i = 20; i >= 0; i--)
	{
		if ((deep[x] - deep[y]) & (1 << i))
		{
			x = fa[x][i];
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
		f[u] = ccc[u];
		return;
	}
	f[u] = ccc[u];;
	long long tmp = 0;
	int flag = 0;
	for (int i = head[u]; i; i = nextx[i])
	{
		int v = vet[i];
		if (v != father)
		{
			flag = 1;
			solve(v, u);
			tmp = tmp + f[v];
		}
	}
	if (flag)
	{
		f[u] = std::min(f[u], tmp);
	}
}

int main()
{
	scanf("%d", &n);
	for (int i = 1; i < n; i++)
	{
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		add(u, v, w);
		add(v, u, w);
	}
	ccc[1] = INF;
	dfs(1, 0, 1);
	edgenum = 0;
	memset(head, 0, sizeof(head));
	scanf("%d", &m);
	for (int i = 1; i <= m; i++)
	{
		int cnt;
		scanf("%d", &cnt);
		for (int j = 1; j <= cnt; j++)
		{
			scanf("%d", &x[j]);
			cc[j] = x[j];
			flag[cc[j]] = 1;
		}
		cnt++;
		x[cnt] = 1;
		cc[cnt] = 1;
		int tmp = cnt;
		std::sort(x + 1, x + cnt + 1, comp);
		cnt = std::unique(x + 1, x + cnt + 1) - x - 1;
		for (int j = 1; j < tmp; j++)
		{
			cnt++;
			x[cnt] = querylca(x[j], x[j + 1]);
		}
		std::sort(x + 1, x + cnt + 1, comp);
		cnt = std::unique(x + 1, x + cnt + 1) - x - 1;
		top = 1;
		stack[top] = x[1];
		for (int j = 2; j <= cnt; j++)
		{
			while (top > 0 && deep[stack[top]] > deep[querylca(stack[top], x[j])])
			{
				top--;
			}
			if (stack[top])
			{
				add(stack[top], x[j], 0);
			}
			top++;
			stack[top] = x[j];
		}
		solve(1, 0);
		printf("%lld\n", f[1]);
		for (int j = 1; j <= tmp; j++)
		{
			flag[cc[j]] = 0;
		}
		edgenum = 0;
		for (int j = 1; j <= cnt; j++)
		{
			head[x[j]] = 0;
		}
	}
	return 0;
}
