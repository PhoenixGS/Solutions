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

const int INF = 1000000000;
const int _n = 80000 + 10;
int cases;
int n, m, T;
char st[10];
int x[_n];
int f[_n], s[_n];
int edgenum;
int vet[2 * _n], nextx[2 * _n], head[_n];
int deep[_n], fa[_n][22];
int knum;
int root[_n];
int sum[20 * 20 * _n], ch[20 * 20 * _n][2];
int lastans;

int findfather(int x)
{
	return f[x] == x ? x : f[x] = findfather(f[x]);
}

void add(int u, int v)
{
	edgenum++;
	vet[edgenum] = v;
	nextx[edgenum] = head[u];
	head[u] = edgenum;
}

void pushup(int k)
{
	sum[k] = sum[ch[k][0]] + sum[ch[k][1]];
}

void change(int &v, int u, int l, int r, int pos, int delta)
{
	knum++;
	v = knum;
	sum[v] = sum[u];
	ch[v][0] = ch[u][0];
	ch[v][1] = ch[u][1];
	if (l == r)
	{
		sum[v] += delta;
		return;
	}
	int mid = (l + r) >> 1;
	if (pos <= mid)
	{
		change(ch[v][0], ch[u][0], l, mid, pos, delta);
	}
	else
	{
		change(ch[v][1], ch[u][1], mid + 1, r, pos, delta);
	}
	pushup(v);
}

int find(int w, int x, int y, int z, int l, int r, int k)
{
	if (l == r)
	{
		return l;
	}
	int mid = (l + r) >> 1;
	if (sum[ch[w][0]] + sum[ch[x][0]] - sum[ch[y][0]] - sum[ch[z][0]] >= k)
	{
		return find(ch[w][0], ch[x][0], ch[y][0], ch[z][0], l, mid, k);
	}
	else
	{
		return find(ch[w][1], ch[x][1], ch[y][1], ch[z][1], mid + 1, r, k - (sum[ch[w][0]] + sum[ch[x][0]] - sum[ch[y][0]] - sum[ch[z][0]]));
	}
}

void dfs(int u, int father, int dep)
{
	deep[u] = dep;
	fa[u][0] = father;
	for (int i = 1; i <= 20; i++)
	{
		fa[u][i] = fa[fa[u][i - 1]][i - 1];
	}
	change(root[u], root[father], 0, INF, x[u], 1);
	for (int i = head[u]; i; i = nextx[i])
	{
		int v = vet[i];
		if (v != father)
		{
			dfs(v, u, dep + 1);
		}
	}
}

int query_lca(int x, int y)
{
	if (deep[x] < deep[y])
	{
		std::swap(x, y);
	}
	for (int i = 0; i <= 20; i++)
	{
		if ((1 << i) & (deep[x] - deep[y]))
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

int main()
{
	scanf("%d", &cases);
	scanf("%d%d%d", &n, &m, &T);
	edgenum = 1;
	for (int i = 1; i <= n; i++)
	{
		head[i] = 0;
		f[i] = i;
		s[i] = 1;
	}
	for (int i = 1; i <= n; i++)
	{
		x[i] = read();
	}
	for (int i = 1; i <= m; i++)
	{
		int u, v;
		u = read();
		v = read();
		add(u, v);
		add(v, u);
		int uu = findfather(u);
		int vv = findfather(v);
		f[uu] = vv;
		s[vv] += s[uu];
	}
	for (int i = 1; i <= n; i++)
	{
		if (findfather(i) == i)
		{
			dfs(i, 0, 0);
		}
	}
	while (T--)
	{
		scanf("%s", st + 1);
		if (st[1] == 'Q')
		{
			int u = read();
			int v = read();
			int k = read();
			u ^= lastans;
			v ^= lastans;
			k ^= lastans;
			int lca = query_lca(u, v);
			lastans = find(root[u], root[v], root[lca], root[fa[lca][0]], 0, INF, k);
			printf("%d\n", lastans);
		}
		else
		{
			int u = read();
			int v = read();
			u ^= lastans;
			v ^= lastans;
			add(u, v);
			add(v, u);
			int uu = findfather(u);
			int vv = findfather(v);
			if (s[uu] < s[vv])
			{
				dfs(u, v, deep[v] + 1);
				f[uu] = vv;
				s[vv] += s[uu];
			}
			else
			{
				dfs(v, u, deep[u] + 1);
				f[vv] = uu;
				s[uu] += s[vv];
			}
		}
	}
	return 0;
}
