#include <cstdio>
#include <cstring>
#include <algorithm>

const int INF = 1e9;
int n, m;
int x[800000], cc[800000];
int edgenum;
int vet[800000], nextx[800000], head[800000];

int times;
int dfn[800000], deep[800000], size[800000];
int fa[400000][22];
int top;
int stack[800000];
int flag[800000];
int down1[800000], pos1[800000], down2[800000], pos2[800000], up[800000], pos3[800000], f[800000], pos[800000];
int ans[800000];

bool comp(int x, int y)
{
	return dfn[x] < dfn[y];
}

void add(int u, int v)
{
	edgenum++;
	vet[edgenum] = v;
	nextx[edgenum] = head[u];
	head[u] = edgenum;
}

void dfs(int u, int father, int dep)
{
	times++;
	dfn[u] = times;
	deep[u] = dep;
	fa[u][0] = father;
	size[u] = 1;
	for (int i = 1; i <= 20; i++)
	{
		fa[u][i] = fa[fa[u][i - 1]][i - 1];
	}
	for (int i = head[u]; i; i = nextx[i])
	{
		int v = vet[i];
		if (v != father)
		{
			dfs(v, u, dep + 1);
			size[u] += size[v];
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

int queryanc(int x, int up)
{
	for (int i = 20; i >= 0; i--)
	{
		if (up & (1 << i))
		{
			x = fa[x][i];
		}
	}
	return x;
}

void dpdown(int u, int father)
{
	down1[u] = flag[u] ? 0 : INF;
	pos1[u] = flag[u] ? u : INF;
	down2[u] = INF;
	pos2[u] = INF;
	for (int i = head[u]; i; i = nextx[i])
	{
		int v = vet[i];
		if (v != father)
		{
			int cost = deep[v] - deep[u];
			dpdown(v, u);
			if (down1[v] + cost < down1[u] || down1[v] + cost == down1[u] && pos1[v] < pos1[u])
			{
				down2[u] = down1[u];
				pos2[u] = pos1[u];
				down1[u] = down1[v] + cost;
				pos1[u] = pos1[v];
			}
			else
			{
				if (down1[v] + cost < down2[u] || down1[v] + cost == down2[u] && pos1[v] < pos2[u])
				{
					down2[u] = down1[v] + cost;
					pos2[u] = pos1[v];
				}
			}
		}
	}
}

void dpup(int u, int father)
{
	up[u] = flag[u] ? 0 : up[u];
	pos3[u] = flag[u] ? u : pos3[u];
	for (int i = head[u]; i; i = nextx[i])
	{
		int v = vet[i];
		if (v != father)
		{
			int cost = deep[v] - deep[u];
			int down, pos;
			if (pos1[v] != pos1[u])
			{
				down = down1[u];
				pos = pos1[u];
			}
			else
			{
				down = down2[u];
				pos = pos2[u];
			}
			if (up[u] < down)
			{
				up[v] = up[u] + cost;
				pos3[v] = pos3[u];
			}
			if (up[u] == down)
			{
				up[v] = up[u] + cost;
				pos3[v] = std::min(pos3[u], pos);
			}
			if (up[u] > down)
			{
				up[v] = down + cost;
				pos3[v] = pos;
			}
			dpup(v, u);
		}
	}
	if (up[u] < down1[u])
	{
		f[u] = up[u];
		pos[u] = pos3[u];
	}
	if (up[u] == down1[u])
	{
		f[u] = up[u];
		pos[u] = std::min(pos1[u], pos3[u]);
	}
	if (up[u] > down1[u])
	{
		f[u] = down1[u];
		pos[u] = pos1[u];
	}
}

int abss(int x)
{
	return x > 0 ? x : -x;
}

int calc(int x, int y)
{
	int cnt = deep[y] - deep[x] - 1;
	if (! cnt)
	{
		return cnt;
	}
	if (pos[x] == pos[y])
	{
		ans[pos[x]] += cnt;
		return cnt;
	}
	int tmp;
	if ((abss(f[x] - f[y]) + cnt) & 1)
	{
		if (pos[x] < pos[y])
		{
			tmp = (f[x] - f[y] + cnt - 1) / 2;
		}
		else
		{
			tmp = (f[x] - f[y] + cnt + 1) / 2;
		}
	}
	else
	{
		tmp = (f[x] - f[y] + cnt) / 2;
	}
	int w1 = queryanc(y, tmp);
	int w2 = queryanc(y, cnt);
	int sum = size[w2] - size[y];
	ans[pos[x]] += size[w2] - size[w1];
	ans[pos[y]] += size[w1] - size[y];
	return sum;
}

int calcans(int u, int father)
{
	int tmp = size[u];
	for (int i = head[u]; i; i = nextx[i])
	{
		int v = vet[i];
		if (v != father)
		{
			tmp -= calc(u, v);
			tmp -= calcans(v, u);
		}
	}
	ans[pos[u]] += tmp;
	return size[u];
}

int main()
{
	scanf("%d", &n);
	for (int i = 1; i < n; i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		add(u, v);
		add(v, u);
	}
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
			ans[cc[i]] = 0;
		}
		cnt++;
		x[cnt] = 1;
		cc[cnt] = 1;
		int tmp = cnt;
		std::sort(x + 1, x + cnt + 1, comp);
		cnt = std::unique(x + 1, x + cnt + 1) - x - 1;
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
			while (top > 0 && stack[top] != querylca(stack[top], x[i]))
			{
				top--;
			}
			if (stack[top])
			{
				add(stack[top], x[i]);
			}
			top++;
			stack[top] = x[i];
		}
		dpdown(1, 0);
		up[1] = INF;
		pos3[1] = INF;
		dpup(1, 0);
		calcans(1, 0);
		for (int i = 1; i <= tmp - 1; i++)
		{
			printf("%d ", ans[cc[i]]);
			flag[cc[i]] = 0;
		}
		printf("\n");
		edgenum = 0;
		for (int i = 1; i <= cnt; i++)
		{
			head[x[i]] = 0;
		}
	}
	return 0;
}
