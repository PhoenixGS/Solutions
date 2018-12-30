#include <cstdio>
#include <cassert>

int n, m;
int fa[200000];
int edgenum;
int vet[400000], nextx[400000], head[200000];
int color[200000];

void add(int u, int v)
{
	edgenum++;
	vet[edgenum] = v;
	nextx[edgenum] = head[u];
	head[u] = edgenum;
}

struct LCT
{
	int sum[200000], ch[200000][2], fa[200000], ss[200000];

	void pushup(int x)
	{
		sum[x] = sum[ch[x][0]] + sum[ch[x][1]] + ss[x] + 1;
	}

	bool isroot(int x)
	{
		return ch[fa[x]][0] != x && ch[fa[x]][1] != x;
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
		for (int t = 0; x; t = x, x = fa[x])
		{
			splay(x);
			if (ch[x][1])
			{
				ss[x] += sum[ch[x][1]];
			}
			if (t)
			{
				ss[x] -= sum[t];
			}
			ch[x][1] = t;
//			printf("G%d %d\n", x, t);
			pushup(x);
		}
	}
	
	void cut(int x, int y)
	{
		access(x);
		splay(x);
		//printf("V%d %d\n", y, ch[x][0]);
		//fa[y] = 0;
		//ch[x][0] = 0;
		ch[x][0] = fa[ch[x][0]] = 0;
		pushup(x);
	}

	void link(int x, int y)
	{
		access(y);
		splay(y);
		access(x);
		splay(x);
		fa[x] = y;
		ss[y] += sum[x];
		pushup(y);
		/*fa[x] = y;
		ch[y][1] = x;
		pushup(y);*/
	}

	int findroot(int x)
	{
		access(x);
//		printf("P%d %d %d\n", 1, ch[1][0], ch[1][1]);
		splay(x);
//		printf("P%d %d %d\n", 1, ch[1][0], ch[1][1]);
		while (ch[x][0])
		{
			x = ch[x][0];
		}
		return x;
	}

	void query(int x)
	{
		int col = color[x];
		x = findroot(x);
		splay(x);
//		printf("V%d %d %d\n", x, sum[ch[x][0]], sum[ch[x][1]]);
		printf("%d\n", color[x] == col ? sum[x] : sum[ch[x][1]]);
	}
};

LCT lct[2];

void dfs(int u, int father)
{
	fa[u] = father;
	lct[0].fa[u] = father;
	for (int i = head[u]; i; i = nextx[i])
	{
		int v = vet[i];
		if (v != father)
		{
			dfs(v, u);
			lct[0].ss[u] += lct[0].sum[v];
		}
	}
	lct[0].pushup(u);
}

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
	{
		color[i] = 0;
	}
	for (int i = 1; i < n; i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		add(u, v);
		add(v, u);
	}
	dfs(1, 0);
	scanf("%d", &m);
	for (int i = 1; i <= m; i++)
	{
		int cas;
		scanf("%d", &cas);
		if (cas == 0)
		{
			int x;
			scanf("%d", &x);
			lct[color[x]].query(x);
		}
		else
		{
			int x;
			scanf("%d", &x);
			if (fa[x])
			{
				lct[color[x]].cut(x, fa[x]);
				lct[color[x] ^ 1].link(x, fa[x]);
			}
			color[x] ^= 1;
		}
	}
	return 0;
}
