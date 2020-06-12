#include <cstdio>
#include <algorithm>
#include <queue>

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
const int _n = 100000 + 10;
int n, q;
int edgenum;
int vet[2 * _n], nextx[2 * _n], head[_n];
int col[_n];

struct HEAP
{
	std::priority_queue<int, std::vector<int>, std::greater<int> > A, B;
	
	bool empty()
	{
		while (! A.empty() && ! B.empty() && A.top() == B.top())
		{
			A.pop();
			B.pop();
		}
		return A.empty();
	}

	int top()
	{
		while (! A.empty() && ! B.empty() && A.top() == B.top())
		{
			A.pop();
			B.pop();
		}
		if (A.empty())
		{
			return INF;
		}
		return A.top();
	}

	void push(int x)
	{
		A.push(x);
	}

	void del(int x)
	{
		B.push(x);
	}
};

HEAP heap[_n];

struct LCT
{
	int ch[_n][2], fa[_n];
	int sum[_n], lmx[_n], rmx[_n];

	bool isroot(int x)
	{
		return ch[fa[x]][0] != x && ch[fa[x]][1] != x;
	}

	void pushup(int x)
	{
		sum[x] = sum[ch[x][0]] + sum[ch[x][1]] + 1;
		lmx[x] = INF;
		lmx[x] = std::min(lmx[x], lmx[ch[x][0]] + 1 + sum[ch[x][1]]);
		lmx[x] = std::min(lmx[x], (col[x] == 0 ? 1 : INF) + sum[ch[x][1]]);
		lmx[x] = std::min(lmx[x], heap[x].top() + 1 + sum[ch[x][1]]);
		lmx[x] = std::min(lmx[x], lmx[ch[x][1]]);
		rmx[x] = INF;
		rmx[x] = std::min(rmx[x], rmx[ch[x][1]] + 1 + sum[ch[x][0]]);
		rmx[x] = std::min(rmx[x], (col[x] == 0 ? 1 : INF) + sum[ch[x][0]]);
		rmx[x] = std::min(rmx[x], heap[x].top() + 1 + sum[ch[x][0]]);
		rmx[x] = std::min(rmx[x], rmx[ch[x][0]]);
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
				heap[i].push(rmx[ch[i][1]]);
			}
			ch[i][1] = t;
			if (ch[i][1])
			{
				heap[i].del(rmx[ch[i][1]]);
			}
			pushup(i);
		}
	}

	int query(int x)
	{
		access(x);
		splay(x);
		return lmx[x];
	}
};

LCT lct;

void add(int u, int v)
{
	edgenum++;
	vet[edgenum] = v;
	nextx[edgenum] = head[u];
	head[u] = edgenum;
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
	lct.lmx[0] = lct.rmx[0] = INF;
	lct.sum[0] = 0;
	dfs(1, 0);
	scanf("%d", &q);
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
			int ans = lct.query(u);
			printf("%d\n", ans == INF ? -1 : ans - 1);
/*			printf("%d %d %d\n", lct.fa[1], lct.fa[2], lct.fa[4]);
			printf("X%d %d\n", lct.lmx[1], lct.rmx[1]);
			printf("Y%d %d\n", lct.lmx[2], lct.rmx[2]);
			printf("Z%d %d\n", lct.lmx[4], lct.rmx[4]);
			printf("%d %d\n", lct.ch[4][0], lct.ch[4][1]);*/
		}
	}
	return 0;
}
