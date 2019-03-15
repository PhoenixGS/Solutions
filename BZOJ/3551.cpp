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

struct node
{
	int u, v, cost;
};

const int INF = 1000000000 + 10;
const int _n = 100000 + 10, _m = 500000 + 10;
int n, m, q;
node e[_m];
int f[2 * _n];
int edgenum;
int vet[4 * _n], nextx[4 * _n], head[2 * _n];
int kk;
int val[2 * _n];
int times;
int in[2 * _n], out[2 * _n];
int root[2 * _n];
int fa[2 * _n][20];
int knum;
int sum[32 * _n], ch[32 * _n][2];
int lastans;

inline bool comp(node x, node y)
{
	return x.cost < y.cost;
}

void add(int u, int v)
{
	edgenum++;
	vet[edgenum] = v;
	nextx[edgenum] = head[u];
	head[u] = edgenum;
}

int findfather(int x)
{
	return f[x] == x ? x : f[x] = findfather(f[x]);
}

void pushup(int k)
{
	sum[k] = sum[ch[k][0]] + sum[ch[k][1]];
}

void change(int u, int &v, int l, int r, int pos, int delta)
{
	knum++;
	v = knum;
	ch[v][0] = ch[u][0];
	ch[v][1] = ch[u][1];
	sum[v] = sum[u];
	if (l == r)
	{
		sum[v] += delta;
		return;
	}
	int mid = (l + r) >> 1;
	if (pos <= mid)
	{
		change(ch[u][0], ch[v][0], l, mid, pos, delta);
	}
	else
	{
		change(ch[u][1], ch[v][1], mid + 1, r, pos, delta);
	}
	pushup(v);
}

int query(int u, int v, int l, int r, int rank)
{
	if (l == r)
	{
		return l;
	}
	int mid = (l + r) >> 1;
	if (sum[ch[u][1]] - sum[ch[v][1]] >= rank)
	{
		return query(ch[u][1], ch[v][1], mid + 1, r, rank);
	}
	else
	{
		return query(ch[u][0], ch[v][0], l, mid, rank - sum[ch[u][1]] + sum[ch[v][1]]);
	}
}

void dfs(int u, int father)
{
	times++;
	in[u] = times;
	if (u <= n)
	{
		change(root[times - 1], root[times], -1, INF, val[u], 1);
	}
	else
	{
		root[times] = root[times - 1];
	}
	fa[u][0] = father;
	for (int i = 1; i <= 19; i++)
	{
		fa[u][i] = fa[fa[u][i - 1]][i - 1];
	}
	for (int i = head[u]; i; i = nextx[i])
	{
		int v = vet[i];
		if (v != father)
		{
			dfs(v, u);
		}
	}
	out[u] = times;
}

int main()
{
	scanf("%d%d%d", &n, &m, &q);
	for (int i = 1; i <= n; i++)
	{
		val[i] = read();
	}
	for (int i = 1; i <= m; i++)
	{
		e[i].u = read();
		e[i].v = read();
		e[i].cost = read();
	}
	std::sort(e + 1, e + m + 1, comp);
	for (int i = 1; i <= 2 * n; i++)
	{
		f[i] = i;
	}
	kk = n;
	for (int i = 1; i <= m; i++)
	{
		int xx = findfather(e[i].u);
		int yy = findfather(e[i].v);
		if (xx != yy)
		{
			kk++;
			val[kk] = e[i].cost;
			add(xx, kk);
			add(kk, xx);
			add(yy, kk);
			add(kk, yy);
			f[xx] = kk;
			f[yy] = kk;
		}
	}
	val[0] = INF;
	for (int i = 1; i <= 2 * n - 1; i++)
	{
		if (findfather(i) == i)
		{
			dfs(i, 0);
		}
	}
	lastans = 0;
	while (q--)
	{
	#ifdef debug
		int v = read();
		int x = read();
		int k = read();
	#else
		int v = read() ^ lastans;
		int x = read() ^ lastans;
		int k = read() ^ lastans;
	#endif
		int u = v;
		for (int i = 19; i >= 0; i--)
		{
			if (val[fa[u][i]] <= x)
			{
				u = fa[u][i];
			}
		}
		lastans = query(root[out[u]], root[in[u] - 1], -1, INF, k);
		if (lastans == -1)
		{
			puts("-1");
			lastans = 0;
		}
		else
		{
			printf("%d\n", lastans);
		}
	}
	return 0;
}
