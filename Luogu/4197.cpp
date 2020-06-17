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
	int u, v, w;
};

const int INF = 1000000000;
const int _n = 100000 + 10, _m = 500000 + 10;
int n, m, q;
int x[_n];
node z[_m];
int f[2 * _n];
int edgenum;
int vet[4 * _n], nextx[4 * _n], head[2 * _n];
int key[2 * _n];
int root[2 * _n];
int times;
int in[2 * _n], out[2 * _n];
int fa[2 * _n][22];

bool comp(node x, node y)
{
	return x.w < y.w;
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

namespace seg
{
	int knum;
	int sum[33 * _n], ch[33 * _n][2];

	void change(int &u, int v, int l, int r, int pos, int delta)
	{
		knum++;
		u = knum;
		sum[u] = sum[v];
		ch[u][0] = ch[v][0];
		ch[u][1] = ch[v][1];
		if (l == r)
		{
			sum[u] += delta;
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
		sum[u] = sum[ch[u][0]] + sum[ch[u][1]];
	}

	int query(int u, int v, int l, int r, int k)
	{
		if (k > sum[v] - sum[u])
		{
			return -1;
		}
		if (l == r)
		{
			return l;
		}
		int mid = (l + r) >> 1;
		if (k <= sum[ch[v][1]] - sum[ch[u][1]])
		{
			return query(ch[u][1], ch[v][1], mid + 1, r, k);
		}
		else
		{
			return query(ch[u][0], ch[v][0], l, mid, k - (sum[ch[v][1]] - sum[ch[u][1]]));
		}
	}
}

void dfs(int u, int father)
{
	fa[u][0] = father;
	for (int i = 1; i <= 20; i++)
	{
		fa[u][i] = fa[fa[u][i - 1]][i - 1];
	}
	times++;
	in[u] = times;
	if (u <= n)
	{
		seg::change(root[times], root[times - 1], 0, INF, x[u], 1);
	}
	else
	{
		root[times] = root[times - 1];
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
	n = read();
	m = read();
	q = read();
	for (int i = 1; i <= n; i++)
	{
		x[i] = read();
	}
	for (int i = 1; i <= m; i++)
	{
		z[i].u = read();
		z[i].v = read();
		z[i].w = read();
	}
	std::sort(z + 1, z + m + 1, comp);
	for (int i = 1; i <= n; i++)
	{
		f[i] = i;
	}
	int nn = n;
	for (int i = 1; i <= m; i++)
	{
		int xx = findfather(z[i].u);
		int yy = findfather(z[i].v);
		if (xx != yy)
		{
			nn++;
			f[xx] = f[yy] = f[nn] = nn;
			add(nn, xx);
			add(xx, nn);
			add(nn, yy);
			add(yy, nn);
			key[nn] = z[i].w;
		}
	}
	key[0] = INF + 10;
	dfs(nn, 0);
	while (q--)
	{
		int v = read();
		int x = read();
		int k = read();
		for (int i = 20; i >= 0; i--)
		{
			if (key[fa[v][i]] <= x)
			{
				v = fa[v][i];
			}
		}
		printf("%d\n", seg::query(root[in[v] - 1], root[out[v]], 0, INF, k));
	}
	return 0;
}
