#include <cstdio>

struct LCT
{
	bool isroot(int x)
	{
		return ch[fa[x]][0] != x && ch[fa[x]][1] != x;
	}

	void pushup(int x)
	{
		sum[x] = sum[ch[x][0]] + sum[ch[x][1]] + 1;
		lmx[x] = INF;
		lmx[x] = std::min(lmx[x], lmx[ch[x][0]] + 1 + size[ch[x][1]]);
		lmx[x] = std::min(lmx[x], (col[x] == 0 ? 1 : INF) + size[ch[x][1]]);
		lmx[x] = std::min(lmx[x], heap[x].top() + 1 + size[ch[x][1]]);
		lmx[x] = std::min(lmx[x], lmx[ch[x][1]]);
		rmx[x] = INF;
		rmx[x] = std::min(rmx[x], rmx[ch[x][1]] + 1 + size[ch[x][0]]);
		rmx[x] = std::min(rmx[x], (col[x] == 0 ? 1 : INF) + size[ch[x][0]]);
		rmx[x] = std::min(rmx[x], heap[x].top() + 1 + size[ch[x][0]]);
		rmx[x] = std::min(rmx[x], rmx)
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
				heap[i].del()
			}
		}
	}
}

void dfs(int u, int father)
{
	lct.fa[u] = father;
	for (int i = head[u]; i; i = nextx[i])
	{
		int v = vet[i];
		if (v != father)
		{
			dfs(v, u);
		}
	}
	if (father)
	{
		heap[father].push(std::min(heap[u].top() + 1, col[u] == 0 ? 1 : INF));
	}
}

int main()
{
	scanf("%d", &n);
	for (int i = 1; i < n; i++)
	{
		int u = read();
		int v = read();
		add(u, v);
		add(v, u);
	}
	for (int i = 1; i <= n; i++)
	{
		col[i] = 1;
	}
	mx[0] = INF;
	sum[0] = 0;
	dfs(1, 0);
	while (q--)
	{
		int op = read();
		if (op == 0)
		{
			int u = read();
			lct.access(u);
			lct.splay(u);
			col[u] ^= 1;
			lct.pushup(u);
		}
		else
		{
			int u = read();
			lct.access(u);
			lct.splay(u);
			printf("%d\n", lct.query(u));
		}
	}
	return 0;
}
