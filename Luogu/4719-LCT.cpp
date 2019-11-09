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

struct matrix
{
	int x[2][2];

	int * operator [] (int pos)
	{
		return x[pos];
	}
};

const int INF = 1000000000;
const int _n = 100000 + 10;
int n, m;
int x[_n];
int edgenum;
int vet[2 * _n], nextx[2 * _n], head[_n];
int g[_n][2];
int fa[_n], ch[_n][2];
matrix sum[_n], mat[_n];
int top;
int stack[_n];

matrix operator * (matrix x, matrix y)
{
	matrix tmp;
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			tmp[i][j] = -INF;
		}
	}
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			for (int k = 0; k < 2; k++)
			{
				tmp[i][k] = std::max((long long)tmp[i][k], (long long)x[i][j] + y[j][k]);
			}
		}
	}
	return tmp;
}

void add(int u, int v)
{
	edgenum++;
	vet[edgenum] = v;
	nextx[edgenum] = head[u];
	head[u] = edgenum;
}

void dfs(int u, int father)
{
	fa[u] = father;
	g[u][0] = 0;
	g[u][1] = x[u];
	for (int i = head[u]; i; i = nextx[i])
	{
		int v = vet[i];
		if (v != father)
		{
			dfs(v, u);
			g[u][0] += std::max(g[v][0], g[v][1]);
			g[u][1] += g[v][0];
		}
	}
	mat[u][0][0] = g[u][0];
	mat[u][0][1] = g[u][0];
	mat[u][1][0] = g[u][1];
	mat[u][1][1] = -INF;
}

bool isroot(int x)
{
	return (ch[fa[x]][0] != x) && (ch[fa[x]][1] != x);
}

void pushup(int x)
{
	sum[x] = sum[ch[x][0]] * mat[x] * sum[ch[x][1]];
}

void rotate(int x)
{
	int y = fa[x];
	int z = fa[y];
	int w = ch[y][1] == x;
	if (! isroot(y))
	{
		ch[z][ch[z][1] == y] = x;
	}
	fa[x] = z;
	ch[y][w] = ch[x][w ^ 1];
	fa[ch[y][w]] = y;
	ch[x][w ^ 1] = y;
	fa[y] = x;
	pushup(y);
	pushup(x);
}

void splay(int x)
{
	while (! isroot(x))
	{
		int y = fa[x];
		int z = fa[y];
		if (! isroot(y))
		{
			if ((ch[z][1] == y) ^ (ch[y][1] == x))
			{
				rotate(x);
			}
			else
			{
				rotate(y);
			}
		}
		rotate(x);
	}
}

void access(int x)
{
	for (int i = x, t = 0; i; t = i, i = fa[i])
	{
		splay(i);
		if (ch[i][1])
		{
			g[i][0] += std::max(sum[ch[i][1]][0][0], sum[ch[i][1]][1][0]);
			g[i][1] += sum[ch[i][1]][0][0];
		}
		ch[i][1] = t;
		if (ch[i][1])
		{
			g[i][0] -= std::max(sum[ch[i][1]][0][0], sum[ch[i][1]][1][0]);
			g[i][1] -= sum[ch[i][1]][0][0];
		}
		mat[i][0][0] = g[i][0];
		mat[i][0][1] = g[i][0];
		mat[i][1][0] = g[i][1];
		mat[i][1][1] = -INF;
		pushup(i);
	}
}

void makeroot(int x)
{
	access(x);
	splay(x);
}

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
	{
		x[i] = read();
	}
	for (int i = 1; i < n; i++)
	{
		int u = read();
		int v = read();
		add(u, v);
		add(v, u);
	}
	mat[0][0][0] = 0;
	mat[0][0][1] = -INF;
	mat[0][1][0] = -INF;
	mat[0][1][1] = 0;
	sum[0][0][0] = 0;
	sum[0][0][1] = -INF;
	sum[0][1][0] = -INF;
	sum[0][1][1] = 0;
	dfs(1, 0);
	while (m--)
	{
		int u, newvalue;
		scanf("%d%d", &u, &newvalue);
		makeroot(u);
		g[u][1] -= x[u];
		x[u] = newvalue;
		g[u][1] += x[u];
		mat[u][0][0] = g[u][0];
		mat[u][0][1] = g[u][0];
		mat[u][1][0] = g[u][1];
		mat[u][1][1] = -INF;
		pushup(u);
		printf("%d\n", std::max(sum[u][0][0], sum[u][1][0]));
	}
	return 0;
}

