#include <cstdio>
#include <algorithm>

int deep[600000];
int f[600000][20];
int in[600000], out[600000];
int bit[2000000];
int n, m;
int times;
int x[2000000];
int edgenum;
int vet[2000000];
int nextx[2000000];
int head[1000000];
char st[20];

void add(int u, int v)
{
	edgenum++;
	vet[edgenum] = v;
	nextx[edgenum] = head[u];
	head[u] = edgenum;
}

void dfs(int u, int father, int dep)
{
	deep[u] = dep;
	f[u][0] = father;
	for (int i = 1; i <= 18; i++)
	{
		f[u][i] = f[f[u][i - 1]][i - 1];
	}
	times++;
	in[u] = times;
	for (int i = head[u]; i; i = nextx[i])
	{
		int v = vet[i];
		if (v != father)
		{
			dfs(v, u, dep + 1);
		}
	}
	out[u] = times;
}

int querylca(int x, int y)
{
	if (deep[x] < deep[y])
	{
		std::swap(x, y);
	}
	for (int i = 18; i >= 0; i--)
	{
		if (deep[f[x][i]] >= deep[y])
		{
			x = f[x][i];
		}
	}
	if (x == y)
	{
		return x;
	}
	for (int i = 18; i >= 0; i--)
	{
		if (f[x][i] != f[y][i])
		{
			x = f[x][i];
			y = f[y][i];
		}
	}
	return f[x][0];
}

int lowbit(int x)
{
	return x & -x;
}

void change(int pos, int delta)
{
	for (int i = pos; i <= n; i += lowbit(i))
	{
		bit[i] ^= delta;
	}
}

int query(int pos)
{
	int ans = 0;
	for (int i = pos; i; i -= lowbit(i))
	{
		ans ^= bit[i];
	}
	return ans;
}

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &x[i]);
	}
	for (int i = 1; i < n; i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		add(u, v);
		add(v, u);
	}
	dfs(1, 0, 1);
	for (int i = 1; i <= n; i++)
	{
		change(in[i], x[i]);
		change(out[i] + 1, x[i]);
	}
	scanf("%d", &m);
	for (int i = 1; i <= m; i++)
	{
		scanf("%s", st + 1);
		if (st[1] == 'Q')
		{
			int u, v;
			scanf("%d%d", &u, &v);
			int lca = querylca(u, v);
			puts((query(in[u]) ^ query(in[v]) ^ x[lca]) == 0 ? "No" : "Yes");
		}
		else
		{
			int pos, newvalue;
			scanf("%d%d", &pos, &newvalue);
			change(in[pos], x[pos]);
			change(out[pos] + 1, x[pos]);
			x[pos] = newvalue;
			change(in[pos], x[pos]);
			change(out[pos] + 1, x[pos]);
		}
	}
	return 0;
}
