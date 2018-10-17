#include <cstdio>
#include <algorithm>
#include <cstring>

const long long INF = 1e18;
int edgenum;
int vet[600000], val[600000], nextx[600000], head[300000];
int fa[300000][22];
long long f[300000];
int cnt;
int x[1200000];
int deep[300000];
int flag[300000];
int cc[1200000];
int n, m;
long long vvv[300000];
int top;
int stack[300000];
int dfn[300000];
int times;

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
			vvv[v] = std::min(vvv[u], (long long)cost);
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

void D(int u, int father)
{
	if (flag[u])
	{
		f[u] = vvv[u];
		return;
	}
	f[u] = vvv[u];
	long long tmp = 0;
	bool ff = 1;
	for (int i = head[u]; i; i = nextx[i])
	{
		int v = vet[i];
		if (v != father)
		{
			D(v, u);
			tmp += f[v];
			ff = 0;
		}
	}
	if (! ff)
	{
		f[u] = std::min(f[u], tmp);
	}
}

int main()
{
	scanf("%d", &n);
	for (int i = 1; i < n; i++)
	{
		int u, v, cost;
		scanf("%d%d%d", &u, &v, &cost);
		add(u, v, cost);
		add(v, u, cost);
	}
	vvv[1] = INF;
	dfs(1, 0, 1);
	edgenum = 0;
	memset(head, 0, sizeof(head));
	scanf("%d", &m);
	while (m--)
	{
		int cnt;
		scanf("%d", &cnt);
		for (int i = 1; i <= cnt; i++)
		{
			scanf("%d", &x[i]);
			cc[i] = x[i];
			flag[cc[i]] = 1;
		}
		cnt++;
		x[cnt] = 1;
		cc[cnt] = 1;
		std::sort(x + 1, x + cnt + 1, comp);
		cnt = std::unique(x + 1, x + cnt + 1) - x - 1;
		int tmp = cnt;
		for (int i = 1; i < tmp; i++)
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
		D(1, 0);
		printf("%lld\n", f[1]);
		for (int i = 1; i <= tmp - 1; i++)
		{
			flag[cc[i]] = 0;
		}
		edgenum = 0;
		for (int i = 1; i <= cnt; i++)
		{
			head[x[i]] = 0;
		}
	}
	return 0;
}
